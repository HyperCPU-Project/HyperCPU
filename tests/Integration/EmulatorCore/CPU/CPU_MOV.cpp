#include "tests/fixtures.hpp"

static constexpr std::uint8_t BYTE_DATA = 0x55;
static constexpr std::uint16_t WORD_DATA = 0x5555;
static constexpr std::uint32_t DWORD_DATA = 0x55555555;
static constexpr std::uint64_t QWORD_DATA = 0x5555555555555555;
static constexpr std::uint64_t RND_QWORD_DATA = 0x0102030405060708;

TEST_F(CPU_TEST, INSTR_MOV_R_R_b8) {
  cpu.mem_controller->Load(*cpu.xip, HyperCPU::Opcode::MOV);
  cpu.mem_controller->Load(*cpu.xip + 2, EncodeTestFlags(HyperCPU::Mode::b8,  HyperCPU::Mode::b8, HyperCPU::OperandTypes::R_R));
  cpu.mem_controller->Load(*cpu.xip + 3, HyperCPU::Reg::XLLL0);
  cpu.mem_controller->Load(*cpu.xip + 4, HyperCPU::Reg::XLLL1);
  cpu.mem_controller->Load(*cpu.xip + 5, HyperCPU::Opcode::HALT);
  cpu.mem_controller->Load(*cpu.xip + 7, HyperCPU::OperandTypes::NONE);
  *cpu.x1 = RND_QWORD_DATA;

  cpu.Run();

  ASSERT_EQ(*cpu.xlll0, *cpu.xlll1);
}

TEST_F(CPU_TEST, INSTR_MOV_R_R_b16) {
  cpu.mem_controller->Load(*cpu.xip, HyperCPU::Opcode::MOV);
  cpu.mem_controller->Load(*cpu.xip + 2, EncodeTestFlags(HyperCPU::Mode::b16,  HyperCPU::Mode::b16, HyperCPU::OperandTypes::R_R));
  cpu.mem_controller->Load(*cpu.xip + 3, HyperCPU::Reg::XLL0);
  cpu.mem_controller->Load(*cpu.xip + 4, HyperCPU::Reg::XLL1);
  cpu.mem_controller->Load(*cpu.xip + 5, HyperCPU::Opcode::HALT);
  cpu.mem_controller->Load(*cpu.xip + 7, HyperCPU::OperandTypes::NONE);
  *cpu.x1 = RND_QWORD_DATA;

  cpu.Run();

  ASSERT_EQ(*cpu.xll0, *cpu.xll1);
}

TEST_F(CPU_TEST, INSTR_MOV_R_R_b32) {
  cpu.mem_controller->Load(*cpu.xip, HyperCPU::Opcode::MOV);
  cpu.mem_controller->Load(*cpu.xip + 2, EncodeTestFlags(HyperCPU::Mode::b32,  HyperCPU::Mode::b32, HyperCPU::OperandTypes::R_R));
  cpu.mem_controller->Load(*cpu.xip + 3, HyperCPU::Reg::XL0);
  cpu.mem_controller->Load(*cpu.xip + 4, HyperCPU::Reg::XL1);
  cpu.mem_controller->Load(*cpu.xip + 5, HyperCPU::Opcode::HALT);
  cpu.mem_controller->Load(*cpu.xip + 7, HyperCPU::OperandTypes::NONE);
  *cpu.x1 = RND_QWORD_DATA;

  cpu.Run();

  ASSERT_EQ(*cpu.xl0, *cpu.xl1);
}

TEST_F(CPU_TEST, INSTR_MOV_R_R_b64) {
  cpu.mem_controller->Load(*cpu.xip, HyperCPU::Opcode::MOV);
  cpu.mem_controller->Load(*cpu.xip + 2, EncodeTestFlags(HyperCPU::Mode::b64,  HyperCPU::Mode::b64, HyperCPU::OperandTypes::R_R));
  cpu.mem_controller->Load(*cpu.xip + 3, HyperCPU::Reg::X0);
  cpu.mem_controller->Load(*cpu.xip + 4, HyperCPU::Reg::X1);
  cpu.mem_controller->Load(*cpu.xip + 5, HyperCPU::Opcode::HALT);
  cpu.mem_controller->Load(*cpu.xip + 7, HyperCPU::OperandTypes::NONE);
  *cpu.x1 = RND_QWORD_DATA;

  cpu.Run();

  ASSERT_EQ(*cpu.x0, *cpu.x1);
}

