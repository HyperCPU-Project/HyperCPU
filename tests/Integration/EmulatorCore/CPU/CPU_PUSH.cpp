#include "tests/fixtures.hpp"
// TODO: fix include order

// TODO: fix constexpr naming
static constexpr std::uint8_t BYTE_DATA1 = 0x55;
static constexpr std::uint16_t WORD_DATA1 = 0x5555;
static constexpr std::uint32_t DWORD_DATA1 = 0x55555555;
static constexpr std::uint64_t QWORD_DATA1 = 0x555555555555555;

TEST_F(CPU_TEST, INSTR_PUSH_R_b8) {
  cpu.mem_controller->Load(*cpu.xip, HyperCPU::Opcode::PUSH);
  cpu.mem_controller->Load(*cpu.xip + 2, EncodeTestFlags(HyperCPU::Mode::b8, HyperCPU::OperandTypes::R));
  cpu.mem_controller->Load(*cpu.xip + 3, HyperCPU::Reg::XLLL0);
  cpu.mem_controller->Load(*cpu.xip + 4, HyperCPU::Opcode::HALT);
  cpu.mem_controller->Load(*cpu.xip + 6, HyperCPU::OperandTypes::NONE);
  *cpu.xlll0 = BYTE_DATA1;
  *cpu.xsp = 512;
  *cpu.xbp = 512;

  cpu.Run();

  ASSERT_EQ(HyperCPU::bit_cast_from<std::uint8_t>(cpu.mem_controller->get_ptr() + *cpu.xsp), BYTE_DATA1);
}

TEST_F(CPU_TEST, INSTR_PUSH_R_b16) {
  cpu.mem_controller->Load(*cpu.xip, HyperCPU::Opcode::PUSH);
  cpu.mem_controller->Load(*cpu.xip + 2, EncodeTestFlags(HyperCPU::Mode::b16, HyperCPU::OperandTypes::R));
  cpu.mem_controller->Load(*cpu.xip + 3, HyperCPU::Reg::XLL0);
  cpu.mem_controller->Load(*cpu.xip + 4, HyperCPU::Opcode::HALT);
  cpu.mem_controller->Load(*cpu.xip + 6, HyperCPU::OperandTypes::NONE);
  *cpu.xll0 = WORD_DATA1;
  *cpu.xsp = 512;
  *cpu.xbp = 512;

  cpu.Run();

  ASSERT_EQ(HyperCPU::bit_cast_from<std::uint16_t>(cpu.mem_controller->get_ptr() + *cpu.xsp), WORD_DATA1);
}

TEST_F(CPU_TEST, INSTR_PUSH_R_b32) {
  cpu.mem_controller->Load(*cpu.xip, HyperCPU::Opcode::PUSH);
  cpu.mem_controller->Load(*cpu.xip + 2, EncodeTestFlags(HyperCPU::Mode::b32, HyperCPU::OperandTypes::R));
  cpu.mem_controller->Load(*cpu.xip + 3, HyperCPU::Reg::XL0);
  cpu.mem_controller->Load(*cpu.xip + 4, HyperCPU::Opcode::HALT);
  cpu.mem_controller->Load(*cpu.xip + 6, HyperCPU::OperandTypes::NONE);
  *cpu.xl0 = DWORD_DATA1;
  *cpu.xsp = 512;
  *cpu.xbp = 512;

  cpu.Run();

  ASSERT_EQ(HyperCPU::bit_cast_from<std::uint32_t>(cpu.mem_controller->get_ptr() + *cpu.xsp), DWORD_DATA1);
}

TEST_F(CPU_TEST, INSTR_PUSH_R_b64) {
  cpu.mem_controller->Load(*cpu.xip, HyperCPU::Opcode::PUSH);
  cpu.mem_controller->Load(*cpu.xip + 2, EncodeTestFlags(HyperCPU::Mode::b64, HyperCPU::OperandTypes::R));
  cpu.mem_controller->Load(*cpu.xip + 3, HyperCPU::Reg::X0);
  cpu.mem_controller->Load(*cpu.xip + 4, HyperCPU::Opcode::HALT);
  cpu.mem_controller->Load(*cpu.xip + 6, HyperCPU::OperandTypes::NONE);
  *cpu.x0 = QWORD_DATA1;
  *cpu.xsp = 512;
  *cpu.xbp = 512;

  cpu.Run();

  ASSERT_EQ(HyperCPU::bit_cast_from<std::uint64_t>(cpu.mem_controller->get_ptr() + *cpu.xsp), QWORD_DATA1);
}

