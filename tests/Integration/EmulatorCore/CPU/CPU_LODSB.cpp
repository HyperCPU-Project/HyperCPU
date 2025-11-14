#include "../../../fixtures.hpp"
#include "fixtures.hpp"

// TODO: fix constexpr naming
static constexpr std::uint8_t BYTE_DATA1 = 0x55;
static constexpr std::uint16_t WORD_DATA1 = 0x5555;
static constexpr std::uint32_t DWORD_DATA1 = 0x55555555;
static constexpr std::uint64_t QWORD_DATA1 = 0x555555555555555;

TEST_F(CPU_TEST, INSTR_LODSB_R_b8) {
  cpu.mem_controller->Load16(*cpu.xip, HyperCPU::Opcode::MOV);
  cpu.mem_controller->Load8(*cpu.xip + 2, EncodeTestFlags(HyperCPU::Mode::b8, HyperCPU::OperandTypes::R_IMM));
  cpu.mem_controller->Load8(*cpu.xip + 3, HyperCPU::Reg::XFST);
  cpu.mem_controller->Load8(*cpu.xip + 4, -16);
  cpu.mem_controller->Load16(*cpu.xip + 5, HyperCPU::Opcode::LODSB);
  cpu.mem_controller->Load8(*cpu.xip + 7, EncodeTestFlags(HyperCPU::Mode::b8, HyperCPU::OperandTypes::R));
  cpu.mem_controller->Load8(*cpu.xip + 8, HyperCPU::Reg::XLLL0);
  cpu.mem_controller->Load16(*cpu.xip + 9, HyperCPU::Opcode::HALT);
  cpu.mem_controller->Load8(*cpu.xip + 11, HyperCPU::OperandTypes::NONE);
  cpu.mem_controller->Load8(*cpu.xip + 496, BYTE_DATA1);
  *cpu.xsp = 512;
  *cpu.xbp = 512;

  cpu.Run();

  ASSERT_EQ(*cpu.xlll0, BYTE_DATA1);
}

TEST_F(CPU_TEST, INSTR_LODSB_R_b16) {
  cpu.mem_controller->Load16(*cpu.xip, HyperCPU::Opcode::MOV);
  cpu.mem_controller->Load8(*cpu.xip + 2, EncodeTestFlags(HyperCPU::Mode::b16, HyperCPU::OperandTypes::R_IMM));
  cpu.mem_controller->Load8(*cpu.xip + 3, HyperCPU::Reg::XFST);
  cpu.mem_controller->Load16(*cpu.xip + 4, -16);
  cpu.mem_controller->Load16(*cpu.xip + 6, HyperCPU::Opcode::LODSB);
  cpu.mem_controller->Load8(*cpu.xip + 8, EncodeTestFlags(HyperCPU::Mode::b16, HyperCPU::OperandTypes::R));
  cpu.mem_controller->Load8(*cpu.xip + 9, HyperCPU::Reg::XLL0);
  cpu.mem_controller->Load16(*cpu.xip + 10, HyperCPU::Opcode::HALT);
  cpu.mem_controller->Load8(*cpu.xip + 12, HyperCPU::OperandTypes::NONE);
  cpu.mem_controller->Load16(*cpu.xip + 496, WORD_DATA1);
  *cpu.xsp = 512;
  *cpu.xbp = 512;

  cpu.Run();

  ASSERT_EQ(*cpu.xll0, WORD_DATA1);
}

TEST_F(CPU_TEST, INSTR_LODSB_R_b32) {
  cpu.mem_controller->Load16(*cpu.xip, HyperCPU::Opcode::MOV);
  cpu.mem_controller->Load8(*cpu.xip + 2, EncodeTestFlags(HyperCPU::Mode::b32, HyperCPU::OperandTypes::R_IMM));
  cpu.mem_controller->Load8(*cpu.xip + 3, HyperCPU::Reg::XFST);
  cpu.mem_controller->Load32(*cpu.xip + 4, -16);
  cpu.mem_controller->Load16(*cpu.xip + 8, HyperCPU::Opcode::LODSB);
  cpu.mem_controller->Load8(*cpu.xip + 10, EncodeTestFlags(HyperCPU::Mode::b32, HyperCPU::OperandTypes::R));
  cpu.mem_controller->Load8(*cpu.xip + 11, HyperCPU::Reg::XL0);
  cpu.mem_controller->Load16(*cpu.xip + 12, HyperCPU::Opcode::HALT);
  cpu.mem_controller->Load8(*cpu.xip + 14, HyperCPU::OperandTypes::NONE);
  cpu.mem_controller->Load32(*cpu.xip + 496, DWORD_DATA1);
  *cpu.xsp = 512;
  *cpu.xbp = 512;

  cpu.Run();

  ASSERT_EQ(*cpu.xl0, DWORD_DATA1);
}

TEST_F(CPU_TEST, INSTR_LODSB_R_b64) {
  cpu.mem_controller->Load16(*cpu.xip, HyperCPU::Opcode::MOV);
  cpu.mem_controller->Load8(*cpu.xip + 2, EncodeTestFlags(HyperCPU::Mode::b64, HyperCPU::OperandTypes::R_IMM));
  cpu.mem_controller->Load8(*cpu.xip + 3, HyperCPU::Reg::XFST);
  cpu.mem_controller->Load64(*cpu.xip + 4, -16);
  cpu.mem_controller->Load16(*cpu.xip + 12, HyperCPU::Opcode::LODSB);
  cpu.mem_controller->Load8(*cpu.xip + 14, EncodeTestFlags(HyperCPU::Mode::b64, HyperCPU::OperandTypes::R));
  cpu.mem_controller->Load8(*cpu.xip + 15, HyperCPU::Reg::X0);
  cpu.mem_controller->Load16(*cpu.xip + 16, HyperCPU::Opcode::HALT);
  cpu.mem_controller->Load8(*cpu.xip + 18, HyperCPU::OperandTypes::NONE);
  cpu.mem_controller->Load64(*cpu.xip + 496, QWORD_DATA1);
  *cpu.xsp = 512;
  *cpu.xbp = 512;

  cpu.Run();

  ASSERT_EQ(*cpu.x0, QWORD_DATA1);
}