TEST_F(CPU_TEST, INSTR_MOV_R_RM_b8) {
  cpu.mem_controller->Load(*cpu.xip, HyperCPU::Opcode::MOV);
  cpu.mem_controller->Load(*cpu.xip + 2, EncodeTestFlags(HyperCPU::Mode::b8,  HyperCPU::Mode::b8, HyperCPU::OperandTypes::R_RM));
  cpu.mem_controller->Load(*cpu.xip + 3, HyperCPU::Reg::XLLL0);
  cpu.mem_controller->Load(*cpu.xip + 4, HyperCPU::Reg::X1);
  cpu.mem_controller->Load(*cpu.xip + 5, HyperCPU::Opcode::HALT);
  cpu.mem_controller->Load(*cpu.xip + 7, HyperCPU::OperandTypes::NONE);
  cpu.mem_controller->Load(*cpu.xip + 1024, BYTE_DATA);
  *cpu.x1 = 1024;

  cpu.Run();

  ASSERT_EQ(*cpu.xlll0, BYTE_DATA);
}

TEST_F(CPU_TEST, INSTR_MOV_R_RM_b16) {
  cpu.mem_controller->Load(*cpu.xip, HyperCPU::Opcode::MOV);
  cpu.mem_controller->Load(*cpu.xip + 2, EncodeTestFlags(HyperCPU::Mode::b16,  HyperCPU::Mode::b16, HyperCPU::OperandTypes::R_RM));
  cpu.mem_controller->Load(*cpu.xip + 3, HyperCPU::Reg::XLL0);
  cpu.mem_controller->Load(*cpu.xip + 4, HyperCPU::Reg::X1);
  cpu.mem_controller->Load(*cpu.xip + 5, HyperCPU::Opcode::HALT);
  cpu.mem_controller->Load(*cpu.xip + 7, HyperCPU::OperandTypes::NONE);
  cpu.mem_controller->Load(*cpu.xip + 1024, WORD_DATA);
  *cpu.x1 = 1024;

  cpu.Run();

  ASSERT_EQ(*cpu.xll0, WORD_DATA);
}

TEST_F(CPU_TEST, INSTR_MOV_R_RM_b32) {
  cpu.mem_controller->Load(*cpu.xip, HyperCPU::Opcode::MOV);
  cpu.mem_controller->Load(*cpu.xip + 2, EncodeTestFlags(HyperCPU::Mode::b32,  HyperCPU::Mode::b32, HyperCPU::OperandTypes::R_RM));
  cpu.mem_controller->Load(*cpu.xip + 3, HyperCPU::Reg::XL0);
  cpu.mem_controller->Load(*cpu.xip + 4, HyperCPU::Reg::X1);
  cpu.mem_controller->Load(*cpu.xip + 5, HyperCPU::Opcode::HALT);
  cpu.mem_controller->Load(*cpu.xip + 7, HyperCPU::OperandTypes::NONE);
  cpu.mem_controller->Load(*cpu.xip + 1024, DWORD_DATA);
  *cpu.x1 = 1024;

  cpu.Run();

  ASSERT_EQ(*cpu.xl0, DWORD_DATA);
}

