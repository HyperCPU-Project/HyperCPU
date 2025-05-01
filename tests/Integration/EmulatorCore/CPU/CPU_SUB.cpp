#include <Core/CPU/Instructions/Registers.hpp>
#include <Core/CPU/Instructions/Flags.hpp>

#include <fixtures.hpp>


static constexpr std::uint8_t BYTE_DATA1 = 0x60;
static constexpr std::uint8_t BYTE_DATA2 = 0x55;
static constexpr std::uint8_t BYTE_RESULT = BYTE_DATA1 - BYTE_DATA2;
static constexpr std::uint16_t WORD_DATA1 = 0x6060;
static constexpr std::uint16_t WORD_DATA2 = 0x5555;
static constexpr std::uint16_t WORD_RESULT = WORD_DATA1 - WORD_DATA2;
static constexpr std::uint32_t DWORD_DATA1 = 0x60606060;
static constexpr std::uint32_t DWORD_DATA2 = 0x55555555;
static constexpr std::uint32_t DWORD_RESULT = DWORD_DATA1 - DWORD_DATA2;
static constexpr std::uint64_t QWORD_DATA1 = 0x6060606060606060;
static constexpr std::uint64_t QWORD_DATA2 = 0x5555555555555555;
static constexpr std::uint64_t QWORD_RESULT = QWORD_DATA1 - QWORD_DATA2;

static constexpr std::uint8_t BYTE_DATA1_UF = 0x60;
static constexpr std::uint8_t BYTE_DATA2_UF = 0xBA;
static constexpr std::uint8_t BYTE_RESULT_UF = static_cast<std::uint8_t>(BYTE_DATA1_UF - BYTE_DATA2_UF);
static constexpr std::uint16_t WORD_DATA1_UF = 0x6060;
static constexpr std::uint16_t WORD_DATA2_UF = 0xBABA;
static constexpr std::uint16_t WORD_RESULT_UF = static_cast<std::uint16_t>(WORD_DATA1_UF - WORD_DATA2_UF);
static constexpr std::uint32_t DWORD_DATA1_UF = 0x60606060;
static constexpr std::uint32_t DWORD_DATA2_UF = 0xBABABABA;
static constexpr std::uint32_t DWORD_RESULT_UF = static_cast<std::uint32_t>(DWORD_DATA1_UF - DWORD_DATA2_UF);
static constexpr std::uint64_t QWORD_DATA1_UF = 0x6060606060606060;
static constexpr std::uint64_t QWORD_DATA2_UF = 0xBABABABABABABABA;
static constexpr std::uint64_t QWORD_RESULT_UF = QWORD_DATA1_UF - QWORD_DATA2_UF;

TEST_F(CPU_TEST, INSTR_SUB_R_R_b8) {
  cpu.mem_controller->Load16(*cpu.xip, HyperCPU::Opcode::SUB);
  cpu.mem_controller->Load8(*cpu.xip + 2, HyperCPU::Mode::b8 << 4 | HyperCPU::OperandTypes::R_R);
  cpu.mem_controller->Load8(*cpu.xip + 3, HyperCPU::Registers::XLLL0);
  cpu.mem_controller->Load8(*cpu.xip + 4, HyperCPU::Registers::XLLL1);
  cpu.mem_controller->Load16(*cpu.xip + 5, HyperCPU::Opcode::HALT);
  cpu.mem_controller->Load8(*cpu.xip + 7, HyperCPU::OperandTypes::NONE);
  *cpu.xlll0 = BYTE_DATA1;
  *cpu.xlll1 = BYTE_DATA2;

  cpu.Run();

  ASSERT_EQ(*cpu.xlll0, BYTE_RESULT);
}

TEST_F(CPU_TEST, INSTR_SUB_R_R_b16) {
  cpu.mem_controller->Load16(*cpu.xip, HyperCPU::Opcode::SUB);
  cpu.mem_controller->Load8(*cpu.xip + 2, HyperCPU::Mode::b16 << 4 | HyperCPU::OperandTypes::R_R);
  cpu.mem_controller->Load8(*cpu.xip + 3, HyperCPU::Registers::XLL0);
  cpu.mem_controller->Load8(*cpu.xip + 4, HyperCPU::Registers::XLL1);
  cpu.mem_controller->Load16(*cpu.xip + 5, HyperCPU::Opcode::HALT);
  cpu.mem_controller->Load8(*cpu.xip + 7, HyperCPU::OperandTypes::NONE);
  *cpu.xll0 = WORD_DATA1;
  *cpu.xll1 = WORD_DATA2;

  cpu.Run();

  ASSERT_EQ(*cpu.xll0, WORD_RESULT);
}

