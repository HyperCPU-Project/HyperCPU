#include "Emulator/Core/CPU/ALU.hpp"
#include "Emulator/Core/CPU/CPU.hpp"

#include "Emulator/Misc/bit_cast.hpp"

class HyperCPU::CPU::CPU_InstrImpl {
public:
  constexpr CPU_InstrImpl() { }

  /* R_R implementation */
  template<typename T1, typename T2, typename T3 = std::int8_t>
  static constexpr T3 __hcpu_cmp_rr_impl(HyperCPU::OperandContainer& op1, HyperCPU::OperandContainer& op2, CPU& /* cpu */) {
    static_assert(std::is_same_v<T1, T2>); // Locked by current CPU specification

    return HyperALU::__hcpu_cmp<T1>(
      HyperCPU::bit_cast_from<T1>(op1.ptr<T1>()),
      HyperCPU::bit_cast_from<T1>(op2.ptr<T2>())
    );
  }

  /* R_RM implementation */
  template<typename T1, typename T2, typename T3 = std::int8_t>
  static constexpr T3 __hcpu_cmp_rrm_impl(HyperCPU::OperandContainer& op1, HyperCPU::OperandContainer& op2, CPU& cpu) {
    static_assert(std::is_same_v<T2, std::uint64_t>); // Locked by current CPU specification

    std::uint64_t ptr;
    std::memcpy(&ptr, op2.ptr<void>(), sizeof(ptr));

    return HyperALU::__hcpu_cmp<T1>(
      HyperCPU::bit_cast_from<T1>(op1.ptr<T1>()),
      cpu.mem_controller->Read<T1>(ptr)
    );
  }

  /* R_M implementation */
  template<typename T1, typename T2, typename T3 = std::int8_t>
  static constexpr T3 __hcpu_cmp_rm_impl(HyperCPU::OperandContainer& op1, HyperCPU::OperandContainer& op2, CPU& cpu) {
    static_assert(std::is_same_v<T2, std::uint64_t>); // Locked by current CPU specification

    return HyperALU::__hcpu_cmp<T1>(
      HyperCPU::bit_cast_from<T1>(op1.ptr<T1>()),
      cpu.mem_controller->Read<T1>(op2)
    );
  }

  /* R_IMM implementation */
  template<typename T1, typename T2, typename T3 = std::int8_t>
  static constexpr T3 __hcpu_cmp_rimm_impl(HyperCPU::OperandContainer& op1, HyperCPU::OperandContainer& op2, CPU& /* cpu */) {
    static_assert(std::is_same_v<T1, T2>); // Locked by current CPU specification

    return HyperALU::__hcpu_cmp<T1>(
      HyperCPU::bit_cast_from<T1>(op1.ptr<T1>()),
      HyperCPU::bit_cast<T1>(op2)
    );
  }

  /* RM_M implementation */
  template<typename T1, typename T2, typename T3 = std::int8_t>
  static constexpr T3 __hcpu_cmp_rmm_impl(HyperCPU::OperandContainer& op1, HyperCPU::OperandContainer& op2, CPU& cpu) {
    static_assert(std::is_same_v<T1, T2>); // Locked by current CPU specification

    return HyperALU::__hcpu_cmp<T1>(
      cpu.mem_controller->Read<T1>(op1.deref<std::uint64_t>()),
      cpu.mem_controller->Read<T1>(HyperCPU::bit_cast<T2>(op2))
    );
  }

  /* RM_R implementation */
  template<typename T1, typename T2, typename T3 = std::int8_t>
  static constexpr T3 __hcpu_cmp_rmr_impl(HyperCPU::OperandContainer& op1, HyperCPU::OperandContainer& op2, CPU& cpu) {
    static_assert(std::is_same_v<T1, std::uint64_t>); // Locked by current CPU specification

    return HyperALU::__hcpu_cmp<T2>(
      cpu.mem_controller->Read<T2>(op1.deref<T1>()),
      op2.deref<T2>()
    );
  }