TEST_F(CPU_TEST, INSTR_MOV_R_RM_b64) {
  cpu.mem_controller->Load(*cpu.xip, HyperCPU::Opcode::MOV);
  cpu.mem_controller->Load(*cpu.xip + 2, EncodeTestFlags(HyperCPU::Mode::b64,  HyperCPU::Mode::b64, HyperCPU::OperandTypes::R_RM));
  cpu.mem_controller->Load(*cpu.xip + 3, HyperCPU::Reg::X0);
  cpu.mem_controller->Load(*cpu.xip + 4, HyperCPU::Reg::X1);
  cpu.mem_controller->Load(*cpu.xip + 5, HyperCPU::Opcode::HALT);
  cpu.mem_controller->Load(*cpu.xip + 7, HyperCPU::OperandTypes::NONE);
  cpu.mem_controller->Load(*cpu.xip + 1024, QWORD_DATA);
  *cpu.x1 = 1024;

  cpu.Run();

  ASSERT_EQ(*cpu.x0, QWORD_DATA);
}

TEST_F(CPU_TEST, INSTR_MOV_R_M_b8) {
  cpu.mem_controller->Load(*cpu.xip, HyperCPU::Opcode::MOV);
  cpu.mem_controller->Load(*cpu.xip + 2, EncodeTestFlags(HyperCPU::Mode::b8,  HyperCPU::Mode::b8, HyperCPU::OperandTypes::R_M));
  cpu.mem_controller->Load(*cpu.xip + 3, HyperCPU::Reg::XLLL0);
  cpu.mem_controller->Load(*cpu.xip + 4, 1024);
  cpu.mem_controller->Load(*cpu.xip + 12, HyperCPU::Opcode::HALT);
  cpu.mem_controller->Load(*cpu.xip + 14, HyperCPU::OperandTypes::NONE);
  cpu.mem_controller->Load(*cpu.xip + 1024, BYTE_DATA);
  *cpu.x1 = 1024;

  cpu.Run();

  ASSERT_EQ(*cpu.xlll0, BYTE_DATA);
}

TEST_F(CPU_TEST, INSTR_MOV_R_M_b16) {
  cpu.mem_controller->Load(*cpu.xip, HyperCPU::Opcode::MOV);
  cpu.mem_controller->Load(*cpu.xip + 2, EncodeTestFlags(HyperCPU::Mode::b16,  HyperCPU::Mode::b16, HyperCPU::OperandTypes::R_M));
  cpu.mem_controller->Load(*cpu.xip + 3, HyperCPU::Reg::XLL0);
  cpu.mem_controller->Load(*cpu.xip + 4, 1024);
  cpu.mem_controller->Load(*cpu.xip + 12, HyperCPU::Opcode::HALT);
  cpu.mem_controller->Load(*cpu.xip + 14, HyperCPU::OperandTypes::NONE);
  cpu.mem_controller->Load(*cpu.xip + 1024, WORD_DATA);
  *cpu.x1 = 1024;

  cpu.Run();

  ASSERT_EQ(*cpu.xll0, WORD_DATA);
}

TEST_F(CPU_TEST, INSTR_MOV_R_M_b32) {
  cpu.mem_controller->Load(*cpu.xip, HyperCPU::Opcode::MOV);
  cpu.mem_controller->Load(*cpu.xip + 2, EncodeTestFlags(HyperCPU::Mode::b32,  HyperCPU::Mode::b32, HyperCPU::OperandTypes::R_M));
  cpu.mem_controller->Load(*cpu.xip + 3, HyperCPU::Reg::XL0);
  cpu.mem_controller->Load(*cpu.xip + 4, 1024);
  cpu.mem_controller->Load(*cpu.xip + 12, HyperCPU::Opcode::HALT);
  cpu.mem_controller->Load(*cpu.xip + 14, HyperCPU::OperandTypes::NONE);
  cpu.mem_controller->Load(*cpu.xip + 1024, DWORD_DATA);
  *cpu.x1 = 1024;

  cpu.Run();

  ASSERT_EQ(*cpu.xl0, DWORD_DATA);
}