TEST_F(CPU_TEST, INSTR_SUB_R_R_b32) {
  cpu.mem_controller->Load16(*cpu.xip, HyperCPU::Opcode::SUB);
  cpu.mem_controller->Load8(*cpu.xip + 2, HyperCPU::Mode::b32 << 4 | HyperCPU::OperandTypes::R_R);
  cpu.mem_controller->Load8(*cpu.xip + 3, HyperCPU::Registers::XL0);
  cpu.mem_controller->Load8(*cpu.xip + 4, HyperCPU::Registers::XL1);
  cpu.mem_controller->Load16(*cpu.xip + 5, HyperCPU::Opcode::HALT);
  cpu.mem_controller->Load8(*cpu.xip + 7, HyperCPU::OperandTypes::NONE);
  *cpu.xl0 = DWORD_DATA1;
  *cpu.xl1 = DWORD_DATA2;

  cpu.Run();

  ASSERT_EQ(*cpu.xl0, DWORD_RESULT);
}

TEST_F(CPU_TEST, INSTR_SUB_R_R_b64) {
  cpu.mem_controller->Load16(*cpu.xip, HyperCPU::Opcode::SUB);
  cpu.mem_controller->Load8(*cpu.xip + 2, HyperCPU::Mode::b64 << 4 | HyperCPU::OperandTypes::R_R);
  cpu.mem_controller->Load8(*cpu.xip + 3, HyperCPU::Registers::X0);
  cpu.mem_controller->Load8(*cpu.xip + 4, HyperCPU::Registers::X1);
  cpu.mem_controller->Load16(*cpu.xip + 5, HyperCPU::Opcode::HALT);
  cpu.mem_controller->Load8(*cpu.xip + 7, HyperCPU::OperandTypes::NONE);
  *cpu.x0 = QWORD_DATA1;
  *cpu.x1 = QWORD_DATA2;

  cpu.Run();

  ASSERT_EQ(*cpu.x0, QWORD_RESULT);
}

TEST_F(CPU_TEST, INSTR_SUB_R_RM_b8) {
  cpu.mem_controller->Load16(*cpu.xip, HyperCPU::Opcode::SUB);
  cpu.mem_controller->Load8(*cpu.xip + 2, HyperCPU::Mode::b8 << 4 | HyperCPU::OperandTypes::R_RM);
  cpu.mem_controller->Load8(*cpu.xip + 3, HyperCPU::Registers::XLLL0);
  cpu.mem_controller->Load8(*cpu.xip + 4, HyperCPU::Registers::X1);
  cpu.mem_controller->Load16(*cpu.xip + 5, HyperCPU::Opcode::HALT);
  cpu.mem_controller->Load8(*cpu.xip + 7, HyperCPU::OperandTypes::NONE);
  *cpu.xlll0 = BYTE_DATA1;
  cpu.mem_controller->Load8(1024, BYTE_DATA2);
  *cpu.x1 = 1024;

  cpu.Run();

  ASSERT_EQ(*cpu.xlll0, BYTE_RESULT);
}

TEST_F(CPU_TEST, INSTR_SUB_R_RM_b16) {
  cpu.mem_controller->Load16(*cpu.xip, HyperCPU::Opcode::SUB);
  cpu.mem_controller->Load8(*cpu.xip + 2, HyperCPU::Mode::b16 << 4 | HyperCPU::OperandTypes::R_RM);
  cpu.mem_controller->Load8(*cpu.xip + 3, HyperCPU::Registers::XLL0);
  cpu.mem_controller->Load8(*cpu.xip + 4, HyperCPU::Registers::X1);
  cpu.mem_controller->Load16(*cpu.xip + 5, HyperCPU::Opcode::HALT);
  cpu.mem_controller->Load8(*cpu.xip + 7, HyperCPU::OperandTypes::NONE);
  *cpu.xll0 = WORD_DATA1;
  cpu.mem_controller->Load16(1024, WORD_DATA2);
  *cpu.x1 = 1024;

  cpu.Run();

  ASSERT_EQ(*cpu.xll0, WORD_RESULT);
}

