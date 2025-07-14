#include "Emulator/Core/CPU/ALU.hpp"
#include "Emulator/Core/CPU/CPU.hpp"

class HyperCPU::CPU::CPU_InstrImpl {
  constexpr CPU_InstrImpl() { }

  template<typename T1, typename T2>
  static constexpr void __hcpu_stdsb_rimm_impl(HyperCPU::OperandContainer& op1, HyperCPU::OperandContainer& op2, CPU& cpu) {
    cpu.mem_controller->Load<T1>(cpu.xbp + HyperCPU::bit_cast<T2>(op2), op1.deref<T1>());
  }
};

template<typename T1, typename TImpl>
[[gnu::always_inline]]
void ResolveOP2Mode(HyperCPU::Mode md2, HyperCPU::OperandContainer& op1, HyperCPU::OperandContainer& op2, HyperCPU::CPU& cpu) {
  TImpl impl;

  switch (md2) {
  case HyperCPU::Mode::b8:  CPU_InstrImpl::template __hcpu_stdsb_rimm_impl<T1, std::int8_t>(op1, op2, cpu);  break;
  case HyperCPU::Mode::b16: CPU_InstrImpl::template __hcpu_stdsb_rimm_impl<T1, std::int16_t>(op1, op2, cpu); break;
  case HyperCPU::Mode::b32: CPU_InstrImpl::template __hcpu_stdsb_rimm_impl<T1, std::int32_t>(op1, op2, cpu); break;
  case HyperCPU::Mode::b64: CPU_InstrImpl::template __hcpu_stdsb_rimm_impl<T1, std::int64_t>(op1, op2, cpu); break;
  default: std::abort();
  }
}

void HyperCPU::CPU::ExecSTDSB(const IInstruction& instr, OperandContainer op1, OperandContainer op2) {
  switch (instr.m_op_types) {
  case OperandTypes::R_IMM: {
    switch (instr.m_opcode_mode.md1) {
    case Mode::b8:
      ResolveOP2Mode<std::uint8_t, CPU_InstrImpl>(instr.m_opcode_mode.md2, op1, op2, *this);
      break;

    case Mode::b16:
      ResolveOP2Mode<std::uint16_t, CPU_InstrImpl>(instr.m_opcode_mode.md2, op1, op2, *this);
      break;

    case Mode::b32:
      ResolveOP2Mode<std::uint32_t, CPU_InstrImpl>(instr.m_opcode_mode.md2, op1, op2, *this);
      break;

    case Mode::b64:
      ResolveOP2Mode<std::uint64_t, CPU_InstrImpl>(instr.m_opcode_mode.md2, op1, op2, *this);
      break;
    }
    break;
  }

  default:
    break;
  }
}