TEST_F(CPU_TEST, INSTR_MOV_R_M_b64) {
  cpu.mem_controller->Load(*cpu.xip, HyperCPU::Opcode::MOV);
  cpu.mem_controller->Load(*cpu.xip + 2, EncodeTestFlags(HyperCPU::Mode::b64,  HyperCPU::Mode::b64, HyperCPU::OperandTypes::R_M));
  cpu.mem_controller->Load(*cpu.xip + 3, HyperCPU::Reg::X0);
  cpu.mem_controller->Load(*cpu.xip + 4, 1024);
  cpu.mem_controller->Load(*cpu.xip + 12, HyperCPU::Opcode::HALT);
  cpu.mem_controller->Load(*cpu.xip + 14, HyperCPU::OperandTypes::NONE);
  cpu.mem_controller->Load(*cpu.xip + 1024, QWORD_DATA);
  *cpu.x1 = 1024;

  cpu.Run();

  ASSERT_EQ(*cpu.x0, QWORD_DATA);
}

TEST_F(CPU_TEST, INSTR_MOV_R_IMM_b8) {
  cpu.mem_controller->Load(*cpu.xip, HyperCPU::Opcode::MOV);
  cpu.mem_controller->Load(*cpu.xip + 2, EncodeTestFlags(HyperCPU::Mode::b8,  HyperCPU::Mode::b8, HyperCPU::OperandTypes::R_IMM));
  cpu.mem_controller->Load(*cpu.xip + 3, HyperCPU::Reg::XLLL0);
  cpu.mem_controller->Load(*cpu.xip + 4, BYTE_DATA);
  cpu.mem_controller->Load(*cpu.xip + 5, HyperCPU::Opcode::HALT);
  cpu.mem_controller->Load(*cpu.xip + 7, HyperCPU::OperandTypes::NONE);

  cpu.Run();

  ASSERT_EQ(*cpu.xlll0, BYTE_DATA);
}

TEST_F(CPU_TEST, INSTR_MOV_R_IMM_b16) {
  cpu.mem_controller->Load(*cpu.xip, HyperCPU::Opcode::MOV);
  cpu.mem_controller->Load(*cpu.xip + 2, EncodeTestFlags(HyperCPU::Mode::b16,  HyperCPU::Mode::b16, HyperCPU::OperandTypes::R_IMM));
  cpu.mem_controller->Load(*cpu.xip + 3, HyperCPU::Reg::XLL0);
  cpu.mem_controller->Load(*cpu.xip + 4, WORD_DATA);
  cpu.mem_controller->Load(*cpu.xip + 6, HyperCPU::Opcode::HALT);
  cpu.mem_controller->Load(*cpu.xip + 8, HyperCPU::OperandTypes::NONE);

  cpu.Run();

  ASSERT_EQ(*cpu.xll0, WORD_DATA);
}

TEST_F(CPU_TEST, INSTR_MOV_R_IMM_b32) {
  cpu.mem_controller->Load(*cpu.xip, HyperCPU::Opcode::MOV);
  cpu.mem_controller->Load(*cpu.xip + 2, EncodeTestFlags(HyperCPU::Mode::b32,  HyperCPU::Mode::b32, HyperCPU::OperandTypes::R_IMM));
  cpu.mem_controller->Load(*cpu.xip + 3, HyperCPU::Reg::XL0);
  cpu.mem_controller->Load(*cpu.xip + 4, DWORD_DATA);
  cpu.mem_controller->Load(*cpu.xip + 8, HyperCPU::Opcode::HALT);
  cpu.mem_controller->Load(*cpu.xip + 10, HyperCPU::OperandTypes::NONE);

  cpu.Run();

  ASSERT_EQ(*cpu.xl0, DWORD_DATA);
}

TEST_F(CPU_TEST, INSTR_MOV_R_IMM_b64) {
  cpu.mem_controller->Load(*cpu.xip, HyperCPU::Opcode::MOV);
  cpu.mem_controller->Load(*cpu.xip + 2, EncodeTestFlags(HyperCPU::Mode::b64,  HyperCPU::Mode::b64, HyperCPU::OperandTypes::R_IMM));
  cpu.mem_controller->Load(*cpu.xip + 3, HyperCPU::Reg::X0);
  cpu.mem_controller->Load(*cpu.xip + 4, QWORD_DATA);
  cpu.mem_controller->Load(*cpu.xip + 12, HyperCPU::Opcode::HALT);
  cpu.mem_controller->Load(*cpu.xip + 14, HyperCPU::OperandTypes::NONE);

  cpu.Run();

  ASSERT_EQ(*cpu.x0, QWORD_DATA);
}