TEST_F(CPU_TEST, INSTR_SUB_R_RM_b32) {
  cpu.mem_controller->Load16(*cpu.xip, HyperCPU::Opcode::SUB);
  cpu.mem_controller->Load8(*cpu.xip + 2, HyperCPU::Mode::b32 << 4 | HyperCPU::OperandTypes::R_RM);
  cpu.mem_controller->Load8(*cpu.xip + 3, HyperCPU::Registers::XL0);
  cpu.mem_controller->Load8(*cpu.xip + 4, HyperCPU::Registers::X1);
  cpu.mem_controller->Load16(*cpu.xip + 5, HyperCPU::Opcode::HALT);
  cpu.mem_controller->Load8(*cpu.xip + 7, HyperCPU::OperandTypes::NONE);
  *cpu.xl0 = DWORD_DATA1;
  cpu.mem_controller->Load32(1024, DWORD_DATA2);
  *cpu.x1 = 1024;

  cpu.Run();

  ASSERT_EQ(*cpu.xl0, DWORD_RESULT);
}

TEST_F(CPU_TEST, INSTR_SUB_R_RM_b64) {
  cpu.mem_controller->Load16(*cpu.xip, HyperCPU::Opcode::SUB);
  cpu.mem_controller->Load8(*cpu.xip + 2, HyperCPU::Mode::b64 << 4 | HyperCPU::OperandTypes::R_RM);
  cpu.mem_controller->Load8(*cpu.xip + 3, HyperCPU::Registers::X0);
  cpu.mem_controller->Load8(*cpu.xip + 4, HyperCPU::Registers::X1);
  cpu.mem_controller->Load16(*cpu.xip + 5, HyperCPU::Opcode::HALT);
  cpu.mem_controller->Load8(*cpu.xip + 7, HyperCPU::OperandTypes::NONE);
  *cpu.x0 = QWORD_DATA1;
  cpu.mem_controller->Load64(1024, QWORD_DATA2);
  *cpu.x1 = 1024;

  cpu.Run();

  ASSERT_EQ(*cpu.x0, QWORD_RESULT);
}

TEST_F(CPU_TEST, INSTR_SUB_R_M_b8) {
  cpu.mem_controller->Load16(*cpu.xip, HyperCPU::Opcode::SUB);
  cpu.mem_controller->Load8(*cpu.xip + 2, HyperCPU::Mode::b8 << 4 | HyperCPU::OperandTypes::R_M);
  cpu.mem_controller->Load8(*cpu.xip + 3, HyperCPU::Registers::XLLL0);
  cpu.mem_controller->Load64(*cpu.xip + 4, 1024);
  cpu.mem_controller->Load16(*cpu.xip + 12, HyperCPU::Opcode::HALT);
  cpu.mem_controller->Load8(*cpu.xip + 14, HyperCPU::OperandTypes::NONE);
  *cpu.xlll0 = BYTE_DATA1;
  cpu.mem_controller->Load8(1024, BYTE_DATA2);

  cpu.Run();

  ASSERT_EQ(*cpu.xlll0, BYTE_RESULT);
}

TEST_F(CPU_TEST, INSTR_SUB_R_M_b16) {
  cpu.mem_controller->Load16(*cpu.xip, HyperCPU::Opcode::SUB);
  cpu.mem_controller->Load8(*cpu.xip + 2, HyperCPU::Mode::b16 << 4 | HyperCPU::OperandTypes::R_M);
  cpu.mem_controller->Load8(*cpu.xip + 3, HyperCPU::Registers::XLL0);
  cpu.mem_controller->Load64(*cpu.xip + 4, 1024);
  cpu.mem_controller->Load16(*cpu.xip + 12, HyperCPU::Opcode::HALT);
  cpu.mem_controller->Load8(*cpu.xip + 14, HyperCPU::OperandTypes::NONE);
  *cpu.xll0 = WORD_DATA1;
  cpu.mem_controller->Load16(1024, WORD_DATA2);

  cpu.Run();

  ASSERT_EQ(*cpu.xll0, WORD_RESULT);
}

TEST_F(CPU_TEST, INSTR_SUB_R_M_b32) {
  cpu.mem_controller->Load16(*cpu.xip, HyperCPU::Opcode::SUB);
  cpu.mem_controller->Load8(*cpu.xip + 2, HyperCPU::Mode::b32 << 4 | HyperCPU::OperandTypes::R_M);
  cpu.mem_controller->Load8(*cpu.xip + 3, HyperCPU::Registers::XL0);
  cpu.mem_controller->Load64(*cpu.xip + 4, 1024);
  cpu.mem_controller->Load16(*cpu.xip + 12, HyperCPU::Opcode::HALT);
  cpu.mem_controller->Load8(*cpu.xip + 14, HyperCPU::OperandTypes::NONE);
  *cpu.xl0 = DWORD_DATA1;
  cpu.mem_controller->Load32(1024, DWORD_DATA2);

  cpu.Run();

  ASSERT_EQ(*cpu.xl0, DWORD_RESULT);
}

