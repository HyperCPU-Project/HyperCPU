#pragma once

#include "PCH/CStd.hpp"

namespace HyperCPU {

  enum class Reg : std::uint8_t {
    X0 = 0,
    X1,
    X2,
    X3,
    X4,
    X5,
    X6,
    X7,
    XH0,
    XH1,
    XH2,
    XH3,
    XH4,
    XH5,
    XH6,
    XH7,
    XL0,
    XL1,
    XL2,
    XL3,
    XL4,
    XL5,
    XL6,
    XL7,
    XLL0,
    XLL1,
    XLL2,
    XLL3,
    XLLH0,
    XLLH1,
    XLLH2,
    XLLH3,
    XLLL0,
    XLLL1,
    XLLL2,
    XLLL3,
    XBP,
    XSP,
    XIP,
    XGDP,
    XIVT,
    XFST
  };

  namespace Validator {
    static constexpr inline bool IsValidRegister(std::uint8_t reg) {
      Reg r = static_cast<Reg>(reg);
      switch (r) {
      case Reg::X0:
      case Reg::X1:
      case Reg::X2:
      case Reg::X3:
      case Reg::X4:
      case Reg::X5:
      case Reg::X6:
      case Reg::X7:
      case Reg::XH0:
      case Reg::XH1:
      case Reg::XH2:
      case Reg::XH3:
      case Reg::XH4:
      case Reg::XH5:
      case Reg::XH6:
      case Reg::XH7:
      case Reg::XL0:
      case Reg::XL1:
      case Reg::XL2:
      case Reg::XL3:
      case Reg::XL4:
      case Reg::XL5:
      case Reg::XL6:
      case Reg::XL7:
      case Reg::XLL0:
      case Reg::XLL1:
      case Reg::XLL2:
      case Reg::XLL3:
      case Reg::XLLH0:
      case Reg::XLLH1:
      case Reg::XLLH2:
      case Reg::XLLH3:
      case Reg::XLLL0:
      case Reg::XLLL1:
      case Reg::XLLL2:
      case Reg::XLLL3:
      case Reg::XBP:
      case Reg::XSP:
      case Reg::XIP:
      case Reg::XGDP:
      case Reg::XIVT:
      case Reg::XFST:
        return true;
      default:
        return false;
      }
    }
  } // namespace Validator
} // namespace HyperCPU
