#include "Emulator/Core/CPU/CPU.hpp"

class HyperCPU::CPU::CPU_InstrImpl {
public:
  /* R_R implementation */
  template<typename T1, typename T2>
  static constexpr void __hcpu_mov_rr_impl(HyperCPU::OperandContainer& op1, HyperCPU::OperandContainer& op2, CPU& /* cpu */) {
    static_assert(std::is_same_v<T1, T2>); // Locked by current CPU specification

    op1.deref<T1>() = op2.deref<T2>();
  }

  /* R_RM implementation */
  template<typename T1, typename T2>
  static constexpr void __hcpu_mov_rrm_impl(HyperCPU::OperandContainer& op1, HyperCPU::OperandContainer& op2, CPU& cpu) {
    static_assert(std::is_same_v<T2, std::uint64_t>); // Locked by current CPU specification

    op1.deref<T1>() = cpu.mem_controller->Read<T1>(op2.deref<T2>());
  }

  /* R_M implementation */
  template<typename T1, typename T2>
  static constexpr void __hcpu_mov_rm_impl(HyperCPU::OperandContainer& op1, HyperCPU::OperandContainer& op2, CPU& cpu) {
    static_assert(std::is_same_v<T2, std::uint64_t>); // Locked by current CPU specification

    op1.deref<T1>() = cpu.mem_controller->Read<T1>(HyperCPU::bit_cast<T2>(op2));
  }

  /* R_IMM implementation */
  template<typename T1, typename T2>
  static constexpr void __hcpu_mov_rimm_impl(HyperCPU::OperandContainer& op1, HyperCPU::OperandContainer& op2, CPU& /* cpu */) {
    static_assert(std::is_same_v<T1, T2>); // Locked by current CPU specification

    op1.deref<T1>() = HyperCPU::bit_cast<T2>(op2);
  }

  /* RM_M implementation */
  template<typename T1, typename T2>
  static constexpr void __hcpu_mov_rmm_impl(HyperCPU::OperandContainer& op1, HyperCPU::OperandContainer& op2, CPU& cpu) {
    static_assert(std::is_same_v<T1, std::uint64_t>); // Locked by current CPU specification

    cpu.mem_controller->Load(op1.deref<T1>(), cpu.mem_controller->Read<T2>(HyperCPU::bit_cast<T2>(op2)));
  }

  /* RM_R implementation */
  template<typename T1, typename T2>
  static constexpr void __hcpu_mov_rmr_impl(HyperCPU::OperandContainer& op1, HyperCPU::OperandContainer& op2, CPU& cpu) {
    static_assert(std::is_same_v<T1, std::uint64_t>); // Locked by current CPU specification

    cpu.mem_controller->Load(op1.deref<T1>(), op1.deref<T2>());
  }

  /* RM_IMM implementation */
  template<typename T1, typename T2>
  static constexpr void __hcpu_mov_rmimm_impl(HyperCPU::OperandContainer& op1, HyperCPU::OperandContainer& op2, CPU& cpu) {
    static_assert(std::is_same_v<T1, std::uint64_t>); // Locked by current CPU specification

    cpu.mem_controller->Load(op1.deref<T1>(), HyperCPU::bit_cast<T2>(op2));
  }

  /* M_R implementation */
  template<typename T1, typename T2>
  static constexpr void __hcpu_mov_mr_impl(HyperCPU::OperandContainer& op1, HyperCPU::OperandContainer& op2, CPU& cpu) {
    static_assert(std::is_same_v<T1, std::uint64_t>); // Locked by current CPU specification

    cpu.mem_controller->Load(HyperCPU::bit_cast<T1>(op2), op1.deref<T2>());
  }
};