TEST_F(CPU_TEST, INSTR_MOV_RM_R_b8) {
  cpu.mem_controller->Load(*cpu.xip, HyperCPU::Opcode::MOV);
  cpu.mem_controller->Load(*cpu.xip + 2, EncodeTestFlags(HyperCPU::Mode::b8,  HyperCPU::Mode::b8, HyperCPU::OperandTypes::RM_R)));
  cpu.mem_controller->Load(*cpu.xip + 3, HyperCPU::Reg::X0);
  cpu.mem_controller->Load(*cpu.xip + 4, HyperCPU::Reg::XLLL1);
  cpu.mem_controller->Load(*cpu.xip + 5, HyperCPU::Opcode::HALT);
  cpu.mem_controller->Load(*cpu.xip + 7, HyperCPU::OperandTypes::NONE);
  *cpu.x0 = 1024;
  *cpu.xlll1 = BYTE_DATA;

  cpu.Run();

  ASSERT_EQ(cpu.mem_controller->Read8(1024), BYTE_DATA);
}

TEST_F(CPU_TEST, INSTR_MOV_RM_R_b16) {
  cpu.mem_controller->Load(*cpu.xip, HyperCPU::Opcode::MOV);
  cpu.mem_controller->Load(*cpu.xip + 2, EncodeTestFlags(HyperCPU::Mode::b16,  HyperCPU::Mode::b16, HyperCPU::OperandTypes::RM_R)));
  cpu.mem_controller->Load(*cpu.xip + 3, HyperCPU::Reg::X0);
  cpu.mem_controller->Load(*cpu.xip + 4, HyperCPU::Reg::XLL1);
  cpu.mem_controller->Load(*cpu.xip + 5, HyperCPU::Opcode::HALT);
  cpu.mem_controller->Load(*cpu.xip + 7, HyperCPU::OperandTypes::NONE);
  *cpu.x0 = 1024;
  *cpu.xll1 = WORD_DATA;

  cpu.Run();

  ASSERT_EQ(cpu.mem_controller->Read16(1024), WORD_DATA);
}

TEST_F(CPU_TEST, INSTR_MOV_RM_R_b32) {
  cpu.mem_controller->Load(*cpu.xip, HyperCPU::Opcode::MOV);
  cpu.mem_controller->Load(*cpu.xip + 2, EncodeTestFlags(HyperCPU::Mode::b32,  HyperCPU::Mode::b32, HyperCPU::OperandTypes::RM_R)));
  cpu.mem_controller->Load(*cpu.xip + 3, HyperCPU::Reg::X0);
  cpu.mem_controller->Load(*cpu.xip + 4, HyperCPU::Reg::XL1);
  cpu.mem_controller->Load(*cpu.xip + 5, HyperCPU::Opcode::HALT);
  cpu.mem_controller->Load(*cpu.xip + 7, HyperCPU::OperandTypes::NONE);
  *cpu.x0 = 1024;
  *cpu.xl1 = DWORD_DATA;

  cpu.Run();

  ASSERT_EQ(cpu.mem_controller->Read32(1024), DWORD_DATA);
}

TEST_F(CPU_TEST, INSTR_MOV_RM_R_b64) {
  cpu.mem_controller->Load(*cpu.xip, HyperCPU::Opcode::MOV);
  cpu.mem_controller->Load(*cpu.xip + 2, EncodeTestFlags(HyperCPU::Mode::b64,  HyperCPU::Mode::b64, HyperCPU::OperandTypes::RM_R)));
  cpu.mem_controller->Load(*cpu.xip + 3, HyperCPU::Reg::X0);
  cpu.mem_controller->Load(*cpu.xip + 4, HyperCPU::Reg::X1);
  cpu.mem_controller->Load(*cpu.xip + 5, HyperCPU::Opcode::HALT);
  cpu.mem_controller->Load(*cpu.xip + 7, HyperCPU::OperandTypes::NONE);
  *cpu.x0 = 1024;
  *cpu.x1 = QWORD_DATA;

  cpu.Run();

  ASSERT_EQ(cpu.mem_controller->Read64(1024), QWORD_DATA);
}

