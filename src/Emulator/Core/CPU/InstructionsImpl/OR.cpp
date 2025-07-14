#include "Emulator/Core/CPU/ALU.hpp"
#include "Emulator/Core/CPU/CPU.hpp"

class HyperCPU::CPU::CPU_InstrImpl {
  /* R_R implementation */
  template<typename T1, typename T2>
  static constexpr void __hcpu_or_rr_impl(HyperCPU::OperandContainer& op1, HyperCPU::OperandContainer& op2, CPU& cpu) {
    static_assert(std::is_same_v<T1, T2>); // Locked by current CPU specification

    op1.deref<T1>() = HyperALU::__hcpu_or<T1>(op1.deref<T1>(), op2.deref<T1>());
  }
};

void HyperCPU::CPU::ExecOR(const IInstruction& instr, OperandContainer op1, OperandContainer op2) {
  switch (instr.m_op_types) {
  case OperandTypes::R_R: {
    switch (instr.m_opcode_mode) {
    case Mode::b8:
      CPU_InstrImpl::__hcpu_or_rr_impl<std::uint8_t, std::uint8_t>(op1, op2, *this);
      break;

    case Mode::b16:
      CPU_InstrImpl::__hcpu_or_rr_impl<std::uint16_t, std::uint16_t>(op1, op2, *this);
      break;

    case Mode::b32:
      CPU_InstrImpl::__hcpu_or_rr_impl<std::uint32_t, std::uint32_t>(op1, op2, *this);
      break;

    case Mode::b64:
      CPU_InstrImpl::__hcpu_or_rr_impl<std::uint64_t, std::uint64_t>(op1, op2, *this);
      break;
    }
    break;
  }

  case OperandTypes::R_RM: {
    std::uint64_t ptr = HyperCPU::bit_cast_from<std::uint64_t>(op2.ptr<std::uint64_t>());

    switch (instr.m_opcode_mode) {
    case Mode::b8: {
      std::uint8_t val = mem_controller->Read8(ptr);
      op1.deref<std::uint8_t>() = __hcpu_or(op1.deref<std::uint8_t>(), val);
      break;
    }

    case Mode::b16: {
      std::uint16_t val = mem_controller->Read16(ptr);
      op1.deref<std::uint16_t>() = __hcpu_or(op1.deref<std::uint16_t>(), val);
      break;
    }

    case Mode::b32: {
      std::uint32_t val = mem_controller->Read32(ptr);
      op1.deref<std::uint32_t>() = __hcpu_or(op1.deref<std::uint32_t>(), val);
      break;
    }

    case Mode::b64: {
      std::uint64_t val = mem_controller->Read64(ptr);
      op1.deref<std::uint64_t>() = __hcpu_or(op1.deref<std::uint64_t>(), val);
      break;
    }
    }
    break;
  }

  case OperandTypes::R_M: {
    std::uint64_t ptr = HyperCPU::bit_cast<std::uint64_t>(op2);

    switch (instr.m_opcode_mode) {
    case Mode::b8: {
      std::uint8_t val = mem_controller->Read8(ptr);
      op1.deref<std::uint8_t>() = __hcpu_or(op1.deref<std::uint8_t>(), val);
      break;
    }

    case Mode::b16: {
      std::uint16_t val = mem_controller->Read16(ptr);
      op1.deref<std::uint16_t>() = __hcpu_or(op1.deref<std::uint16_t>(), val);
      break;
    }

    case Mode::b32: {
      std::uint32_t val = mem_controller->Read32(ptr);
      op1.deref<std::uint32_t>() = __hcpu_or(op1.deref<std::uint32_t>(), val);
      break;
    }

    case Mode::b64: {
      std::uint64_t val = mem_controller->Read64(ptr);
      op1.deref<std::uint64_t>() = __hcpu_or(op1.deref<std::uint64_t>(), val);
      break;
    }
    }
    break;
  }

  case OperandTypes::R_IMM: {
    switch (instr.m_opcode_mode) {
    case Mode::b8: {
      std::uint8_t val = HyperCPU::bit_cast<std::uint8_t>(op2);
      op1.deref<std::uint8_t>() = __hcpu_or(op1.deref<std::uint8_t>(), val);
      break;
    }

    case Mode::b16: {
      std::uint16_t val = HyperCPU::bit_cast<std::uint16_t>(op2);
      op1.deref<std::uint16_t>() = __hcpu_or(op1.deref<std::uint16_t>(), val);
      break;
    }

    case Mode::b32: {
      std::uint32_t val = HyperCPU::bit_cast<std::uint32_t>(op2);
      op1.deref<std::uint32_t>() = __hcpu_or(op1.deref<std::uint32_t>(), val);
      break;
    }

    case Mode::b64: {
      std::uint64_t val = HyperCPU::bit_cast<std::uint64_t>(op2);
      op1.deref<std::uint64_t>() = __hcpu_or(op1.deref<std::uint64_t>(), val);
      break;
    }
    }
    break;
  }

  default:
    break;
  }
}
