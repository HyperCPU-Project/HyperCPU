#include <spdlog/spdlog.h>

#include "Assembler/Core/BinaryTransformer.hpp"
#include "Assembler/Core/Compiler.hpp"
#include "Common/Exit.hpp"
#include "Common/LanguageSpec/Flags.hpp"
#include "Common/LanguageSpec/Opcodes.hpp"
#include "PCH/CStd.hpp"

HyperCPU::OperandTypes HCAsm::BinaryTransformer::DetermineOperandTypes(Operand& op1, Operand& op2) {
  Op1T tp1 = Op1T::NONE; // Placeholder
  Op2T tp2 = Op2T::NONE; // Placeholder

  switch (op1.type) {
  case HCAsm::OperandType::reg:
    tp1 = Op1T::R;
    break;
  case HCAsm::OperandType::mem_reg_add_int:
  case HCAsm::OperandType::memaddr_reg:
    tp1 = Op1T::RM;
    break;
  case HCAsm::OperandType::sint:
  case HCAsm::OperandType::uint:
  case HCAsm::OperandType::label:
    tp1 = Op1T::IMM;
    break;
  case HCAsm::OperandType::memaddr_int:
  case HCAsm::OperandType::memaddr_lbl:
    tp1 = Op1T::M;
    break;
  case HCAsm::OperandType::none:
    tp1 = Op1T::NONE;
    break;
  default:
    HyperCPU::unreachable();
  }

  switch (op2.type) {
  case HCAsm::OperandType::reg:
    tp2 = Op2T::R;
    break;
  case HCAsm::OperandType::mem_reg_add_int:
  case HCAsm::OperandType::memaddr_reg:
    tp2 = Op2T::RM;
    break;
  case HCAsm::OperandType::sint:
  case HCAsm::OperandType::uint:
  case HCAsm::OperandType::label:
    tp2 = Op2T::IMM;
    break;
  case HCAsm::OperandType::memaddr_int:
  case HCAsm::OperandType::memaddr_lbl:
    tp2 = Op2T::M;
    break;
  case HCAsm::OperandType::none:
    tp2 = Op2T::NONE;
    break;
  default:
    HyperCPU::unreachable();
  }

  return QuickCast(QuickOR(tp1, tp2));
}

