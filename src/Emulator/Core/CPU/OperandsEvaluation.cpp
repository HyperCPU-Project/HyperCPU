#include "PCH/CStd.hpp"

#include "Common/LanguageSpec/Registers.hpp"
#include "Emulator/Core/CPU/CPU.hpp"
#include "Emulator/Misc/bit_cast.hpp"

HyperCPU::OperandContainer HyperCPU::CPU::GetRegister(OperandContainer& op1) {
  HyperCPU::Reg reg;
  memcpy(&reg, &op1, sizeof(HyperCPU::Reg));

  switch (reg) {
  case HyperCPU::Reg::X0:
    return OperandContainer{x0};
  case HyperCPU::Reg::X1:
    return OperandContainer{x1};
  case HyperCPU::Reg::X2:
    return OperandContainer{x2};
  case HyperCPU::Reg::X3:
    return OperandContainer{x3};
  case HyperCPU::Reg::X4:
    return OperandContainer{x4};
  case HyperCPU::Reg::X5:
    return OperandContainer{x5};
  case HyperCPU::Reg::X6:
    return OperandContainer{x6};
  case HyperCPU::Reg::X7:
    return OperandContainer{x7};

  case HyperCPU::Reg::XH0:
    return OperandContainer{xh0};
  case HyperCPU::Reg::XH1:
    return OperandContainer{xh1};
  case HyperCPU::Reg::XH2:
    return OperandContainer{xh2};
  case HyperCPU::Reg::XH3:
    return OperandContainer{xh3};
  case HyperCPU::Reg::XH4:
    return OperandContainer{xh4};
  case HyperCPU::Reg::XH5:
    return OperandContainer{xh5};
  case HyperCPU::Reg::XH6:
    return OperandContainer{xh6};
  case HyperCPU::Reg::XH7:
    return OperandContainer{xh7};

  case HyperCPU::Reg::XL0:
    return OperandContainer{xl0};
  case HyperCPU::Reg::XL1:
    return OperandContainer{xl1};
  case HyperCPU::Reg::XL2:
    return OperandContainer{xl2};
  case HyperCPU::Reg::XL3:
    return OperandContainer{xl3};
  case HyperCPU::Reg::XL4:
    return OperandContainer{xl4};
  case HyperCPU::Reg::XL5:
    return OperandContainer{xl5};
  case HyperCPU::Reg::XL6:
    return OperandContainer{xl6};
  case HyperCPU::Reg::XL7:
    return OperandContainer{xl7};

  case HyperCPU::Reg::XLL0:
    return OperandContainer{xll0};
  case HyperCPU::Reg::XLL1:
    return OperandContainer{xll1};
  case HyperCPU::Reg::XLL2:
    return OperandContainer{xll2};
  case HyperCPU::Reg::XLL3:
    return OperandContainer{xll3};

  case HyperCPU::Reg::XLLH0:
    return OperandContainer{xllh0};
  case HyperCPU::Reg::XLLH1:
    return OperandContainer{xllh1};
  case HyperCPU::Reg::XLLH2:
    return OperandContainer{xllh2};
  case HyperCPU::Reg::XLLH3:
    return OperandContainer{xllh3};

  case HyperCPU::Reg::XLLL0:
    return OperandContainer{xlll0};
  case HyperCPU::Reg::XLLL1:
    return OperandContainer{xlll1};
  case HyperCPU::Reg::XLLL2:
    return OperandContainer{xlll2};
  case HyperCPU::Reg::XLLL3:
    return OperandContainer{xlll3};

  case HyperCPU::Reg::XBP:
    return OperandContainer{xbp};
  case HyperCPU::Reg::XSP:
    return OperandContainer{xsp};
  case HyperCPU::Reg::XIP:
    return OperandContainer{xip};
  case HyperCPU::Reg::XGDP:
    return OperandContainer{xgdp};
  case HyperCPU::Reg::XIVT:
    return OperandContainer{xivt};
  default:
    throw std::runtime_error("Invalid register");
  }
}

std::pair<HyperCPU::OperandContainer, HyperCPU::OperandContainer> HyperCPU::CPU::GetOperands(OperandTypes op_types, ModePack md, OperandContainer& op1, OperandContainer& op2) {
  switch (op_types) {
  case OperandTypes::R_R:
  case OperandTypes::R_RM:
  case OperandTypes::RM_R: {
    OperandContainer op_1, op_2;
    op_1 = GetRegister(op1);
    op_2 = GetRegister(op2);
    return std::make_pair(op_1, op_2);
  }

  case OperandTypes::RM_M:
  case OperandTypes::R_M:
    return std::make_pair(GetRegister(op1), op2);

  case OperandTypes::RM_IMM:
  case OperandTypes::R_IMM: {
    switch (md.md2) {
    case Mode::b8: {
      std::uint8_t imm8;
      std::memcpy(&imm8, &op2, sizeof(std::uint8_t));
      return std::make_pair(GetRegister(op1), OperandContainer{HyperCPU::bit_cast<std::uint64_t>(imm8)});
    }
    case Mode::b16: {
      std::uint16_t imm16;
      std::memcpy(&imm16, &op2, sizeof(std::uint16_t));
      return std::make_pair(GetRegister(op1), OperandContainer{HyperCPU::bit_cast<std::uint64_t>(imm16)});
    }
    case Mode::b32: {
      std::uint32_t imm32;
      std::memcpy(&imm32, &op2, sizeof(std::uint32_t));
      return std::make_pair(GetRegister(op1), OperandContainer{HyperCPU::bit_cast<std::uint64_t>(imm32)});
    }
    case Mode::b64: {
      std::uint64_t imm64;
      std::memcpy(&imm64, &op2, sizeof(std::uint64_t));
      return std::make_pair(GetRegister(op1), OperandContainer{HyperCPU::bit_cast<std::uint64_t>(imm64)});
    }
    }
    break;
  }

  case OperandTypes::M_R:
    return std::make_pair(op1, GetRegister(op2));

  case OperandTypes::R:
    return std::make_pair(GetRegister(op1), nullptr);

  case OperandTypes::IMM:
  case OperandTypes::M:
    return std::make_pair(op1, nullptr);

  case OperandTypes::NONE:
    return std::make_pair(nullptr, nullptr);
  default:
    std::abort();
  }
  return {};
}
