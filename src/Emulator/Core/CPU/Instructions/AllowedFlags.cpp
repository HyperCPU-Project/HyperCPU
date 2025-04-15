#include <pch.hpp>

#include <Core/CPU/Instructions/AllowedFlags.hpp>


namespace HyperCPU {
  const std::uint8_t allowed_op_modes[128][12] = {
    {}, // NULL
    {SUPPORT_ALL, SUPPORT_ALL, SUPPORT_ALL, SUPPORT_ALL, 0, 0, 0, 0, 0, 0, 0, 0}, // ADC
    {SUPPORT_ALL, SUPPORT_ALL, SUPPORT_ALL, SUPPORT_ALL, 0, 0, 0, 0, 0, 0, 0, 0}, // ADD
    {SUPPORT_ALL, SUPPORT_ALL, SUPPORT_ALL, SUPPORT_ALL, 0, 0, 0, 0, 0, 0, 0, 0}, // AND
    {SUPPORT_ALL, SUPPORT_ALL, SUPPORT_ALL, SUPPORT_ALL, 0, 0, 0, 0, 0, 0, 0, 0}, // ANDN
    {0, 0, 0, 0, 0, 0, 0, 0, SUPPORT_ALL, 0, 0, 0}, // BSWAP
    {0, 0, 0, 0, 0, 0, 0, 0, 0b00000011, 0, 0b00000011, 0}, // CALL
    {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, SUPPORT_ALL}, // CCRF
    {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, SUPPORT_ALL}, // COVF
    {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, SUPPORT_ALL}, // CUDF
    {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, SUPPORT_ALL}, // HID
    {0, 0, 0, 0, 0, 0, 0, 0, SUPPORT_ALL, 0, 0, 0}, // INC
    {0, 0, 0, 0, 0, 0, 0, 0, SUPPORT_ALL, 0, 0, 0}, // DEC
    {0, 0, 0, 0, 0, 0, 0, 0, SUPPORT_ALL, 0, 0, 0}, // DIV
    {SUPPORT_ALL, SUPPORT_ALL, SUPPORT_ALL, SUPPORT_ALL, 0, 0, 0, 0, 0, 0, 0, 0}, // MUL
    {SUPPORT_ALL, SUPPORT_ALL, SUPPORT_ALL, SUPPORT_ALL, 0, 0, 0, 0, 0, 0, 0, 0}, // SUB
    {SUPPORT_ALL, 0, 0, SUPPORT_ALL, 0, 0, 0, 0, 0, 0, 0, 0}, // SHFR
    {SUPPORT_ALL, 0, 0, SUPPORT_ALL, 0, 0, 0, 0, 0, 0, 0, 0}, // SHFL
    {SUPPORT_ALL, SUPPORT_ALL, SUPPORT_ALL, SUPPORT_ALL, 0, 0, 0, 0, 0, 0, 0, 0}, // OR
    {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, SUPPORT_ALL}, // HALT
    {0, 0, 0, 0, 0, 0, 0, 0, 0b00000011, 0, 0b00000011, 0}, // LOIVT
    {0, 0, 0, 0, 0, 0, 0, 0, SUPPORT_ALL, 0, 0, 0}, // INTR
    {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, SUPPORT_ALL}, // IRET
    {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, SUPPORT_ALL}, // RET
    {0, 0, 0, 0, 0, 0, 0, 0, 0b11000000, 0, 0b11000000, 0}, // READ
    {0b11000000, 0, 0, 0b11000000, 0, 0, 0, 0, 0, 0, 0}, // WRITE
    {0, 0, 0, 0, 0, 0, 0, 0, 0b00000011, 0, 0b00000011, 0}, // JMP
    {0, 0, 0, 0, 0, 0, 0, 0, SUPPORT_ALL, 0, SUPPORT_ALL, 0}, // PUSH
    {0, 0, 0, 0, 0, 0, 0, 0, SUPPORT_ALL, 0, 0, 0, }, // POP
    {0, 0, 0, 0, 0, 0, 0, 0, 0b00000011, 0, 0b00000011, 0}, // CALLE
    {0, 0, 0, 0, 0, 0, 0, 0, 0b00000011, 0, 0b00000011, 0}, // CALLGR
    {0, 0, 0, 0, 0, 0, 0, 0, 0b00000011, 0, 0b00000011, 0}, // CALLL
    {0, 0, 0, 0, 0, 0, 0, 0, 0b00000011, 0, 0b00000011, 0}, // JME
    {0, 0, 0, 0, 0, 0, 0, 0, 0b00000011, 0, 0b00000011, 0}, // JMGR
    {0, 0, 0, 0, 0, 0, 0, 0, 0b00000011, 0, 0b00000011, 0}, // JML
    {SUPPORT_ALL, SUPPORT_ALL, SUPPORT_ALL, SUPPORT_ALL, SUPPORT_ALL, SUPPORT_ALL, SUPPORT_ALL, SUPPORT_ALL, 0, 0, 0, 0}, // CMP
    {},
    {},
    {},
    {},
    {},
    {},
    {},
    {},
    {},
    {},
    {},
    {},
    {},
    {},
    {},
    {},
    {},
    {},
    {},
    {},
    {},
    {},
    {},
    {},
    {},
    {},
    {},
    {},
    {},
    {},
    {},
    {},
    {},
    {},
    {},
    {},
    {},
    {},
    {},
    {},
    {},
    {},
    {},
    {},
    {},
    {},
    {},
    {},
    {},
    {},
    {},
    {},
    {},
    {},
    {},
    {},
    {},
    {},
    {},
    {},
    {},
    {},
    {},
    {},
    {},
    {},
    {},
    {},
    {},
    {},
    {},
    {},
    {},
    {},
    {},
    {},
    {},
    {},
    {},
    {},
    {},
    {},
    {},
    {},
    {},
    {},
    {},
    {},
    {},
    {},
    {},
    {SUPPORT_ALL, SUPPORT_ALL, SUPPORT_ALL, SUPPORT_ALL, SUPPORT_ALL, SUPPORT_ALL, SUPPORT_ALL, SUPPORT_ALL, 0, 0, 0, 0}, // MOV
  };
}
