#include "PCH/CStd.hpp"

#include "Common/LanguageSpec/AllowedFlags.hpp"
#include "Common/LanguageSpec/Flags.hpp"
#include "Common/LanguageSpec/Opcodes.hpp"
#include "Common/LanguageSpec/Registers.hpp"
#include "Emulator/Core/CPU/CPU.hpp"
#include "Emulator/Core/CPU/Decoders/StdDecoder.hpp"

// TODO: лишать кошка жена за такое
#define dcdr_assert(expr){                       \
  RaiseException((expr));                        \
  if (cpu && cpu->pending_interrupt.has_value()) \
  return {.m_opcode = Opcode::_CONT, .m_opcode_mode = Mode::b64, .m_op_types = OperandTypes::NONE, .m_op1 = {}, .m_op2 = {}, .addr_extension_status = HyperCPU::AddrExtensionStatus::Disabled, .extension = 0};}

void HyperCPU::Decoder::RaiseException(bool expr) noexcept {
  if (!(expr)) {
    if (cpu == nullptr) {
      std::cerr << "Invalid opcode!\n";
      std::exit(1);
    } else {
      cpu->TriggerInterrupt(HyperCPU::cpu_exceptions::IO);
    }
  }
}

bool HyperCPU::Decoder::CheckSupportedOperandSize(std::uint8_t byte, Mode mode) const noexcept {
  switch (mode) {
  case Mode::b8:
    return byte & 0b11000000;
  case Mode::b16:
    return byte & 0b00110000;
  case Mode::b32:
    return byte & 0b00001100;
  case Mode::b64:
    return byte & 0b00000011;
  default:
    std::abort();
  }
}

bool HyperCPU::Decoder::IsHalted() const noexcept {
  return decoder_halted;
}