void HCAsm::BinaryTransformer::EncodeInstruction(HCAsm::Instruction& instr) {
  HyperCPU::OperandTypes types = DetermineOperandTypes(instr.op1, instr.op2);

  res.push(static_cast<std::uint16_t>(instr.opcode));

  switch (instr.opcode) {
  case HyperCPU::Opcode::IRET:
    return;
  default:
    break;
  }

  std::uint8_t encoded_operands = 0;

  if (HasAddressAddition(instr.op1.type) && HasAddressAddition(instr.op2.type)) {
    spdlog::error("You can't use memory address additions for two operands!");
    // TODO: handle error
  } else if (HasAddressAddition(instr.op1.type) || HasAddressAddition(instr.op2.type)) {
    encoded_operands |= 0b10000000;
    if (HasAddressAddition(instr.op2.type)) {
      encoded_operands |= 0b01000000;
    } else {
      // Do nothing - bit 0 means first operand
    }
  }

  // Handle case when one of operands is a label - we should mock the immediate 64 bit value
  switch (instr.op1.type) {
  case HCAsm::OperandType::label:
  case HCAsm::OperandType::memaddr_lbl:
    instr.op1.variant = state->labels.at(*std::get<std::shared_ptr<std::string>>(instr.op1.variant));
    break;
  default:
    break;
  }

  switch (instr.op2.type) {
  case HCAsm::OperandType::label:
  case HCAsm::OperandType::memaddr_lbl:
    instr.op2.variant = state->labels.at(*std::get<std::shared_ptr<std::string>>(instr.op2.variant));
    break;
  default:
    break;
  }

  HCAsm::Mode md = HCAsm::Mode::b8; // Placeholder
  switch (types) {
  case HyperCPU::OperandTypes::RM_M:
    if (instr.op2.mode != HCAsm::Mode::none) {
      md = instr.op2.mode;
      break;
    }
    [[fallthrough]];
  case HyperCPU::OperandTypes::RM_IMM:
    if (instr.op1.mode == HCAsm::Mode::none) {
      spdlog::error("Ambiguous operand size!");
      // TODO: handle error
    }
    [[fallthrough]];
  case HyperCPU::OperandTypes::R_R:
  case HyperCPU::OperandTypes::R_RM:
  case HyperCPU::OperandTypes::R_M:
  case HyperCPU::OperandTypes::R_IMM:
  case HyperCPU::OperandTypes::R:
    md = instr.op1.mode;
    [[fallthrough]];
  case HyperCPU::OperandTypes::IMM:
    if (instr.op1.mode == Mode::none) {
      spdlog::error("Undefined operand size!");
      // TODO: handle error
    }
    md = instr.op1.mode;
    break;
  case HyperCPU::OperandTypes::RM_R:
  case HyperCPU::OperandTypes::M_R:
    md = instr.op2.mode;
    break;
  case HyperCPU::OperandTypes::NONE:
    md = HCAsm::Mode::b8; // Placeholder
    break;
  default:
    HyperCPU::unreachable();
  }

  encoded_operands |= (static_cast<std::uint8_t>(md) << 4);
  encoded_operands |= static_cast<std::uint8_t>(types);

  res.push(static_cast<std::uint8_t>(encoded_operands));

  switch (types) {
  case HyperCPU::OperandTypes::R_R:
  case HyperCPU::OperandTypes::R_RM:
  case HyperCPU::OperandTypes::RM_R:
    res.push(static_cast<std::uint8_t>(instr.op1.reg));
    res.push(static_cast<std::uint8_t>(instr.op2.reg));
    break;
  case HyperCPU::OperandTypes::RM_M:
  case HyperCPU::OperandTypes::R_M:
    res.push(static_cast<std::uint8_t>(instr.op1.reg));
    res.push(std::get<std::uint64_t>(instr.op2.variant));
    break;
  case HyperCPU::OperandTypes::RM_IMM:
  case HyperCPU::OperandTypes::R_IMM:
    res.push(static_cast<std::uint8_t>(instr.op1.reg));
    if (std::holds_alternative<std::uint64_t>(instr.op2.variant)) {
      switch (md) {
      case HCAsm::Mode::b8:
        res.push(static_cast<std::uint8_t>(std::get<std::uint64_t>(instr.op2.variant)));
        break;
      case HCAsm::Mode::b16:
        res.push(static_cast<std::uint16_t>(std::get<std::uint64_t>(instr.op2.variant)));
        break;
      case HCAsm::Mode::b32:
        res.push(static_cast<std::uint32_t>(std::get<std::uint64_t>(instr.op2.variant)));
        break;
      case HCAsm::Mode::b64:
        res.push(static_cast<std::uint64_t>(std::get<std::uint64_t>(instr.op2.variant)));
        break;
      default:
        HyperCPU::unreachable();
      }
    } else {
      switch (md) {
      case HCAsm::Mode::b8:
        res.push(static_cast<std::int8_t>(std::get<std::int64_t>(instr.op2.variant)));
        break;
      case HCAsm::Mode::b16:
        res.push(static_cast<std::int16_t>(std::get<std::int64_t>(instr.op2.variant)));
        break;
      case HCAsm::Mode::b32:
        res.push(static_cast<std::int32_t>(std::get<std::int64_t>(instr.op2.variant)));
        break;
      case HCAsm::Mode::b64:
        res.push(static_cast<std::int64_t>(std::get<std::int64_t>(instr.op2.variant)));
        break;
      default:
        HyperCPU::unreachable();
      }
    }
    break;
  case HyperCPU::OperandTypes::R:
    res.push(static_cast<std::uint8_t>(instr.op1.reg));
    break;
  case HyperCPU::OperandTypes::M:
    res.push(std::get<std::uint64_t>(instr.op2.variant));
    break;
  case HyperCPU::OperandTypes::IMM:
    if (std::holds_alternative<std::uint64_t>(instr.op2.variant)) {
      switch (md) {
      case HCAsm::Mode::b8:
        res.push(static_cast<std::uint8_t>(std::get<std::uint64_t>(instr.op1.variant)));
        break;
      case HCAsm::Mode::b16:
        res.push(static_cast<std::uint16_t>(std::get<std::uint64_t>(instr.op1.variant)));
        break;
      case HCAsm::Mode::b32:
        res.push(static_cast<std::uint32_t>(std::get<std::uint64_t>(instr.op1.variant)));
        break;
      case HCAsm::Mode::b64:
        res.push(static_cast<std::uint64_t>(std::get<std::uint64_t>(instr.op1.variant)));
        break;
      default:
        HyperCPU::unreachable();
      }
    } else {
      switch (md) {
      case HCAsm::Mode::b8:
        res.push(static_cast<std::int8_t>(std::get<std::int64_t>(instr.op1.variant)));
        break;
      case HCAsm::Mode::b16:
        res.push(static_cast<std::int16_t>(std::get<std::int64_t>(instr.op1.variant)));
        break;
      case HCAsm::Mode::b32:
        res.push(static_cast<std::int32_t>(std::get<std::int64_t>(instr.op1.variant)));
        break;
      case HCAsm::Mode::b64:
        res.push(static_cast<std::int64_t>(std::get<std::int64_t>(instr.op1.variant)));
        break;
      default:
        HyperCPU::unreachable();
      }
    }
    break;
  case HyperCPU::OperandTypes::M_R:
    res.push(std::get<std::uint64_t>(instr.op2.variant));
    res.push(static_cast<std::uint8_t>(instr.op2.reg));
    break;
  case HyperCPU::OperandTypes::NONE:
    break;
  }
}
