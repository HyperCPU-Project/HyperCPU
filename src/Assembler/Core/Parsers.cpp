#include "Assembler/Core/Compiler.hpp"
#include "Assembler/Core/ModeNameAssoc.hpp"
#include "Assembler/Core/RegNameAssoc.hpp"
#include "PCH/CStd.hpp"
#include "Pog/Pog.hpp"

using HCAsm::Value;

Value HCAsm::ParseOperand1(pog::Parser<Value>& parser, std::vector<pog::TokenWithLineSpec<Value>>&& args) {
  return {
      .val = Operand{
          .type = HCAsm::OperandType::memaddr_int,
          .mode = HCAsm::Mode::none,
          .tokens = {parser.get_compiler_state()->pool.allocate(std::move(args[1]))},
          .variant = {std::get<std::uint64_t>(args[1].value.val)}}};
}

Value HCAsm::ParseOperand2(pog::Parser<Value>& parser, std::vector<pog::TokenWithLineSpec<Value>>&& args) {
  auto reg = std::get<std::string>(args[1].value.val);

  if (registers_assoc.contains(reg.c_str())) {
    return {
        .val = Operand{
            .type = HCAsm::OperandType::memaddr_reg,
            .reg = registers_assoc.at(reg.c_str()),
            .mode = HCAsm::Mode::none,
            .tokens = {
                parser.get_compiler_state()->pool.allocate(std::move(args[1]))}}};
  } else {
    return {
        .val = Operand{
            .type = HCAsm::OperandType::memaddr_lbl,
            .mode = HCAsm::Mode::b64,
            .needs_resolve = !parser.get_compiler_state()->labels.contains(reg),
            .tokens = {
                parser.get_compiler_state()->pool.allocate(std::move(args[1]))},
            .variant = {std::make_shared<std::string>(reg)}}};
  }
}

Value HCAsm::ParseOperand3(pog::Parser<Value>& parser, std::vector<pog::TokenWithLineSpec<Value>>&& args) {
  auto& reg = std::get<std::string>(args[1].value.val);

  if (!registers_assoc.contains(reg.c_str())) [[unlikely]] {
    ThrowError(
        args[1],
        parser,
        fmt::format("expected register, got unknown identifier \"{}\"", std::get<std::string>(args[1].value.val)));
  } else if (std::get<std::uint64_t>(args[3].value.val) > 255) [[unlikely]] {
    ThrowError(
        args[3],
        parser,
        fmt::format("out of bounds integer provided: {} > 255", std::get<std::uint64_t>(args[3].value.val)));
  }

  return {
      .val = Operand{
          .type = HCAsm::OperandType::mem_reg_add_int,
          .reg = registers_assoc.at(reg.c_str()),
          .mode = HCAsm::Mode::none,
          .tokens = {
              parser.get_compiler_state()->pool.allocate(std::move(args[1])),
              parser.get_compiler_state()->pool.allocate(std::move(args[3]))},
          .variant = {std::get<std::uint64_t>(args[3].value.val)}}};
}

Value HCAsm::ParseOperand4(pog::Parser<Value>& parser, std::vector<pog::TokenWithLineSpec<Value>>&& args) {
  auto& Mode = std::get<std::string>(args[0].value.val);

  if (!mode_assoc.contains(Mode.c_str())) [[unlikely]] {
    ThrowError(
        args[0],
        parser,
        fmt::format("unknown data size specified: \"{}\"", Mode));
  } else if (std::get<std::string>(args[1].value.val) != "ptr") {
    ThrowError(args[1], parser,
               fmt::format(R"(unknown keyword "{}" specified, "ptr" expected)",
                           std::get<std::string>(args[1].value.val)));
  }

  return {
      .val = Operand{
          .type = HCAsm::OperandType::memaddr_int,
          .mode = mode_assoc.at(Mode.c_str()),
          .tokens = {
              parser.get_compiler_state()->pool.allocate(std::move(args[3]))},
          .variant = {std::get<std::uint64_t>(args[3].value.val)}}};
}

