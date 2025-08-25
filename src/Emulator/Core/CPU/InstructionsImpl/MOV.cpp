#include "Emulator/Core/CPU/CPU.hpp"

void HyperCPU::CPU::ExecMOV(const IInstruction& instr, OperandContainer op1, OperandContainer op2) {
  switch (instr.m_op_types) {
  case OperandTypes::R_R: {
    switch (instr.m_opcode_mode) {
    case Mode::b8:
      std::memcpy(op1, op2.ptr<void>(), 1);
      break;

    case Mode::b16:
      std::memcpy(op1, op2.ptr<void>(), 2);
      break;

    case Mode::b32:
      std::memcpy(op1, op2.ptr<void>(), 4);
      break;

    case Mode::b64:
      std::memcpy(op1, op2.ptr<void>(), 8);
      break;
    }
    break;
  }

  case OperandTypes::R_RM: {
    std::uint64_t ptr = 0;
    std::memcpy(&ptr, op2.ptr<void>(), 8);

    switch (instr.m_opcode_mode) {
    case Mode::b8:
      *static_cast<std::uint8_t*>(op1) = mem_controller->Read8(ptr);
      break;

    case Mode::b16:
      *static_cast<std::uint16_t*>(op1) = mem_controller->Read16(ptr);
      break;

    case Mode::b32:
      *static_cast<std::uint32_t*>(op1) = mem_controller->Read32(ptr);
      break;

    case Mode::b64:
      *static_cast<std::uint64_t*>(op1) = mem_controller->Read64(ptr);
      break;
    }
    break;
  }

  case OperandTypes::R_M: {
    std::uint64_t ptr = op2;

    switch (instr.m_opcode_mode) {
    case Mode::b8:
      *static_cast<std::uint8_t*>(op1) = mem_controller->Read8(ptr);
      break;

    case Mode::b16:
      *static_cast<std::uint16_t*>(op1) = mem_controller->Read16(ptr);
      break;

    case Mode::b32:
      *static_cast<std::uint32_t*>(op1) = mem_controller->Read32(ptr);
      break;

    case Mode::b64:
      *static_cast<std::uint64_t*>(op1) = mem_controller->Read64(ptr);
      break;
    }
    break;
  }

  case OperandTypes::R_IMM: {
    switch (instr.m_opcode_mode) {
    case Mode::b8:
      std::memcpy(op1, &op2.ref(), 1);
      break;

    case Mode::b16:
      std::memcpy(op1, &op2.ref(), 2);
      break;

    case Mode::b32:
      std::memcpy(op1, &op2.ref(), 4);
      break;

    case Mode::b64:
      std::memcpy(op1, &op2.ref(), 8);
      break;
    }
    break;
  }

  case OperandTypes::RM_M: {
    std::uint64_t ptr1 = 0, ptr2 = 0;
    std::memcpy(&ptr1, op1.ptr<void>(), 8);
    ptr2 = op2;

    switch (instr.m_opcode_mode) {
    case Mode::b8:
      mem_controller->Load8(ptr1, mem_controller->Read8(ptr2));
      break;

    case Mode::b16:
      mem_controller->Load16(ptr1, mem_controller->Read16(ptr2));
      break;

    case Mode::b32:
      mem_controller->Load32(ptr1, mem_controller->Read32(ptr2));
      break;

    case Mode::b64:
      mem_controller->Load64(ptr1, mem_controller->Read64(ptr2));
      break;
    }
    break;
  }

  case OperandTypes::RM_R: {
    std::uint64_t ptr = op1.deref<std::uint64_t>();

    switch (instr.m_opcode_mode) {
    case Mode::b8: {
      mem_controller->Load8(ptr, *static_cast<std::uint8_t*>(op2));
      break;
    }

    case Mode::b16: {
      mem_controller->Load16(ptr, *static_cast<std::uint16_t*>(op2));
      break;
    }

    case Mode::b32: {
      mem_controller->Load32(ptr, *static_cast<std::uint32_t*>(op2));
      break;
    }

    case Mode::b64: {
      mem_controller->Load64(ptr, *static_cast<std::uint64_t*>(op2));
      break;
    }
    }
    break;
  }

  case OperandTypes::RM_IMM: {
    std::uint64_t ptr1 = op1.deref<std::uint64_t>();

    switch (instr.m_opcode_mode) {
    case Mode::b8:
      mem_controller->Load8(ptr1, HyperCPU::bit_cast<std::uint8_t>(op2));
      break;

    case Mode::b16:
      mem_controller->Load16(ptr1, HyperCPU::bit_cast<std::uint16_t>(op2));
      break;

    case Mode::b32:
      mem_controller->Load32(ptr1, HyperCPU::bit_cast<std::uint32_t>(op2));
      break;

    case Mode::b64:
      mem_controller->Load64(ptr1, HyperCPU::bit_cast<std::uint64_t>(op2));
      break;
    }
    break;
  }

  case OperandTypes::M_R: {
    auto ptr1 = HyperCPU::bit_cast<std::size_t>(op1);

    switch (instr.m_opcode_mode) {
    case Mode::b8: {
      mem_controller->Load8(ptr1, HyperCPU::bit_cast_from<std::uint8_t>(op2.ptr<std::uint8_t>()));
      break;
    }

    case Mode::b16: {
      mem_controller->Load16(ptr1, HyperCPU::bit_cast_from<std::uint16_t>(op2.ptr<std::uint16_t>()));
      break;
    }

    case Mode::b32: {
      mem_controller->Load32(ptr1, HyperCPU::bit_cast_from<std::uint32_t>(op2.ptr<std::uint32_t>()));
      break;
    }

    case Mode::b64: {
      mem_controller->Load64(ptr1, HyperCPU::bit_cast_from<std::uint64_t>(op2.ptr<std::uint64_t>()));
      break;
    }
    }
    break;
  }

  default:
    break;
  }
}
