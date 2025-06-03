#include "Emulator/Core/CPU/ALU.hpp"
#include "Emulator/Core/CPU/CPU.hpp"

#include "Emulator/Misc/bit_cast.hpp"

class HyperCPU::CPU::CPU_InstrImpl {
public:
  constexpr CPU_InstrImpl() { }

  /* R_R implementation */
  template<typename T1, typename T2, typename T3>
  static constexpr T3 __hcpu_cmp_rr_impl(HyperCPU::OperandContainer& op1, HyperCPU::OperandContainer& op2, CPU& cpu) {
    static_assert(std::is_same_v<T1, T2>); // Locked by current CPU specification

    return HyperALU::__hcpu_cmp(
      HyperCPU::bit_cast_from<T1>(op1.ptr<T1>()),
      HyperCPU::bit_cast_from<T2>(op2.ptr<T2>())
    );
  }

  /* R_RM implementation */
  template<typename T1, typename T2, typename T3>
  static constexpr T3 __hcpu_cmp_rrm_impl(HyperCPU::OperandContainer& op1, HyperCPU::OperandContainer& op2, CPU& cpu) {
    static_assert(std::is_same_v<T2, std::uint64_t>); // Locked by current CPU specification

    return HyperALU::__hcpu_cmp(
      HyperCPU::bit_cast_from<T1>(op1.ptr<T1>()),
      HyperCPU::bit_cast_from<T2>(op2.ptr<T2>())
    );
  }

  /* R_M implementation */
  template<typename T1, typename T2, typename T3>
  static constexpr T3 __hcpu_cmp_rm_impl(HyperCPU::OperandContainer& op1, HyperCPU::OperandContainer& op2, CPU& cpu) {
    static_assert(std::is_same_v<T2, std::uint64_t>); // Locked by current CPU specification

    T2 ptr = HyperCPU::bit_cast<T2>(op2);
    T1 val = cpu.mem_controller->Read8(ptr);

    op1.deref<T1>() = HyperALU::__hcpu_and(op1.deref<T1>(), val);
  }

  /* R_IMM implementation */
  template<typename T1, typename T2, typename T3>
  static constexpr T3 __hcpu_cmp_rimm_impl(HyperCPU::OperandContainer& op1, HyperCPU::OperandContainer& op2, CPU& cpu) {
    static_assert(std::is_same_v<T1, T2>); // Locked by current CPU specification

    T1 val = HyperCPU::bit_cast<T1>(op2);
    
    op1.deref<T1>() = HyperALU::__hcpu_and(op1.deref<T1>(), val);
  }
};

