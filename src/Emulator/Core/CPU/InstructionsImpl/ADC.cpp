#include "Emulator/Core/CPU/ALU.hpp"
#include "Emulator/Core/CPU/CPU.hpp"

#include "Emulator/Misc/bit_cast.hpp"
#include "Emulator/Misc/overflow.hpp"

using namespace HyperALU;

void HyperCPU::CPU::ExecADC(const IInstruction& instr, OperandContainer op1, OperandContainer op2) {
  switch (instr.m_op_types) {
  case OperandTypes::R_R: {
    switch (instr.m_opcode_mode) {
    case Mode::b8:
      ovf = AdditionWillOverflow(op1.deref<std::uint8_t>(), op2.deref<std::uint8_t>());
      op1.deref<std::uint8_t>() = HyperALU::__hcpu_add(op1.deref<std::uint8_t>(), HyperCPU::bit_cast_from<std::uint8_t>(op2.ptr<std::uint8_t>()));
      if (crf)
        ++op1.deref<std::uint8_t>();
      break;

    case Mode::b16:
      ovf = AdditionWillOverflow(op1.deref<std::uint16_t>(), op2.deref<std::uint16_t>());
      op1.deref<std::uint16_t>() = HyperALU::__hcpu_add(op1.deref<std::uint16_t>(), HyperCPU::bit_cast_from<std::uint16_t>(op2.ptr<std::uint16_t>()));
      if (crf)
        ++op1.deref<std::uint16_t>();
      break;

    case Mode::b32:
      ovf = AdditionWillOverflow(op1.deref<std::uint32_t>(), op2.deref<std::uint32_t>());
      op1.deref<std::uint32_t>() = HyperALU::__hcpu_add(op1.deref<std::uint32_t>(), HyperCPU::bit_cast_from<std::uint32_t>(op2.ptr<std::uint32_t>()));
      if (crf)
        ++op1.deref<std::uint32_t>();
      break;

    case Mode::b64:
      ovf = AdditionWillOverflow(op1.deref<std::uint64_t>(), op2.deref<std::uint64_t>());
      op1.deref<std::uint64_t>() = HyperALU::__hcpu_add(op1.deref<std::uint64_t>(), HyperCPU::bit_cast_from<std::uint64_t>(op2.ptr<std::uint64_t>()));
      if (crf)
        ++op1.deref<std::uint64_t>();
      break;
    }
    break;
  }

  case OperandTypes::R_RM: {
    auto ptr = HyperCPU::bit_cast_from<std::uint64_t>(op2.ptr<std::uint64_t>());

    switch (instr.m_opcode_mode) {
    case Mode::b8: {
      std::uint8_t val = mem_controller->Read8(ptr);
      ovf = AdditionWillOverflow(op1.deref<std::uint8_t>(), val);
      op1.deref<std::uint8_t>() = HyperALU::__hcpu_add(op1.deref<std::uint8_t>(), val);
      if (crf)
        ++op1.deref<std::uint8_t>();
      break;
    }

    case Mode::b16: {
      std::uint16_t val = mem_controller->Read16(ptr);
      ovf = AdditionWillOverflow(op1.deref<std::uint16_t>(), val);
      op1.deref<std::uint16_t>() = HyperALU::__hcpu_add(op1.deref<std::uint16_t>(), val);
      if (crf)
        ++op1.deref<std::uint16_t>();
      break;
    }

    case Mode::b32: {
      std::uint32_t val = mem_controller->Read32(ptr);
      ovf = AdditionWillOverflow(op1.deref<std::uint32_t>(), val);
      op1.deref<std::uint32_t>() = HyperALU::__hcpu_add(op1.deref<std::uint32_t>(), val);
      if (crf)
        ++op1.deref<std::uint32_t>();
      break;
    }

    case Mode::b64: {
      std::uint64_t val = mem_controller->Read64(ptr);
      ovf = AdditionWillOverflow(op1.deref<std::uint64_t>(), val);
      op1.deref<std::uint64_t>() = HyperALU::__hcpu_add(op1.deref<std::uint64_t>(), val);
      if (crf)
        ++op1.deref<std::uint64_t>();
      break;
    }
    }
    break;
  }

  case OperandTypes::R_M: {
    auto ptr = HyperCPU::bit_cast<std::uint64_t>(op2);

    switch (instr.m_opcode_mode) {
    case Mode::b8: {
      std::uint8_t val = mem_controller->Read8(ptr);
      ovf = AdditionWillOverflow(op1.deref<std::uint8_t>(), val);
      op1.deref<std::uint8_t>() = HyperALU::__hcpu_add(op1.deref<std::uint8_t>(), val);
      if (crf)
        ++op1.deref<std::uint8_t>();
      break;
    }

    case Mode::b16: {
      std::uint16_t val = mem_controller->Read16(ptr);
      ovf = AdditionWillOverflow(op1.deref<std::uint16_t>(), val);
      op1.deref<std::uint16_t>() = HyperALU::__hcpu_add(op1.deref<std::uint16_t>(), val);
      if (crf)
        ++op1.deref<std::uint16_t>();
      break;
    }

    case Mode::b32: {
      std::uint32_t val = mem_controller->Read32(ptr);
      ovf = AdditionWillOverflow(op1.deref<std::uint32_t>(), val);
      op1.deref<std::uint32_t>() = HyperALU::__hcpu_add(op1.deref<std::uint32_t>(), val);
      if (crf)
        ++op1.deref<std::uint32_t>();
      break;
    }

    case Mode::b64: {
      std::uint64_t val = mem_controller->Read64(ptr);
      ovf = AdditionWillOverflow(op1.deref<std::uint64_t>(), val);
      op1.deref<std::uint64_t>() = HyperALU::__hcpu_add(op1.deref<std::uint64_t>(), val);
      if (crf)
        ++op1.deref<std::uint64_t>();
      break;
    }
    }
    break;
  }

  case OperandTypes::R_IMM: {
    switch (instr.m_opcode_mode) {
    case Mode::b8: {
      auto val = HyperCPU::bit_cast<std::uint8_t>(op2);
      ovf = AdditionWillOverflow(op1.deref<std::uint8_t>(), val);
      op1.deref<std::uint8_t>() = HyperALU::__hcpu_add(op1.deref<std::uint8_t>(), val);
      if (crf)
        ++op1.deref<std::uint8_t>();
      break;
    }

    case Mode::b16: {
      auto val = HyperCPU::bit_cast<std::uint16_t>(op2);
      ovf = AdditionWillOverflow(op1.deref<std::uint16_t>(), val);
      op1.deref<std::uint16_t>() = HyperALU::__hcpu_add(op1.deref<std::uint16_t>(), val);
      if (crf)
        ++op1.deref<std::uint16_t>();
      break;
    }

    case Mode::b32: {
      auto val = HyperCPU::bit_cast<std::uint32_t>(op2);
      ovf = AdditionWillOverflow(op1.deref<std::uint32_t>(), val);
      op1.deref<std::uint32_t>() = HyperALU::__hcpu_add(op1.deref<std::uint32_t>(), val);
      if (crf)
        ++op1.deref<std::uint32_t>();
      break;
    }

    case Mode::b64: {
      auto val = HyperCPU::bit_cast<std::uint64_t>(op2);
      ovf = AdditionWillOverflow(op1.deref<std::uint64_t>(), val);
      op1.deref<std::uint64_t>() = HyperALU::__hcpu_add(op1.deref<std::uint64_t>(), val);
      if (crf)
        ++op1.deref<std::uint64_t>();
      break;
    }
    }
    break;
  }

  default:
    break;
  }
}
