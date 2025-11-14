#pragma once

#include "PCH/CStd.hpp"

namespace HyperCPU {
  enum class Opcode : std::uint16_t {
    ADC = 0x0001,
    ADD = 0x0002,
    AND = 0x0003,
    ANDN = 0x0004,
    BSWAP = 0x0005,
    CALL = 0x0006,
    CCRF = 0x0007,
    COVF = 0x0008,
    CUDF = 0x0009,
    HID = 0x000A,
    INC = 0x000B,
    DEC = 0x000C,
    DIV = 0x000D,
    MUL = 0x000E,
    SUB = 0x000F,
    SHFR = 0x0010,
    SHFL = 0x0011,
    OR = 0x0012,
    HALT = 0x0013,
    LOIVT = 0x0014,
    INTR = 0x0015,
    RET = 0x0016,
    IRET = 0x0017,
    READ = 0x0018,
    WRITE = 0x0019,
    JMP = 0x001A,
    PUSH = 0x001B,
    POP = 0x001C,
    CALLE = 0x001D,
    CALLGR = 0x001E,
    CALLL = 0x001F,
    JME = 0x0020,
    JMGR = 0x0021,
    JML = 0x0022,
    CMP = 0x0023,
    LODSB = 0x0024,
    STDSB = 0x0025,
    MOV = 0x007F,
    _CONT = 0x6934
  };

  namespace Validator {
    static constexpr inline bool IsValidOpcode(std::uint16_t op) {
      Opcode code = static_cast<Opcode>(op);
      switch (code) {
      case Opcode::ADC:
      case Opcode::ADD:
      case Opcode::AND:
      case Opcode::ANDN:
      case Opcode::BSWAP:
      case Opcode::CALL:
      case Opcode::CCRF:
      case Opcode::COVF:
      case Opcode::CUDF:
      case Opcode::HALT:
      case Opcode::HID:
      case Opcode::INC:
      case Opcode::DEC:
      case Opcode::DIV:
      case Opcode::MUL:
      case Opcode::MOV:
      case Opcode::SUB:
      case Opcode::SHFR:
      case Opcode::SHFL:
      case Opcode::OR:
      case Opcode::LOIVT:
      case Opcode::INTR:
      case Opcode::READ:
      case Opcode::WRITE:
      case Opcode::JMP:
      case Opcode::IRET:
      case Opcode::PUSH:
      case Opcode::POP:
      case Opcode::CALLE:
      case Opcode::CALLGR:
      case Opcode::CALLL:
      case Opcode::JME:
      case Opcode::JMGR:
      case Opcode::JML:
      case Opcode::CMP:
      case Opcode::LODSB:
      case Opcode::STDSB:
        return true;
      default:
        return false;
      }
    }
  } // namespace Validator
} // namespace HyperCPU