  /* RM_IMM implementation */
  template<typename T1, typename T2, typename T3 = std::int8_t>
  static constexpr T3 __hcpu_cmp_rmimm_impl(HyperCPU::OperandContainer& op1, HyperCPU::OperandContainer& op2, CPU& cpu) {
    static_assert(std::is_same_v<T1, std::uint64_t>); // Locked by current CPU specification

    return HyperALU::__hcpu_cmp<T2>(
      cpu.mem_controller->Read<T2>(op1.deref<T1>()),
      HyperCPU::bit_cast<T2>(op2)
    );
  }

  /* M_R implementation */
  template<typename T1, typename T2, typename T3 = std::int8_t>
  static constexpr T3 __hcpu_cmp_mr_impl(HyperCPU::OperandContainer& op1, HyperCPU::OperandContainer& op2, CPU& cpu) {
    static_assert(std::is_same_v<T1, std::uint64_t>); // Locked by current CPU specification

    return HyperALU::__hcpu_cmp<T2>(
      cpu.mem_controller->Read<T2>(HyperCPU::bit_cast<T1>(op1)),
      op2.deref<T2>()
    );
  }
};

void HyperCPU::CPU::ExecCMP(const IInstruction& instr, OperandContainer op1, OperandContainer op2) {
  CPU_InstrImpl impl;
  std::int8_t res = 0;

  switch (instr.m_op_types) {
  case OperandTypes::R_R: {
    switch (instr.m_opcode_mode.md1) {
    case Mode::b8:
      res = impl.__hcpu_cmp_rr_impl<std::uint8_t, std::uint8_t>(op1, op2, *this);
      break;

    case Mode::b16:
      res = impl.__hcpu_cmp_rr_impl<std::uint16_t, std::uint16_t>(op1, op2, *this);
      break;

    case Mode::b32:
      res = impl.__hcpu_cmp_rr_impl<std::uint32_t, std::uint32_t>(op1, op2, *this);
      break;

    case Mode::b64:
      res = impl.__hcpu_cmp_rr_impl<std::uint64_t, std::uint64_t>(op1, op2, *this);
      break;
    }
    break;
  }

  case OperandTypes::R_RM: {
    switch (instr.m_opcode_mode.md1) {
    case Mode::b8:
      res = impl.__hcpu_cmp_rrm_impl<std::uint8_t, std::uint64_t>(op1, op2, *this);
      break;

    case Mode::b16:
      res = impl.__hcpu_cmp_rrm_impl<std::uint16_t, std::uint64_t>(op1, op2, *this);
      break;

    case Mode::b32:
      res = impl.__hcpu_cmp_rrm_impl<std::uint32_t, std::uint64_t>(op1, op2, *this);
      break;

    case Mode::b64:
      res = impl.__hcpu_cmp_rrm_impl<std::uint64_t, std::uint64_t>(op1, op2, *this);
      break;
    }
    break;
  }

  case OperandTypes::R_M: {
    switch (instr.m_opcode_mode.md1) {
    case Mode::b8:
      res = impl.__hcpu_cmp_rrm_impl<std::uint8_t, std::uint64_t>(op1, op2, *this);
      break;

    case Mode::b16:
      res = impl.__hcpu_cmp_rrm_impl<std::uint16_t, std::uint64_t>(op1, op2, *this);
      break;

    case Mode::b32:
      res = impl.__hcpu_cmp_rrm_impl<std::uint32_t, std::uint64_t>(op1, op2, *this);
      break;

    case Mode::b64:
      res = impl.__hcpu_cmp_rrm_impl<std::uint64_t, std::uint64_t>(op1, op2, *this);
      break;
    }
    break;
  }

  case OperandTypes::R_IMM: {
    switch (instr.m_opcode_mode.md1) {
    case Mode::b8:
      res = impl.__hcpu_cmp_rimm_impl<std::uint8_t, std::uint8_t>(op1, op2, *this);
      break;

    case Mode::b16:
      res = impl.__hcpu_cmp_rimm_impl<std::uint16_t, std::uint16_t>(op1, op2, *this);
      break;

    case Mode::b32:
      res = impl.__hcpu_cmp_rimm_impl<std::uint32_t, std::uint32_t>(op1, op2, *this);
      break;

    case Mode::b64:
      res = impl.__hcpu_cmp_rimm_impl<std::uint64_t, std::uint64_t>(op1, op2, *this);
      break;
    }
    break;
  }

  case OperandTypes::RM_M: {
    switch (instr.m_opcode_mode.md1) {
    case Mode::b8:
      res = impl.__hcpu_cmp_rmm_impl<std::uint8_t, std::uint8_t>(op1, op2, *this);
      break;

    case Mode::b16:
      res = impl.__hcpu_cmp_rmm_impl<std::uint16_t, std::uint16_t>(op1, op2, *this);
      break;

    case Mode::b32:
      res = impl.__hcpu_cmp_rmm_impl<std::uint32_t, std::uint32_t>(op1, op2, *this);
      break;

    case Mode::b64:
      res = impl.__hcpu_cmp_rmm_impl<std::uint64_t, std::uint64_t>(op1, op2, *this);
      break;
    }
    break;
  }

  case OperandTypes::RM_R: {
    switch (instr.m_opcode_mode.md1) {
    case Mode::b8:
      res = impl.__hcpu_cmp_rmr_impl<std::uint64_t, std::uint8_t>(op1, op2, *this);
      break;

    case Mode::b16:
      res = impl.__hcpu_cmp_rmr_impl<std::uint64_t, std::uint16_t>(op1, op2, *this);
      break;

    case Mode::b32:
      res = impl.__hcpu_cmp_rmr_impl<std::uint64_t, std::uint32_t>(op1, op2, *this);
      break;

    case Mode::b64:
      res = impl.__hcpu_cmp_rmr_impl<std::uint64_t, std::uint64_t>(op1, op2, *this);
      break;
    }
    break;
  }

  case OperandTypes::RM_IMM: {
    switch (instr.m_opcode_mode.md1) {
    case Mode::b8:
      res = impl.__hcpu_cmp_rmimm_impl<std::uint64_t, std::uint8_t>(op1, op2, *this);
      break;

    case Mode::b16:
      res = impl.__hcpu_cmp_rmimm_impl<std::uint64_t, std::uint16_t>(op1, op2, *this);
      break;

    case Mode::b32:
      res = impl.__hcpu_cmp_rmimm_impl<std::uint64_t, std::uint32_t>(op1, op2, *this);
      break;

    case Mode::b64:
      res = impl.__hcpu_cmp_rmimm_impl<std::uint64_t, std::uint64_t>(op1, op2, *this);
      break;
    }
    break;
  }

  case OperandTypes::M_R: {
    switch (instr.m_opcode_mode.md1) {
    case Mode::b8:
      res = impl.__hcpu_cmp_mr_impl<std::uint64_t, std::uint8_t>(op1, op2, *this);
      break;

    case Mode::b16:
      res = impl.__hcpu_cmp_mr_impl<std::uint64_t, std::uint16_t>(op1, op2, *this);
      break;

    case Mode::b32:
      res = impl.__hcpu_cmp_mr_impl<std::uint64_t, std::uint32_t>(op1, op2, *this);
      break;

    case Mode::b64:
      res = impl.__hcpu_cmp_mr_impl<std::uint64_t, std::uint64_t>(op1, op2, *this);
      break;
    }
    break;
  }

  default:
    break;
  }

  switch (res) {
  case -1:
    zrf = 0;
    crf = 1;
    break;
  case 0:
    zrf = 1;
    crf = 0;
    break;
  case 1:
    zrf = 0;
    crf = 0;
    break;
  }
}
