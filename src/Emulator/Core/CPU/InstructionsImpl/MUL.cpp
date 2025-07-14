#include "Emulator/Core/CPU/ALU.hpp"
#include "Emulator/Core/CPU/CPU.hpp"

#include "Emulator/Misc/overflow.hpp"

class HyperCPU::CPU::CPU_InstrImpl {
public:
  constexpr CPU_InstrImpl() { }

  /* R_R implementation */
  template<typename T1, typename T2>
  static constexpr void __hcpu_mul_rr_impl(HyperCPU::OperandContainer& op1, HyperCPU::OperandContainer& op2, CPU& cpu) {
    static_assert(std::is_same_v<T1, T2>); // Locked by current CPU specification

    cpu.ovf = MultiplicationWillOverflow(op1.deref<T1>(), op2.deref<T2>());
    op1.deref<T1>() = HyperALU::__hcpu_mul<T1>(op1.deref<T1>(), HyperCPU::bit_cast_from<T1>(op2.ptr<T2>()));
  }

  /* R_RM implementation */
  template<typename T1, typename T2>
  static constexpr void __hcpu_mul_rrm_impl(HyperCPU::OperandContainer& op1, HyperCPU::OperandContainer& op2, CPU& cpu) {
    static_assert(std::is_same_v<T2, std::uint64_t>); // Locked by current CPU specification

    T1 val = cpu.mem_controller->Read<T1>(HyperCPU::bit_cast_from<T2>(op2.ptr<T2>()));
    cpu.ovf = MultiplicationWillOverflow(op1.deref<T1>(), val);

    op1.deref<T1>() = HyperALU::__hcpu_mul<T1>(op1.deref<T1>(), val);
  }

  /* R_M implementation */
  template<typename T1, typename T2>
  static constexpr void __hcpu_mul_rm_impl(HyperCPU::OperandContainer& op1, HyperCPU::OperandContainer& op2, CPU& cpu) {
    static_assert(std::is_same_v<T2, std::uint64_t>); // Locked by current CPU specification

    T1 val = cpu.mem_controller->Read<T1>(HyperCPU::bit_cast<T2>(op2));
    cpu.ovf = MultiplicationWillOverflow(op1.deref<T1>(), val);

    op1.deref<T1>() = HyperALU::__hcpu_mul<T1>(op1.deref<T1>(), val);
  }

  /* R_IMM implementation */
  template<typename T1, typename T2>
  static constexpr void __hcpu_mul_rimm_impl(HyperCPU::OperandContainer& op1, HyperCPU::OperandContainer& op2, CPU& cpu) {
    static_assert(std::is_same_v<T1, T2>); // Locked by current CPU specification

    T1 val = HyperCPU::bit_cast<T1>(op2);
    cpu.ovf = MultiplicationWillOverflow(op1.deref<T1>(), val);

    op1.deref<T1>() = HyperALU::__hcpu_mul<T1>(op1.deref<T1>(), val);
  }
};

void HyperCPU::CPU::ExecMUL(const IInstruction& instr, OperandContainer op1, OperandContainer op2) {
  CPU_InstrImpl impl;

  switch (instr.m_op_types) {
  case OperandTypes::R_R: {
    switch (instr.m_opcode_mode) {
    case Mode::b8:
      CPU_InstrImpl::__hcpu_mul_rr_impl<std::uint8_t, std::uint8_t>(op1, op2, *this);
      break;

    case Mode::b16:
      CPU_InstrImpl::__hcpu_mul_rr_impl<std::uint16_t, std::uint16_t>(op1, op2, *this);
      break;

    case Mode::b32:
      CPU_InstrImpl::__hcpu_mul_rr_impl<std::uint32_t, std::uint32_t>(op1, op2, *this);
      break;

    case Mode::b64:
      CPU_InstrImpl::__hcpu_mul_rr_impl<std::uint64_t, std::uint64_t>(op1, op2, *this);
      break;
    }
    break;
  }

  case OperandTypes::R_RM: {
    switch (instr.m_opcode_mode) {
    case Mode::b8:
      CPU_InstrImpl::__hcpu_mul_rrm_impl<std::uint8_t, std::uint8_t>(op1, op2, *this);
      break;

    case Mode::b16:
      CPU_InstrImpl::__hcpu_mul_rrm_impl<std::uint16_t, std::uint16_t>(op1, op2, *this);
      break;

    case Mode::b32:
      CPU_InstrImpl::__hcpu_mul_rrm_impl<std::uint32_t, std::uint32_t>(op1, op2, *this);
      break;

    case Mode::b64:
      CPU_InstrImpl::__hcpu_mul_rrm_impl<std::uint64_t, std::uint64_t>(op1, op2, *this);
      break;
    }
    break;
  }

  case OperandTypes::R_M: {
    switch (instr.m_opcode_mode) {
    case Mode::b8:
      CPU_InstrImpl::__hcpu_mul_rm_impl<std::uint8_t, std::uint8_t>(op1, op2, *this);
      break;

    case Mode::b16:
      CPU_InstrImpl::__hcpu_mul_rm_impl<std::uint16_t, std::uint16_t>(op1, op2, *this);
      break;

    case Mode::b32:
      CPU_InstrImpl::__hcpu_mul_rm_impl<std::uint32_t, std::uint32_t>(op1, op2, *this);
      break;

    case Mode::b64:
      CPU_InstrImpl::__hcpu_mul_rm_impl<std::uint64_t, std::uint64_t>(op1, op2, *this);
      break;
    }
    break;
  }

  case OperandTypes::R_IMM: {
    switch (instr.m_opcode_mode) {
    case Mode::b8:
      CPU_InstrImpl::__hcpu_mul_rimm_impl<std::uint8_t, std::uint8_t>(op1, op2, *this);
      break;

    case Mode::b16:
      CPU_InstrImpl::__hcpu_mul_rimm_impl<std::uint16_t, std::uint16_t>(op1, op2, *this);
      break;

    case Mode::b32:
      CPU_InstrImpl::__hcpu_mul_rimm_impl<std::uint32_t, std::uint32_t>(op1, op2, *this);
      break;

    case Mode::b64:
      CPU_InstrImpl::__hcpu_mul_rimm_impl<std::uint64_t, std::uint64_t>(op1, op2, *this);
      break;
    }
    break;
  }

  default:
    break;
  }
}
