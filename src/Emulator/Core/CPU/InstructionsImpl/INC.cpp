#include "Emulator/Core/CPU/CPU.hpp"

void HyperCPU::CPU::ExecINC(const IInstruction& instr, OperandContainer op1, OperandContainer /* op2 */) {
  switch (instr.m_opcode_mode.md1) {
  case Mode::b8: {
    auto& dst = op1.deref<std::uint8_t>();
    ++dst;
    ovf = (dst == 0);
    break;
  }

  case Mode::b16: {
    auto& dst = op1.deref<std::uint16_t>();
    ++dst;
    ovf = (dst == 0);
    break;
  }

  case Mode::b32: {
    auto& dst = op1.deref<std::uint32_t>();
    ++dst;
    ovf = (dst == 0);
    break;
  }

  case Mode::b64: {
    auto& dst = op1.deref<std::uint64_t>();
    ++dst;
    ovf = (dst == 0);
    break;
  }
  }
}