TEST_F(CPU_TEST, INSTR_SUB_R_M_b64) {
  cpu.mem_controller->Load16(*cpu.xip, HyperCPU::Opcode::SUB);
  cpu.mem_controller->Load8(*cpu.xip + 2, HyperCPU::Mode::b64 << 4 | HyperCPU::OperandTypes::R_M);
  cpu.mem_controller->Load8(*cpu.xip + 3, HyperCPU::Registers::X0);
  cpu.mem_controller->Load64(*cpu.xip + 4, 1024);
  cpu.mem_controller->Load16(*cpu.xip + 12, HyperCPU::Opcode::HALT);
  cpu.mem_controller->Load8(*cpu.xip + 14, HyperCPU::OperandTypes::NONE);
  *cpu.x0 = QWORD_DATA1;
  cpu.mem_controller->Load64(1024, QWORD_DATA2);

  cpu.Run();

  ASSERT_EQ(*cpu.x0, QWORD_RESULT);
}

TEST_F(CPU_TEST, INSTR_SUB_R_IMM_b8) {
  cpu.mem_controller->Load16(*cpu.xip, HyperCPU::Opcode::SUB);
  cpu.mem_controller->Load8(*cpu.xip + 2, HyperCPU::Mode::b8 << 4 | HyperCPU::OperandTypes::R_IMM);
  cpu.mem_controller->Load8(*cpu.xip + 3, HyperCPU::Registers::XLLL0);
  cpu.mem_controller->Load8(*cpu.xip + 4, BYTE_DATA2);
  cpu.mem_controller->Load16(*cpu.xip + 5, HyperCPU::Opcode::HALT);
  cpu.mem_controller->Load8(*cpu.xip + 7, HyperCPU::OperandTypes::NONE);
  *cpu.xlll0 = BYTE_DATA1;

  cpu.Run();

  ASSERT_EQ(*cpu.xlll0, BYTE_RESULT);
}

TEST_F(CPU_TEST, INSTR_SUB_R_IMM_b16) {
  cpu.mem_controller->Load16(*cpu.xip, HyperCPU::Opcode::SUB);
  cpu.mem_controller->Load8(*cpu.xip + 2, HyperCPU::Mode::b16 << 4 | HyperCPU::OperandTypes::R_IMM);
  cpu.mem_controller->Load8(*cpu.xip + 3, HyperCPU::Registers::XLL0);
  cpu.mem_controller->Load16(*cpu.xip + 4, WORD_DATA2);
  cpu.mem_controller->Load16(*cpu.xip + 6, HyperCPU::Opcode::HALT);
  cpu.mem_controller->Load8(*cpu.xip + 8, HyperCPU::OperandTypes::NONE);
  *cpu.xll0 = WORD_DATA1;

  cpu.Run();

  ASSERT_EQ(*cpu.xll0, WORD_RESULT);
}

TEST_F(CPU_TEST, INSTR_SUB_R_IMM_b32) {
  cpu.mem_controller->Load16(*cpu.xip, HyperCPU::Opcode::SUB);
  cpu.mem_controller->Load8(*cpu.xip + 2, HyperCPU::Mode::b32 << 4 | HyperCPU::OperandTypes::R_IMM);
  cpu.mem_controller->Load8(*cpu.xip + 3, HyperCPU::Registers::XL0);
  cpu.mem_controller->Load32(*cpu.xip + 4, DWORD_DATA2);
  cpu.mem_controller->Load16(*cpu.xip + 8, HyperCPU::Opcode::HALT);
  cpu.mem_controller->Load8(*cpu.xip + 10, HyperCPU::OperandTypes::NONE);
  *cpu.xl0 = DWORD_DATA1;

  cpu.Run();

  ASSERT_EQ(*cpu.xl0, DWORD_RESULT);
}

