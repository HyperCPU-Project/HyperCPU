#pragma once

// TODO: fix this in hpool
#include <cstring>
#include <hpool.hpp>

#include "Common/Helpers/Classes.hpp"
#include "Common/LanguageSpec/Opcodes.hpp"
#include "Common/LanguageSpec/Registers.hpp"
#include "PCH/CStd.hpp"
#include "Pog/Pog.hpp"

namespace HCAsm {
  enum class ValueType {
    operand,
    string,
    sint,
    uint,
  };

  enum class OperandType {
    reg,
    mem_reg_add_int,
    sint,
    uint,
    memaddr_reg,
    memaddr_int,
    memaddr_lbl,
    label,
    str_lit,
    none
  };

  enum class Mode : std::uint8_t {
    b8 = 0b00,
    b16 = 0b01,
    b32 = 0b10,
    b64 = 0b11,
    b64_label,
    b8_str,
    none
  };

  struct Value;

  struct Operand {
    OperandType type;
    HyperCPU::Reg reg;
    enum Mode mode;
    bool needs_resolve;
    std::array<HPool::Ptr<pog::TokenWithLineSpec<Value>>, 2> tokens;
    std::variant<std::uint64_t, std::int64_t, std::shared_ptr<std::string>> variant;
  };

  struct Instruction {
    HyperCPU::Opcode opcode;
    Operand op1, op2;
  };

  struct RawValue {
    enum Mode mode;
    Operand value; // Label resolver requires reference to operand
  };

  struct Value {
    std::variant<std::int64_t, std::uint64_t, std::string, Operand, Instruction> val;
  };

  struct Label {
    std::string name;
    std::uint64_t index;
    bool is_entry_point;
  };

  template <typename T>
  concept Integral = std::is_integral_v<T>;

  struct BinaryResult {
    BinaryResult()
        : binary(nullptr), ptr(0), entry_point(0) {
    }
    BinaryResult(unsigned char* ptr)
        : binary(ptr), ptr(0), entry_point(0) {
    }

    unsigned char* binary;
    std::uint64_t ptr;
    std::uint32_t entry_point;

    template <Integral T>
    constexpr inline void push(T data) {
      std::memcpy(binary + ptr, &data, sizeof(data));
      ptr += sizeof(data);
    }

    inline void push(const std::string& data) {
      std::memcpy(binary + ptr, data.data(), data.length());
      ptr += data.length();
    }

    ~BinaryResult() {
      delete[] binary;
    }
  };

  struct PendingLabelReferenceResolve {
    std::uint32_t idx;
    std::uint8_t op;
  };

  // Some magic for std::visit
  template <typename... T>
  struct MakeOverload : T... {
    using T::operator()...;
  };

  template <typename... T>
  MakeOverload(T...) -> MakeOverload<T...>;

  template <typename Variant, typename... Alternatives>
  constexpr inline decltype(auto) VisitVariant(Variant&& variant, Alternatives&&... alternatives) {
    return std::visit(
        MakeOverload{std::forward<Alternatives>(alternatives)..., [](auto const&) {}},
        variant);
  }

  // Needs improvements and optimizations
  struct CompilerState {
    CompilerState(HPool::HPool<pog::TokenWithLineSpec<Value>>& pool)
        : pool(pool), code_size(0), entry_point(0) {
    }

    std::vector<PendingLabelReferenceResolve> pending_resolves;
    std::vector<pog::TokenWithLineSpec<Value>> tmp_args;
    std::vector<std::variant<Instruction, Label, RawValue>> ir;
    std::unordered_map<std::string, std::uint64_t> labels;
    HPool::HPool<pog::TokenWithLineSpec<Value>>& pool;
    std::uint64_t code_size;
    std::uint32_t entry_point;
  };

  constexpr inline Mode ModeFromRegister(HyperCPU::Reg reg) {
    using namespace HyperCPU;
    switch (reg) {
    case Reg::X0:
    case Reg::X1:
    case Reg::X2:
    case Reg::X3:
    case Reg::X4:
    case Reg::X5:
    case Reg::X6:
    case Reg::X7:
    case Reg::XBP:
    case Reg::XSP:
    case Reg::XIP:
      return Mode::b64;
    case Reg::XH0:
    case Reg::XH1:
    case Reg::XH2:
    case Reg::XH3:
    case Reg::XH4:
    case Reg::XH5:
    case Reg::XH6:
    case Reg::XH7:
    case Reg::XL0:
    case Reg::XL1:
    case Reg::XL2:
    case Reg::XL3:
    case Reg::XL4:
    case Reg::XL5:
    case Reg::XL6:
    case Reg::XL7:
      return Mode::b32;
    case Reg::XLL0:
    case Reg::XLL1:
    case Reg::XLL2:
    case Reg::XLL3:
      return Mode::b16;
    case Reg::XLLH0:
    case Reg::XLLH1:
    case Reg::XLLH2:
    case Reg::XLLH3:
    case Reg::XLLL0:
    case Reg::XLLL1:
    case Reg::XLLL2:
    case Reg::XLLL3:
      return Mode::b8;
    default:
      std::abort();
    }
    // TODO: handle missing return
  }