TEST_F(CPU_TEST, INSTR_MOV_RM_M_b8) {
  cpu.mem_controller->Load(*cpu.xip, HyperCPU::Opcode::MOV);
  cpu.mem_controller->Load(*cpu.xip + 2, EncodeTestFlags(HyperCPU::Mode::b8,  HyperCPU::Mode::b8, HyperCPU::OperandTypes::RM_M)));
  cpu.mem_controller->Load(*cpu.xip + 3, HyperCPU::Reg::X0);
  cpu.mem_controller->Load(*cpu.xip + 4, 1536);
  cpu.mem_controller->Load(*cpu.xip + 12, HyperCPU::Opcode::HALT);
  cpu.mem_controller->Load(*cpu.xip + 14, HyperCPU::OperandTypes::NONE);
  cpu.mem_controller->Load(1536, BYTE_DATA);
  *cpu.x0 = 1024;

  cpu.Run();

  ASSERT_EQ(cpu.mem_controller->Read8(1024), BYTE_DATA);
}

TEST_F(CPU_TEST, INSTR_MOV_RM_M_b16) {
  cpu.mem_controller->Load(*cpu.xip, HyperCPU::Opcode::MOV);
  cpu.mem_controller->Load(*cpu.xip + 2, EncodeTestFlags(HyperCPU::Mode::b16,  HyperCPU::Mode::b16, HyperCPU::OperandTypes::RM_M)));
  cpu.mem_controller->Load(*cpu.xip + 3, HyperCPU::Reg::X0);
  cpu.mem_controller->Load(*cpu.xip + 4, 1536);
  cpu.mem_controller->Load(*cpu.xip + 12, HyperCPU::Opcode::HALT);
  cpu.mem_controller->Load(*cpu.xip + 14, HyperCPU::OperandTypes::NONE);
  cpu.mem_controller->Load(1536, WORD_DATA);
  *cpu.x0 = 1024;

  cpu.Run();

  ASSERT_EQ(cpu.mem_controller->Read16(1024), WORD_DATA);
}

TEST_F(CPU_TEST, INSTR_MOV_RM_M_b32) {
  cpu.mem_controller->Load(*cpu.xip, HyperCPU::Opcode::MOV);
  cpu.mem_controller->Load(*cpu.xip + 2, EncodeTestFlags(HyperCPU::Mode::b32,  HyperCPU::Mode::b32, HyperCPU::OperandTypes::RM_M)));
  cpu.mem_controller->Load(*cpu.xip + 3, HyperCPU::Reg::X0);
  cpu.mem_controller->Load(*cpu.xip + 4, 1536);
  cpu.mem_controller->Load(*cpu.xip + 12, HyperCPU::Opcode::HALT);
  cpu.mem_controller->Load(*cpu.xip + 14, HyperCPU::OperandTypes::NONE);
  cpu.mem_controller->Load(1536, DWORD_DATA);
  *cpu.x0 = 1024;

  cpu.Run();

  ASSERT_EQ(cpu.mem_controller->Read32(1024), DWORD_DATA);
}

TEST_F(CPU_TEST, INSTR_MOV_RM_M_b64) {
  cpu.mem_controller->Load(*cpu.xip, HyperCPU::Opcode::MOV);
  cpu.mem_controller->Load(*cpu.xip + 2, EncodeTestFlags(HyperCPU::Mode::b64,  HyperCPU::Mode::b64, HyperCPU::OperandTypes::RM_M)));
  cpu.mem_controller->Load(*cpu.xip + 3, HyperCPU::Reg::X0);
  cpu.mem_controller->Load(*cpu.xip + 4, 1536);
  cpu.mem_controller->Load(*cpu.xip + 12, HyperCPU::Opcode::HALT);
  cpu.mem_controller->Load(*cpu.xip + 14, HyperCPU::OperandTypes::NONE);
  cpu.mem_controller->Load(1536, QWORD_DATA);
  *cpu.x0 = 1024;

  cpu.Run();

  ASSERT_EQ(cpu.mem_controller->Read64(1024), QWORD_DATA);
}

