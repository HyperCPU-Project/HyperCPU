#pragma once

#include <cstdint>
#include <mapbox/eternal.hpp>

#include "Common/LanguageSpec/Opcodes.hpp"
#include "PCH/CStd.hpp"

constexpr inline const auto opcode_assoc = mapbox::eternal::hash_map<mapbox::eternal::string, HyperCPU::Opcode>(
    {{"adc", HyperCPU::Opcode::ADC},
     {"add", HyperCPU::Opcode::ADD},
     {"and", HyperCPU::Opcode::AND},
     {"andn", HyperCPU::Opcode::ANDN},
     {"bswap", HyperCPU::Opcode::BSWAP},
     {"call", HyperCPU::Opcode::CALL},
     {"ccrf", HyperCPU::Opcode::CCRF},
     {"covf", HyperCPU::Opcode::COVF},
     {"cudf", HyperCPU::Opcode::CUDF},
     {"hid", HyperCPU::Opcode::HID},
     {"inc", HyperCPU::Opcode::INC},
     {"dec", HyperCPU::Opcode::DEC},
     {"div", HyperCPU::Opcode::DIV},
     {"mul", HyperCPU::Opcode::MUL},
     {"sub", HyperCPU::Opcode::SUB},
     {"shfr", HyperCPU::Opcode::SHFR},
     {"shfl", HyperCPU::Opcode::SHFL},
     {"or", HyperCPU::Opcode::OR},
     {"halt", HyperCPU::Opcode::HALT},
     {"loivt", HyperCPU::Opcode::LOIVT},
     {"intr", HyperCPU::Opcode::INTR},
     //{"ret", HyperCPU::Opcode::RET},
     {"iret", HyperCPU::Opcode::IRET},
     {"mov", HyperCPU::Opcode::MOV},
     {"read", HyperCPU::Opcode::READ},
     {"write", HyperCPU::Opcode::WRITE},
     {"jmp", HyperCPU::Opcode::JMP},
     {"push", HyperCPU::Opcode::PUSH},
     {"pop", HyperCPU::Opcode::POP},
     {"calle", HyperCPU::Opcode::CALLE},
     {"callgr", HyperCPU::Opcode::CALLGR},
     {"calll", HyperCPU::Opcode::CALLL},
     {"jme", HyperCPU::Opcode::JME},
     {"jmgr", HyperCPU::Opcode::JMGR},
     {"jml", HyperCPU::Opcode::JML},
     {"cmp", HyperCPU::Opcode::CMP},
    {"lodsb", HyperCPU::Opcode::LODSB},
    {"stdsb", HyperCPU::Opcode::STDSB},});