  std::string_view FindLine(const pog::LineSpecialization&, const std::string_view&);
  void WriteResultFile(HyperCPU::FileType type, HCAsm::BinaryResult& result, std::ofstream& output, std::uint32_t code_size, std::uint32_t entry_point);

  [[noreturn]] void ThrowError(pog::TokenWithLineSpec<Value>& err_token, pog::Parser<Value>& parser, std::string err_msg);

  Value TokenizeSignedInt(std::string_view str);
  Value TokenizeUnsignedInt(std::string_view str);
  Value TokenizeString(std::string_view str);
  Value TokenizeHexadecimal(std::string_view str);
  Value TokenizeIdentifier(std::string_view str);
  Value TokenizeBinary(std::string_view str);
  Value TokenizeChar(std::string_view str);

  Value ParseOperand1(pog::Parser<Value>&, std::vector<pog::TokenWithLineSpec<Value>>&& args);
  Value ParseOperand2(pog::Parser<Value>&, std::vector<pog::TokenWithLineSpec<Value>>&& args);
  Value ParseOperand3(pog::Parser<Value>&, std::vector<pog::TokenWithLineSpec<Value>>&& args);
  Value ParseOperand4(pog::Parser<Value>&, std::vector<pog::TokenWithLineSpec<Value>>&& args);
  Value ParseOperand5(pog::Parser<Value>&, std::vector<pog::TokenWithLineSpec<Value>>&& args);
  Value ParseOperand6(pog::Parser<Value>&, std::vector<pog::TokenWithLineSpec<Value>>&& args);
  Value ParseOperand7(pog::Parser<Value>&, std::vector<pog::TokenWithLineSpec<Value>>&& args);
  Value ParseOperand8(pog::Parser<Value>&, std::vector<pog::TokenWithLineSpec<Value>>&& args);
  Value ParseOperand9(pog::Parser<Value>&, std::vector<pog::TokenWithLineSpec<Value>>&& args);
  Value ParseOperand10(pog::Parser<Value>&, std::vector<pog::TokenWithLineSpec<Value>>&& args);
  Value ParseOperand11(pog::Parser<Value>&, std::vector<pog::TokenWithLineSpec<Value>>&& args);
  Value ParseOperand12(pog::Parser<Value>&, std::vector<pog::TokenWithLineSpec<Value>>&& args);

  Value CompileStatement1(pog::Parser<Value>&, std::vector<pog::TokenWithLineSpec<Value>>&& args);
  Value CompileStatement2(pog::Parser<Value>&, std::vector<pog::TokenWithLineSpec<Value>>&& args);
  Value CompileStatement3(pog::Parser<Value>&, std::vector<pog::TokenWithLineSpec<Value>>&& args);
  Value CompileEntryLabel(pog::Parser<Value>&, std::vector<pog::TokenWithLineSpec<Value>>&& args);
  Value CompileLabel(pog::Parser<Value>&, std::vector<pog::TokenWithLineSpec<Value>>&& args);
  Value CompileRawValueb8_str(pog::Parser<Value>&, std::vector<pog::TokenWithLineSpec<Value>>&& args);
  Value CompileRawValueb8(pog::Parser<Value>&, std::vector<pog::TokenWithLineSpec<Value>>&& args);
  Value CompileRawValueb16(pog::Parser<Value>&, std::vector<pog::TokenWithLineSpec<Value>>&& args);
  Value CompileRawValueb32(pog::Parser<Value>&, std::vector<pog::TokenWithLineSpec<Value>>&& args);
  Value CompileRawValueb64(pog::Parser<Value>&, std::vector<pog::TokenWithLineSpec<Value>>&& args);

  extern CompilerState* current_state;
  extern std::uint64_t current_index;

  class HCAsmCompiler {
  public:
    HCAsmCompiler();

    BinaryResult Compile(std::string& contents, std::uint32_t& code_size);
    CompilerState TransformToIR(std::string& src);
    BinaryResult TransformToBinary(CompilerState& ir);

  private:
    pog::Parser<Value> parser;
    CompilerState* state;
    std::queue<std::string> files;
    HPool::HPool<pog::TokenWithLineSpec<Value>> pool;

    constexpr inline std::uint8_t OperandSize(const OperandType op);
    std::uint8_t InstructionSize(Instruction& instr);
    std::uint8_t ModeToSize(const Operand& op);
    std::uint8_t ModeToSize(Mode md);
  };

} // namespace HCAsm
