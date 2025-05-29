#pragma once

#include "PCH/CStd.hpp"

namespace HyperCPU {
  enum class Mode : std::uint8_t {
    b8 = 0,
    b16,
    b32,
    b64
  };

  struct ModePack {
    Mode md1;
    Mode md2;
  };

  enum class OperandTypes {
    R_R = 0,
    R_RM,
    R_M,
    R_IMM,
    RM_R,
    RM_M,
    RM_IMM,
    M_R,
    R,
    M,
    IMM,
    NONE
  };
} // namespace HyperCPU
