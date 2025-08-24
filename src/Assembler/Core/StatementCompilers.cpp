#include "Assembler/Core/Compiler.hpp"
#include "Assembler/Core/OpcodeNameAssoc.hpp"
#include "Assembler/Core/RegNameAssoc.hpp"
#include "PCH/CStd.hpp"
#include "Pog/Pog.hpp"

using HCAsm::Value;

Value HCAsm::CompileStatement1([[maybe_unused]] pog::Parser<Value>& parser, std::vector<pog::TokenWithLineSpec<Value>>&& args) {
  auto& instr_name = std::get<std::string>(args[0].value.val);

  if (!opcode_assoc.contains(instr_name.c_str())) {
    ThrowError(args[0], parser, "unknown instruction name");
  }

  ++current_index;

  current_state->ir.emplace_back(
      Instruction{.opcode = opcode_assoc.at(instr_name.c_str()),
                  .op1 = std::get<Operand>(args[1].value.val),
                  .op2 = std::get<Operand>(args[3].value.val)});

  if (std::get<Operand>(args[1].value.val).type == OperandType::label) {
    parser.get_compiler_state()->pending_resolves.push_back(PendingLabelReferenceResolve{
        .idx = static_cast<uint32_t>(current_state->ir.size() - 1),
        .op = 0});
  } else if (std::get<Operand>(args[1].value.val).type == OperandType::label) {
    parser.get_compiler_state()->pending_resolves.push_back(PendingLabelReferenceResolve{
        .idx = static_cast<uint32_t>(current_state->ir.size() - 1),
        .op = 1});
  }

  return {};
}

Value HCAsm::CompileStatement2(pog::Parser<Value>& parser, std::vector<pog::TokenWithLineSpec<Value>>&& args) {
  auto& instr_name = std::get<std::string>(args[0].value.val);

  if (!opcode_assoc.contains(instr_name.c_str())) {
    ThrowError(args[0], parser, "unknown instruction name");
  }

  ++current_index;

  auto& tmp_op = std::get<Operand>(args[1].value.val);

  current_state->ir.emplace_back(
      Instruction{.opcode = opcode_assoc.at(instr_name.c_str()),
                  .op1 = tmp_op,
                  .op2 = {.type = HCAsm::OperandType::none}});

  if (tmp_op.type == OperandType::label) {
    parser.get_compiler_state()->pending_resolves.push_back(PendingLabelReferenceResolve{
        .idx = static_cast<uint32_t>(current_state->ir.size() - 1),
        .op = 0});
  }

  return {};
}

Value HCAsm::CompileStatement3(pog::Parser<Value>& parser, std::vector<pog::TokenWithLineSpec<Value>>&& args) {
  auto& instr_name = std::get<std::string>(args[0].value.val);

  if (!opcode_assoc.contains(instr_name.c_str())) {
    ThrowError(args[0], parser, "unknown instruction name");
  }

  ++current_index;

  current_state->ir.emplace_back(
      Instruction{.opcode = opcode_assoc.at(instr_name.c_str()),
                  .op1 = {.type = HCAsm::OperandType::none},
                  .op2 = {.type = HCAsm::OperandType::none}});
  return {};
}

Value HCAsm::CompileLabel(pog::Parser<Value>& parser, std::vector<pog::TokenWithLineSpec<Value>>&& args) {
  // Label cant be register or instruction name
  auto& name = std::get<std::string>(args[0].value.val);

  if (opcode_assoc.contains(name.c_str()) || registers_assoc.contains(name.c_str())) {
    ThrowError(args[0], parser, "reserved identifier cannot be used as a label");
  }

  if (current_state->labels.contains(name)) {
    ThrowError(args[0], parser, fmt::format("redefinition of label", name));
  }

  current_state->ir.emplace_back(HCAsm::Label{
      .name = name, .index = current_index++, .is_entry_point = false});
  current_state->labels[name] = current_index - 1;
  return {};
}

Value HCAsm::CompileEntryLabel(pog::Parser<Value>& parser, std::vector<pog::TokenWithLineSpec<Value>>&& args) {
  // Label cant be register or instruction name
  auto& name = std::get<std::string>(args[1].value.val);

  if (opcode_assoc.contains(name.c_str()) || registers_assoc.contains(name.c_str())) {
    ThrowError(args[0], parser, "reserved identifier cannot be used as a label");
  }

  if (current_state->labels.contains(name)) {
    ThrowError(args[0], parser, fmt::format("redefinition of label", name));
  }

  current_state->ir.emplace_back(HCAsm::Label{
      .name = name, .index = current_index++, .is_entry_point = true});
  current_state->labels[name] = current_index - 1;
  return {};
}

Value HCAsm::CompileRawValueb8(pog::Parser<Value>& parser, std::vector<pog::TokenWithLineSpec<Value>>&& args) {
  if (std::get<Operand>(args[1].value.val).type != OperandType::uint) {
    ThrowError(*std::get<Operand>(args[1].value.val).tokens[0], parser, "invalid operand type for directive '.b8', expected uint");
  }
  current_state->ir.emplace_back(HCAsm::RawValue{
      .mode = Mode::b8, .value = std::get<Operand>(args[1].value.val)});
  return {};
}

Value HCAsm::CompileRawValueb8_str([[maybe_unused]] pog::Parser<Value>& parser, std::vector<pog::TokenWithLineSpec<Value>>&& args) {
  if (!std::holds_alternative<std::string>(args[1].value.val)) {
    ThrowError(*std::get<Operand>(args[1].value.val).tokens[0], parser, "invalid operand type for directive '.b8' expected uint or string");
  }

  current_state->ir.emplace_back(HCAsm::RawValue{
      .mode = Mode::b8_str,
      .value = Operand{.variant = std::make_shared<std::string>(std::move(
                           std::get<std::string>(args[1].value.val)))}});

  return {};
}

Value HCAsm::CompileRawValueb16(pog::Parser<Value>& parser, std::vector<pog::TokenWithLineSpec<Value>>&& args) {
  if (std::get<Operand>(args[1].value.val).type != OperandType::uint) {
    ThrowError(*std::get<Operand>(args[1].value.val).tokens[0], parser, "invalid operand type for directive '.b16' expected uint");
  }
  current_state->ir.emplace_back(HCAsm::RawValue{
      .mode = Mode::b16, .value = std::get<Operand>(args[1].value.val)});
  return {};
}

Value HCAsm::CompileRawValueb32(pog::Parser<Value>& parser, std::vector<pog::TokenWithLineSpec<Value>>&& args) {
  if (std::get<Operand>(args[1].value.val).type != OperandType::uint) {
    ThrowError(*std::get<Operand>(args[1].value.val).tokens[0], parser, "invalid operand type for directive '.b32', expected uint");
  }
  current_state->ir.emplace_back(HCAsm::RawValue{
      .mode = Mode::b32, .value = std::get<Operand>(args[1].value.val)});
  return {};
}

Value HCAsm::CompileRawValueb64(pog::Parser<Value>& parser, std::vector<pog::TokenWithLineSpec<Value>>&& args) {
  auto& op = std::get<Operand>(args[1].value.val);

  switch (op.type) {
  case HCAsm::OperandType::uint:
    current_state->ir.emplace_back(
        HCAsm::RawValue{.mode = Mode::b64, .value = op});
    break;
  case HCAsm::OperandType::label:
    current_state->ir.emplace_back(
        HCAsm::RawValue{.mode = Mode::b64_label, .value = op});
    break;
  default:
    ThrowError(*std::get<Operand>(args[1].value.val).tokens[0], parser, "invalid operand type for directive '.b64', label or uint expected");
  }
  return {};
}
