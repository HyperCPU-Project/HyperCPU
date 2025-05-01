#pragma once

#include <Pog/Pog.hpp>
#include <pch.hpp>

#include <Emulator/Core/CPU/Instructions/Registers.hpp>
#include <Emulator/Core/CPU/Instructions/Opcodes.hpp>
#include <Emulator/Main/Main.hpp>
#include <Logger/Logger.hpp>
#include <Exit.hpp>

#include <hpool.hpp>


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
    b8  = 0b00,
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
    HyperCPU::Registers reg;
    enum Mode mode;
    bool needs_resolve;
    std::array<hpool::Ptr<pog::TokenWithLineSpec<Value>, hpool::ReallocationPolicy::OffsetRealloc>, 2> tokens;
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

  template<typename T>
  concept Integral = std::is_integral_v<T>;

  struct BinaryResult {
    BinaryResult() : binary(nullptr), ptr(0), entry_point(0) { }
    BinaryResult(unsigned char* ptr) : binary(ptr), ptr(0), entry_point(0) { }

    unsigned char* binary;
    std::uint64_t ptr;
    std::uint32_t entry_point;

    template<Integral T>
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
  template<typename... T>
  struct MakeOverload : T... {
    using T::operator()...;
  };

  template<typename... T>
  MakeOverload(T...) -> MakeOverload<T...>;

  template<typename Variant, typename... Alternatives>
  constexpr inline decltype(auto) VisitVariant(Variant&& variant, Alternatives&&... alternatives) {
    return std::visit(
      MakeOverload{std::forward<Alternatives>(alternatives)..., [](auto const&){}},
      variant
    );
  }

  // Needs improvements and optimizations
  struct CompilerState {
    CompilerState(hpool::HPool<pog::TokenWithLineSpec<Value>, hpool::ReallocationPolicy::OffsetRealloc>& pool) : pool(pool), code_size(0), entry_point(0) { }

    std::vector<PendingLabelReferenceResolve> pending_resolves;
    std::vector<pog::TokenWithLineSpec<Value>> tmp_args;
    std::vector<std::variant<Instruction, Label, RawValue>> ir;
    std::unordered_map<std::string, std::uint64_t> labels;
    hpool::HPool<pog::TokenWithLineSpec<Value>, hpool::ReallocationPolicy::OffsetRealloc>& pool;
    std::uint64_t code_size;
    std::uint32_t entry_point;
  };

  constexpr inline Mode ModeFromRegister(HyperCPU::Registers reg) {
    using namespace HyperCPU;
    switch (reg) {
      case Registers::X0:
      case Registers::X1:
      case Registers::X2:
      case Registers::X3:
      case Registers::X4:
      case Registers::X5:
      case Registers::X6:
      case Registers::X7:
      case Registers::XBP:
      case Registers::XSP:
      case Registers::XIP:
        return Mode::b64;
      case Registers::XH0:
      case Registers::XH1:
      case Registers::XH2:
      case Registers::XH3:
      case Registers::XH4:
      case Registers::XH5:
      case Registers::XH6:
      case Registers::XH7:
      case Registers::XL0:
      case Registers::XL1:
      case Registers::XL2:
      case Registers::XL3:
      case Registers::XL4:
      case Registers::XL5:
      case Registers::XL6:
      case Registers::XL7:
        return Mode::b32;
      case Registers::XLL0:
      case Registers::XLL1:
      case Registers::XLL2:
      case Registers::XLL3:
        return Mode::b16;
      case Registers::XLLH0:
      case Registers::XLLH1:
      case Registers::XLLH2:
      case Registers::XLLH3:
      case Registers::XLLL0:
      case Registers::XLLL1:
      case Registers::XLLL2:
      case Registers::XLLL3:
        return Mode::b8;
      default:
        UNREACHABLE();
    }
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

  extern HyperCPU::Logger logger;
  extern CompilerState* current_state;
  extern std::uint64_t current_index;

  class HCAsmCompiler {
  public:
    HCAsmCompiler(HyperCPU::LogLevel lvl = HyperCPU::LogLevel::WARNING);

    BinaryResult Compile(std::string& contents, std::uint32_t& code_size);
    CompilerState TransformToIR(std::string& src);
    BinaryResult TransformToBinary(CompilerState& ir);

  private:
    pog::Parser<Value> parser;
    CompilerState* state;
    std::queue<std::string> files;
    hpool::HPool<pog::TokenWithLineSpec<Value>, hpool::ReallocationPolicy::OffsetRealloc> pool;

    constexpr inline std::uint8_t OperandSize(const OperandType op);
    std::uint8_t InstructionSize(Instruction& instr);
    std::uint8_t ModeToSize(const Operand& op);
    std::uint8_t ModeToSize(Mode md);
  };

}
