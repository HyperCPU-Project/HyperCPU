#include "Emulator/Core/CPU/CPU.hpp"

#include "Emulator/Misc/byteswap.hpp"

void HyperCPU::CPU::ExecBSWAP(const IInstruction& instr, OperandContainer op1, OperandContainer /* op2 */) {
  switch (instr.m_opcode_mode.md1) {
  case Mode::b8:
    break;

  case Mode::b16: {
    auto& dst = op1.deref<std::uint16_t>();
    dst = HyperCPU::byteswap(op1.deref<std::uint16_t>());
    break;
  }

  case Mode::b32: {
    auto& dst = op1.deref<std::uint32_t>();
    dst = HyperCPU::byteswap(op1.deref<std::uint32_t>());
    break;
  }

  case Mode::b64: {
    auto& dst = op1.deref<std::uint64_t>();
    dst = HyperCPU::byteswap(op1.deref<std::uint64_t>());
    break;
  }
  }
}
