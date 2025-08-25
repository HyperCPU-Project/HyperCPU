#include "Emulator/Core/CPU/ALU.hpp"
#include "Emulator/Core/CPU/CPU.hpp"
#include "Emulator/Core/CPU/Interrupts/ReservedInterrupts.hpp"

using namespace HyperALU;

void HyperCPU::CPU::ExecDIV(const IInstruction& instr, OperandContainer op1, OperandContainer /* op2 */) {
  if (!(*x2)) {
    TriggerInterrupt(cpu_exceptions::ZRDIV);
    return;
  }

  switch (instr.m_opcode_mode) {
  case Mode::b8: {
    auto& dst = op1.deref<std::uint8_t>();
    *x1 = __hcpu_div_remainder(dst, static_cast<std::uint8_t>(*x2));
    dst = __hcpu_div(dst, static_cast<std::uint8_t>(*x2));
    break;
  }

  case Mode::b16: {
    auto& dst = op1.deref<std::uint16_t>();
    *x1 = __hcpu_div_remainder(dst, static_cast<std::uint16_t>(*x2));
    dst = __hcpu_div(dst, static_cast<std::uint16_t>(*x2));
    break;
  }

  case Mode::b32: {
    auto& dst = op1.deref<std::uint32_t>();
    *x1 = __hcpu_div_remainder(dst, static_cast<std::uint32_t>(*x2));
    dst = __hcpu_div(dst, static_cast<std::uint32_t>(*x2));
    break;
  }

  case Mode::b64: {
    auto& dst = op1.deref<std::uint64_t>();
    *x1 = __hcpu_div_remainder(dst, static_cast<std::uint64_t>(*x2));
    dst = __hcpu_div(dst, static_cast<std::uint64_t>(*x2));
    break;
  }
  }
}
