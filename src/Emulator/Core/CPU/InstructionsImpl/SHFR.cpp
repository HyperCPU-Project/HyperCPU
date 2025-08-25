#include "Emulator/Core/CPU/CPU.hpp"

void HyperCPU::CPU::ExecSHFR(const IInstruction& instr, OperandContainer op1, OperandContainer op2) {
  switch (instr.m_op_types) {
  case OperandTypes::R_R: {
    switch (instr.m_opcode_mode) {
    case Mode::b8:
      op1.deref<std::uint8_t>() >>= op2.deref<std::uint8_t>();
      break;

    case Mode::b16:
      op1.deref<std::uint16_t>() >>= op2.deref<std::uint16_t>();
      break;

    case Mode::b32:
      op1.deref<std::uint32_t>() >>= op2.deref<std::uint32_t>();
      break;

    case Mode::b64:
      op1.deref<std::uint64_t>() >>= op2.deref<std::uint64_t>();
      break;
    }
    break;
  }

  case OperandTypes::R_IMM: {
    switch (instr.m_opcode_mode) {
    case Mode::b8: {
      auto val = HyperCPU::bit_cast<std::uint8_t>(op2);
      op1.deref<std::uint8_t>() >>= val;
      break;
    }

    case Mode::b16: {
      auto val = HyperCPU::bit_cast<std::uint16_t>(op2);
      op1.deref<std::uint16_t>() >>= val;
      break;
    }

    case Mode::b32: {
      auto val = HyperCPU::bit_cast<std::uint32_t>(op2);
      op1.deref<std::uint32_t>() >>= val;
      break;
    }

    case Mode::b64: {
      auto val = HyperCPU::bit_cast<std::uint64_t>(op2);
      op1.deref<std::uint64_t>() >>= val;
      break;
    }
    }
    break;
  }

  default:
    break;
  }
}
