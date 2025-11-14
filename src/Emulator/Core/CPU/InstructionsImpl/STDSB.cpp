#include "Emulator/Core/CPU/CPU.hpp"

void HyperCPU::CPU::ExecSTDSB(const IInstruction& instr, OperandContainer op1, OperandContainer op2) {
  switch (instr.m_opcode_mode) {
  case Mode::b8: {
    std::int8_t offset;
    std::memcpy(&offset, xfst, 1);
    std::memcpy(HyperCPU::bit_cast<std::uint8_t*>(xsp) + offset, op1.ptr<std::uint8_t>() + offset, 1);
    break;
  }
  case Mode::b16: {
    std::int16_t offset;
    std::memcpy(&offset, xfst, 2);
    std::memcpy(HyperCPU::bit_cast<std::uint8_t*>(xsp) + offset, op1.ptr<std::uint8_t>() + offset, 2);
    break;
  }
  case Mode::b32: {
    std::int32_t offset;
    std::memcpy(&offset, xfst, 4);
    std::memcpy(HyperCPU::bit_cast<std::uint8_t*>(xsp) + offset, op1.ptr<std::uint8_t>() + offset, 4);
    break;
  }
  case Mode::b64: {
    std::int64_t offset;
    std::memcpy(&offset, xfst, 8);
    std::memcpy(HyperCPU::bit_cast<std::uint8_t*>(xsp) + offset, op1.ptr<std::uint8_t>() + offset, 8);
    break;
  }
  }
}