#include "tests/fixtures.hpp"

static constexpr std::uint8_t BYTE_DATA1 = 0x55;
static constexpr std::uint8_t BYTE_DATA2 = 0x60;
static constexpr std::uint8_t BYTE_SUM = BYTE_DATA1 + BYTE_DATA2;
static constexpr std::uint16_t WORD_DATA1 = 0x5555;
static constexpr std::uint16_t WORD_DATA2 = 0x6060;
static constexpr std::uint16_t WORD_SUM = WORD_DATA1 + WORD_DATA2;
static constexpr std::uint32_t DWORD_DATA1 = 0x55555555;
static constexpr std::uint32_t DWORD_DATA2 = 0x60606060;
static constexpr std::uint32_t DWORD_SUM = DWORD_DATA1 + DWORD_DATA2;
static constexpr std::uint64_t QWORD_DATA1 = 0x555555555555555;
static constexpr std::uint64_t QWORD_DATA2 = 0x6060606060606060;
static constexpr std::uint64_t QWORD_SUM = QWORD_DATA1 + QWORD_DATA2;

static constexpr std::uint8_t BYTE_DATA1_OF = 0xBA;
static constexpr std::uint8_t BYTE_DATA2_OF = 0x60;
static constexpr std::uint8_t BYTE_SUM_OF = static_cast<std::uint8_t>(BYTE_DATA1_OF + BYTE_DATA2_OF);
static constexpr std::uint16_t WORD_DATA1_OF = 0xBABA;
static constexpr std::uint16_t WORD_DATA2_OF = 0x6060;
static constexpr std::uint16_t WORD_SUM_OF = static_cast<std::uint16_t>(WORD_DATA1_OF + WORD_DATA2_OF);
static constexpr std::uint32_t DWORD_DATA1_OF = 0xBABABABA;
static constexpr std::uint32_t DWORD_DATA2_OF = 0x60606060;
static constexpr std::uint32_t DWORD_SUM_OF = static_cast<std::uint32_t>(DWORD_DATA1_OF + DWORD_DATA2_OF);
static constexpr std::uint64_t QWORD_DATA1_OF = 0xBABABABABABABABA;
static constexpr std::uint64_t QWORD_DATA2_OF = 0x6060606060606060;
static constexpr std::uint64_t QWORD_SUM_OF = QWORD_DATA1_OF + QWORD_DATA2_OF;

TEST_F(CPU_TEST, INSTR_ADD_R_R_b8) {
  cpu.mem_controller->Load16(*cpu.xip, HyperCPU::Opcode::ADD);
  cpu.mem_controller->Load8(*cpu.xip + 2, EncodeTestFlags(HyperCPU::Mode::b8,  HyperCPU::Mode::b8, HyperCPU::OperandTypes::R_R));
  cpu.mem_controller->Load8(*cpu.xip + 3, HyperCPU::Reg::XLLL0);
  cpu.mem_controller->Load8(*cpu.xip + 4, HyperCPU::Reg::XLLL1);
  cpu.mem_controller->Load16(*cpu.xip + 5, HyperCPU::Opcode::HALT);
  cpu.mem_controller->Load8(*cpu.xip + 7, HyperCPU::OperandTypes::NONE);
  *cpu.xlll0 = BYTE_DATA1;
  *cpu.xlll1 = BYTE_DATA2;

  cpu.Run();

  ASSERT_EQ(*cpu.xlll0, BYTE_SUM);
}

TEST_F(CPU_TEST, INSTR_ADD_R_R_b16) {
  cpu.mem_controller->Load16(*cpu.xip, HyperCPU::Opcode::ADD);
  cpu.mem_controller->Load8(*cpu.xip + 2, EncodeTestFlags(HyperCPU::Mode::b16,  HyperCPU::Mode::b16, HyperCPU::OperandTypes::R_R));
  cpu.mem_controller->Load8(*cpu.xip + 3, HyperCPU::Reg::XLL0);
  cpu.mem_controller->Load8(*cpu.xip + 4, HyperCPU::Reg::XLL1);
  cpu.mem_controller->Load16(*cpu.xip + 5, HyperCPU::Opcode::HALT);
  cpu.mem_controller->Load8(*cpu.xip + 7, HyperCPU::OperandTypes::NONE);
  *cpu.xll0 = WORD_DATA1;
  *cpu.xll1 = WORD_DATA2;

  cpu.Run();

  ASSERT_EQ(*cpu.xll0, WORD_SUM);
}