void HyperCPU::CPU::ExecMOV(const IInstruction& instr, OperandContainer op1, OperandContainer op2) {
  switch (instr.m_op_types) {
  case OperandTypes::R_R: {
    switch (instr.m_opcode_mode.md1) {
    case Mode::b8:
      CPU_InstrImpl::__hcpu_mov_rr_impl<std::uint8_t, std::uint8_t>(op1, op2, *this);
      break;

    case Mode::b16:
      CPU_InstrImpl::__hcpu_mov_rr_impl<std::uint16_t, std::uint16_t>(op1, op2, *this);
      break;

    case Mode::b32:
      CPU_InstrImpl::__hcpu_mov_rr_impl<std::uint32_t, std::uint32_t>(op1, op2, *this);
      break;

    case Mode::b64:
      CPU_InstrImpl::__hcpu_mov_rr_impl<std::uint64_t, std::uint64_t>(op1, op2, *this);
      break;
    }
    break;
  }

  case OperandTypes::R_RM: {
    switch (instr.m_opcode_mode.md1) {
    case Mode::b8:
      CPU_InstrImpl::__hcpu_mov_rrm_impl<std::uint8_t, std::uint64_t>(op1, op2, *this);
      break;

    case Mode::b16:
      CPU_InstrImpl::__hcpu_mov_rrm_impl<std::uint16_t, std::uint64_t>(op1, op2, *this);
      break;

    case Mode::b32:
      CPU_InstrImpl::__hcpu_mov_rrm_impl<std::uint32_t, std::uint64_t>(op1, op2, *this);
      break;

    case Mode::b64:
      CPU_InstrImpl::__hcpu_mov_rrm_impl<std::uint64_t, std::uint64_t>(op1, op2, *this);
      break;
    }
    break;
  }

  case OperandTypes::R_M: {
    switch (instr.m_opcode_mode.md1) {
    case Mode::b8:
      CPU_InstrImpl::__hcpu_mov_rm_impl<std::uint8_t, std::uint64_t>(op1, op2, *this);
      break;

    case Mode::b16:
      CPU_InstrImpl::__hcpu_mov_rm_impl<std::uint16_t, std::uint64_t>(op1, op2, *this);
      break;

    case Mode::b32:
      CPU_InstrImpl::__hcpu_mov_rm_impl<std::uint32_t, std::uint64_t>(op1, op2, *this);
      break;

    case Mode::b64:
      CPU_InstrImpl::__hcpu_mov_rm_impl<std::uint64_t, std::uint64_t>(op1, op2, *this);
      break;
    }
    break;
  }

  case OperandTypes::R_IMM: {
    switch (instr.m_opcode_mode.md1) {
    case Mode::b8:
      CPU_InstrImpl::__hcpu_mov_rimm_impl<std::uint8_t, std::uint8_t>(op1, op2, *this);
      break;

    case Mode::b16:
      CPU_InstrImpl::__hcpu_mov_rimm_impl<std::uint16_t, std::uint16_t>(op1, op2, *this);
      break;

    case Mode::b32:
      CPU_InstrImpl::__hcpu_mov_rimm_impl<std::uint32_t, std::uint32_t>(op1, op2, *this);
      break;

    case Mode::b64:
      CPU_InstrImpl::__hcpu_mov_rimm_impl<std::uint64_t, std::uint64_t>(op1, op2, *this);
      break;
    }
    break;
  }

  case OperandTypes::RM_M: {
    switch (instr.m_opcode_mode.md1) {
    case Mode::b8:
      CPU_InstrImpl::__hcpu_mov_rmm_impl<std::uint64_t, std::uint64_t>(op1, op2, *this);
      break;

    case Mode::b16:
      CPU_InstrImpl::__hcpu_mov_rmm_impl<std::uint64_t, std::uint64_t>(op1, op2, *this);
      break;

    case Mode::b32:
      CPU_InstrImpl::__hcpu_mov_rmm_impl<std::uint64_t, std::uint64_t>(op1, op2, *this);
      break;

    case Mode::b64:
      CPU_InstrImpl::__hcpu_mov_rmm_impl<std::uint64_t, std::uint64_t>(op1, op2, *this);
      break;
    }
    break;
  }

  case OperandTypes::RM_R: {
    switch (instr.m_opcode_mode.md1) {
    case Mode::b8:
      CPU_InstrImpl::__hcpu_mov_rmr_impl<std::uint64_t, std::uint8_t>(op1, op2, *this);
      break;

    case Mode::b16:
      CPU_InstrImpl::__hcpu_mov_rmr_impl<std::uint64_t, std::uint16_t>(op1, op2, *this);
      break;

    case Mode::b32:
      CPU_InstrImpl::__hcpu_mov_rmr_impl<std::uint64_t, std::uint32_t>(op1, op2, *this);
      break;

    case Mode::b64:
      CPU_InstrImpl::__hcpu_mov_rmr_impl<std::uint64_t, std::uint64_t>(op1, op2, *this);
      break;
    }
    break;
  }

  case OperandTypes::RM_IMM: {
    switch (instr.m_opcode_mode.md1) {
    case Mode::b8:
      CPU_InstrImpl::__hcpu_mov_rmimm_impl<std::uint64_t, std::uint8_t>(op1, op2, *this);
      break;

    case Mode::b16:
      CPU_InstrImpl::__hcpu_mov_rmimm_impl<std::uint64_t, std::uint16_t>(op1, op2, *this);
      break;

    case Mode::b32:
      CPU_InstrImpl::__hcpu_mov_rmimm_impl<std::uint64_t, std::uint32_t>(op1, op2, *this);
      break;

    case Mode::b64:
      CPU_InstrImpl::__hcpu_mov_rmimm_impl<std::uint64_t, std::uint64_t>(op1, op2, *this);
      break;
    }
    break;
  }

  case OperandTypes::M_R: {
    switch (instr.m_opcode_mode.md1) {
    case Mode::b8:
      CPU_InstrImpl::__hcpu_mov_mr_impl<std::uint64_t, std::uint8_t>(op1, op2, *this);
      break;

    case Mode::b16:
      CPU_InstrImpl::__hcpu_mov_mr_impl<std::uint64_t, std::uint16_t>(op1, op2, *this);
      break;

    case Mode::b32:
      CPU_InstrImpl::__hcpu_mov_mr_impl<std::uint64_t, std::uint32_t>(op1, op2, *this);
      break;

    case Mode::b64:
      CPU_InstrImpl::__hcpu_mov_mr_impl<std::uint64_t, std::uint64_t>(op1, op2, *this);
      break;
    }
    break;
  }

  default:
    break;
  }
}
