#include "Emulator/Core/CPU/ALU.hpp"
#include "Emulator/Core/CPU/CPU.hpp"

using namespace HyperALU;

void HyperCPU::CPU::ExecOR(const IInstruction& instr, OperandContainer op1, OperandContainer op2) {
  switch (instr.m_op_types) {
  case OperandTypes::R_R: {
    switch (instr.m_opcode_mode) {
    case Mode::b8:
      op1.deref<std::uint8_t>() = __hcpu_or(op1.deref<std::uint8_t>(), HyperCPU::bit_cast_from<std::uint8_t>(op2.ptr<std::uint8_t>()));
      break;

    case Mode::b16:
      op1.deref<std::uint16_t>() = __hcpu_or(op1.deref<std::uint16_t>(), HyperCPU::bit_cast_from<std::uint16_t>(op2.ptr<std::uint16_t>()));
      break;

    case Mode::b32:
      op1.deref<std::uint32_t>() = __hcpu_or(op1.deref<std::uint32_t>(), HyperCPU::bit_cast_from<std::uint32_t>(op2.ptr<std::uint32_t>()));
      break;

    case Mode::b64:
      op1.deref<std::uint64_t>() = __hcpu_or(op1.deref<std::uint64_t>(), HyperCPU::bit_cast_from<std::uint64_t>(op2.ptr<std::uint64_t>()));
      break;
    }
    break;
  }

  case OperandTypes::R_RM: {
    std::uint64_t ptr = HyperCPU::bit_cast_from<std::uint64_t>(op2.ptr<std::uint64_t>());

    switch (instr.m_opcode_mode) {
    case Mode::b8: {
      std::uint8_t val = mem_controller->Read8(ptr);
      op1.deref<std::uint8_t>() = __hcpu_or(op1.deref<std::uint8_t>(), val);
      break;
    }

    case Mode::b16: {
      std::uint16_t val = mem_controller->Read16(ptr);
      op1.deref<std::uint16_t>() = __hcpu_or(op1.deref<std::uint16_t>(), val);
      break;
    }

    case Mode::b32: {
      std::uint32_t val = mem_controller->Read32(ptr);
      op1.deref<std::uint32_t>() = __hcpu_or(op1.deref<std::uint32_t>(), val);
      break;
    }

    case Mode::b64: {
      std::uint64_t val = mem_controller->Read64(ptr);
      op1.deref<std::uint64_t>() = __hcpu_or(op1.deref<std::uint64_t>(), val);
      break;
    }
    }
    break;
  }

  case OperandTypes::R_M: {
    std::uint64_t ptr = HyperCPU::bit_cast<std::uint64_t>(op2);

    switch (instr.m_opcode_mode) {
    case Mode::b8: {
      std::uint8_t val = mem_controller->Read8(ptr);
      op1.deref<std::uint8_t>() = __hcpu_or(op1.deref<std::uint8_t>(), val);
      break;
    }

    case Mode::b16: {
      std::uint16_t val = mem_controller->Read16(ptr);
      op1.deref<std::uint16_t>() = __hcpu_or(op1.deref<std::uint16_t>(), val);
      break;
    }

    case Mode::b32: {
      std::uint32_t val = mem_controller->Read32(ptr);
      op1.deref<std::uint32_t>() = __hcpu_or(op1.deref<std::uint32_t>(), val);
      break;
    }

    case Mode::b64: {
      std::uint64_t val = mem_controller->Read64(ptr);
      op1.deref<std::uint64_t>() = __hcpu_or(op1.deref<std::uint64_t>(), val);
      break;
    }
    }
    break;
  }

  case OperandTypes::R_IMM: {
    switch (instr.m_opcode_mode) {
    case Mode::b8: {
      std::uint8_t val = HyperCPU::bit_cast<std::uint8_t>(op2);
      op1.deref<std::uint8_t>() = __hcpu_or(op1.deref<std::uint8_t>(), val);
      break;
    }

    case Mode::b16: {
      std::uint16_t val = HyperCPU::bit_cast<std::uint16_t>(op2);
      op1.deref<std::uint16_t>() = __hcpu_or(op1.deref<std::uint16_t>(), val);
      break;
    }

    case Mode::b32: {
      std::uint32_t val = HyperCPU::bit_cast<std::uint32_t>(op2);
      op1.deref<std::uint32_t>() = __hcpu_or(op1.deref<std::uint32_t>(), val);
      break;
    }

    case Mode::b64: {
      std::uint64_t val = HyperCPU::bit_cast<std::uint64_t>(op2);
      op1.deref<std::uint64_t>() = __hcpu_or(op1.deref<std::uint64_t>(), val);
      break;
    }
    }
    break;
  }

  default:
    break;
  }
}
