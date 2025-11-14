#include "Emulator/Core/CPU/CPU.hpp"

void HyperCPU::CPU::ExecLODSB(const IInstruction& instr, OperandContainer op1, OperandContainer op2) {
  switch (instr.m_opcode_mode) {
  case Mode::b8: {
    std::int8_t offset;
    std::memcpy(&offset, xfst, 1);
    op1.deref<std::uint8_t>() = mem_controller->Read8(*xsp + offset);
    break;
  }
  case Mode::b16: {
    std::int16_t offset;
    std::memcpy(&offset, xfst, 2);
    op1.deref<std::uint16_t>() = mem_controller->Read16(*xsp + offset);
    break;
  }
  case Mode::b32: {
    std::int32_t offset;
    std::memcpy(&offset, xfst, 4);
    op1.deref<std::uint32_t>() = mem_controller->Read32(*xsp + offset);
    break;
  }
  case Mode::b64: {
    std::int64_t offset;
    std::memcpy(&offset, xfst, 8);
    op1.deref<std::uint64_t>() = mem_controller->Read64(*xsp + offset);
    break;
  }
  }
}