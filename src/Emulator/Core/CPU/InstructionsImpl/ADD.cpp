#include "Common/LanguageSpec/Flags.hpp"
#include "Emulator/Core/CPU/ALU.hpp"
#include "Emulator/Core/CPU/CPU.hpp"

#include "Emulator/Core/CPU/Decoders/StdDecoder.hpp"
#include "Emulator/Core/CPU/Interrupts/ReservedInterrupts.hpp"
#include "Emulator/Misc/smallest_type.hpp"
#include "Emulator/Misc/bit_cast.hpp"
#include "Emulator/Misc/overflow.hpp"


class HyperCPU::CPU::CPU_InstrImpl {
public:
  constexpr CPU_InstrImpl() { }

  /* R_R implementation */
  template<typename T1, typename T2>
  static constexpr void __hcpu_add_rr_impl(HyperCPU::OperandContainer& op1, HyperCPU::OperandContainer& op2, CPU& cpu) {
    static_assert(std::is_same_v<T1, T2>); // Locked by current CPU specification

    cpu.ovf = AdditionWillOverflow(op1.deref<T1>(), op2.deref<T2>());
    op1.deref<T1>() = HyperALU::__hcpu_add(op1.deref<T1>(), HyperCPU::bit_cast_from<T2>(op2.ptr<T2>()));
  }

  /* R_RM implementation */
  template<typename T1, typename T2>
  static constexpr void __hcpu_add_rrm_impl(HyperCPU::OperandContainer& op1, HyperCPU::OperandContainer& op2, CPU& cpu) {
    static_assert(std::is_same_v<T2, std::uint64_t>); // Locked by current CPU specification

    T2 ptr = HyperCPU::bit_cast_from<T2>(op2.ptr<T2>());
    T1 val = cpu.mem_controller->Read<T1>(ptr);
    cpu.ovf = AdditionWillOverflow(op1.deref<T1>(), val);

    op1.deref<T1>() = HyperALU::__hcpu_add(op1.deref<T1>(), val);
  }

  /* R_M implementation */
  template<typename T1, typename T2>
  static constexpr void __hcpu_add_rm_impl(HyperCPU::OperandContainer& op1, HyperCPU::OperandContainer& op2, CPU& cpu) {
    static_assert(std::is_same_v<T2, std::uint64_t>); // Locked by current CPU specification

    T2 ptr = HyperCPU::bit_cast<T2>(op2);
    T1 val = cpu.mem_controller->Read<T1>(ptr);
    cpu.ovf = AdditionWillOverflow(op1.deref<T1>(), val);

    op1.deref<T1>() = HyperALU::__hcpu_add(op1.deref<T1>(), val);
  }

  /* R_IMM implementation */
  template<typename T1, typename T2>
  static constexpr void __hcpu_add_rimm_impl(HyperCPU::OperandContainer& op1, HyperCPU::OperandContainer& op2, CPU& cpu) {
    static_assert(std::is_same_v<T1, T2>); // Locked by current CPU specification

    T1 val = HyperCPU::bit_cast<T1>(op2);
    cpu.ovf = AdditionWillOverflow(op1.deref<T1>(), val);

    op1.deref<T1>() = HyperALU::__hcpu_add(op1.deref<T1>(), val);
  }
};

void HyperCPU::CPU::ExecADD(const IInstruction& instr, OperandContainer op1, OperandContainer op2) {
  CPU_InstrImpl impl;

  switch (instr.m_op_types) {
  case OperandTypes::R_R: {
    if (instr.m_opcode_mode.md1 != instr.m_opcode_mode.md2) {
      TriggerInterrupt(HyperCPU::cpu_exceptions::IO);
      return;
    }

    /* ADD R_R does not support different register sizes - we can call implementation directly */
    switch (instr.m_opcode_mode.md1) {
    case Mode::b8:
      impl.__hcpu_add_rr_impl<std::uint8_t, std::uint8_t>(op1, op2, *this);
      break;
    case Mode::b16:
      impl.__hcpu_add_rr_impl<std::uint16_t, std::uint16_t>(op1, op2, *this);
      break;
    case Mode::b32:
      impl.__hcpu_add_rr_impl<std::uint32_t, std::uint32_t>(op1, op2, *this);
      break;
    case Mode::b64:
      impl.__hcpu_add_rr_impl<std::uint64_t, std::uint64_t>(op1, op2, *this);
      break;
    }
    break;
  }

  case OperandTypes::R_RM: {
    if (instr.m_opcode_mode.md2 != Mode::b64) {
      TriggerInterrupt(HyperCPU::cpu_exceptions::IO);
      return;
    }

    /* ADD R_RM does not support different register sizes - we can call implementation directly */
    switch (instr.m_opcode_mode.md1) {
    case Mode::b8:
      impl.__hcpu_add_rrm_impl<std::uint8_t, std::uint64_t>(op1, op2, *this);
      break;
    case Mode::b16:
      impl.__hcpu_add_rrm_impl<std::uint16_t, std::uint64_t>(op1, op2, *this);
      break;
    case Mode::b32:
      impl.__hcpu_add_rrm_impl<std::uint32_t, std::uint64_t>(op1, op2, *this);
      break;
    case Mode::b64:
      impl.__hcpu_add_rrm_impl<std::uint64_t, std::uint64_t>(op1, op2, *this);
      break;
    }
    break;
  }

  case OperandTypes::R_M: {
    if (instr.m_opcode_mode.md2 != Mode::b64) {
      TriggerInterrupt(HyperCPU::cpu_exceptions::IO);
      return;
    }

    /* ADD R_RM does not support different register sizes - we can call implementation directly */
    switch (instr.m_opcode_mode.md1) {
    case Mode::b8:
      impl.__hcpu_add_rm_impl<std::uint8_t, std::uint64_t>(op1, op2, *this);
      break;
    case Mode::b16:
      impl.__hcpu_add_rm_impl<std::uint16_t, std::uint64_t>(op1, op2, *this);
      break;
    case Mode::b32:
      impl.__hcpu_add_rm_impl<std::uint32_t, std::uint64_t>(op1, op2, *this);
      break;
    case Mode::b64:
      impl.__hcpu_add_rm_impl<std::uint64_t, std::uint64_t>(op1, op2, *this);
      break;
    }
    break;
  }

  case OperandTypes::R_IMM: {
    if (instr.m_opcode_mode.md2 != instr.m_opcode_mode.md1) {
      TriggerInterrupt(HyperCPU::cpu_exceptions::IO);
      return;
    }

    /* ADD R_RM does not support different register sizes - we can call implementation directly */
    switch (instr.m_opcode_mode.md1) {
    case Mode::b8:
      impl.__hcpu_add_rimm_impl<std::uint8_t, std::uint8_t>(op1, op2, *this);
      break;
    case Mode::b16:
      impl.__hcpu_add_rimm_impl<std::uint16_t, std::uint16_t>(op1, op2, *this);
      break;
    case Mode::b32:
      impl.__hcpu_add_rimm_impl<std::uint32_t, std::uint32_t>(op1, op2, *this);
      break;
    case Mode::b64:
      impl.__hcpu_add_rimm_impl<std::uint64_t, std::uint64_t>(op1, op2, *this);
      break;
    }
    break;
  }

  default:
    break;
  }
}