TEST_F(CPU_TEST, INSTR_SUB_R_IMM_b64) {
  cpu.mem_controller->Load16(*cpu.xip, HyperCPU::Opcode::SUB);
  cpu.mem_controller->Load8(*cpu.xip + 2, HyperCPU::Mode::b64 << 4 | HyperCPU::OperandTypes::R_IMM);
  cpu.mem_controller->Load8(*cpu.xip + 3, HyperCPU::Registers::X0);
  cpu.mem_controller->Load64(*cpu.xip + 4, QWORD_DATA2);
  cpu.mem_controller->Load16(*cpu.xip + 12, HyperCPU::Opcode::HALT);
  cpu.mem_controller->Load8(*cpu.xip + 14, HyperCPU::OperandTypes::NONE);
  *cpu.x0 = QWORD_DATA1;

  cpu.Run();

  ASSERT_EQ(*cpu.x0, QWORD_RESULT);
}

TEST_F(CPU_TEST, INSTR_SUB_R_R_b8_UF) {
  cpu.mem_controller->Load16(*cpu.xip, HyperCPU::Opcode::SUB);
  cpu.mem_controller->Load8(*cpu.xip + 2, HyperCPU::Mode::b8 << 4 | HyperCPU::OperandTypes::R_R);
  cpu.mem_controller->Load8(*cpu.xip + 3, HyperCPU::Registers::XLLL0);
  cpu.mem_controller->Load8(*cpu.xip + 4, HyperCPU::Registers::XLLL1);
  cpu.mem_controller->Load16(*cpu.xip + 5, HyperCPU::Opcode::HALT);
  cpu.mem_controller->Load8(*cpu.xip + 7, HyperCPU::OperandTypes::NONE);
  *cpu.xlll0 = BYTE_DATA1_UF;
  *cpu.xlll1 = BYTE_DATA2_UF;

  cpu.Run();

  ASSERT_EQ(*cpu.xlll0, BYTE_RESULT_UF);
  ASSERT_TRUE(cpu.udf);
}

TEST_F(CPU_TEST, INSTR_SUB_R_R_b16_UF) {
  cpu.mem_controller->Load16(*cpu.xip, HyperCPU::Opcode::SUB);
  cpu.mem_controller->Load8(*cpu.xip + 2, HyperCPU::Mode::b16 << 4 | HyperCPU::OperandTypes::R_R);
  cpu.mem_controller->Load8(*cpu.xip + 3, HyperCPU::Registers::XLL0);
  cpu.mem_controller->Load8(*cpu.xip + 4, HyperCPU::Registers::XLL1);
  cpu.mem_controller->Load16(*cpu.xip + 5, HyperCPU::Opcode::HALT);
  cpu.mem_controller->Load8(*cpu.xip + 7, HyperCPU::OperandTypes::NONE);
  *cpu.xll0 = WORD_DATA1_UF;
  *cpu.xll1 = WORD_DATA2_UF;

  cpu.Run();

  ASSERT_EQ(*cpu.xll0, WORD_RESULT_UF);
  ASSERT_TRUE(cpu.udf);
}

TEST_F(CPU_TEST, INSTR_SUB_R_R_b32_UF) {
  cpu.mem_controller->Load16(*cpu.xip, HyperCPU::Opcode::SUB);
  cpu.mem_controller->Load8(*cpu.xip + 2, HyperCPU::Mode::b32 << 4 | HyperCPU::OperandTypes::R_R);
  cpu.mem_controller->Load8(*cpu.xip + 3, HyperCPU::Registers::XL0);
  cpu.mem_controller->Load8(*cpu.xip + 4, HyperCPU::Registers::XL1);
  cpu.mem_controller->Load16(*cpu.xip + 5, HyperCPU::Opcode::HALT);
  cpu.mem_controller->Load8(*cpu.xip + 7, HyperCPU::OperandTypes::NONE);
  *cpu.xl0 = DWORD_DATA1_UF;
  *cpu.xl1 = DWORD_DATA2_UF;

  cpu.Run();

  ASSERT_EQ(*cpu.xl0, DWORD_RESULT_UF);
  ASSERT_TRUE(cpu.udf);
}

TEST_F(CPU_TEST, INSTR_SUB_R_R_b64_UF) {
  cpu.mem_controller->Load16(*cpu.xip, HyperCPU::Opcode::SUB);
  cpu.mem_controller->Load8(*cpu.xip + 2, HyperCPU::Mode::b64 << 4 | HyperCPU::OperandTypes::R_R);
  cpu.mem_controller->Load8(*cpu.xip + 3, HyperCPU::Registers::X0);
  cpu.mem_controller->Load8(*cpu.xip + 4, HyperCPU::Registers::X1);
  cpu.mem_controller->Load16(*cpu.xip + 5, HyperCPU::Opcode::HALT);
  cpu.mem_controller->Load8(*cpu.xip + 7, HyperCPU::OperandTypes::NONE);
  *cpu.x0 = QWORD_DATA1_UF;
  *cpu.x1 = QWORD_DATA2_UF;

  cpu.Run();

  ASSERT_EQ(*cpu.x0, QWORD_RESULT_UF);
  ASSERT_TRUE(cpu.udf);
}