HyperCPU::IInstruction HyperCPU::Decoder::FetchAndDecode() {
  std::uint16_t opcode;
  std::uint8_t flags;
  IInstruction instruction;

  // Fetch opcode and check if its valid
  opcode = mem_controller->Fetch16(*xip);
  dcdr_assert(Validator::IsValidOpcode(opcode));

  // Convert opcode
  instruction.m_opcode = static_cast<enum Opcode>(opcode);

  switch (instruction.m_opcode) {
  case Opcode::IRET:
    return instruction;
  default:
    break;
  }

  // Fetch flags, set opcode Mode and verify operand types
  flags = mem_controller->Fetch8(*xip);
  instruction.m_opcode_mode = ModePack {
    static_cast<enum Mode>((flags & 0b11000000) >> 6),
    static_cast<enum Mode>((flags & 0b00110000) >> 4)
  };

  dcdr_assert((flags & 0b00001111) <= static_cast<decltype(flags)>(OperandTypes::NONE));
  instruction.m_op_types = static_cast<enum OperandTypes>(flags & 0b00001111);

  instruction.addr_extension_status = static_cast<AddrExtensionStatus>((flags & 0b11000000) >> 6);
  if (instruction.addr_extension_status != AddrExtensionStatus::Disabled) {
    instruction.extension = mem_controller->Fetch8(*xip);
  }

  // Check if op Mode is valid for this opcode
  
  dcdr_assert(AllowedOpModes[opcode][static_cast<std::uint8_t>(instruction.m_op_types)]);

  if (AllowedOpModes[opcode][static_cast<std::uint8_t>(instruction.m_op_types)] == SUPPORT_ALL) {
    goto skip_op_type_verification;
  }
  switch (instruction.m_op_types) {
    case HyperCPU::OperandTypes::R_R:
    case HyperCPU::OperandTypes::R_RM:
    case HyperCPU::OperandTypes::R_M:
    case HyperCPU::OperandTypes::R_IMM:
    case HyperCPU::OperandTypes::RM_R:
    case HyperCPU::OperandTypes::RM_M:
    case HyperCPU::OperandTypes::RM_IMM:
    case HyperCPU::OperandTypes::M_R:
      dcdr_assert((CheckSupportedOperandSize(AllowedOpModes[opcode][static_cast<std::uint8_t>(instruction.m_op_types)], instruction.m_opcode_mode.md2)));
    case HyperCPU::OperandTypes::R:
    case HyperCPU::OperandTypes::M:
    case HyperCPU::OperandTypes::IMM:
    case HyperCPU::OperandTypes::NONE:
      dcdr_assert((CheckSupportedOperandSize(AllowedOpModes[opcode][static_cast<std::uint8_t>(instruction.m_op_types)], instruction.m_opcode_mode.md1)));
  }

skip_op_type_verification:

  switch (instruction.m_op_types) {
  case OperandTypes::R_R:
  case OperandTypes::RM_R:
  case OperandTypes::R_RM: {
    std::uint8_t tmp = mem_controller->Fetch8(*xip);
    dcdr_assert(Validator::IsValidRegister(tmp));
    instruction.m_op1 = OperandContainer(HyperCPU::bit_cast<std::uint64_t>(tmp));

    tmp = mem_controller->Fetch8(*xip);
    dcdr_assert(Validator::IsValidRegister(tmp));
    instruction.m_op2 = OperandContainer(HyperCPU::bit_cast<std::uint64_t>(tmp));
    break;
  }

  case OperandTypes::RM_M:
  case OperandTypes::R_M: {
    std::uint8_t tmp = mem_controller->Fetch8(*xip);
    dcdr_assert(Validator::IsValidRegister(tmp));
    instruction.m_op1 = OperandContainer(HyperCPU::bit_cast<std::uint64_t>(tmp));

    instruction.m_op2 = OperandContainer{mem_controller->Fetch64(*xip)};
    break;
  }

  case OperandTypes::RM_IMM:
  case OperandTypes::R_IMM: {
    std::uint8_t tmp = mem_controller->Fetch8(*xip);
    dcdr_assert(Validator::IsValidRegister(tmp));
    instruction.m_op1 = OperandContainer(HyperCPU::bit_cast<std::uint64_t>(tmp));

    switch (instruction.m_opcode_mode.md2) {
    case Mode::b8: {
      std::uint8_t vtmp = mem_controller->Fetch8(*xip);
      instruction.m_op2 = OperandContainer(HyperCPU::bit_cast<std::uint64_t>(vtmp));
      break;
    }

    case Mode::b16: {
      std::uint16_t vtmp = mem_controller->Fetch16(*xip);
      instruction.m_op2 = OperandContainer(HyperCPU::bit_cast<std::uint64_t>(vtmp));
      break;
    }

    case Mode::b32: {
      std::uint32_t vtmp = mem_controller->Fetch32(*xip);
      instruction.m_op2 = OperandContainer(HyperCPU::bit_cast<std::uint64_t>(vtmp));
      break;
    }

    case Mode::b64: {
      instruction.m_op2 = OperandContainer{mem_controller->Fetch64(*xip)};
      break;
    }
    }
    break;
  }

  case OperandTypes::M_R: {
    instruction.m_op1 = OperandContainer{mem_controller->Fetch64(*xip)};

    std::uint8_t tmp = mem_controller->Fetch8(*xip);
    dcdr_assert(Validator::IsValidRegister(tmp));
    instruction.m_op2 = OperandContainer(HyperCPU::bit_cast<std::uint64_t>(tmp));
    break;
  }

  case OperandTypes::R: {
    std::uint8_t tmp = mem_controller->Fetch8(*xip);
    dcdr_assert(Validator::IsValidRegister(tmp));
    instruction.m_op1 = OperandContainer(HyperCPU::bit_cast<std::uint64_t>(tmp));
    break;
  }

  case OperandTypes::M:
    instruction.m_op1 = OperandContainer{mem_controller->Fetch64(*xip)};
    break;

  case OperandTypes::IMM:
    switch (instruction.m_opcode_mode.md1) {
    case Mode::b8: {
      std::uint8_t vtmp = mem_controller->Fetch8(*xip);
      instruction.m_op1 = OperandContainer(HyperCPU::bit_cast<std::uint64_t>(vtmp));
      break;
    }

    case Mode::b16: {
      std::uint16_t vtmp = mem_controller->Fetch16(*xip);
      instruction.m_op1 = OperandContainer(HyperCPU::bit_cast<std::uint64_t>(vtmp));
      break;
    }

    case Mode::b32: {
      std::uint32_t vtmp = mem_controller->Fetch32(*xip);
      instruction.m_op1 = OperandContainer(HyperCPU::bit_cast<std::uint64_t>(vtmp));
      break;
    }

    case Mode::b64: {
      instruction.m_op1 = OperandContainer{mem_controller->Fetch64(*xip)};
      break;
    }
    }
    break;

  case OperandTypes::NONE:
    break;
  }

  return instruction;
}