void HyperCPU::CPU::ExecCMP(const IInstruction& instr, OperandContainer op1, OperandContainer op2) {
  std::int8_t res = 0;
  switch (instr.m_op_types) {
  case OperandTypes::R_R: {
    switch (instr.m_opcode_mode) {
    case Mode::b8:
      res = StdALU::__hcpu_cmp(HyperCPU::bit_cast_from<std::uint8_t>(op1.ptr<std::uint8_t>()), HyperCPU::bit_cast_from<std::uint8_t>(op2.ptr<std::uint8_t>()));
      break;

    case Mode::b16:
      res = StdALU::__hcpu_cmp(HyperCPU::bit_cast_from<std::uint16_t>(op1.ptr<std::uint16_t>()), HyperCPU::bit_cast_from<std::uint16_t>(op2.ptr<std::uint16_t>()));
      break;

    case Mode::b32:
      res = StdALU::__hcpu_cmp(HyperCPU::bit_cast_from<std::uint32_t>(op1.ptr<std::uint32_t>()), HyperCPU::bit_cast_from<std::uint32_t>(op2.ptr<std::uint32_t>()));
      break;

    case Mode::b64:
      res = StdALU::__hcpu_cmp(HyperCPU::bit_cast_from<std::uint64_t>(op1.ptr<std::uint64_t>()), HyperCPU::bit_cast_from<std::uint64_t>(op2.ptr<std::uint64_t>()));
      break;
    }
    break;
  }

  case OperandTypes::R_RM: {
    std::uint64_t ptr;
    std::memcpy(&ptr, op2.ptr<void>(), 8);

    switch (instr.m_opcode_mode) {
    case Mode::b8:
      res = StdALU::__hcpu_cmp(HyperCPU::bit_cast_from<std::uint8_t>(op1.ptr<std::uint8_t>()), mem_controller->Read8(ptr));
      break;

    case Mode::b16:
      res = StdALU::__hcpu_cmp(HyperCPU::bit_cast_from<std::uint16_t>(op1.ptr<std::uint16_t>()), mem_controller->Read16(ptr));
      break;

    case Mode::b32:
      res = StdALU::__hcpu_cmp(HyperCPU::bit_cast_from<std::uint32_t>(op1.ptr<std::uint32_t>()), mem_controller->Read32(ptr));
      break;

    case Mode::b64:
      res = StdALU::__hcpu_cmp(HyperCPU::bit_cast_from<std::uint64_t>(op1.ptr<std::uint64_t>()), mem_controller->Read64(ptr));
      break;
    }
    break;
  }

  case OperandTypes::R_M: {
    std::uint64_t ptr = op2;

    switch (instr.m_opcode_mode) {
    case Mode::b8:
      res = StdALU::__hcpu_cmp(HyperCPU::bit_cast_from<std::uint8_t>(op1.ptr<std::uint8_t>()), mem_controller->Read8(ptr));
      break;

    case Mode::b16:
      res = StdALU::__hcpu_cmp(HyperCPU::bit_cast_from<std::uint16_t>(op1.ptr<std::uint16_t>()), mem_controller->Read16(ptr));
      break;

    case Mode::b32:
      res = StdALU::__hcpu_cmp(HyperCPU::bit_cast_from<std::uint32_t>(op1.ptr<std::uint32_t>()), mem_controller->Read32(ptr));
      break;

    case Mode::b64:
      res = StdALU::__hcpu_cmp(HyperCPU::bit_cast_from<std::uint64_t>(op1.ptr<std::uint64_t>()), mem_controller->Read64(ptr));
      break;
    }
    break;
  }

  case OperandTypes::R_IMM: {
    switch (instr.m_opcode_mode) {
    case Mode::b8:
      res = StdALU::__hcpu_cmp(HyperCPU::bit_cast_from<std::uint8_t>(op1.ptr<std::uint8_t>()), HyperCPU::bit_cast<std::uint8_t>(op2));
      break;

    case Mode::b16:
      res = StdALU::__hcpu_cmp(HyperCPU::bit_cast_from<std::uint16_t>(op1.ptr<std::uint16_t>()), HyperCPU::bit_cast<std::uint16_t>(op2));
      break;

    case Mode::b32:
      res = StdALU::__hcpu_cmp(HyperCPU::bit_cast_from<std::uint32_t>(op1.ptr<std::uint32_t>()), HyperCPU::bit_cast<std::uint32_t>(op2));
      break;

    case Mode::b64:
      res = StdALU::__hcpu_cmp(HyperCPU::bit_cast_from<std::uint64_t>(op1.ptr<std::uint64_t>()), HyperCPU::bit_cast<std::uint64_t>(op2));
      break;
    }
    break;
  }

  case OperandTypes::RM_M: {
    std::uint64_t ptr1, ptr2 = 0;
    std::memcpy(&ptr1, op1.ptr<void>(), 8);
    ptr2 = HyperCPU::bit_cast<std::uint64_t>(op2);

    switch (instr.m_opcode_mode) {
    case Mode::b8:
      res = StdALU::__hcpu_cmp(mem_controller->Read8(ptr1), mem_controller->Read8(ptr2));
      break;

    case Mode::b16:
      res = StdALU::__hcpu_cmp(mem_controller->Read16(ptr1), mem_controller->Read16(ptr2));
      break;

    case Mode::b32:
      res = StdALU::__hcpu_cmp(mem_controller->Read32(ptr1), mem_controller->Read32(ptr2));
      break;

    case Mode::b64:
      res = StdALU::__hcpu_cmp(mem_controller->Read64(ptr1), mem_controller->Read64(ptr2));
      break;
    }
    break;
  }

  case OperandTypes::RM_R: {
    std::uint64_t ptr = op1.deref<std::uint64_t>();

    switch (instr.m_opcode_mode) {
    case Mode::b8:
      res = StdALU::__hcpu_cmp(mem_controller->Read8(ptr), HyperCPU::bit_cast_from<std::uint8_t>(op2.ptr<std::uint8_t>()));
      break;

    case Mode::b16:
      res = StdALU::__hcpu_cmp(mem_controller->Read16(ptr), HyperCPU::bit_cast_from<std::uint16_t>(op2.ptr<std::uint16_t>()));
      break;

    case Mode::b32:
      res = StdALU::__hcpu_cmp(mem_controller->Read32(ptr), HyperCPU::bit_cast_from<std::uint32_t>(op2.ptr<std::uint32_t>()));
      break;

    case Mode::b64:
      res = StdALU::__hcpu_cmp(mem_controller->Read64(ptr), HyperCPU::bit_cast_from<std::uint64_t>(op2.ptr<std::uint64_t>()));
      break;
    }
    break;
  }

  case OperandTypes::RM_IMM: {
    std::uint64_t ptr = op1.deref<std::uint64_t>();

    switch (instr.m_opcode_mode) {
    case Mode::b8:
      res = StdALU::__hcpu_cmp(mem_controller->Read8(ptr), HyperCPU::bit_cast<std::uint8_t>(op2));
      break;

    case Mode::b16:
      res = StdALU::__hcpu_cmp(mem_controller->Read16(ptr), HyperCPU::bit_cast<std::uint16_t>(op2));
      break;

    case Mode::b32:
      res = StdALU::__hcpu_cmp(mem_controller->Read32(ptr), HyperCPU::bit_cast<std::uint32_t>(op2));
      break;

    case Mode::b64:
      res = StdALU::__hcpu_cmp(mem_controller->Read64(ptr), HyperCPU::bit_cast<std::uint64_t>(op2));
      break;
    }
    break;
  }

  case OperandTypes::M_R: {
    std::size_t ptr = HyperCPU::bit_cast<std::size_t>(op1);

    switch (instr.m_opcode_mode) {
    case Mode::b8:
      res = StdALU::__hcpu_cmp(mem_controller->Read8(ptr), HyperCPU::bit_cast_from<std::uint8_t>(op2.ptr<std::uint8_t>()));
      break;

    case Mode::b16:
      res = StdALU::__hcpu_cmp(mem_controller->Read16(ptr), HyperCPU::bit_cast_from<std::uint16_t>(op2.ptr<std::uint16_t>()));
      break;

    case Mode::b32:
      res = StdALU::__hcpu_cmp(mem_controller->Read32(ptr), HyperCPU::bit_cast_from<std::uint32_t>(op2.ptr<std::uint32_t>()));
      break;

    case Mode::b64:
      res = StdALU::__hcpu_cmp(mem_controller->Read64(ptr), HyperCPU::bit_cast_from<std::uint64_t>(op2.ptr<std::uint64_t>()));
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