TEST_F(CPU_TEST, INSTR_ADD_R_R_b32) {
  cpu.mem_controller->Load16(*cpu.xip, HyperCPU::Opcode::ADD);
  cpu.mem_controller->Load8(*cpu.xip + 2, EncodeTestFlags(HyperCPU::Mode::b32,  HyperCPU::Mode::b32, HyperCPU::OperandTypes::R_R));
  cpu.mem_controller->Load8(*cpu.xip + 3, HyperCPU::Reg::XL0);
  cpu.mem_controller->Load8(*cpu.xip + 4, HyperCPU::Reg::XL1);
  cpu.mem_controller->Load16(*cpu.xip + 5, HyperCPU::Opcode::HALT);
  cpu.mem_controller->Load8(*cpu.xip + 7, HyperCPU::OperandTypes::NONE);
  *cpu.xl0 = DWORD_DATA1;
  *cpu.xl1 = DWORD_DATA2;

  cpu.Run();

  ASSERT_EQ(*cpu.xl0, DWORD_SUM);
}

TEST_F(CPU_TEST, INSTR_ADD_R_R_b64) {
  cpu.mem_controller->Load16(*cpu.xip, HyperCPU::Opcode::ADD);
  cpu.mem_controller->Load8(*cpu.xip + 2, EncodeTestFlags(HyperCPU::Mode::b64,  HyperCPU::Mode::b64, HyperCPU::OperandTypes::R_R));
  cpu.mem_controller->Load8(*cpu.xip + 3, HyperCPU::Reg::X0);
  cpu.mem_controller->Load8(*cpu.xip + 4, HyperCPU::Reg::X1);
  cpu.mem_controller->Load16(*cpu.xip + 5, HyperCPU::Opcode::HALT);
  cpu.mem_controller->Load8(*cpu.xip + 7, HyperCPU::OperandTypes::NONE);
  *cpu.x0 = QWORD_DATA1;
  *cpu.x1 = QWORD_DATA2;

  cpu.Run();

  ASSERT_EQ(*cpu.x0, QWORD_SUM);
}