Value HCAsm::ParseOperand5(pog::Parser<Value>& parser, std::vector<pog::TokenWithLineSpec<Value>>&& args) {
  auto& reg = std::get<std::string>(args[3].value.val);
  auto& Mode = std::get<std::string>(args[0].value.val);

  if (!registers_assoc.contains(reg.c_str())) [[unlikely]] {
    ThrowError(
        args[3],
        parser,
        fmt::format("expected register, got unknown identifier \"{}\"", std::get<std::string>(args[3].value.val)));
  } else if (!mode_assoc.contains(Mode.c_str())) [[unlikely]] {
    ThrowError(
        args[0],
        parser,
        fmt::format("unknown data size specified: \"{}\"", Mode));
  } else if (std::get<std::string>(args[1].value.val) != "ptr") [[unlikely]] {
    ThrowError(args[1], parser,
               fmt::format(R"(unknown keyword "{}" specified, "ptr" expected)",
                           std::get<std::string>(args[1].value.val)));
  }

  return {
      .val = Operand{
          .type = HCAsm::OperandType::memaddr_reg,
          .reg = registers_assoc.at(reg.c_str()),
          .mode = mode_assoc.at(Mode.c_str()),
          .tokens = {
              parser.get_compiler_state()->pool.allocate(std::move(args[3]))}}};
}

Value HCAsm::ParseOperand6(pog::Parser<Value>& parser, std::vector<pog::TokenWithLineSpec<Value>>&& args) {
  auto& reg = std::get<std::string>(args[3].value.val);
  auto& Mode = std::get<std::string>(args[0].value.val);

  if (!registers_assoc.contains(reg.c_str())) {
    ThrowError(
        args[3],
        parser,
        fmt::format("expected register, got unknown identifier \"{}\"", std::get<std::string>(args[3].value.val)));
  } else if (!mode_assoc.contains(Mode.c_str())) {
    ThrowError(
        args[0],
        parser,
        fmt::format("unknown data size specified: \"{}\"", Mode));
  } else if (std::get<std::string>(args[1].value.val) != "ptr") {
    ThrowError(args[1], parser,
               fmt::format(R"(unknown keyword "{}" specified, "ptr" expected)",
                           std::get<std::string>(args[1].value.val)));
  } else if (std::get<std::uint64_t>(args[5].value.val) > 255) [[unlikely]] {
    ThrowError(
        args[5],
        parser,
        fmt::format("out of bounds integer provided: {} > 255", std::get<std::uint64_t>(args[5].value.val)));
  }

  return {
      .val = Operand{
          .type = HCAsm::OperandType::mem_reg_add_int,
          .reg = registers_assoc.at(reg.c_str()),
          .mode = mode_assoc.at(Mode.c_str()),
          .tokens = {
              parser.get_compiler_state()->pool.allocate(std::move(args[5]))},
          .variant = {std::get<std::uint64_t>(args[5].value.val)}}};
}

Value HCAsm::ParseOperand7(pog::Parser<Value>& parser, std::vector<pog::TokenWithLineSpec<Value>>&& args) {
  return {
      .val = Operand{
          .type = HCAsm::OperandType::sint,
          .mode = HCAsm::Mode::none,
          .tokens = {
              parser.get_compiler_state()->pool.allocate(std::move(args[0]))},
          .variant = {std::get<std::int64_t>(args[0].value.val)}}};
}

Value HCAsm::ParseOperand8(pog::Parser<Value>& parser, std::vector<pog::TokenWithLineSpec<Value>>&& args) {
  return {
      .val = Operand{
          .type = HCAsm::OperandType::uint,
          .mode = HCAsm::Mode::none,
          .tokens = {
              parser.get_compiler_state()->pool.allocate(std::move(args[0]))},
          .variant = {std::get<std::uint64_t>(args[0].value.val)}}};
}

