#include "Emulator/Core/CPU/CPU.hpp"

void HyperCPU::CPU::ExecSTDSB(const IInstruction& instr, OperandContainer op1, OperandContainer op2) {
  std::int64_t offset;
  std::memcpy(&offset, xfst, sizeof(std::int64_t));
  switch (instr.m_opcode_mode) {
  case Mode::b8: {
    mem_controller->Load8(*xsp + offset, op1.deref<std::int8_t>());
    break;
  }
  case Mode::b16: {
    mem_controller->Load16(*xsp + offset, op1.deref<std::int16_t>());
    break;
  }
  case Mode::b32: {
    mem_controller->Load32(*xsp + offset, op1.deref<std::int32_t>());
    break;
  }
  case Mode::b64: {
    mem_controller->Load64(*xsp + offset, op1.deref<std::int64_t>());
    break;
  }
  }
}