TEST_F(CPU_TEST, INSTR_SUB_R_RM_b8_UF) {
  cpu.mem_controller->Load16(*cpu.xip, HyperCPU::Opcode::SUB);
  cpu.mem_controller->Load8(*cpu.xip + 2, HyperCPU::Mode::b8 << 4 | HyperCPU::OperandTypes::R_RM);
  cpu.mem_controller->Load8(*cpu.xip + 3, HyperCPU::Registers::XLLL0);
  cpu.mem_controller->Load8(*cpu.xip + 4, HyperCPU::Registers::X1);
  cpu.mem_controller->Load16(*cpu.xip + 5, HyperCPU::Opcode::HALT);
  cpu.mem_controller->Load8(*cpu.xip + 7, HyperCPU::OperandTypes::NONE);
  *cpu.xlll0 = BYTE_DATA1_UF;
  cpu.mem_controller->Load8(1024, BYTE_DATA2_UF);
  *cpu.x1 = 1024;

  cpu.Run();

  ASSERT_EQ(*cpu.xlll0, BYTE_RESULT_UF);
  ASSERT_TRUE(cpu.udf);
}

TEST_F(CPU_TEST, INSTR_SUB_R_RM_b16_UF) {
  cpu.mem_controller->Load16(*cpu.xip, HyperCPU::Opcode::SUB);
  cpu.mem_controller->Load8(*cpu.xip + 2, HyperCPU::Mode::b16 << 4 | HyperCPU::OperandTypes::R_RM);
  cpu.mem_controller->Load8(*cpu.xip + 3, HyperCPU::Registers::XLL0);
  cpu.mem_controller->Load8(*cpu.xip + 4, HyperCPU::Registers::X1);
  cpu.mem_controller->Load16(*cpu.xip + 5, HyperCPU::Opcode::HALT);
  cpu.mem_controller->Load8(*cpu.xip + 7, HyperCPU::OperandTypes::NONE);
  *cpu.xll0 = WORD_DATA1_UF;
  cpu.mem_controller->Load16(1024, WORD_DATA2_UF);
  *cpu.x1 = 1024;

  cpu.Run();

  ASSERT_EQ(*cpu.xll0, WORD_RESULT_UF);
  ASSERT_TRUE(cpu.udf);
}

TEST_F(CPU_TEST, INSTR_SUB_R_RM_b32_UF) {
  cpu.mem_controller->Load16(*cpu.xip, HyperCPU::Opcode::SUB);
  cpu.mem_controller->Load8(*cpu.xip + 2, HyperCPU::Mode::b32 << 4 | HyperCPU::OperandTypes::R_RM);
  cpu.mem_controller->Load8(*cpu.xip + 3, HyperCPU::Registers::XL0);
  cpu.mem_controller->Load8(*cpu.xip + 4, HyperCPU::Registers::X1);
  cpu.mem_controller->Load16(*cpu.xip + 5, HyperCPU::Opcode::HALT);
  cpu.mem_controller->Load8(*cpu.xip + 7, HyperCPU::OperandTypes::NONE);
  *cpu.xl0 = DWORD_DATA1_UF;
  cpu.mem_controller->Load32(1024, DWORD_DATA2_UF);
  *cpu.x1 = 1024;

  cpu.Run();

  ASSERT_EQ(*cpu.xl0, DWORD_RESULT_UF);
  ASSERT_TRUE(cpu.udf);
}