TEST_F(CPU_TEST, INSTR_PUSH_IMM_b8) {
  cpu.mem_controller->Load(*cpu.xip, HyperCPU::Opcode::PUSH);
  cpu.mem_controller->Load(*cpu.xip + 2, EncodeTestFlags(HyperCPU::Mode::b8, HyperCPU::OperandTypes::IMM));
  cpu.mem_controller->Load(*cpu.xip + 3, BYTE_DATA1);
  cpu.mem_controller->Load(*cpu.xip + 4, HyperCPU::Opcode::HALT);
  cpu.mem_controller->Load(*cpu.xip + 6, HyperCPU::OperandTypes::NONE);
  *cpu.xsp = 512;
  *cpu.xbp = 512;

  cpu.Run();

  ASSERT_EQ(HyperCPU::bit_cast_from<std::uint8_t>(cpu.mem_controller->get_ptr() + *cpu.xsp), BYTE_DATA1);
}

TEST_F(CPU_TEST, INSTR_PUSH_IMM_b16) {
  cpu.mem_controller->Load(*cpu.xip, HyperCPU::Opcode::PUSH);
  cpu.mem_controller->Load(*cpu.xip + 2, EncodeTestFlags(HyperCPU::Mode::b16, HyperCPU::OperandTypes::IMM));
  cpu.mem_controller->Load(*cpu.xip + 3, WORD_DATA1);
  cpu.mem_controller->Load(*cpu.xip + 5, HyperCPU::Opcode::HALT);
  cpu.mem_controller->Load(*cpu.xip + 7, HyperCPU::OperandTypes::NONE);
  *cpu.xsp = 512;
  *cpu.xbp = 512;

  cpu.Run();

  ASSERT_EQ(HyperCPU::bit_cast_from<std::uint16_t>(cpu.mem_controller->get_ptr() + *cpu.xsp), WORD_DATA1);
}

TEST_F(CPU_TEST, INSTR_PUSH_IMM_b32) {
  cpu.mem_controller->Load(*cpu.xip, HyperCPU::Opcode::PUSH);
  cpu.mem_controller->Load(*cpu.xip + 2, EncodeTestFlags(HyperCPU::Mode::b32, HyperCPU::OperandTypes::IMM));
  cpu.mem_controller->Load(*cpu.xip + 3, DWORD_DATA1);
  cpu.mem_controller->Load(*cpu.xip + 7, HyperCPU::Opcode::HALT);
  cpu.mem_controller->Load(*cpu.xip + 9, HyperCPU::OperandTypes::NONE);
  *cpu.xsp = 512;
  *cpu.xbp = 512;

  cpu.Run();

  ASSERT_EQ(HyperCPU::bit_cast_from<std::uint32_t>(cpu.mem_controller->get_ptr() + *cpu.xsp), DWORD_DATA1);
}

TEST_F(CPU_TEST, INSTR_PUSH_IMM_b64) {
  cpu.mem_controller->Load(*cpu.xip, HyperCPU::Opcode::PUSH);
  cpu.mem_controller->Load(*cpu.xip + 2, EncodeTestFlags(HyperCPU::Mode::b64, HyperCPU::OperandTypes::IMM));
  cpu.mem_controller->Load(*cpu.xip + 3, QWORD_DATA1);
  cpu.mem_controller->Load(*cpu.xip + 11, HyperCPU::Opcode::HALT);
  cpu.mem_controller->Load(*cpu.xip + 13, HyperCPU::OperandTypes::NONE);
  *cpu.xsp = 512;
  *cpu.xbp = 512;

  cpu.Run();

  ASSERT_EQ(HyperCPU::bit_cast_from<std::uint64_t>(cpu.mem_controller->get_ptr() + *cpu.xsp), QWORD_DATA1);
}