TEST_F(CPU_TEST, INSTR_ADD_R_RM_b8) {
  cpu.mem_controller->Load16(*cpu.xip, HyperCPU::Opcode::ADD);
  cpu.mem_controller->Load8(*cpu.xip + 2, EncodeTestFlags(HyperCPU::Mode::b8,  HyperCPU::Mode::b8, HyperCPU::OperandTypes::R_RM)
;
  cpu.mem_controller->Load8(*cpu.xip + 3, HyperCPU::Reg::XLLL0);
  cpu.mem_controller->Load8(*cpu.xip + 4, HyperCPU::Reg::X1);
  cpu.mem_controller->Load16(*cpu.xip + 5, HyperCPU::Opcode::HALT);
  cpu.mem_controller->Load8(*cpu.xip + 7, HyperCPU::OperandTypes::NONE);
  *cpu.xlll0 = BYTE_DATA1;
  cpu.mem_controller->Load8(1024, BYTE_DATA2);
  *cpu.x1 = 1024;

  cpu.Run();

  ASSERT_EQ(*cpu.xlll0, BYTE_SUM);
}

TEST_F(CPU_TEST, INSTR_ADD_R_RM_b16) {
  cpu.mem_controller->Load16(*cpu.xip, HyperCPU::Opcode::ADD);
  cpu.mem_controller->Load8(*cpu.xip + 2, EncodeTestFlags(HyperCPU::Mode::b16,  HyperCPU::Mode::b16, HyperCPU::OperandTypes::R_RM)
;
  cpu.mem_controller->Load8(*cpu.xip + 3, HyperCPU::Reg::XLL0);
  cpu.mem_controller->Load8(*cpu.xip + 4, HyperCPU::Reg::X1);
  cpu.mem_controller->Load16(*cpu.xip + 5, HyperCPU::Opcode::HALT);
  cpu.mem_controller->Load8(*cpu.xip + 7, HyperCPU::OperandTypes::NONE);
  *cpu.xll0 = WORD_DATA1;
  cpu.mem_controller->Load16(1024, WORD_DATA2);
  *cpu.x1 = 1024;

  cpu.Run();

  ASSERT_EQ(*cpu.xll0, WORD_SUM);
}

TEST_F(CPU_TEST, INSTR_ADD_R_RM_b32) {
  cpu.mem_controller->Load16(*cpu.xip, HyperCPU::Opcode::ADD);
  cpu.mem_controller->Load8(*cpu.xip + 2, EncodeTestFlags(HyperCPU::Mode::b32,  HyperCPU::Mode::b32, HyperCPU::OperandTypes::R_RM)
;
  cpu.mem_controller->Load8(*cpu.xip + 3, HyperCPU::Reg::XL0);
  cpu.mem_controller->Load8(*cpu.xip + 4, HyperCPU::Reg::X1);
  cpu.mem_controller->Load16(*cpu.xip + 5, HyperCPU::Opcode::HALT);
  cpu.mem_controller->Load8(*cpu.xip + 7, HyperCPU::OperandTypes::NONE);
  *cpu.xl0 = DWORD_DATA1;
  cpu.mem_controller->Load32(1024, DWORD_DATA2);
  *cpu.x1 = 1024;

  cpu.Run();

  ASSERT_EQ(*cpu.xl0, DWORD_SUM);
}

TEST_F(CPU_TEST, INSTR_ADD_R_RM_b64) {
  cpu.mem_controller->Load16(*cpu.xip, HyperCPU::Opcode::ADD);
  cpu.mem_controller->Load8(*cpu.xip + 2, EncodeTestFlags(HyperCPU::Mode::b64,  HyperCPU::Mode::b64, HyperCPU::OperandTypes::R_RM)
;
  cpu.mem_controller->Load8(*cpu.xip + 3, HyperCPU::Reg::X0);
  cpu.mem_controller->Load8(*cpu.xip + 4, HyperCPU::Reg::X1);
  cpu.mem_controller->Load16(*cpu.xip + 5, HyperCPU::Opcode::HALT);
  cpu.mem_controller->Load8(*cpu.xip + 7, HyperCPU::OperandTypes::NONE);
  *cpu.x0 = QWORD_DATA1;
  cpu.mem_controller->Load64(1024, QWORD_DATA2);
  *cpu.x1 = 1024;

  cpu.Run();

  ASSERT_EQ(*cpu.x0, QWORD_SUM);
}

TEST_F(CPU_TEST, INSTR_ADD_R_M_b8) {
  cpu.mem_controller->Load16(*cpu.xip, HyperCPU::Opcode::ADD);
  cpu.mem_controller->Load8(*cpu.xip + 2, EncodeTestFlags(HyperCPU::Mode::b8,  HyperCPU::Mode::b8, HyperCPU::OperandTypes::R_M)
;
  cpu.mem_controller->Load8(*cpu.xip + 3, HyperCPU::Reg::XLLL0);
  cpu.mem_controller->Load64(*cpu.xip + 4, 1024);
  cpu.mem_controller->Load16(*cpu.xip + 12, HyperCPU::Opcode::HALT);
  cpu.mem_controller->Load8(*cpu.xip + 14, HyperCPU::OperandTypes::NONE);
  *cpu.xlll0 = BYTE_DATA1;
  cpu.mem_controller->Load8(1024, BYTE_DATA2);

  cpu.Run();

  ASSERT_EQ(*cpu.xlll0, BYTE_SUM);
}

TEST_F(CPU_TEST, INSTR_ADD_R_M_b16) {
  cpu.mem_controller->Load16(*cpu.xip, HyperCPU::Opcode::ADD);
  cpu.mem_controller->Load8(*cpu.xip + 2, EncodeTestFlags(HyperCPU::Mode::b16,  HyperCPU::Mode::b16, HyperCPU::OperandTypes::R_M)
;
  cpu.mem_controller->Load8(*cpu.xip + 3, HyperCPU::Reg::XLL0);
  cpu.mem_controller->Load64(*cpu.xip + 4, 1024);
  cpu.mem_controller->Load16(*cpu.xip + 12, HyperCPU::Opcode::HALT);
  cpu.mem_controller->Load8(*cpu.xip + 14, HyperCPU::OperandTypes::NONE);
  *cpu.xll0 = WORD_DATA1;
  cpu.mem_controller->Load16(1024, WORD_DATA2);

  cpu.Run();

  ASSERT_EQ(*cpu.xll0, WORD_SUM);
}

TEST_F(CPU_TEST, INSTR_ADD_R_M_b32) {
  cpu.mem_controller->Load16(*cpu.xip, HyperCPU::Opcode::ADD);
  cpu.mem_controller->Load8(*cpu.xip + 2, EncodeTestFlags(HyperCPU::Mode::b32,  HyperCPU::Mode::b32, HyperCPU::OperandTypes::R_M)
;
  cpu.mem_controller->Load8(*cpu.xip + 3, HyperCPU::Reg::XL0);
  cpu.mem_controller->Load64(*cpu.xip + 4, 1024);
  cpu.mem_controller->Load16(*cpu.xip + 12, HyperCPU::Opcode::HALT);
  cpu.mem_controller->Load8(*cpu.xip + 14, HyperCPU::OperandTypes::NONE);
  *cpu.xl0 = DWORD_DATA1;
  cpu.mem_controller->Load32(1024, DWORD_DATA2);

  cpu.Run();

  ASSERT_EQ(*cpu.xl0, DWORD_SUM);
}

TEST_F(CPU_TEST, INSTR_ADD_R_M_b64) {
  cpu.mem_controller->Load16(*cpu.xip, HyperCPU::Opcode::ADD);
  cpu.mem_controller->Load8(*cpu.xip + 2, EncodeTestFlags(HyperCPU::Mode::b64,  HyperCPU::Mode::b64, HyperCPU::OperandTypes::R_M)
;
  cpu.mem_controller->Load8(*cpu.xip + 3, HyperCPU::Reg::X0);
  cpu.mem_controller->Load64(*cpu.xip + 4, 1024);
  cpu.mem_controller->Load16(*cpu.xip + 12, HyperCPU::Opcode::HALT);
  cpu.mem_controller->Load8(*cpu.xip + 14, HyperCPU::OperandTypes::NONE);
  *cpu.x0 = QWORD_DATA1;
  cpu.mem_controller->Load64(1024, QWORD_DATA2);

  cpu.Run();

  ASSERT_EQ(*cpu.x0, QWORD_SUM);
}

TEST_F(CPU_TEST, INSTR_ADD_R_IMM_b8) {
  cpu.mem_controller->Load16(*cpu.xip, HyperCPU::Opcode::ADD);
  cpu.mem_controller->Load8(*cpu.xip + 2, EncodeTestFlags(HyperCPU::Mode::b8,  HyperCPU::Mode::b8, HyperCPU::OperandTypes::R_IMM)
;
  cpu.mem_controller->Load8(*cpu.xip + 3, HyperCPU::Reg::XLLL0);
  cpu.mem_controller->Load8(*cpu.xip + 4, BYTE_DATA2);
  cpu.mem_controller->Load16(*cpu.xip + 5, HyperCPU::Opcode::HALT);
  cpu.mem_controller->Load8(*cpu.xip + 7, HyperCPU::OperandTypes::NONE);
  *cpu.xlll0 = BYTE_DATA1;

  cpu.Run();

  ASSERT_EQ(*cpu.xlll0, BYTE_SUM);
}

TEST_F(CPU_TEST, INSTR_ADD_R_IMM_b16) {
  cpu.mem_controller->Load16(*cpu.xip, HyperCPU::Opcode::ADD);
  cpu.mem_controller->Load8(*cpu.xip + 2, EncodeTestFlags(HyperCPU::Mode::b16,  HyperCPU::Mode::b16, HyperCPU::OperandTypes::R_IMM)
;
  cpu.mem_controller->Load8(*cpu.xip + 3, HyperCPU::Reg::XLL0);
  cpu.mem_controller->Load16(*cpu.xip + 4, WORD_DATA2);
  cpu.mem_controller->Load16(*cpu.xip + 6, HyperCPU::Opcode::HALT);
  cpu.mem_controller->Load8(*cpu.xip + 8, HyperCPU::OperandTypes::NONE);
  *cpu.xll0 = WORD_DATA1;

  cpu.Run();

  ASSERT_EQ(*cpu.xll0, WORD_SUM);
}

TEST_F(CPU_TEST, INSTR_ADD_R_IMM_b32) {
  cpu.mem_controller->Load16(*cpu.xip, HyperCPU::Opcode::ADD);
  cpu.mem_controller->Load8(*cpu.xip + 2, EncodeTestFlags(HyperCPU::Mode::b32,  HyperCPU::Mode::b32, HyperCPU::OperandTypes::R_IMM)
;
  cpu.mem_controller->Load8(*cpu.xip + 3, HyperCPU::Reg::XL0);
  cpu.mem_controller->Load32(*cpu.xip + 4, DWORD_DATA2);
  cpu.mem_controller->Load16(*cpu.xip + 8, HyperCPU::Opcode::HALT);
  cpu.mem_controller->Load8(*cpu.xip + 10, HyperCPU::OperandTypes::NONE);
  *cpu.xl0 = DWORD_DATA1;

  cpu.Run();

  ASSERT_EQ(*cpu.xl0, DWORD_SUM);
}

TEST_F(CPU_TEST, INSTR_ADD_R_IMM_b64) {
  cpu.mem_controller->Load16(*cpu.xip, HyperCPU::Opcode::ADD);
  cpu.mem_controller->Load8(*cpu.xip + 2, EncodeTestFlags(HyperCPU::Mode::b64,  HyperCPU::Mode::b64, HyperCPU::OperandTypes::R_IMM));
  cpu.mem_controller->Load8(*cpu.xip + 3, HyperCPU::Reg::X0);
  cpu.mem_controller->Load64(*cpu.xip + 4, QWORD_DATA2);
  cpu.mem_controller->Load16(*cpu.xip + 12, HyperCPU::Opcode::HALT);
  cpu.mem_controller->Load8(*cpu.xip + 14, HyperCPU::OperandTypes::NONE);
  *cpu.x0 = QWORD_DATA1;

  cpu.Run();

  ASSERT_EQ(*cpu.x0, QWORD_SUM);
}

TEST_F(CPU_TEST, INSTR_ADD_R_R_b8_OF) {
  cpu.mem_controller->Load16(*cpu.xip, HyperCPU::Opcode::ADD);
  cpu.mem_controller->Load8(*cpu.xip + 2, EncodeTestFlags(HyperCPU::Mode::b8,  HyperCPU::Mode::b8, HyperCPU::OperandTypes::R_R));
  cpu.mem_controller->Load8(*cpu.xip + 3, HyperCPU::Reg::XLLL0);
  cpu.mem_controller->Load8(*cpu.xip + 4, HyperCPU::Reg::XLLL1);
  cpu.mem_controller->Load16(*cpu.xip + 5, HyperCPU::Opcode::HALT);
  cpu.mem_controller->Load8(*cpu.xip + 7, HyperCPU::OperandTypes::NONE);
  *cpu.xlll0 = BYTE_DATA1_OF;
  *cpu.xlll1 = BYTE_DATA2_OF;

  cpu.Run();

  ASSERT_EQ(*cpu.xlll0, BYTE_SUM_OF);
  ASSERT_TRUE(cpu.ovf);
}

TEST_F(CPU_TEST, INSTR_ADD_R_R_b16_OF) {
  cpu.mem_controller->Load16(*cpu.xip, HyperCPU::Opcode::ADD);
  cpu.mem_controller->Load8(*cpu.xip + 2, EncodeTestFlags(HyperCPU::Mode::b16,  HyperCPU::Mode::b16, HyperCPU::OperandTypes::R_R));
  cpu.mem_controller->Load8(*cpu.xip + 3, HyperCPU::Reg::XLL0);
  cpu.mem_controller->Load8(*cpu.xip + 4, HyperCPU::Reg::XLL1);
  cpu.mem_controller->Load16(*cpu.xip + 5, HyperCPU::Opcode::HALT);
  cpu.mem_controller->Load8(*cpu.xip + 7, HyperCPU::OperandTypes::NONE);
  *cpu.xll0 = WORD_DATA1_OF;
  *cpu.xll1 = WORD_DATA2_OF;

  cpu.Run();

  ASSERT_EQ(*cpu.xll0, WORD_SUM_OF);
  ASSERT_TRUE(cpu.ovf);
}

TEST_F(CPU_TEST, INSTR_ADD_R_R_b32_OF) {
  cpu.mem_controller->Load16(*cpu.xip, HyperCPU::Opcode::ADD);
  cpu.mem_controller->Load8(*cpu.xip + 2, EncodeTestFlags(HyperCPU::Mode::b32,  HyperCPU::Mode::b32, HyperCPU::OperandTypes::R_R));
  cpu.mem_controller->Load8(*cpu.xip + 3, HyperCPU::Reg::XL0);
  cpu.mem_controller->Load8(*cpu.xip + 4, HyperCPU::Reg::XL1);
  cpu.mem_controller->Load16(*cpu.xip + 5, HyperCPU::Opcode::HALT);
  cpu.mem_controller->Load8(*cpu.xip + 7, HyperCPU::OperandTypes::NONE);
  *cpu.xl0 = DWORD_DATA1_OF;
  *cpu.xl1 = DWORD_DATA2_OF;

  cpu.Run();

  ASSERT_EQ(*cpu.xl0, DWORD_SUM_OF);
  ASSERT_TRUE(cpu.ovf);
}

TEST_F(CPU_TEST, INSTR_ADD_R_R_b64_OF) {
  cpu.mem_controller->Load16(*cpu.xip, HyperCPU::Opcode::ADD);
  cpu.mem_controller->Load8(*cpu.xip + 2, EncodeTestFlags(HyperCPU::Mode::b64,  HyperCPU::Mode::b64, HyperCPU::OperandTypes::R_R));
  cpu.mem_controller->Load8(*cpu.xip + 3, HyperCPU::Reg::X0);
  cpu.mem_controller->Load8(*cpu.xip + 4, HyperCPU::Reg::X1);
  cpu.mem_controller->Load16(*cpu.xip + 5, HyperCPU::Opcode::HALT);
  cpu.mem_controller->Load8(*cpu.xip + 7, HyperCPU::OperandTypes::NONE);
  *cpu.x0 = QWORD_DATA1_OF;
  *cpu.x1 = QWORD_DATA2_OF;

  cpu.Run();

  ASSERT_EQ(*cpu.x0, QWORD_SUM_OF);
  ASSERT_TRUE(cpu.ovf);
}

TEST_F(CPU_TEST, INSTR_ADD_R_RM_b8_OF) {
  cpu.mem_controller->Load16(*cpu.xip, HyperCPU::Opcode::ADD);
  cpu.mem_controller->Load8(*cpu.xip + 2, EncodeTestFlags(HyperCPU::Mode::b8,  HyperCPU::Mode::b8, HyperCPU::OperandTypes::R_RM)
;
  cpu.mem_controller->Load8(*cpu.xip + 3, HyperCPU::Reg::XLLL0);
  cpu.mem_controller->Load8(*cpu.xip + 4, HyperCPU::Reg::X1);
  cpu.mem_controller->Load16(*cpu.xip + 5, HyperCPU::Opcode::HALT);
  cpu.mem_controller->Load8(*cpu.xip + 7, HyperCPU::OperandTypes::NONE);
  *cpu.xlll0 = BYTE_DATA1_OF;
  cpu.mem_controller->Load8(1024, BYTE_DATA2_OF);
  *cpu.x1 = 1024;

  cpu.Run();

  ASSERT_EQ(*cpu.xlll0, BYTE_SUM_OF);
  ASSERT_TRUE(cpu.ovf);
}

TEST_F(CPU_TEST, INSTR_ADD_R_RM_b16_OF) {
  cpu.mem_controller->Load16(*cpu.xip, HyperCPU::Opcode::ADD);
  cpu.mem_controller->Load8(*cpu.xip + 2, EncodeTestFlags(HyperCPU::Mode::b16,  HyperCPU::Mode::b16, HyperCPU::OperandTypes::R_RM)
;
  cpu.mem_controller->Load8(*cpu.xip + 3, HyperCPU::Reg::XLL0);
  cpu.mem_controller->Load8(*cpu.xip + 4, HyperCPU::Reg::X1);
  cpu.mem_controller->Load16(*cpu.xip + 5, HyperCPU::Opcode::HALT);
  cpu.mem_controller->Load8(*cpu.xip + 7, HyperCPU::OperandTypes::NONE);
  *cpu.xll0 = WORD_DATA1_OF;
  cpu.mem_controller->Load16(1024, WORD_DATA2_OF);
  *cpu.x1 = 1024;

  cpu.Run();

  ASSERT_EQ(*cpu.xll0, WORD_SUM_OF);
  ASSERT_TRUE(cpu.ovf);
}

TEST_F(CPU_TEST, INSTR_ADD_R_RM_b32_OF) {
  cpu.mem_controller->Load16(*cpu.xip, HyperCPU::Opcode::ADD);
  cpu.mem_controller->Load8(*cpu.xip + 2, EncodeTestFlags(HyperCPU::Mode::b32,  HyperCPU::Mode::b32, HyperCPU::OperandTypes::R_RM)
;
  cpu.mem_controller->Load8(*cpu.xip + 3, HyperCPU::Reg::XL0);
  cpu.mem_controller->Load8(*cpu.xip + 4, HyperCPU::Reg::X1);
  cpu.mem_controller->Load16(*cpu.xip + 5, HyperCPU::Opcode::HALT);
  cpu.mem_controller->Load8(*cpu.xip + 7, HyperCPU::OperandTypes::NONE);
  *cpu.xl0 = DWORD_DATA1_OF;
  cpu.mem_controller->Load32(1024, DWORD_DATA2_OF);
  *cpu.x1 = 1024;

  cpu.Run();

  ASSERT_EQ(*cpu.xl0, DWORD_SUM_OF);
  ASSERT_TRUE(cpu.ovf);
}

TEST_F(CPU_TEST, INSTR_ADD_R_RM_b64_OF) {
  cpu.mem_controller->Load16(*cpu.xip, HyperCPU::Opcode::ADD);
  cpu.mem_controller->Load8(*cpu.xip + 2, EncodeTestFlags(HyperCPU::Mode::b64,  HyperCPU::Mode::b64, HyperCPU::OperandTypes::R_RM)
;
  cpu.mem_controller->Load8(*cpu.xip + 3, HyperCPU::Reg::X0);
  cpu.mem_controller->Load8(*cpu.xip + 4, HyperCPU::Reg::X1);
  cpu.mem_controller->Load16(*cpu.xip + 5, HyperCPU::Opcode::HALT);
  cpu.mem_controller->Load8(*cpu.xip + 7, HyperCPU::OperandTypes::NONE);
  *cpu.x0 = QWORD_DATA1_OF;
  cpu.mem_controller->Load64(1024, QWORD_DATA2_OF);
  *cpu.x1 = 1024;

  cpu.Run();

  ASSERT_EQ(*cpu.x0, QWORD_SUM_OF);
  ASSERT_TRUE(cpu.ovf);
}

TEST_F(CPU_TEST, INSTR_ADD_R_M_b8_OF) {
  cpu.mem_controller->Load16(*cpu.xip, HyperCPU::Opcode::ADD);
  cpu.mem_controller->Load8(*cpu.xip + 2, EncodeTestFlags(HyperCPU::Mode::b8,  HyperCPU::Mode::b8, HyperCPU::OperandTypes::R_M)
;
  cpu.mem_controller->Load8(*cpu.xip + 3, HyperCPU::Reg::XLLL0);
  cpu.mem_controller->Load64(*cpu.xip + 4, 1024);
  cpu.mem_controller->Load16(*cpu.xip + 12, HyperCPU::Opcode::HALT);
  cpu.mem_controller->Load8(*cpu.xip + 14, HyperCPU::OperandTypes::NONE);
  *cpu.xlll0 = BYTE_DATA1_OF;
  cpu.mem_controller->Load8(1024, BYTE_DATA2_OF);

  cpu.Run();

  ASSERT_EQ(*cpu.xlll0, BYTE_SUM_OF);
  ASSERT_TRUE(cpu.ovf);
}

TEST_F(CPU_TEST, INSTR_ADD_R_M_b16_OF) {
  cpu.mem_controller->Load16(*cpu.xip, HyperCPU::Opcode::ADD);
  cpu.mem_controller->Load8(*cpu.xip + 2, EncodeTestFlags(HyperCPU::Mode::b16,  HyperCPU::Mode::b16, HyperCPU::OperandTypes::R_M)
;
  cpu.mem_controller->Load8(*cpu.xip + 3, HyperCPU::Reg::XLL0);
  cpu.mem_controller->Load64(*cpu.xip + 4, 1024);
  cpu.mem_controller->Load16(*cpu.xip + 12, HyperCPU::Opcode::HALT);
  cpu.mem_controller->Load8(*cpu.xip + 14, HyperCPU::OperandTypes::NONE);
  *cpu.xll0 = WORD_DATA1_OF;
  cpu.mem_controller->Load16(1024, WORD_DATA2_OF);

  cpu.Run();

  ASSERT_EQ(*cpu.xll0, WORD_SUM_OF);
  ASSERT_TRUE(cpu.ovf);
}

TEST_F(CPU_TEST, INSTR_ADD_R_M_b32_OF) {
  cpu.mem_controller->Load16(*cpu.xip, HyperCPU::Opcode::ADD);
  cpu.mem_controller->Load8(*cpu.xip + 2, EncodeTestFlags(HyperCPU::Mode::b32,  HyperCPU::Mode::b32, HyperCPU::OperandTypes::R_M)
;
  cpu.mem_controller->Load8(*cpu.xip + 3, HyperCPU::Reg::XL0);
  cpu.mem_controller->Load64(*cpu.xip + 4, 1024);
  cpu.mem_controller->Load16(*cpu.xip + 12, HyperCPU::Opcode::HALT);
  cpu.mem_controller->Load8(*cpu.xip + 14, HyperCPU::OperandTypes::NONE);
  *cpu.xl0 = DWORD_DATA1_OF;
  cpu.mem_controller->Load32(1024, DWORD_DATA2_OF);

  cpu.Run();

  ASSERT_EQ(*cpu.xl0, DWORD_SUM_OF);
  ASSERT_TRUE(cpu.ovf);
}

TEST_F(CPU_TEST, INSTR_ADD_R_M_b64_OF) {
  cpu.mem_controller->Load16(*cpu.xip, HyperCPU::Opcode::ADD);
  cpu.mem_controller->Load8(*cpu.xip + 2, EncodeTestFlags(HyperCPU::Mode::b64,  HyperCPU::Mode::b64, HyperCPU::OperandTypes::R_M)
;
  cpu.mem_controller->Load8(*cpu.xip + 3, HyperCPU::Reg::X0);
  cpu.mem_controller->Load64(*cpu.xip + 4, 1024);
  cpu.mem_controller->Load16(*cpu.xip + 12, HyperCPU::Opcode::HALT);
  cpu.mem_controller->Load8(*cpu.xip + 14, HyperCPU::OperandTypes::NONE);
  *cpu.x0 = QWORD_DATA1_OF;
  cpu.mem_controller->Load64(1024, QWORD_DATA2_OF);

  cpu.Run();

  ASSERT_EQ(*cpu.x0, QWORD_SUM_OF);
  ASSERT_TRUE(cpu.ovf);
}

TEST_F(CPU_TEST, INSTR_ADD_R_IMM_b8_OF) {
  cpu.mem_controller->Load16(*cpu.xip, HyperCPU::Opcode::ADD);
  cpu.mem_controller->Load8(*cpu.xip + 2, EncodeTestFlags(HyperCPU::Mode::b8,  HyperCPU::Mode::b8, HyperCPU::OperandTypes::R_IMM)
;
  cpu.mem_controller->Load8(*cpu.xip + 3, HyperCPU::Reg::XLLL0);
  cpu.mem_controller->Load8(*cpu.xip + 4, BYTE_DATA2_OF);
  cpu.mem_controller->Load16(*cpu.xip + 5, HyperCPU::Opcode::HALT);
  cpu.mem_controller->Load8(*cpu.xip + 7, HyperCPU::OperandTypes::NONE);
  *cpu.xlll0 = BYTE_DATA1_OF;

  cpu.Run();

  ASSERT_EQ(*cpu.xlll0, BYTE_SUM_OF);
  ASSERT_TRUE(cpu.ovf);
}

TEST_F(CPU_TEST, INSTR_ADD_R_IMM_b16_OF) {
  cpu.mem_controller->Load16(*cpu.xip, HyperCPU::Opcode::ADD);
  cpu.mem_controller->Load8(*cpu.xip + 2, EncodeTestFlags(HyperCPU::Mode::b16,  HyperCPU::Mode::b16, HyperCPU::OperandTypes::R_IMM)
;
  cpu.mem_controller->Load8(*cpu.xip + 3, HyperCPU::Reg::XLL0);
  cpu.mem_controller->Load16(*cpu.xip + 4, WORD_DATA2_OF);
  cpu.mem_controller->Load16(*cpu.xip + 6, HyperCPU::Opcode::HALT);
  cpu.mem_controller->Load8(*cpu.xip + 8, HyperCPU::OperandTypes::NONE);
  *cpu.xll0 = WORD_DATA1_OF;

  cpu.Run();

  ASSERT_EQ(*cpu.xll0, WORD_SUM_OF);
  ASSERT_TRUE(cpu.ovf);
}

TEST_F(CPU_TEST, INSTR_ADD_R_IMM_b32_OF) {
  cpu.mem_controller->Load16(*cpu.xip, HyperCPU::Opcode::ADD);
  cpu.mem_controller->Load8(*cpu.xip + 2, EncodeTestFlags(HyperCPU::Mode::b32,  HyperCPU::Mode::b32, HyperCPU::OperandTypes::R_IMM)
;
  cpu.mem_controller->Load8(*cpu.xip + 3, HyperCPU::Reg::XL0);
  cpu.mem_controller->Load32(*cpu.xip + 4, DWORD_DATA2_OF);
  cpu.mem_controller->Load16(*cpu.xip + 8, HyperCPU::Opcode::HALT);
  cpu.mem_controller->Load8(*cpu.xip + 10, HyperCPU::OperandTypes::NONE);
  *cpu.xl0 = DWORD_DATA1_OF;

  cpu.Run();

  ASSERT_EQ(*cpu.xl0, DWORD_SUM_OF);
  ASSERT_TRUE(cpu.ovf);
}

TEST_F(CPU_TEST, INSTR_ADD_R_IMM_b64_OF) {
  cpu.mem_controller->Load16(*cpu.xip, HyperCPU::Opcode::ADD);
  cpu.mem_controller->Load8(*cpu.xip + 2, EncodeTestFlags(HyperCPU::Mode::b64,  HyperCPU::Mode::b64, HyperCPU::OperandTypes::R_IMM));
  cpu.mem_controller->Load8(*cpu.xip + 3, HyperCPU::Reg::X0);
  cpu.mem_controller->Load64(*cpu.xip + 4, QWORD_DATA2_OF);
  cpu.mem_controller->Load16(*cpu.xip + 12, HyperCPU::Opcode::HALT);
  cpu.mem_controller->Load8(*cpu.xip + 14, HyperCPU::OperandTypes::NONE);
  *cpu.x0 = QWORD_DATA1_OF;

  cpu.Run();

  ASSERT_EQ(*cpu.x0, QWORD_SUM_OF);
  ASSERT_TRUE(cpu.ovf);
}