TEST_F(CPU_TEST, INSTR_SUB_R_RM_b64_UF) {
  cpu.mem_controller->Load16(*cpu.xip, HyperCPU::Opcode::SUB);
  cpu.mem_controller->Load8(*cpu.xip + 2, HyperCPU::Mode::b64 << 4 | HyperCPU::OperandTypes::R_RM);
  cpu.mem_controller->Load8(*cpu.xip + 3, HyperCPU::Registers::X0);
  cpu.mem_controller->Load8(*cpu.xip + 4, HyperCPU::Registers::X1);
  cpu.mem_controller->Load16(*cpu.xip + 5, HyperCPU::Opcode::HALT);
  cpu.mem_controller->Load8(*cpu.xip + 7, HyperCPU::OperandTypes::NONE);
  *cpu.x0 = QWORD_DATA1_UF;
  cpu.mem_controller->Load64(1024, QWORD_DATA2_UF);
  *cpu.x1 = 1024;

  cpu.Run();

  ASSERT_EQ(*cpu.x0, QWORD_RESULT_UF);
  ASSERT_TRUE(cpu.udf);
}

TEST_F(CPU_TEST, INSTR_SUB_R_M_b8_UF) {
  cpu.mem_controller->Load16(*cpu.xip, HyperCPU::Opcode::SUB);
  cpu.mem_controller->Load8(*cpu.xip + 2, HyperCPU::Mode::b8 << 4 | HyperCPU::OperandTypes::R_M);
  cpu.mem_controller->Load8(*cpu.xip + 3, HyperCPU::Registers::XLLL0);
  cpu.mem_controller->Load64(*cpu.xip + 4, 1024);
  cpu.mem_controller->Load16(*cpu.xip + 12, HyperCPU::Opcode::HALT);
  cpu.mem_controller->Load8(*cpu.xip + 14, HyperCPU::OperandTypes::NONE);
  *cpu.xlll0 = BYTE_DATA1_UF;
  cpu.mem_controller->Load8(1024, BYTE_DATA2_UF);

  cpu.Run();

  ASSERT_EQ(*cpu.xlll0, BYTE_RESULT_UF);
  ASSERT_TRUE(cpu.udf);
}

TEST_F(CPU_TEST, INSTR_SUB_R_M_b16_UF) {
  cpu.mem_controller->Load16(*cpu.xip, HyperCPU::Opcode::SUB);
  cpu.mem_controller->Load8(*cpu.xip + 2, HyperCPU::Mode::b16 << 4 | HyperCPU::OperandTypes::R_M);
  cpu.mem_controller->Load8(*cpu.xip + 3, HyperCPU::Registers::XLL0);
  cpu.mem_controller->Load64(*cpu.xip + 4, 1024);
  cpu.mem_controller->Load16(*cpu.xip + 12, HyperCPU::Opcode::HALT);
  cpu.mem_controller->Load8(*cpu.xip + 14, HyperCPU::OperandTypes::NONE);
  *cpu.xll0 = WORD_DATA1_UF;
  cpu.mem_controller->Load16(1024, WORD_DATA2_UF);

  cpu.Run();

  ASSERT_EQ(*cpu.xll0, WORD_RESULT_UF);
  ASSERT_TRUE(cpu.udf);
}

TEST_F(CPU_TEST, INSTR_SUB_R_M_b32_UF) {
  cpu.mem_controller->Load16(*cpu.xip, HyperCPU::Opcode::SUB);
  cpu.mem_controller->Load8(*cpu.xip + 2, HyperCPU::Mode::b32 << 4 | HyperCPU::OperandTypes::R_M);
  cpu.mem_controller->Load8(*cpu.xip + 3, HyperCPU::Registers::XL0);
  cpu.mem_controller->Load64(*cpu.xip + 4, 1024);
  cpu.mem_controller->Load16(*cpu.xip + 12, HyperCPU::Opcode::HALT);
  cpu.mem_controller->Load8(*cpu.xip + 14, HyperCPU::OperandTypes::NONE);
  *cpu.xl0 = DWORD_DATA1_UF;
  cpu.mem_controller->Load32(1024, DWORD_DATA2_UF);

  cpu.Run();

  ASSERT_EQ(*cpu.xl0, DWORD_RESULT_UF);
  ASSERT_TRUE(cpu.udf);
}

TEST_F(CPU_TEST, INSTR_SUB_R_M_b64_UF) {
  cpu.mem_controller->Load16(*cpu.xip, HyperCPU::Opcode::SUB);
  cpu.mem_controller->Load8(*cpu.xip + 2, HyperCPU::Mode::b64 << 4 | HyperCPU::OperandTypes::R_M);
  cpu.mem_controller->Load8(*cpu.xip + 3, HyperCPU::Registers::X0);
  cpu.mem_controller->Load64(*cpu.xip + 4, 1024);
  cpu.mem_controller->Load16(*cpu.xip + 12, HyperCPU::Opcode::HALT);
  cpu.mem_controller->Load8(*cpu.xip + 14, HyperCPU::OperandTypes::NONE);
  *cpu.x0 = QWORD_DATA1_UF;
  cpu.mem_controller->Load64(1024, QWORD_DATA2_UF);

  cpu.Run();

  ASSERT_EQ(*cpu.x0, QWORD_RESULT_UF);
  ASSERT_TRUE(cpu.udf);
}

