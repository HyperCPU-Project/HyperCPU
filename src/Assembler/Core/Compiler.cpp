#include <spdlog/spdlog.h>

#include "Assembler/Core/BinaryTransformer.hpp"
#include "Assembler/Core/Compiler.hpp"
#include "Common/Exit.hpp"
#include "Common/Helpers/Classes.hpp"
#include "PCH/CStd.hpp"
#include "Pog/Pog.hpp"

namespace HCAsm {
  HCAsm::CompilerState* current_state;
  std::uint64_t current_index = 0;
} // namespace HCAsm

// TODO: fix constants
HCAsm::HCAsmCompiler::HCAsmCompiler()
    : pool(32) {
  // Setup tokens
  parser.token("[^\\S\n]+")
      .action([this]([[maybe_unused]] std::string_view tok) -> Value {
        parser.get_line_offset() += tok.length();
        return {};
      });
  parser.token("\\/\\/.*");           // Single line comment
  parser.token(R"(\/\*[\S\s]+\*\/)"); /* Multi-line comment */
  parser.token(R"(\+)")
      .symbol("+");
  parser.token(R"(-)")
      .symbol("-");
  parser.token(",")
      .symbol(",");
  parser.token("\\[")
      .symbol("[");
  parser.token("\\]")
      .symbol("]");
  parser.token(";")
      .symbol(";");
  parser.token(":")
      .symbol(":");
  parser.token(R"(\n)")
      .action([this]([[maybe_unused]] std::string_view tok) -> Value {
        ++parser.get_line_counter();
        parser.reset_line_offset();
        return {};
      });

  parser.token(R"(\.attr\(entry\))")
      .symbol("entry");

  parser.token("#use")
      .fullword()
      .symbol("use");
  parser.token("\\.b8")
      .fullword()
      .symbol(".b8");
  parser.token("\\.b16")
      .fullword()
      .symbol(".b16");
  parser.token("\\.b32")
      .fullword()
      .symbol(".b32");
  parser.token("\\.b64")
      .fullword()
      .symbol(".b64");

  parser.token("[a-zA-Z_][a-zA-Z0-9_]*")
      .symbol("ident")
      .action(TokenizeIdentifier);
  parser.token(R"lit("((?:\\[\s\S]|[^"\\])*)")lit")
      .symbol("string")
      .action(TokenizeString);
  parser.token(R"(0s[0-9]+)")
      .symbol("sint")
      .action(TokenizeSignedInt);
  parser.token(R"(0u[0-9]+)")
      .symbol("uint")
      .action(TokenizeUnsignedInt);
  parser.token(R"(0x[0-9a-fA-F]+)")
      .symbol("hex")
      .action(TokenizeHexadecimal);
  parser.token(R"(0b[0-1]+)")
      .symbol("binary")
      .action(TokenizeBinary);
  parser.token(R"('.')")
      .symbol("char")
      .action(TokenizeChar);
  parser.end_token().action([this](std::string_view) -> Value {
    parser.pop_input_stream();
    return {};
  });
  spdlog::debug("Tokens configured");

  // Setup parser rules
  parser.set_start_symbol("statements");
  parser.rule("statements")
      .production("statements", "statement")
      .production("statement");
  parser.rule("statement")
      /* Reserved statements */
      .production(".b8", "operand", ";", CompileRawValueb8)
      .production(".b8", "string", ";", CompileRawValueb8_str)
      .production(".b16", "operand", ";", CompileRawValueb16)
      .production(".b32", "operand", ";", CompileRawValueb32)
      .production(".b64", "operand", ";", CompileRawValueb64)
      .production("ident", "operand", ",", "operand", ";", CompileStatement1)
      .production("ident", "operand", ";", CompileStatement2)
      .production("ident", ";", CompileStatement3)
      .production("entry", "ident", ":", CompileEntryLabel)
      .production("ident", ":", CompileLabel);

  parser.rule("operand")
      .production("[", "hex", "]", ParseOperand1)
      .production("[", "ident", "]", ParseOperand2)
      .production("[", "ident", "+", "uint", "]", ParseOperand3)
      .production("[", "ident", "+", "hex", "]", ParseOperand3)
      .production("[", "ident", "+", "binary", "]", ParseOperand3)
      .production("ident", "ident", "[", "hex", "]", ParseOperand4)
      .production("ident", "ident", "[", "ident", "]", ParseOperand5)
      .production("ident", "ident", "[", "ident", "+", "uint", "]", ParseOperand6)
      .production("ident", "ident", "[", "ident", "+", "hex", "]", ParseOperand6)
      .production("ident", "ident", "[", "ident", "+", "binary", "]", ParseOperand6)
      .production("ident", "hex", ParseOperand10)
      .production("ident", "binary", ParseOperand10)
      .production("ident", "uint", ParseOperand10)
      .production("ident", "char", ParseOperand10)
      .production("ident", "sint", ParseOperand11)
      .production("ident", "ident", ParseOperand12)
      .production("hex", ParseOperand8)
      .production("binary", ParseOperand8)
      .production("sint", ParseOperand7)
      .production("uint", ParseOperand8)
      .production("char", ParseOperand8)
      .production("ident", ParseOperand9);
}

HCAsm::BinaryResult HCAsm::HCAsmCompiler::Compile(std::string& contents, std::uint32_t& code_size) {
  files.push(std::move(contents));

  spdlog::info("Stage 1 compiling - transforming to IR");
  CompilerState ir = TransformToIR(files.back());

  spdlog::info("Stage 2 compiling - transforming to binary");
  auto binary = TransformToBinary(ir);
  code_size = ir.code_size;

  return binary;
}

HCAsm::CompilerState HCAsm::HCAsmCompiler::TransformToIR(std::string& src) {
  CompilerState state(pool);
  current_state = &state;
  this->state = &state;
  parser.set_compiler_state(&state);

  parser.prepare();
  spdlog::info("Parser prepared.");
  spdlog::info("Compiling...");

  parser.parse(src);
  current_state = nullptr;
  return state;
}

constexpr inline std::uint8_t HCAsm::HCAsmCompiler::OperandSize(HCAsm::OperandType op) {
  switch (op) {
  case HCAsm::OperandType::mem_reg_add_int:
  case HCAsm::OperandType::memaddr_reg:
  case HCAsm::OperandType::reg:
    return 1;
  case HCAsm::OperandType::memaddr_int:
  case HCAsm::OperandType::sint:
  case HCAsm::OperandType::uint:
  case HCAsm::OperandType::label:
    return 8;
  default:
    std::abort();
  }
}

std::uint8_t HCAsm::HCAsmCompiler::ModeToSize(const Operand& op) {
  switch (op.mode) {
  case Mode::b8_str:
    return std::get<std::shared_ptr<std::string>>(op.variant)->size();
  case Mode::b8:
    return 1;
  case Mode::b16:
    return 2;
  case Mode::b32:
    return 4;
  case Mode::b64_label:
  case Mode::b64:
    return 8;
  default:
    std::abort();
  }
}

std::uint8_t HCAsm::HCAsmCompiler::ModeToSize(Mode md) {
  switch (md) {
  case Mode::b8:
    return 1;
  case Mode::b16:
    return 2;
  case Mode::b32:
    return 4;
  case Mode::b64_label:
  case Mode::b64:
    return 8;
  default:
    std::abort();
  }
}

std::uint8_t HCAsm::HCAsmCompiler::InstructionSize(HCAsm::Instruction& instr) {
  switch (instr.opcode) {
  case HyperCPU::Opcode::IRET:
    return 2;
  default:
    break;
  }

  std::uint8_t result = 3; // Opcode is always two bytes long + one byte for operand types
  switch (instr.op1.type) {
  case OperandType::reg: // R_*
    switch (instr.op2.type) {
    case OperandType::memaddr_reg: // R_RM
      [[fallthrough]];
    case OperandType::reg: // R_R
      result += 2;
      break;
    case OperandType::sint:
      [[fallthrough]];
    case OperandType::uint: // R_IMM
      result += 1 + ModeToSize(instr.op1);
      break;
    case OperandType::label:
      [[fallthrough]];
    case OperandType::memaddr_int: // R_M
      result += 9;
      break;
    case OperandType::mem_reg_add_int:
      result += 10;
      break;
    case OperandType::none: // R
      result += 1;
      break;
    default:
      HyperCPU::unreachable();
    }
    break;
  case OperandType::mem_reg_add_int:
    ++result;
    [[fallthrough]];
  case OperandType::memaddr_reg:
    switch (instr.op2.type) {
    case OperandType::reg: // RM_R
      result += 2;
      break;
    case OperandType::sint:
      [[fallthrough]];
    case OperandType::uint: // RM_IMM
      result += 1 + ModeToSize(instr.op1);
      break;
    case OperandType::label:
      [[fallthrough]];
    case OperandType::memaddr_int: // RM_M
      result += 9;
      break;
    case OperandType::mem_reg_add_int:
      result += 10;
      break;
    default:
      HyperCPU::unreachable();
    }
    break;
  case OperandType::sint:
    [[fallthrough]];
  case OperandType::uint: // IMM
    switch (instr.op1.mode) {
    case Mode::none:
      ThrowError(*(instr.op1.tokens[0]), parser, "unknown operand size");
      break;
    default:
      result += ModeToSize(instr.op1);
      break;
    }
    break;
  case OperandType::memaddr_lbl:
  case OperandType::memaddr_int:
    result += 8;
    switch (instr.op2.type) {
    case OperandType::reg: // M_R
      ++result;
      break;
    default:
      HyperCPU::unreachable();
    }
    break;
  case OperandType::label:
    result += 8;
    break;
  case OperandType::none:
    break;
  default:
    std::abort();
  }

  return result;
}

HCAsm::BinaryResult HCAsm::HCAsmCompiler::TransformToBinary(HCAsm::CompilerState& ir) {
  // Count code size - pass 1
  spdlog::info("Running pass 1 - counting code size");

  for (auto& instr : ir.ir) {
    VisitVariant(instr, [this, &ir](Instruction& instruction) mutable -> void { ir.code_size += InstructionSize(instruction); }, [&ir](Label& label) mutable -> void {
      ir.labels[label.name] = ir.code_size;
      if (label.is_entry_point) {
        ir.entry_point = ir.code_size;
      } }, [&ir](RawValue& raw) mutable -> void { ir.code_size += [&raw]() -> std::uint8_t {
                                                                                                                                                                                                                   switch (raw.mode) {
                                                                                                                                                                                                                   case Mode::b8_str:
                                                                                                                                                                                                                     return std::get<std::shared_ptr<std::string>>(raw.value.variant)->size();
                                                                                                                                                                                                                   case Mode::b8:
                                                                                                                                                                                                                     return 1;
                                                                                                                                                                                                                   case Mode::b16:
                                                                                                                                                                                                                     return 2;
                                                                                                                                                                                                                   case Mode::b32:
                                                                                                                                                                                                                     return 4;
                                                                                                                                                                                                                   case Mode::b64_label:
                                                                                                                                                                                                                   case Mode::b64:
                                                                                                                                                                                                                     return 8;
                                                                                                                                                                                                                   default:
                                                                                                                                                                                                                     std::abort();
                                                                                                                                                                                                                   }
                                                                                                                                                                                                                 }(); });
  }

  // Resolve references - pass 2
  spdlog::info("{} label references are waiting for resolve", ir.pending_resolves.size());
  if (!ir.pending_resolves.empty()) {
    spdlog::info("Resolving label references");

    for (auto& args : ir.pending_resolves) {
      auto& instr = ir.ir[args.idx];
      auto* op = args.op ? &std::get<Instruction>(instr).op2 : &std::get<Instruction>(instr).op1;

      if (ir.labels.contains(*std::get<std::shared_ptr<std::string>>(op->variant))) {
        op->type = OperandType::uint;
        op->variant.emplace<0>(ir.labels[*std::get<std::shared_ptr<std::string>>(op->variant)]);
      } else {
        ThrowError(*op->tokens[0], parser, fmt::format("failed to resolve undefined reference to \"{}\"", *std::get<std::shared_ptr<std::string>>(op->variant)));
      }
    }
  }

  // Compile code - pass 3
  BinaryResult binary = {new unsigned char[ir.code_size]};
  if (!binary.binary) {
    spdlog::error("Failed to allocate memory for binary data!");
    HyperCPU::exit(1);
  }

  spdlog::info("Running pass 3 - compiling");

  BinaryTransformer transformer(binary, &ir);

  for (auto& instr : ir.ir) {
    VisitVariant(instr, [&transformer](Instruction& instruction) mutable -> void { transformer.EncodeInstruction(instruction); }, [&binary, &ir, this](RawValue& raw) mutable -> void {
      switch (raw.mode) {
        case Mode::b8_str:
          binary.push(*std::get<std::shared_ptr<std::string>>(raw.value.variant));
          break;
        case Mode::b8:
          binary.push(static_cast<std::uint8_t>(std::get<std::uint64_t>(raw.value.variant)));
          break;
        case Mode::b16:
          binary.push(static_cast<std::uint16_t>(std::get<std::uint64_t>(raw.value.variant)));
          break;
        case Mode::b32:
          binary.push(static_cast<std::uint32_t>(std::get<std::uint64_t>(raw.value.variant)));
          break;
        case Mode::b64_label:
          if (!ir.labels.contains(*std::get<std::shared_ptr<std::string>>(raw.value.variant))) {
            ThrowError(*raw.value.tokens[1], parser, fmt::format("failed to resolve undefined reference to \"{}\"", *std::get<std::shared_ptr<std::string>>(raw.value.variant)));
          }
          binary.push(static_cast<std::uint64_t>(ir.labels.at(*std::get<std::shared_ptr<std::string>>(raw.value.variant))));
          break;
        case Mode::b64:
          binary.push(static_cast<std::uint64_t>(std::get<std::uint64_t>(raw.value.variant)));
          break;
        default:
          HyperCPU::unreachable();
      } }, [](Label&) {});
  }

  binary.entry_point = ir.entry_point;

  return binary;
}

std::string_view HCAsm::FindLine(const pog::LineSpecialization& line_spec, const std::string_view& str) {
  std::size_t start = 0;
  std::size_t end = 0;
  std::size_t current_line = 1;

  while (end < str.size()) {
    if (str[end] == '\n') {
      if (current_line == line_spec.line) {
        return std::string_view{str.begin() + start, end - start};
      }
      start = end + 1;
      current_line++;
    }
    end++;
  }

  if (current_line == line_spec.line) {
    return std::string_view{str.begin() + start, str.end()};
  }

  throw std::out_of_range("Line number out of range");
}

[[noreturn]] void HCAsm::ThrowError(pog::TokenWithLineSpec<Value>& err_token, pog::Parser<Value>& parser, std::string err_msg) {
  spdlog::error("error: {}", err_msg);
  auto line = FindLine(err_token.line_spec, parser.get_top_file());
  spdlog::debug("{} | {}", err_token.line_spec.line, line);
  spdlog::debug("{:<{}} | {:<{}}{}",
                "", std::to_string(err_token.line_spec.line).length(),
                "", err_token.line_spec.offset,
                std::string(err_token.line_spec.length, '^'));
  HyperCPU::exit(1);
}

void HCAsm::WriteResultFile(HyperCPU::FileType type, HCAsm::BinaryResult& result, std::ofstream& output, std::uint32_t code_size, std::uint32_t entry_point) {
  HyperCPU::GenericHeader gen_header{};
  gen_header.type = type;
  gen_header.magic = HyperCPU::magic;
  gen_header.version = HyperCPU::current_version;
  gen_header.code_size = code_size;
  gen_header.entry_point = entry_point;
  output.write(reinterpret_cast<char*>(&gen_header), sizeof(gen_header));

  output.write(reinterpret_cast<char*>(result.binary), code_size);
}