TEST_F(CPU_TEST, INSTR_MOV_M_R_b8) {
  cpu.mem_controller->Load(*cpu.xip, HyperCPU::Opcode::MOV);
  cpu.mem_controller->Load(*cpu.xip + 2, EncodeTestFlags(HyperCPU::Mode::b8, HyperCPU::OperandTypes::M_R));
  cpu.mem_controller->Load(*cpu.xip + 3, 1024);
  cpu.mem_controller->Load(*cpu.xip + 11, HyperCPU::Reg::XLLL0);
  cpu.mem_controller->Load(*cpu.xip + 12, HyperCPU::Opcode::HALT);
  cpu.mem_controller->Load(*cpu.xip + 14, HyperCPU::OperandTypes::NONE);
  *cpu.xlll0 = BYTE_DATA;

  cpu.Run();

  ASSERT_EQ(cpu.mem_controller->Read8(1024), BYTE_DATA);
}

TEST_F(CPU_TEST, INSTR_MOV_M_R_b16) {
  cpu.mem_controller->Load(*cpu.xip, HyperCPU::Opcode::MOV);
  cpu.mem_controller->Load(*cpu.xip + 2, EncodeTestFlags(HyperCPU::Mode::b16, HyperCPU::OperandTypes::M_R));
  cpu.mem_controller->Load(*cpu.xip + 3, 1024);
  cpu.mem_controller->Load(*cpu.xip + 11, HyperCPU::Reg::XLL0);
  cpu.mem_controller->Load(*cpu.xip + 12, HyperCPU::Opcode::HALT);
  cpu.mem_controller->Load(*cpu.xip + 14, HyperCPU::OperandTypes::NONE);
  *cpu.xll0 = WORD_DATA;

  cpu.Run();

  ASSERT_EQ(cpu.mem_controller->Read16(1024), WORD_DATA);
}

TEST_F(CPU_TEST, INSTR_MOV_M_R_b32) {
  cpu.mem_controller->Load(*cpu.xip, HyperCPU::Opcode::MOV);
  cpu.mem_controller->Load(*cpu.xip + 2, EncodeTestFlags(HyperCPU::Mode::b32, HyperCPU::OperandTypes::M_R));
  cpu.mem_controller->Load(*cpu.xip + 3, 1024);
  cpu.mem_controller->Load(*cpu.xip + 11, HyperCPU::Reg::XL0);
  cpu.mem_controller->Load(*cpu.xip + 12, HyperCPU::Opcode::HALT);
  cpu.mem_controller->Load(*cpu.xip + 14, HyperCPU::OperandTypes::NONE);
  *cpu.xl0 = DWORD_DATA;

  cpu.Run();

  ASSERT_EQ(cpu.mem_controller->Read32(1024), DWORD_DATA);
}

TEST_F(CPU_TEST, INSTR_MOV_M_R_b64) {
  cpu.mem_controller->Load(*cpu.xip, HyperCPU::Opcode::MOV);
  cpu.mem_controller->Load(*cpu.xip + 2, EncodeTestFlags(HyperCPU::Mode::b64, HyperCPU::OperandTypes::M_R));
  cpu.mem_controller->Load(*cpu.xip + 3, 1024);
  cpu.mem_controller->Load(*cpu.xip + 11, HyperCPU::Reg::X0);
  cpu.mem_controller->Load(*cpu.xip + 12, HyperCPU::Opcode::HALT);
  cpu.mem_controller->Load(*cpu.xip + 14, HyperCPU::OperandTypes::NONE);
  *cpu.x0 = QWORD_DATA;

  cpu.Run();

  ASSERT_EQ(cpu.mem_controller->Read64(1024), QWORD_DATA);
}