TEST_F(CPU_TEST, INSTR_SUB_R_IMM_b8_UF) {
  cpu.mem_controller->Load16(*cpu.xip, HyperCPU::Opcode::SUB);
  cpu.mem_controller->Load8(*cpu.xip + 2, HyperCPU::Mode::b8 << 4 | HyperCPU::OperandTypes::R_IMM);
  cpu.mem_controller->Load8(*cpu.xip + 3, HyperCPU::Registers::XLLL0);
  cpu.mem_controller->Load8(*cpu.xip + 4, BYTE_DATA2_UF);
  cpu.mem_controller->Load16(*cpu.xip + 5, HyperCPU::Opcode::HALT);
  cpu.mem_controller->Load8(*cpu.xip + 7, HyperCPU::OperandTypes::NONE);
  *cpu.xlll0 = BYTE_DATA1_UF;

  cpu.Run();

  ASSERT_EQ(*cpu.xlll0, BYTE_RESULT_UF);
  ASSERT_TRUE(cpu.udf);
}

TEST_F(CPU_TEST, INSTR_SUB_R_IMM_b16_UF) {
  cpu.mem_controller->Load16(*cpu.xip, HyperCPU::Opcode::SUB);
  cpu.mem_controller->Load8(*cpu.xip + 2, HyperCPU::Mode::b16 << 4 | HyperCPU::OperandTypes::R_IMM);
  cpu.mem_controller->Load8(*cpu.xip + 3, HyperCPU::Registers::XLL0);
  cpu.mem_controller->Load16(*cpu.xip + 4, WORD_DATA2_UF);
  cpu.mem_controller->Load16(*cpu.xip + 6, HyperCPU::Opcode::HALT);
  cpu.mem_controller->Load8(*cpu.xip + 8, HyperCPU::OperandTypes::NONE);
  *cpu.xll0 = WORD_DATA1_UF;

  cpu.Run();

  ASSERT_EQ(*cpu.xll0, WORD_RESULT_UF);
  ASSERT_TRUE(cpu.udf);
}

TEST_F(CPU_TEST, INSTR_SUB_R_IMM_b32_UF) {
  cpu.mem_controller->Load16(*cpu.xip, HyperCPU::Opcode::SUB);
  cpu.mem_controller->Load8(*cpu.xip + 2, HyperCPU::Mode::b32 << 4 | HyperCPU::OperandTypes::R_IMM);
  cpu.mem_controller->Load8(*cpu.xip + 3, HyperCPU::Registers::XL0);
  cpu.mem_controller->Load32(*cpu.xip + 4, DWORD_DATA2_UF);
  cpu.mem_controller->Load16(*cpu.xip + 8, HyperCPU::Opcode::HALT);
  cpu.mem_controller->Load8(*cpu.xip + 10, HyperCPU::OperandTypes::NONE);
  *cpu.xl0 = DWORD_DATA1_UF;

  cpu.Run();

  ASSERT_EQ(*cpu.xl0, DWORD_RESULT_UF);
  ASSERT_TRUE(cpu.udf);
}

TEST_F(CPU_TEST, INSTR_SUB_R_IMM_b64_UF) {
  cpu.mem_controller->Load16(*cpu.xip, HyperCPU::Opcode::SUB);
  cpu.mem_controller->Load8(*cpu.xip + 2, HyperCPU::Mode::b64 << 4 | HyperCPU::OperandTypes::R_IMM);
  cpu.mem_controller->Load8(*cpu.xip + 3, HyperCPU::Registers::X0);
  cpu.mem_controller->Load64(*cpu.xip + 4, QWORD_DATA2_UF);
  cpu.mem_controller->Load16(*cpu.xip + 12, HyperCPU::Opcode::HALT);
  cpu.mem_controller->Load8(*cpu.xip + 14, HyperCPU::OperandTypes::NONE);
  *cpu.x0 = QWORD_DATA1_UF;

  cpu.Run();

  ASSERT_EQ(*cpu.x0, QWORD_RESULT_UF);
  ASSERT_TRUE(cpu.udf);
}