Value HCAsm::ParseOperand9(pog::Parser<Value>& parser, std::vector<pog::TokenWithLineSpec<Value>>&& args) {
  auto reg = std::get<std::string>(args[0].value.val);

  if (registers_assoc.contains(reg.c_str())) {
    return {
        .val = Operand{
            .type = HCAsm::OperandType::reg,
            .reg = registers_assoc.at(reg.c_str()),
            .mode = ModeFromRegister(registers_assoc.at(reg.c_str())),
            .tokens = {
                parser.get_compiler_state()->pool.allocate(std::move(args[0]))},
        }};
  } else {
    parser.get_compiler_state()->tmp_args = args;
    return {
        .val = Operand{
            .type = HCAsm::OperandType::label,
            .mode = Mode::b64,
            .needs_resolve = !parser.get_compiler_state()->labels.contains(reg),
            .tokens = {
                parser.get_compiler_state()->pool.allocate(std::move(args[0]))},
            .variant = {std::make_shared<std::string>(reg)} // TODO: use std::move on reg
        }};
  }
}

Value HCAsm::ParseOperand10(pog::Parser<Value>& parser, std::vector<pog::TokenWithLineSpec<Value>>&& args) {
  auto mode = std::get<std::string>(args[0].value.val);

  if (!mode_assoc.contains(mode.c_str())) { // TODO: add [[unlikely]] attribute for error handling branches
    ThrowError(
        args[0],
        parser,
        fmt::format("unknown data size specified: \"{}\"", mode));
  }

  return {
      .val = Operand{
          .type = HCAsm::OperandType::uint,
          .mode = mode_assoc.at(mode.c_str()),
          .tokens = {
              parser.get_compiler_state()->pool.allocate(std::move(args[1]))},
          .variant = {std::get<std::uint64_t>(args[1].value.val)}}};
}

Value HCAsm::ParseOperand11(pog::Parser<Value>& parser, std::vector<pog::TokenWithLineSpec<Value>>&& args) {
  auto mode = std::get<std::string>(args[0].value.val);

  if (!mode_assoc.contains(mode.c_str())) {
    ThrowError(
        args[0],
        parser,
        fmt::format("unknown data size specified: \"{}\"", mode));
  }

  return {
      .val = Operand{
          .type = HCAsm::OperandType::sint,
          .mode = mode_assoc.at(mode.c_str()),
          .tokens = {
              parser.get_compiler_state()->pool.allocate(std::move(args[1]))},
          .variant = {std::get<std::int64_t>(args[1].value.val)}}};
}

Value HCAsm::ParseOperand12(pog::Parser<Value>& parser, std::vector<pog::TokenWithLineSpec<Value>>&& args) {
  auto mode = std::get<std::string>(args[0].value.val);
  auto reg = std::get<std::string>(args[1].value.val);

  if (!mode_assoc.contains(mode.c_str())) {
    ThrowError(
        args[0],
        parser,
        fmt::format("unknown data size specified: \"{}\"", mode));
  } else if (!registers_assoc.contains(reg.c_str())) {
    return {
        .val = Operand{
            .type = HCAsm::OperandType::label,
            .mode = mode_assoc.at(mode.c_str()),
            .needs_resolve = !parser.get_compiler_state()->labels.contains(reg),
            .tokens = {
                parser.get_compiler_state()->pool.allocate(std::move(args[1]))},
            .variant = {std::make_shared<std::string>(reg)} // TODO: use std::move on reg
        }};
  }

  return {
      .val = Operand{
          .type = HCAsm::OperandType::reg,
          .mode = mode_assoc.at(mode.c_str()),
          .tokens = {
              parser.get_compiler_state()->pool.allocate(std::move(args[1]))},
          .variant = {std::make_unique<std::string>(reg)}}};
}
