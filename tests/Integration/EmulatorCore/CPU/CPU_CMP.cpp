#include <Common/LanguageSpec/Flags.hpp>
#include <Common/LanguageSpec/Registers.hpp>

#include "tests/fixtures.hpp"

TEST_F(CPU_TEST, INSTR_CMP_R_R_b8_LE) {
  cpu.mem_controller->Load16(*cpu.xip, HyperCPU::Opcode::CMP);
  cpu.mem_controller->Load8(*cpu.xip + 2, EncodeTestFlags(HyperCPU::Mode::b8,  HyperCPU::Mode::b8, HyperCPU::OperandTypes::R_R));
  cpu.mem_controller->Load8(*cpu.xip + 3, HyperCPU::Reg::XLLL0);
  cpu.mem_controller->Load8(*cpu.xip + 4, HyperCPU::Reg::XLLL1);
  cpu.mem_controller->Load16(*cpu.xip + 5, HyperCPU::Opcode::HALT);
  cpu.mem_controller->Load8(*cpu.xip + 7, HyperCPU::OperandTypes::NONE);
  *cpu.xlll0 = 0x0F;
  *cpu.xlll1 = 0x1F;

  cpu.Run();

  ASSERT_FALSE(cpu.zrf);
  ASSERT_TRUE(cpu.crf);
}

TEST_F(CPU_TEST, INSTR_CMP_R_R_b8_GR) {
  cpu.mem_controller->Load16(*cpu.xip, HyperCPU::Opcode::CMP);
  cpu.mem_controller->Load8(*cpu.xip + 2, EncodeTestFlags(HyperCPU::Mode::b8,  HyperCPU::Mode::b8, HyperCPU::OperandTypes::R_R));
  cpu.mem_controller->Load8(*cpu.xip + 3, HyperCPU::Reg::XLLL0);
  cpu.mem_controller->Load8(*cpu.xip + 4, HyperCPU::Reg::XLLL1);
  cpu.mem_controller->Load16(*cpu.xip + 5, HyperCPU::Opcode::HALT);
  cpu.mem_controller->Load8(*cpu.xip + 7, HyperCPU::OperandTypes::NONE);
  *cpu.xlll0 = 0x1F;
  *cpu.xlll1 = 0x0F;

  cpu.Run();

  ASSERT_FALSE(cpu.zrf);
  ASSERT_FALSE(cpu.crf);
}

TEST_F(CPU_TEST, INSTR_CMP_R_R_b8_EQ) {
  cpu.mem_controller->Load16(*cpu.xip, HyperCPU::Opcode::CMP);
  cpu.mem_controller->Load8(*cpu.xip + 2, EncodeTestFlags(HyperCPU::Mode::b8,  HyperCPU::Mode::b8, HyperCPU::OperandTypes::R_R));
  cpu.mem_controller->Load8(*cpu.xip + 3, HyperCPU::Reg::XLLL0);
  cpu.mem_controller->Load8(*cpu.xip + 4, HyperCPU::Reg::XLLL1);
  cpu.mem_controller->Load16(*cpu.xip + 5, HyperCPU::Opcode::HALT);
  cpu.mem_controller->Load8(*cpu.xip + 7, HyperCPU::OperandTypes::NONE);
  *cpu.xlll0 = 0x1F;
  *cpu.xlll1 = 0x1F;

  cpu.Run();

  ASSERT_TRUE(cpu.zrf);
  ASSERT_FALSE(cpu.crf);
}

TEST_F(CPU_TEST, INSTR_CMP_R_R_b16_LE) {
  cpu.mem_controller->Load16(*cpu.xip, HyperCPU::Opcode::CMP);
  cpu.mem_controller->Load8(*cpu.xip + 2, EncodeTestFlags(HyperCPU::Mode::b16,  HyperCPU::Mode::b16, HyperCPU::OperandTypes::R_R));
  cpu.mem_controller->Load8(*cpu.xip + 3, HyperCPU::Reg::XLL0);
  cpu.mem_controller->Load8(*cpu.xip + 4, HyperCPU::Reg::XLL1);
  cpu.mem_controller->Load16(*cpu.xip + 5, HyperCPU::Opcode::HALT);
  cpu.mem_controller->Load8(*cpu.xip + 7, HyperCPU::OperandTypes::NONE);
  *cpu.xll0 = 0x0F;
  *cpu.xll1 = 0x1F;

  cpu.Run();

  ASSERT_FALSE(cpu.zrf);
  ASSERT_TRUE(cpu.crf);
}

TEST_F(CPU_TEST, INSTR_CMP_R_R_b16_GR) {
  cpu.mem_controller->Load16(*cpu.xip, HyperCPU::Opcode::CMP);
  cpu.mem_controller->Load8(*cpu.xip + 2, EncodeTestFlags(HyperCPU::Mode::b16,  HyperCPU::Mode::b16, HyperCPU::OperandTypes::R_R));
  cpu.mem_controller->Load8(*cpu.xip + 3, HyperCPU::Reg::XLL0);
  cpu.mem_controller->Load8(*cpu.xip + 4, HyperCPU::Reg::XLL1);
  cpu.mem_controller->Load16(*cpu.xip + 5, HyperCPU::Opcode::HALT);
  cpu.mem_controller->Load8(*cpu.xip + 7, HyperCPU::OperandTypes::NONE);
  *cpu.xll0 = 0x1F;
  *cpu.xll1 = 0x0F;

  cpu.Run();

  ASSERT_FALSE(cpu.zrf);
  ASSERT_FALSE(cpu.crf);
}

TEST_F(CPU_TEST, INSTR_CMP_R_R_b16_EQ) {
  cpu.mem_controller->Load16(*cpu.xip, HyperCPU::Opcode::CMP);
  cpu.mem_controller->Load8(*cpu.xip + 2, EncodeTestFlags(HyperCPU::Mode::b16,  HyperCPU::Mode::b16, HyperCPU::OperandTypes::R_R));
  cpu.mem_controller->Load8(*cpu.xip + 3, HyperCPU::Reg::XLL0);
  cpu.mem_controller->Load8(*cpu.xip + 4, HyperCPU::Reg::XLL1);
  cpu.mem_controller->Load16(*cpu.xip + 5, HyperCPU::Opcode::HALT);
  cpu.mem_controller->Load8(*cpu.xip + 7, HyperCPU::OperandTypes::NONE);
  *cpu.xll0 = 0x1F;
  *cpu.xll1 = 0x1F;

  cpu.Run();

  ASSERT_TRUE(cpu.zrf);
  ASSERT_FALSE(cpu.crf);
}

TEST_F(CPU_TEST, INSTR_CMP_R_R_b32_LE) {
  cpu.mem_controller->Load16(*cpu.xip, HyperCPU::Opcode::CMP);
  cpu.mem_controller->Load8(*cpu.xip + 2, EncodeTestFlags(HyperCPU::Mode::b32,  HyperCPU::Mode::b32, HyperCPU::OperandTypes::R_R));
  cpu.mem_controller->Load8(*cpu.xip + 3, HyperCPU::Reg::XL0);
  cpu.mem_controller->Load8(*cpu.xip + 4, HyperCPU::Reg::XL1);
  cpu.mem_controller->Load16(*cpu.xip + 5, HyperCPU::Opcode::HALT);
  cpu.mem_controller->Load8(*cpu.xip + 7, HyperCPU::OperandTypes::NONE);
  *cpu.xl0 = 0x0F;
  *cpu.xl1 = 0x1F;

  cpu.Run();

  ASSERT_FALSE(cpu.zrf);
  ASSERT_TRUE(cpu.crf);
}

TEST_F(CPU_TEST, INSTR_CMP_R_R_b32_GR) {
  cpu.mem_controller->Load16(*cpu.xip, HyperCPU::Opcode::CMP);
  cpu.mem_controller->Load8(*cpu.xip + 2, EncodeTestFlags(HyperCPU::Mode::b32,  HyperCPU::Mode::b32, HyperCPU::OperandTypes::R_R));
  cpu.mem_controller->Load8(*cpu.xip + 3, HyperCPU::Reg::XL0);
  cpu.mem_controller->Load8(*cpu.xip + 4, HyperCPU::Reg::XL1);
  cpu.mem_controller->Load16(*cpu.xip + 5, HyperCPU::Opcode::HALT);
  cpu.mem_controller->Load8(*cpu.xip + 7, HyperCPU::OperandTypes::NONE);
  *cpu.xl0 = 0x1F;
  *cpu.xl1 = 0x0F;

  cpu.Run();

  ASSERT_FALSE(cpu.zrf);
  ASSERT_FALSE(cpu.crf);
}

TEST_F(CPU_TEST, INSTR_CMP_R_R_b32_EQ) {
  cpu.mem_controller->Load16(*cpu.xip, HyperCPU::Opcode::CMP);
  cpu.mem_controller->Load8(*cpu.xip + 2, EncodeTestFlags(HyperCPU::Mode::b64,  HyperCPU::Mode::b64, HyperCPU::OperandTypes::R_R));
  cpu.mem_controller->Load8(*cpu.xip + 3, HyperCPU::Reg::XL0);
  cpu.mem_controller->Load8(*cpu.xip + 4, HyperCPU::Reg::XL1);
  cpu.mem_controller->Load16(*cpu.xip + 5, HyperCPU::Opcode::HALT);
  cpu.mem_controller->Load8(*cpu.xip + 7, HyperCPU::OperandTypes::NONE);
  *cpu.xl0 = 0x1F;
  *cpu.xl1 = 0x1F;

  cpu.Run();

  ASSERT_TRUE(cpu.zrf);
  ASSERT_FALSE(cpu.crf);
}

TEST_F(CPU_TEST, INSTR_CMP_R_R_b64_LE) {
  cpu.mem_controller->Load16(*cpu.xip, HyperCPU::Opcode::CMP);
  cpu.mem_controller->Load8(*cpu.xip + 2, EncodeTestFlags(HyperCPU::Mode::b64,  HyperCPU::Mode::b64, HyperCPU::OperandTypes::R_R));
  cpu.mem_controller->Load8(*cpu.xip + 3, HyperCPU::Reg::X0);
  cpu.mem_controller->Load8(*cpu.xip + 4, HyperCPU::Reg::X1);
  cpu.mem_controller->Load16(*cpu.xip + 5, HyperCPU::Opcode::HALT);
  cpu.mem_controller->Load8(*cpu.xip + 7, HyperCPU::OperandTypes::NONE);
  *cpu.x0 = 0x0F;
  *cpu.x1 = 0x1F;

  cpu.Run();

  ASSERT_FALSE(cpu.zrf);
  ASSERT_TRUE(cpu.crf);
}

TEST_F(CPU_TEST, INSTR_CMP_R_R_b64_GR) {
  cpu.mem_controller->Load16(*cpu.xip, HyperCPU::Opcode::CMP);
  cpu.mem_controller->Load8(*cpu.xip + 2, EncodeTestFlags(HyperCPU::Mode::b64,  HyperCPU::Mode::b64, HyperCPU::OperandTypes::R_R));
  cpu.mem_controller->Load8(*cpu.xip + 3, HyperCPU::Reg::X0);
  cpu.mem_controller->Load8(*cpu.xip + 4, HyperCPU::Reg::X1);
  cpu.mem_controller->Load16(*cpu.xip + 5, HyperCPU::Opcode::HALT);
  cpu.mem_controller->Load8(*cpu.xip + 7, HyperCPU::OperandTypes::NONE);
  *cpu.x0 = 0x1F;
  *cpu.x1 = 0x0F;

  cpu.Run();

  ASSERT_FALSE(cpu.zrf);
  ASSERT_FALSE(cpu.crf);
}

TEST_F(CPU_TEST, INSTR_CMP_R_R_b64_EQ) {
  cpu.mem_controller->Load16(*cpu.xip, HyperCPU::Opcode::CMP);
  cpu.mem_controller->Load8(*cpu.xip + 2, EncodeTestFlags(HyperCPU::Mode::b64,  HyperCPU::Mode::b64, HyperCPU::OperandTypes::R_R));
  cpu.mem_controller->Load8(*cpu.xip + 3, HyperCPU::Reg::X0);
  cpu.mem_controller->Load8(*cpu.xip + 4, HyperCPU::Reg::X1);
  cpu.mem_controller->Load16(*cpu.xip + 5, HyperCPU::Opcode::HALT);
  cpu.mem_controller->Load8(*cpu.xip + 7, HyperCPU::OperandTypes::NONE);
  *cpu.x0 = 0x1F;
  *cpu.x1 = 0x1F;

  cpu.Run();

  ASSERT_TRUE(cpu.zrf);
  ASSERT_FALSE(cpu.crf);
}

TEST_F(CPU_TEST, INSTR_CMP_R_RM_b8_LE) {
  cpu.mem_controller->Load16(*cpu.xip, HyperCPU::Opcode::CMP);
  cpu.mem_controller->Load8(*cpu.xip + 2, EncodeTestFlags(HyperCPU::Mode::b8,  HyperCPU::Mode::b8, HyperCPU::OperandTypes::R_RM)
;
  cpu.mem_controller->Load8(*cpu.xip + 3, HyperCPU::Reg::XLLL0);
  cpu.mem_controller->Load8(*cpu.xip + 4, HyperCPU::Reg::X1);
  cpu.mem_controller->Load16(*cpu.xip + 5, HyperCPU::Opcode::HALT);
  cpu.mem_controller->Load8(*cpu.xip + 7, HyperCPU::OperandTypes::NONE);
  cpu.mem_controller->Load8(*cpu.xip + 1024, 0x1F);
  *cpu.xlll0 = 0x0F;
  *cpu.x1 = 1024;

  cpu.Run();

  ASSERT_FALSE(cpu.zrf);
  ASSERT_TRUE(cpu.crf);
}

TEST_F(CPU_TEST, INSTR_CMP_R_RM_b8_GR) {
  cpu.mem_controller->Load16(*cpu.xip, HyperCPU::Opcode::CMP);
  cpu.mem_controller->Load8(*cpu.xip + 2, EncodeTestFlags(HyperCPU::Mode::b8,  HyperCPU::Mode::b8, HyperCPU::OperandTypes::R_RM)
;
  cpu.mem_controller->Load8(*cpu.xip + 3, HyperCPU::Reg::XLLL0);
  cpu.mem_controller->Load8(*cpu.xip + 4, HyperCPU::Reg::X1);
  cpu.mem_controller->Load16(*cpu.xip + 5, HyperCPU::Opcode::HALT);
  cpu.mem_controller->Load8(*cpu.xip + 7, HyperCPU::OperandTypes::NONE);
  cpu.mem_controller->Load8(*cpu.xip + 1024, 0x0F);
  *cpu.xlll0 = 0x1F;
  *cpu.x1 = 1024;

  cpu.Run();

  ASSERT_FALSE(cpu.zrf);
  ASSERT_FALSE(cpu.crf);
}

TEST_F(CPU_TEST, INSTR_CMP_R_RM_b8_EQ) {
  cpu.mem_controller->Load16(*cpu.xip, HyperCPU::Opcode::CMP);
  cpu.mem_controller->Load8(*cpu.xip + 2, EncodeTestFlags(HyperCPU::Mode::b8,  HyperCPU::Mode::b8, HyperCPU::OperandTypes::R_RM)
;
  cpu.mem_controller->Load8(*cpu.xip + 3, HyperCPU::Reg::XLLL0);
  cpu.mem_controller->Load8(*cpu.xip + 4, HyperCPU::Reg::X1);
  cpu.mem_controller->Load16(*cpu.xip + 5, HyperCPU::Opcode::HALT);
  cpu.mem_controller->Load8(*cpu.xip + 7, HyperCPU::OperandTypes::NONE);
  cpu.mem_controller->Load8(*cpu.xip + 1024, 0x1F);
  *cpu.xlll0 = 0x1F;
  *cpu.x1 = 1024;

  cpu.Run();

  ASSERT_TRUE(cpu.zrf);
  ASSERT_FALSE(cpu.crf);
}

TEST_F(CPU_TEST, INSTR_CMP_R_RM_b16_LE) {
  cpu.mem_controller->Load16(*cpu.xip, HyperCPU::Opcode::CMP);
  cpu.mem_controller->Load8(*cpu.xip + 2, EncodeTestFlags(HyperCPU::Mode::b16,  HyperCPU::Mode::b16, HyperCPU::OperandTypes::R_RM)
;
  cpu.mem_controller->Load8(*cpu.xip + 3, HyperCPU::Reg::XLL0);
  cpu.mem_controller->Load8(*cpu.xip + 4, HyperCPU::Reg::X1);
  cpu.mem_controller->Load16(*cpu.xip + 5, HyperCPU::Opcode::HALT);
  cpu.mem_controller->Load8(*cpu.xip + 7, HyperCPU::OperandTypes::NONE);
  cpu.mem_controller->Load16(*cpu.xip + 1024, 0x1F);
  *cpu.xll0 = 0x0F;
  *cpu.x1 = 1024;

  cpu.Run();

  ASSERT_FALSE(cpu.zrf);
  ASSERT_TRUE(cpu.crf);
}

TEST_F(CPU_TEST, INSTR_CMP_R_RM_b16_GR) {
  cpu.mem_controller->Load16(*cpu.xip, HyperCPU::Opcode::CMP);
  cpu.mem_controller->Load8(*cpu.xip + 2, EncodeTestFlags(HyperCPU::Mode::b16,  HyperCPU::Mode::b16, HyperCPU::OperandTypes::R_RM)
;
  cpu.mem_controller->Load8(*cpu.xip + 3, HyperCPU::Reg::XLL0);
  cpu.mem_controller->Load8(*cpu.xip + 4, HyperCPU::Reg::X1);
  cpu.mem_controller->Load16(*cpu.xip + 5, HyperCPU::Opcode::HALT);
  cpu.mem_controller->Load8(*cpu.xip + 7, HyperCPU::OperandTypes::NONE);
  cpu.mem_controller->Load16(*cpu.xip + 1024, 0x0F);
  *cpu.xll0 = 0x1F;
  *cpu.x1 = 1024;

  cpu.Run();

  ASSERT_FALSE(cpu.zrf);
  ASSERT_FALSE(cpu.crf);
}

TEST_F(CPU_TEST, INSTR_CMP_R_RM_b16_EQ) {
  cpu.mem_controller->Load16(*cpu.xip, HyperCPU::Opcode::CMP);
  cpu.mem_controller->Load8(*cpu.xip + 2, EncodeTestFlags(HyperCPU::Mode::b16,  HyperCPU::Mode::b16, HyperCPU::OperandTypes::R_RM)
;
  cpu.mem_controller->Load8(*cpu.xip + 3, HyperCPU::Reg::XLL0);
  cpu.mem_controller->Load8(*cpu.xip + 4, HyperCPU::Reg::X1);
  cpu.mem_controller->Load16(*cpu.xip + 5, HyperCPU::Opcode::HALT);
  cpu.mem_controller->Load8(*cpu.xip + 7, HyperCPU::OperandTypes::NONE);
  cpu.mem_controller->Load16(*cpu.xip + 1024, 0x1F);
  *cpu.xll0 = 0x1F;
  *cpu.x1 = 1024;

  cpu.Run();

  ASSERT_TRUE(cpu.zrf);
  ASSERT_FALSE(cpu.crf);
}

TEST_F(CPU_TEST, INSTR_CMP_R_RM_b32_LE) {
  cpu.mem_controller->Load16(*cpu.xip, HyperCPU::Opcode::CMP);
  cpu.mem_controller->Load8(*cpu.xip + 2, EncodeTestFlags(HyperCPU::Mode::b32,  HyperCPU::Mode::b32, HyperCPU::OperandTypes::R_RM)
;
  cpu.mem_controller->Load8(*cpu.xip + 3, HyperCPU::Reg::XL0);
  cpu.mem_controller->Load8(*cpu.xip + 4, HyperCPU::Reg::X1);
  cpu.mem_controller->Load16(*cpu.xip + 5, HyperCPU::Opcode::HALT);
  cpu.mem_controller->Load8(*cpu.xip + 7, HyperCPU::OperandTypes::NONE);
  cpu.mem_controller->Load32(*cpu.xip + 1024, 0x1F);
  *cpu.xl0 = 0x0F;
  *cpu.x1 = 1024;

  cpu.Run();

  ASSERT_FALSE(cpu.zrf);
  ASSERT_TRUE(cpu.crf);
}

TEST_F(CPU_TEST, INSTR_CMP_R_RM_b32_GR) {
  cpu.mem_controller->Load16(*cpu.xip, HyperCPU::Opcode::CMP);
  cpu.mem_controller->Load8(*cpu.xip + 2, EncodeTestFlags(HyperCPU::Mode::b32,  HyperCPU::Mode::b32, HyperCPU::OperandTypes::R_RM)
;
  cpu.mem_controller->Load8(*cpu.xip + 3, HyperCPU::Reg::XL0);
  cpu.mem_controller->Load8(*cpu.xip + 4, HyperCPU::Reg::X1);
  cpu.mem_controller->Load16(*cpu.xip + 5, HyperCPU::Opcode::HALT);
  cpu.mem_controller->Load8(*cpu.xip + 7, HyperCPU::OperandTypes::NONE);
  cpu.mem_controller->Load32(*cpu.xip + 1024, 0x0F);
  *cpu.xl0 = 0x1F;
  *cpu.x1 = 1024;

  cpu.Run();

  ASSERT_FALSE(cpu.zrf);
  ASSERT_FALSE(cpu.crf);
}

TEST_F(CPU_TEST, INSTR_CMP_R_RM_b32_EQ) {
  cpu.mem_controller->Load16(*cpu.xip, HyperCPU::Opcode::CMP);
  cpu.mem_controller->Load8(*cpu.xip + 2, EncodeTestFlags(HyperCPU::Mode::b32,  HyperCPU::Mode::b32, HyperCPU::OperandTypes::R_RM)
;
  cpu.mem_controller->Load8(*cpu.xip + 3, HyperCPU::Reg::XL0);
  cpu.mem_controller->Load8(*cpu.xip + 4, HyperCPU::Reg::X1);
  cpu.mem_controller->Load16(*cpu.xip + 5, HyperCPU::Opcode::HALT);
  cpu.mem_controller->Load8(*cpu.xip + 7, HyperCPU::OperandTypes::NONE);
  cpu.mem_controller->Load32(*cpu.xip + 1024, 0x1F);
  *cpu.xl0 = 0x1F;
  *cpu.x1 = 1024;

  cpu.Run();

  ASSERT_TRUE(cpu.zrf);
  ASSERT_FALSE(cpu.crf);
}

TEST_F(CPU_TEST, INSTR_CMP_R_RM_b64_LE) {
  cpu.mem_controller->Load16(*cpu.xip, HyperCPU::Opcode::CMP);
  cpu.mem_controller->Load8(*cpu.xip + 2, EncodeTestFlags(HyperCPU::Mode::b64,  HyperCPU::Mode::b64, HyperCPU::OperandTypes::R_RM)
;
  cpu.mem_controller->Load8(*cpu.xip + 3, HyperCPU::Reg::X0);
  cpu.mem_controller->Load8(*cpu.xip + 4, HyperCPU::Reg::X1);
  cpu.mem_controller->Load16(*cpu.xip + 5, HyperCPU::Opcode::HALT);
  cpu.mem_controller->Load8(*cpu.xip + 7, HyperCPU::OperandTypes::NONE);
  cpu.mem_controller->Load64(*cpu.xip + 1024, 0x1F);
  *cpu.x0 = 0x0F;
  *cpu.x1 = 1024;

  cpu.Run();

  ASSERT_FALSE(cpu.zrf);
  ASSERT_TRUE(cpu.crf);
}

TEST_F(CPU_TEST, INSTR_CMP_R_RM_b64_GR) {
  cpu.mem_controller->Load16(*cpu.xip, HyperCPU::Opcode::CMP);
  cpu.mem_controller->Load8(*cpu.xip + 2, EncodeTestFlags(HyperCPU::Mode::b64,  HyperCPU::Mode::b64, HyperCPU::OperandTypes::R_RM)
;
  cpu.mem_controller->Load8(*cpu.xip + 3, HyperCPU::Reg::X0);
  cpu.mem_controller->Load8(*cpu.xip + 4, HyperCPU::Reg::X1);
  cpu.mem_controller->Load16(*cpu.xip + 5, HyperCPU::Opcode::HALT);
  cpu.mem_controller->Load8(*cpu.xip + 7, HyperCPU::OperandTypes::NONE);
  cpu.mem_controller->Load64(*cpu.xip + 1024, 0x0F);
  *cpu.x0 = 0x1F;
  *cpu.x1 = 1024;

  cpu.Run();

  ASSERT_FALSE(cpu.zrf);
  ASSERT_FALSE(cpu.crf);
}

TEST_F(CPU_TEST, INSTR_CMP_R_RM_b64_EQ) {
  cpu.mem_controller->Load16(*cpu.xip, HyperCPU::Opcode::CMP);
  cpu.mem_controller->Load8(*cpu.xip + 2, EncodeTestFlags(HyperCPU::Mode::b64,  HyperCPU::Mode::b64, HyperCPU::OperandTypes::R_RM)
;
  cpu.mem_controller->Load8(*cpu.xip + 3, HyperCPU::Reg::X0);
  cpu.mem_controller->Load8(*cpu.xip + 4, HyperCPU::Reg::X1);
  cpu.mem_controller->Load16(*cpu.xip + 5, HyperCPU::Opcode::HALT);
  cpu.mem_controller->Load8(*cpu.xip + 7, HyperCPU::OperandTypes::NONE);
  cpu.mem_controller->Load64(*cpu.xip + 1024, 0x0F);
  *cpu.x0 = 0x0F;
  *cpu.x1 = 1024;

  cpu.Run();

  ASSERT_TRUE(cpu.zrf);
  ASSERT_FALSE(cpu.crf);
}

TEST_F(CPU_TEST, INSTR_CMP_R_M_b8_LE) {
  cpu.mem_controller->Load16(*cpu.xip, HyperCPU::Opcode::CMP);
  cpu.mem_controller->Load8(*cpu.xip + 2, EncodeTestFlags(HyperCPU::Mode::b8,  HyperCPU::Mode::b8, HyperCPU::OperandTypes::R_M)
;
  cpu.mem_controller->Load8(*cpu.xip + 3, HyperCPU::Reg::XLLL0);
  cpu.mem_controller->Load64(*cpu.xip + 4, 1024);
  cpu.mem_controller->Load16(*cpu.xip + 12, HyperCPU::Opcode::HALT);
  cpu.mem_controller->Load8(*cpu.xip + 14, HyperCPU::OperandTypes::NONE);
  cpu.mem_controller->Load8(*cpu.xip + 1024, 0x1F);
  *cpu.xlll0 = 0x0F;

  cpu.Run();

  ASSERT_FALSE(cpu.zrf);
  ASSERT_TRUE(cpu.crf);
}

TEST_F(CPU_TEST, INSTR_CMP_R_M_b8_GR) {
  cpu.mem_controller->Load16(*cpu.xip, HyperCPU::Opcode::CMP);
  cpu.mem_controller->Load8(*cpu.xip + 2, EncodeTestFlags(HyperCPU::Mode::b8,  HyperCPU::Mode::b8, HyperCPU::OperandTypes::R_M)
;
  cpu.mem_controller->Load8(*cpu.xip + 3, HyperCPU::Reg::XLLL0);
  cpu.mem_controller->Load64(*cpu.xip + 4, 1024);
  cpu.mem_controller->Load16(*cpu.xip + 12, HyperCPU::Opcode::HALT);
  cpu.mem_controller->Load8(*cpu.xip + 14, HyperCPU::OperandTypes::NONE);
  cpu.mem_controller->Load8(*cpu.xip + 1024, 0x0F);
  *cpu.xlll0 = 0x1F;

  cpu.Run();

  ASSERT_FALSE(cpu.zrf);
  ASSERT_FALSE(cpu.crf);
}

TEST_F(CPU_TEST, INSTR_CMP_R_M_b8_EQ) {
  cpu.mem_controller->Load16(*cpu.xip, HyperCPU::Opcode::CMP);
  cpu.mem_controller->Load8(*cpu.xip + 2, EncodeTestFlags(HyperCPU::Mode::b8,  HyperCPU::Mode::b8, HyperCPU::OperandTypes::R_M)
;
  cpu.mem_controller->Load8(*cpu.xip + 3, HyperCPU::Reg::XLLL0);
  cpu.mem_controller->Load64(*cpu.xip + 4, 1024);
  cpu.mem_controller->Load16(*cpu.xip + 12, HyperCPU::Opcode::HALT);
  cpu.mem_controller->Load8(*cpu.xip + 14, HyperCPU::OperandTypes::NONE);
  cpu.mem_controller->Load8(*cpu.xip + 1024, 0x0F);
  *cpu.xlll0 = 0x0F;

  cpu.Run();

  ASSERT_TRUE(cpu.zrf);
  ASSERT_FALSE(cpu.crf);
}

TEST_F(CPU_TEST, INSTR_CMP_R_M_b16_LE) {
  cpu.mem_controller->Load16(*cpu.xip, HyperCPU::Opcode::CMP);
  cpu.mem_controller->Load8(*cpu.xip + 2, EncodeTestFlags(HyperCPU::Mode::b16,  HyperCPU::Mode::b16, HyperCPU::OperandTypes::R_M)
;
  cpu.mem_controller->Load8(*cpu.xip + 3, HyperCPU::Reg::XLL0);
  cpu.mem_controller->Load64(*cpu.xip + 4, 1024);
  cpu.mem_controller->Load16(*cpu.xip + 12, HyperCPU::Opcode::HALT);
  cpu.mem_controller->Load8(*cpu.xip + 14, HyperCPU::OperandTypes::NONE);
  cpu.mem_controller->Load16(*cpu.xip + 1024, 0x1F);
  *cpu.xll0 = 0x0F;

  cpu.Run();

  ASSERT_FALSE(cpu.zrf);
  ASSERT_TRUE(cpu.crf);
}

TEST_F(CPU_TEST, INSTR_CMP_R_M_b16_GR) {
  cpu.mem_controller->Load16(*cpu.xip, HyperCPU::Opcode::CMP);
  cpu.mem_controller->Load8(*cpu.xip + 2, EncodeTestFlags(HyperCPU::Mode::b16,  HyperCPU::Mode::b16, HyperCPU::OperandTypes::R_M)
;
  cpu.mem_controller->Load8(*cpu.xip + 3, HyperCPU::Reg::XLL0);
  cpu.mem_controller->Load64(*cpu.xip + 4, 1024);
  cpu.mem_controller->Load16(*cpu.xip + 12, HyperCPU::Opcode::HALT);
  cpu.mem_controller->Load8(*cpu.xip + 14, HyperCPU::OperandTypes::NONE);
  cpu.mem_controller->Load16(*cpu.xip + 1024, 0x0F);
  *cpu.xll0 = 0x1F;

  cpu.Run();

  ASSERT_FALSE(cpu.zrf);
  ASSERT_FALSE(cpu.crf);
}

TEST_F(CPU_TEST, INSTR_CMP_R_M_b16_EQ) {
  cpu.mem_controller->Load16(*cpu.xip, HyperCPU::Opcode::CMP);
  cpu.mem_controller->Load8(*cpu.xip + 2, EncodeTestFlags(HyperCPU::Mode::b16,  HyperCPU::Mode::b16, HyperCPU::OperandTypes::R_M)
;
  cpu.mem_controller->Load8(*cpu.xip + 3, HyperCPU::Reg::XLL0);
  cpu.mem_controller->Load64(*cpu.xip + 4, 1024);
  cpu.mem_controller->Load16(*cpu.xip + 12, HyperCPU::Opcode::HALT);
  cpu.mem_controller->Load8(*cpu.xip + 14, HyperCPU::OperandTypes::NONE);
  cpu.mem_controller->Load16(*cpu.xip + 1024, 0x0F);
  *cpu.xll0 = 0x0F;

  cpu.Run();

  ASSERT_TRUE(cpu.zrf);
  ASSERT_FALSE(cpu.crf);
}

TEST_F(CPU_TEST, INSTR_CMP_R_M_b32_LE) {
  cpu.mem_controller->Load16(*cpu.xip, HyperCPU::Opcode::CMP);
  cpu.mem_controller->Load8(*cpu.xip + 2, EncodeTestFlags(HyperCPU::Mode::b32,  HyperCPU::Mode::b32, HyperCPU::OperandTypes::R_M)
;
  cpu.mem_controller->Load8(*cpu.xip + 3, HyperCPU::Reg::XL0);
  cpu.mem_controller->Load64(*cpu.xip + 4, 1024);
  cpu.mem_controller->Load16(*cpu.xip + 12, HyperCPU::Opcode::HALT);
  cpu.mem_controller->Load8(*cpu.xip + 14, HyperCPU::OperandTypes::NONE);
  cpu.mem_controller->Load32(*cpu.xip + 1024, 0x1F);
  *cpu.xl0 = 0x0F;

  cpu.Run();

  ASSERT_FALSE(cpu.zrf);
  ASSERT_TRUE(cpu.crf);
}

TEST_F(CPU_TEST, INSTR_CMP_R_M_b32_GR) {
  cpu.mem_controller->Load16(*cpu.xip, HyperCPU::Opcode::CMP);
  cpu.mem_controller->Load8(*cpu.xip + 2, EncodeTestFlags(HyperCPU::Mode::b32,  HyperCPU::Mode::b32, HyperCPU::OperandTypes::R_M)
;
  cpu.mem_controller->Load8(*cpu.xip + 3, HyperCPU::Reg::XL0);
  cpu.mem_controller->Load64(*cpu.xip + 4, 1024);
  cpu.mem_controller->Load16(*cpu.xip + 12, HyperCPU::Opcode::HALT);
  cpu.mem_controller->Load8(*cpu.xip + 14, HyperCPU::OperandTypes::NONE);
  cpu.mem_controller->Load32(*cpu.xip + 1024, 0x0F);
  *cpu.xl0 = 0x1F;

  cpu.Run();

  ASSERT_FALSE(cpu.zrf);
  ASSERT_FALSE(cpu.crf);
}

TEST_F(CPU_TEST, INSTR_CMP_R_M_b32_EQ) {
  cpu.mem_controller->Load16(*cpu.xip, HyperCPU::Opcode::CMP);
  cpu.mem_controller->Load8(*cpu.xip + 2, EncodeTestFlags(HyperCPU::Mode::b32,  HyperCPU::Mode::b32, HyperCPU::OperandTypes::R_M)
;
  cpu.mem_controller->Load8(*cpu.xip + 3, HyperCPU::Reg::XL0);
  cpu.mem_controller->Load64(*cpu.xip + 4, 1024);
  cpu.mem_controller->Load16(*cpu.xip + 12, HyperCPU::Opcode::HALT);
  cpu.mem_controller->Load8(*cpu.xip + 14, HyperCPU::OperandTypes::NONE);
  cpu.mem_controller->Load32(*cpu.xip + 1024, 0x0F);
  *cpu.xl0 = 0x0F;

  cpu.Run();

  ASSERT_TRUE(cpu.zrf);
  ASSERT_FALSE(cpu.crf);
}

TEST_F(CPU_TEST, INSTR_CMP_R_M_b64_LE) {
  cpu.mem_controller->Load16(*cpu.xip, HyperCPU::Opcode::CMP);
  cpu.mem_controller->Load8(*cpu.xip + 2, EncodeTestFlags(HyperCPU::Mode::b64,  HyperCPU::Mode::b64, HyperCPU::OperandTypes::R_M)
;
  cpu.mem_controller->Load8(*cpu.xip + 3, HyperCPU::Reg::X0);
  cpu.mem_controller->Load64(*cpu.xip + 4, 1024);
  cpu.mem_controller->Load16(*cpu.xip + 12, HyperCPU::Opcode::HALT);
  cpu.mem_controller->Load8(*cpu.xip + 14, HyperCPU::OperandTypes::NONE);
  cpu.mem_controller->Load64(*cpu.xip + 1024, 0x1F);
  *cpu.x0 = 0x0F;

  cpu.Run();

  ASSERT_FALSE(cpu.zrf);
  ASSERT_TRUE(cpu.crf);
}

TEST_F(CPU_TEST, INSTR_CMP_R_M_b64_GR) {
  cpu.mem_controller->Load16(*cpu.xip, HyperCPU::Opcode::CMP);
  cpu.mem_controller->Load8(*cpu.xip + 2, EncodeTestFlags(HyperCPU::Mode::b64,  HyperCPU::Mode::b64, HyperCPU::OperandTypes::R_M)
;
  cpu.mem_controller->Load8(*cpu.xip + 3, HyperCPU::Reg::X0);
  cpu.mem_controller->Load64(*cpu.xip + 4, 1024);
  cpu.mem_controller->Load16(*cpu.xip + 12, HyperCPU::Opcode::HALT);
  cpu.mem_controller->Load8(*cpu.xip + 14, HyperCPU::OperandTypes::NONE);
  cpu.mem_controller->Load64(*cpu.xip + 1024, 0x0F);
  *cpu.x0 = 0x1F;

  cpu.Run();

  ASSERT_FALSE(cpu.zrf);
  ASSERT_FALSE(cpu.crf);
}

TEST_F(CPU_TEST, INSTR_CMP_R_M_b64_EQ) {
  cpu.mem_controller->Load16(*cpu.xip, HyperCPU::Opcode::CMP);
  cpu.mem_controller->Load8(*cpu.xip + 2, EncodeTestFlags(HyperCPU::Mode::b64,  HyperCPU::Mode::b64, HyperCPU::OperandTypes::R_M)
;
  cpu.mem_controller->Load8(*cpu.xip + 3, HyperCPU::Reg::X0);
  cpu.mem_controller->Load64(*cpu.xip + 4, 1024);
  cpu.mem_controller->Load16(*cpu.xip + 12, HyperCPU::Opcode::HALT);
  cpu.mem_controller->Load8(*cpu.xip + 14, HyperCPU::OperandTypes::NONE);
  cpu.mem_controller->Load64(*cpu.xip + 1024, 0x0F);
  *cpu.x0 = 0x0F;

  cpu.Run();

  ASSERT_TRUE(cpu.zrf);
  ASSERT_FALSE(cpu.crf);
}

TEST_F(CPU_TEST, INSTR_CMP_R_IMM_b8_LE) {
  cpu.mem_controller->Load16(*cpu.xip, HyperCPU::Opcode::CMP);
  cpu.mem_controller->Load8(*cpu.xip + 2, EncodeTestFlags(HyperCPU::Mode::b8,  HyperCPU::Mode::b8, HyperCPU::OperandTypes::R_IMM)
;
  cpu.mem_controller->Load8(*cpu.xip + 3, HyperCPU::Reg::XLLL0);
  cpu.mem_controller->Load8(*cpu.xip + 4, 0x1F);
  cpu.mem_controller->Load16(*cpu.xip + 5, HyperCPU::Opcode::HALT);
  cpu.mem_controller->Load8(*cpu.xip + 7, HyperCPU::OperandTypes::NONE);
  *cpu.xlll0 = 0x0F;

  cpu.Run();

  ASSERT_FALSE(cpu.zrf);
  ASSERT_TRUE(cpu.crf);
}

TEST_F(CPU_TEST, INSTR_CMP_R_IMM_b8_GR) {
  cpu.mem_controller->Load16(*cpu.xip, HyperCPU::Opcode::CMP);
  cpu.mem_controller->Load8(*cpu.xip + 2, EncodeTestFlags(HyperCPU::Mode::b8,  HyperCPU::Mode::b8, HyperCPU::OperandTypes::R_IMM)
;
  cpu.mem_controller->Load8(*cpu.xip + 3, HyperCPU::Reg::XLLL0);
  cpu.mem_controller->Load8(*cpu.xip + 4, 0x0F);
  cpu.mem_controller->Load16(*cpu.xip + 5, HyperCPU::Opcode::HALT);
  cpu.mem_controller->Load8(*cpu.xip + 7, HyperCPU::OperandTypes::NONE);
  *cpu.xlll0 = 0x1F;

  cpu.Run();

  ASSERT_FALSE(cpu.zrf);
  ASSERT_FALSE(cpu.crf);
}

TEST_F(CPU_TEST, INSTR_CMP_R_IMM_b8_EQ) {
  cpu.mem_controller->Load16(*cpu.xip, HyperCPU::Opcode::CMP);
  cpu.mem_controller->Load8(*cpu.xip + 2, EncodeTestFlags(HyperCPU::Mode::b8,  HyperCPU::Mode::b8, HyperCPU::OperandTypes::R_IMM)
;
  cpu.mem_controller->Load8(*cpu.xip + 3, HyperCPU::Reg::XLLL0);
  cpu.mem_controller->Load8(*cpu.xip + 4, 0x0F);
  cpu.mem_controller->Load16(*cpu.xip + 5, HyperCPU::Opcode::HALT);
  cpu.mem_controller->Load8(*cpu.xip + 7, HyperCPU::OperandTypes::NONE);
  *cpu.xlll0 = 0x0F;

  cpu.Run();

  ASSERT_TRUE(cpu.zrf);
  ASSERT_FALSE(cpu.crf);
}

TEST_F(CPU_TEST, INSTR_CMP_R_IMM_b16_LE) {
  cpu.mem_controller->Load16(*cpu.xip, HyperCPU::Opcode::CMP);
  cpu.mem_controller->Load8(*cpu.xip + 2, EncodeTestFlags(HyperCPU::Mode::b16,  HyperCPU::Mode::b16, HyperCPU::OperandTypes::R_IMM)
;
  cpu.mem_controller->Load8(*cpu.xip + 3, HyperCPU::Reg::XLL0);
  cpu.mem_controller->Load16(*cpu.xip + 4, 0x1F);
  cpu.mem_controller->Load16(*cpu.xip + 6, HyperCPU::Opcode::HALT);
  cpu.mem_controller->Load8(*cpu.xip + 8, HyperCPU::OperandTypes::NONE);
  *cpu.xll0 = 0x0F;

  cpu.Run();

  ASSERT_FALSE(cpu.zrf);
  ASSERT_TRUE(cpu.crf);
}

TEST_F(CPU_TEST, INSTR_CMP_R_IMM_b16_GR) {
  cpu.mem_controller->Load16(*cpu.xip, HyperCPU::Opcode::CMP);
  cpu.mem_controller->Load8(*cpu.xip + 2, EncodeTestFlags(HyperCPU::Mode::b16,  HyperCPU::Mode::b16, HyperCPU::OperandTypes::R_IMM)
;
  cpu.mem_controller->Load8(*cpu.xip + 3, HyperCPU::Reg::XLL0);
  cpu.mem_controller->Load16(*cpu.xip + 4, 0x0F);
  cpu.mem_controller->Load16(*cpu.xip + 6, HyperCPU::Opcode::HALT);
  cpu.mem_controller->Load8(*cpu.xip + 8, HyperCPU::OperandTypes::NONE);
  *cpu.xll0 = 0x1F;

  cpu.Run();

  ASSERT_FALSE(cpu.zrf);
  ASSERT_FALSE(cpu.crf);
}

TEST_F(CPU_TEST, INSTR_CMP_R_IMM_b16_EQ) {
  cpu.mem_controller->Load16(*cpu.xip, HyperCPU::Opcode::CMP);
  cpu.mem_controller->Load8(*cpu.xip + 2, EncodeTestFlags(HyperCPU::Mode::b16,  HyperCPU::Mode::b16, HyperCPU::OperandTypes::R_IMM)
;
  cpu.mem_controller->Load8(*cpu.xip + 3, HyperCPU::Reg::XLL0);
  cpu.mem_controller->Load16(*cpu.xip + 4, 0x0F);
  cpu.mem_controller->Load16(*cpu.xip + 6, HyperCPU::Opcode::HALT);
  cpu.mem_controller->Load8(*cpu.xip + 8, HyperCPU::OperandTypes::NONE);
  *cpu.xll0 = 0x0F;

  cpu.Run();

  ASSERT_TRUE(cpu.zrf);
  ASSERT_FALSE(cpu.crf);
}

TEST_F(CPU_TEST, INSTR_CMP_R_IMM_b32_LE) {
  cpu.mem_controller->Load16(*cpu.xip, HyperCPU::Opcode::CMP);
  cpu.mem_controller->Load8(*cpu.xip + 2, EncodeTestFlags(HyperCPU::Mode::b32,  HyperCPU::Mode::b32, HyperCPU::OperandTypes::R_IMM)
;
  cpu.mem_controller->Load8(*cpu.xip + 3, HyperCPU::Reg::XL0);
  cpu.mem_controller->Load32(*cpu.xip + 4, 0x1F);
  cpu.mem_controller->Load16(*cpu.xip + 8, HyperCPU::Opcode::HALT);
  cpu.mem_controller->Load8(*cpu.xip + 10, HyperCPU::OperandTypes::NONE);
  *cpu.xl0 = 0x0F;

  cpu.Run();

  ASSERT_FALSE(cpu.zrf);
  ASSERT_TRUE(cpu.crf);
}

TEST_F(CPU_TEST, INSTR_CMP_R_IMM_b32_GR) {
  cpu.mem_controller->Load16(*cpu.xip, HyperCPU::Opcode::CMP);
  cpu.mem_controller->Load8(*cpu.xip + 2, EncodeTestFlags(HyperCPU::Mode::b32,  HyperCPU::Mode::b32, HyperCPU::OperandTypes::R_IMM)
;
  cpu.mem_controller->Load8(*cpu.xip + 3, HyperCPU::Reg::XL0);
  cpu.mem_controller->Load32(*cpu.xip + 4, 0x0F);
  cpu.mem_controller->Load16(*cpu.xip + 8, HyperCPU::Opcode::HALT);
  cpu.mem_controller->Load8(*cpu.xip + 10, HyperCPU::OperandTypes::NONE);
  *cpu.xl0 = 0x1F;

  cpu.Run();

  ASSERT_FALSE(cpu.zrf);
  ASSERT_FALSE(cpu.crf);
}

TEST_F(CPU_TEST, INSTR_CMP_R_IMM_b32_EQ) {
  cpu.mem_controller->Load16(*cpu.xip, HyperCPU::Opcode::CMP);
  cpu.mem_controller->Load8(*cpu.xip + 2, EncodeTestFlags(HyperCPU::Mode::b32,  HyperCPU::Mode::b32, HyperCPU::OperandTypes::R_IMM)
;
  cpu.mem_controller->Load8(*cpu.xip + 3, HyperCPU::Reg::XL0);
  cpu.mem_controller->Load32(*cpu.xip + 4, 0x0F);
  cpu.mem_controller->Load16(*cpu.xip + 8, HyperCPU::Opcode::HALT);
  cpu.mem_controller->Load8(*cpu.xip + 10, HyperCPU::OperandTypes::NONE);
  *cpu.xl0 = 0x0F;

  cpu.Run();

  ASSERT_TRUE(cpu.zrf);
  ASSERT_FALSE(cpu.crf);
}

TEST_F(CPU_TEST, INSTR_CMP_R_IMM_b64_LE) {
  cpu.mem_controller->Load16(*cpu.xip, HyperCPU::Opcode::CMP);
  cpu.mem_controller->Load8(*cpu.xip + 2, EncodeTestFlags(HyperCPU::Mode::b64,  HyperCPU::Mode::b64, HyperCPU::OperandTypes::R_IMM));
  cpu.mem_controller->Load8(*cpu.xip + 3, HyperCPU::Reg::X0);
  cpu.mem_controller->Load64(*cpu.xip + 4, 0x1F);
  cpu.mem_controller->Load16(*cpu.xip + 12, HyperCPU::Opcode::HALT);
  cpu.mem_controller->Load8(*cpu.xip + 14, HyperCPU::OperandTypes::NONE);
  *cpu.x0 = 0x0F;

  cpu.Run();

  ASSERT_FALSE(cpu.zrf);
  ASSERT_TRUE(cpu.crf);
}

TEST_F(CPU_TEST, INSTR_CMP_R_IMM_b64_GR) {
  cpu.mem_controller->Load16(*cpu.xip, HyperCPU::Opcode::CMP);
  cpu.mem_controller->Load8(*cpu.xip + 2, EncodeTestFlags(HyperCPU::Mode::b64,  HyperCPU::Mode::b64, HyperCPU::OperandTypes::R_IMM));
  cpu.mem_controller->Load8(*cpu.xip + 3, HyperCPU::Reg::X0);
  cpu.mem_controller->Load64(*cpu.xip + 4, 0x0F);
  cpu.mem_controller->Load16(*cpu.xip + 12, HyperCPU::Opcode::HALT);
  cpu.mem_controller->Load8(*cpu.xip + 14, HyperCPU::OperandTypes::NONE);
  *cpu.x0 = 0x1F;

  cpu.Run();

  ASSERT_FALSE(cpu.zrf);
  ASSERT_FALSE(cpu.crf);
}

TEST_F(CPU_TEST, INSTR_CMP_R_IMM_b64_EQ) {
  cpu.mem_controller->Load16(*cpu.xip, HyperCPU::Opcode::CMP);
  cpu.mem_controller->Load8(*cpu.xip + 2, EncodeTestFlags(HyperCPU::Mode::b64,  HyperCPU::Mode::b64, HyperCPU::OperandTypes::R_IMM));
  cpu.mem_controller->Load8(*cpu.xip + 3, HyperCPU::Reg::X0);
  cpu.mem_controller->Load64(*cpu.xip + 4, 0x0F);
  cpu.mem_controller->Load16(*cpu.xip + 12, HyperCPU::Opcode::HALT);
  cpu.mem_controller->Load8(*cpu.xip + 14, HyperCPU::OperandTypes::NONE);
  *cpu.x0 = 0x0F;

  cpu.Run();

  ASSERT_TRUE(cpu.zrf);
  ASSERT_FALSE(cpu.crf);
}

TEST_F(CPU_TEST, INSTR_CMP_RM_R_b8_LE) {
  cpu.mem_controller->Load16(*cpu.xip, HyperCPU::Opcode::CMP);
  cpu.mem_controller->Load8(*cpu.xip + 2, EncodeTestFlags(HyperCPU::Mode::b8,  HyperCPU::Mode::b8, HyperCPU::OperandTypes::RM_R))
;
  cpu.mem_controller->Load8(*cpu.xip + 3, HyperCPU::Reg::X0);
  cpu.mem_controller->Load8(*cpu.xip + 4, HyperCPU::Reg::XLLL1);
  cpu.mem_controller->Load16(*cpu.xip + 5, HyperCPU::Opcode::HALT);
  cpu.mem_controller->Load8(*cpu.xip + 7, HyperCPU::OperandTypes::NONE);
  cpu.mem_controller->Load8(1024, 0x0F);
  *cpu.x0 = 1024;
  *cpu.xlll1 = 0x1F;

  cpu.Run();

  ASSERT_FALSE(cpu.zrf);
  ASSERT_TRUE(cpu.crf);
}

TEST_F(CPU_TEST, INSTR_CMP_RM_R_b8_GR) {
  cpu.mem_controller->Load16(*cpu.xip, HyperCPU::Opcode::CMP);
  cpu.mem_controller->Load8(*cpu.xip + 2, EncodeTestFlags(HyperCPU::Mode::b8,  HyperCPU::Mode::b8, HyperCPU::OperandTypes::RM_R))
;
  cpu.mem_controller->Load8(*cpu.xip + 3, HyperCPU::Reg::X0);
  cpu.mem_controller->Load8(*cpu.xip + 4, HyperCPU::Reg::XLLL1);
  cpu.mem_controller->Load16(*cpu.xip + 5, HyperCPU::Opcode::HALT);
  cpu.mem_controller->Load8(*cpu.xip + 7, HyperCPU::OperandTypes::NONE);
  cpu.mem_controller->Load8(1024, 0x1F);
  *cpu.x0 = 1024;
  *cpu.xlll1 = 0x0F;

  cpu.Run();

  ASSERT_FALSE(cpu.zrf);
  ASSERT_FALSE(cpu.crf);
}

TEST_F(CPU_TEST, INSTR_CMP_RM_R_b8_EQ) {
  cpu.mem_controller->Load16(*cpu.xip, HyperCPU::Opcode::CMP);
  cpu.mem_controller->Load8(*cpu.xip + 2, EncodeTestFlags(HyperCPU::Mode::b8,  HyperCPU::Mode::b8, HyperCPU::OperandTypes::RM_R))
;
  cpu.mem_controller->Load8(*cpu.xip + 3, HyperCPU::Reg::X0);
  cpu.mem_controller->Load8(*cpu.xip + 4, HyperCPU::Reg::XLLL1);
  cpu.mem_controller->Load16(*cpu.xip + 5, HyperCPU::Opcode::HALT);
  cpu.mem_controller->Load8(*cpu.xip + 7, HyperCPU::OperandTypes::NONE);
  cpu.mem_controller->Load8(1024, 0x0F);
  *cpu.x0 = 1024;
  *cpu.xlll1 = 0x0F;

  cpu.Run();

  ASSERT_TRUE(cpu.zrf);
  ASSERT_FALSE(cpu.crf);
}

TEST_F(CPU_TEST, INSTR_CMP_RM_R_b16_LE) {
  cpu.mem_controller->Load16(*cpu.xip, HyperCPU::Opcode::CMP);
  cpu.mem_controller->Load8(*cpu.xip + 2, EncodeTestFlags(HyperCPU::Mode::b16,  HyperCPU::Mode::b16, HyperCPU::OperandTypes::RM_R))
;
  cpu.mem_controller->Load8(*cpu.xip + 3, HyperCPU::Reg::X0);
  cpu.mem_controller->Load8(*cpu.xip + 4, HyperCPU::Reg::XLL1);
  cpu.mem_controller->Load16(*cpu.xip + 5, HyperCPU::Opcode::HALT);
  cpu.mem_controller->Load8(*cpu.xip + 7, HyperCPU::OperandTypes::NONE);
  cpu.mem_controller->Load16(1024, 0x0F);
  *cpu.x0 = 1024;
  *cpu.xll1 = 0x1F;

  cpu.Run();

  ASSERT_FALSE(cpu.zrf);
  ASSERT_TRUE(cpu.crf);
}

TEST_F(CPU_TEST, INSTR_CMP_RM_R_b16_GR) {
  cpu.mem_controller->Load16(*cpu.xip, HyperCPU::Opcode::CMP);
  cpu.mem_controller->Load8(*cpu.xip + 2, EncodeTestFlags(HyperCPU::Mode::b16,  HyperCPU::Mode::b16, HyperCPU::OperandTypes::RM_R))
;
  cpu.mem_controller->Load8(*cpu.xip + 3, HyperCPU::Reg::X0);
  cpu.mem_controller->Load8(*cpu.xip + 4, HyperCPU::Reg::XLL1);
  cpu.mem_controller->Load16(*cpu.xip + 5, HyperCPU::Opcode::HALT);
  cpu.mem_controller->Load8(*cpu.xip + 7, HyperCPU::OperandTypes::NONE);
  cpu.mem_controller->Load16(1024, 0x1F);
  *cpu.x0 = 1024;
  *cpu.xll1 = 0x0F;

  cpu.Run();

  ASSERT_FALSE(cpu.zrf);
  ASSERT_FALSE(cpu.crf);
}

TEST_F(CPU_TEST, INSTR_CMP_RM_R_b16_EQ) {
  cpu.mem_controller->Load16(*cpu.xip, HyperCPU::Opcode::CMP);
  cpu.mem_controller->Load8(*cpu.xip + 2, EncodeTestFlags(HyperCPU::Mode::b16,  HyperCPU::Mode::b16, HyperCPU::OperandTypes::RM_R))
;
  cpu.mem_controller->Load8(*cpu.xip + 3, HyperCPU::Reg::X0);
  cpu.mem_controller->Load8(*cpu.xip + 4, HyperCPU::Reg::XLL1);
  cpu.mem_controller->Load16(*cpu.xip + 5, HyperCPU::Opcode::HALT);
  cpu.mem_controller->Load8(*cpu.xip + 7, HyperCPU::OperandTypes::NONE);
  cpu.mem_controller->Load16(1024, 0x0F);
  *cpu.x0 = 1024;
  *cpu.xll1 = 0x0F;

  cpu.Run();

  ASSERT_TRUE(cpu.zrf);
  ASSERT_FALSE(cpu.crf);
}

TEST_F(CPU_TEST, INSTR_CMP_RM_R_b32_LE) {
  cpu.mem_controller->Load16(*cpu.xip, HyperCPU::Opcode::CMP);
  cpu.mem_controller->Load8(*cpu.xip + 2, EncodeTestFlags(HyperCPU::Mode::b32,  HyperCPU::Mode::b32, HyperCPU::OperandTypes::RM_R))
;
  cpu.mem_controller->Load8(*cpu.xip + 3, HyperCPU::Reg::X0);
  cpu.mem_controller->Load8(*cpu.xip + 4, HyperCPU::Reg::XL1);
  cpu.mem_controller->Load16(*cpu.xip + 5, HyperCPU::Opcode::HALT);
  cpu.mem_controller->Load8(*cpu.xip + 7, HyperCPU::OperandTypes::NONE);
  cpu.mem_controller->Load32(1024, 0x0F);
  *cpu.x0 = 1024;
  *cpu.xl1 = 0x1F;

  cpu.Run();

  ASSERT_FALSE(cpu.zrf);
  ASSERT_TRUE(cpu.crf);
}

TEST_F(CPU_TEST, INSTR_CMP_RM_R_b32_GR) {
  cpu.mem_controller->Load16(*cpu.xip, HyperCPU::Opcode::CMP);
  cpu.mem_controller->Load8(*cpu.xip + 2, EncodeTestFlags(HyperCPU::Mode::b32,  HyperCPU::Mode::b32, HyperCPU::OperandTypes::RM_R))
;
  cpu.mem_controller->Load8(*cpu.xip + 3, HyperCPU::Reg::X0);
  cpu.mem_controller->Load8(*cpu.xip + 4, HyperCPU::Reg::XL1);
  cpu.mem_controller->Load16(*cpu.xip + 5, HyperCPU::Opcode::HALT);
  cpu.mem_controller->Load8(*cpu.xip + 7, HyperCPU::OperandTypes::NONE);
  cpu.mem_controller->Load32(1024, 0x1F);
  *cpu.x0 = 1024;
  *cpu.xl1 = 0x0F;

  cpu.Run();

  ASSERT_FALSE(cpu.zrf);
  ASSERT_FALSE(cpu.crf);
}

TEST_F(CPU_TEST, INSTR_CMP_RM_R_b32_EQ) {
  cpu.mem_controller->Load16(*cpu.xip, HyperCPU::Opcode::CMP);
  cpu.mem_controller->Load8(*cpu.xip + 2, EncodeTestFlags(HyperCPU::Mode::b32,  HyperCPU::Mode::b32, HyperCPU::OperandTypes::RM_R))
;
  cpu.mem_controller->Load8(*cpu.xip + 3, HyperCPU::Reg::X0);
  cpu.mem_controller->Load8(*cpu.xip + 4, HyperCPU::Reg::XL1);
  cpu.mem_controller->Load16(*cpu.xip + 5, HyperCPU::Opcode::HALT);
  cpu.mem_controller->Load8(*cpu.xip + 7, HyperCPU::OperandTypes::NONE);
  cpu.mem_controller->Load32(1024, 0x0F);
  *cpu.x0 = 1024;
  *cpu.xl1 = 0x0F;

  cpu.Run();

  ASSERT_TRUE(cpu.zrf);
  ASSERT_FALSE(cpu.crf);
}

TEST_F(CPU_TEST, INSTR_CMP_RM_R_b64_LE) {
  cpu.mem_controller->Load16(*cpu.xip, HyperCPU::Opcode::CMP);
  cpu.mem_controller->Load8(*cpu.xip + 2, EncodeTestFlags(HyperCPU::Mode::b64,  HyperCPU::Mode::b64, HyperCPU::OperandTypes::RM_R))
;
  cpu.mem_controller->Load8(*cpu.xip + 3, HyperCPU::Reg::X0);
  cpu.mem_controller->Load8(*cpu.xip + 4, HyperCPU::Reg::X1);
  cpu.mem_controller->Load16(*cpu.xip + 5, HyperCPU::Opcode::HALT);
  cpu.mem_controller->Load8(*cpu.xip + 7, HyperCPU::OperandTypes::NONE);
  cpu.mem_controller->Load64(1024, 0x0F);
  *cpu.x0 = 1024;
  *cpu.x1 = 0x1F;

  cpu.Run();

  ASSERT_FALSE(cpu.zrf);
  ASSERT_TRUE(cpu.crf);
}

TEST_F(CPU_TEST, INSTR_CMP_RM_R_b64_GR) {
  cpu.mem_controller->Load16(*cpu.xip, HyperCPU::Opcode::CMP);
  cpu.mem_controller->Load8(*cpu.xip + 2, EncodeTestFlags(HyperCPU::Mode::b64,  HyperCPU::Mode::b64, HyperCPU::OperandTypes::RM_R))
;
  cpu.mem_controller->Load8(*cpu.xip + 3, HyperCPU::Reg::X0);
  cpu.mem_controller->Load8(*cpu.xip + 4, HyperCPU::Reg::X1);
  cpu.mem_controller->Load16(*cpu.xip + 5, HyperCPU::Opcode::HALT);
  cpu.mem_controller->Load8(*cpu.xip + 7, HyperCPU::OperandTypes::NONE);
  cpu.mem_controller->Load64(1024, 0x1F);
  *cpu.x0 = 1024;
  *cpu.x1 = 0x0F;

  cpu.Run();

  ASSERT_FALSE(cpu.zrf);
  ASSERT_FALSE(cpu.crf);
}

TEST_F(CPU_TEST, INSTR_CMP_RM_R_b64_EQ) {
  cpu.mem_controller->Load16(*cpu.xip, HyperCPU::Opcode::CMP);
  cpu.mem_controller->Load8(*cpu.xip + 2, EncodeTestFlags(HyperCPU::Mode::b64,  HyperCPU::Mode::b64, HyperCPU::OperandTypes::RM_R))
;
  cpu.mem_controller->Load8(*cpu.xip + 3, HyperCPU::Reg::X0);
  cpu.mem_controller->Load8(*cpu.xip + 4, HyperCPU::Reg::X1);
  cpu.mem_controller->Load16(*cpu.xip + 5, HyperCPU::Opcode::HALT);
  cpu.mem_controller->Load8(*cpu.xip + 7, HyperCPU::OperandTypes::NONE);
  cpu.mem_controller->Load64(1024, 0x0F);
  *cpu.x0 = 1024;
  *cpu.x1 = 0x0F;

  cpu.Run();

  ASSERT_TRUE(cpu.zrf);
  ASSERT_FALSE(cpu.crf);
}

TEST_F(CPU_TEST, INSTR_CMP_RM_M_b8_LE) {
  cpu.mem_controller->Load16(*cpu.xip, HyperCPU::Opcode::CMP);
  cpu.mem_controller->Load8(*cpu.xip + 2, EncodeTestFlags(HyperCPU::Mode::b8,  HyperCPU::Mode::b8, HyperCPU::OperandTypes::RM_M))
;
  cpu.mem_controller->Load8(*cpu.xip + 3, HyperCPU::Reg::X0);
  cpu.mem_controller->Load64(*cpu.xip + 4, 1536);
  cpu.mem_controller->Load16(*cpu.xip + 12, HyperCPU::Opcode::HALT);
  cpu.mem_controller->Load8(*cpu.xip + 14, HyperCPU::OperandTypes::NONE);
  cpu.mem_controller->Load8(1024, 0x0F);
  cpu.mem_controller->Load8(1536, 0x1F);
  *cpu.x0 = 1024;

  cpu.Run();

  ASSERT_FALSE(cpu.zrf);
  ASSERT_TRUE(cpu.crf);
}

TEST_F(CPU_TEST, INSTR_CMP_RM_M_b8_GR) {
  cpu.mem_controller->Load16(*cpu.xip, HyperCPU::Opcode::CMP);
  cpu.mem_controller->Load8(*cpu.xip + 2, EncodeTestFlags(HyperCPU::Mode::b8,  HyperCPU::Mode::b8, HyperCPU::OperandTypes::RM_M))
;
  cpu.mem_controller->Load8(*cpu.xip + 3, HyperCPU::Reg::X0);
  cpu.mem_controller->Load64(*cpu.xip + 4, 1536);
  cpu.mem_controller->Load16(*cpu.xip + 12, HyperCPU::Opcode::HALT);
  cpu.mem_controller->Load8(*cpu.xip + 14, HyperCPU::OperandTypes::NONE);
  cpu.mem_controller->Load8(1024, 0x1F);
  cpu.mem_controller->Load8(1536, 0x0F);
  *cpu.x0 = 1024;

  cpu.Run();

  ASSERT_FALSE(cpu.zrf);
  ASSERT_FALSE(cpu.crf);
}

TEST_F(CPU_TEST, INSTR_CMP_RM_M_b8_EQ) {
  cpu.mem_controller->Load16(*cpu.xip, HyperCPU::Opcode::CMP);
  cpu.mem_controller->Load8(*cpu.xip + 2, EncodeTestFlags(HyperCPU::Mode::b8,  HyperCPU::Mode::b8, HyperCPU::OperandTypes::RM_M))
;
  cpu.mem_controller->Load8(*cpu.xip + 3, HyperCPU::Reg::X0);
  cpu.mem_controller->Load64(*cpu.xip + 4, 1536);
  cpu.mem_controller->Load16(*cpu.xip + 12, HyperCPU::Opcode::HALT);
  cpu.mem_controller->Load8(*cpu.xip + 14, HyperCPU::OperandTypes::NONE);
  cpu.mem_controller->Load8(1024, 0x0F);
  cpu.mem_controller->Load8(1536, 0x0F);
  *cpu.x0 = 1024;

  cpu.Run();

  ASSERT_TRUE(cpu.zrf);
  ASSERT_FALSE(cpu.crf);
}

TEST_F(CPU_TEST, INSTR_CMP_RM_M_b16_LE) {
  cpu.mem_controller->Load16(*cpu.xip, HyperCPU::Opcode::CMP);
  cpu.mem_controller->Load8(*cpu.xip + 2, EncodeTestFlags(HyperCPU::Mode::b16,  HyperCPU::Mode::b16, HyperCPU::OperandTypes::RM_M))
;
  cpu.mem_controller->Load8(*cpu.xip + 3, HyperCPU::Reg::X0);
  cpu.mem_controller->Load64(*cpu.xip + 4, 1536);
  cpu.mem_controller->Load16(*cpu.xip + 12, HyperCPU::Opcode::HALT);
  cpu.mem_controller->Load8(*cpu.xip + 14, HyperCPU::OperandTypes::NONE);
  cpu.mem_controller->Load16(1024, 0x0F);
  cpu.mem_controller->Load16(1536, 0x1F);
  *cpu.x0 = 1024;

  cpu.Run();

  ASSERT_FALSE(cpu.zrf);
  ASSERT_TRUE(cpu.crf);
}

TEST_F(CPU_TEST, INSTR_CMP_RM_M_b16_GR) {
  cpu.mem_controller->Load16(*cpu.xip, HyperCPU::Opcode::CMP);
  cpu.mem_controller->Load8(*cpu.xip + 2, EncodeTestFlags(HyperCPU::Mode::b16,  HyperCPU::Mode::b16, HyperCPU::OperandTypes::RM_M))
;
  cpu.mem_controller->Load8(*cpu.xip + 3, HyperCPU::Reg::X0);
  cpu.mem_controller->Load64(*cpu.xip + 4, 1536);
  cpu.mem_controller->Load16(*cpu.xip + 12, HyperCPU::Opcode::HALT);
  cpu.mem_controller->Load8(*cpu.xip + 14, HyperCPU::OperandTypes::NONE);
  cpu.mem_controller->Load16(1024, 0x1F);
  cpu.mem_controller->Load16(1536, 0x0F);
  *cpu.x0 = 1024;

  cpu.Run();

  ASSERT_FALSE(cpu.zrf);
  ASSERT_FALSE(cpu.crf);
}

TEST_F(CPU_TEST, INSTR_CMP_RM_M_b16_EQ) {
  cpu.mem_controller->Load16(*cpu.xip, HyperCPU::Opcode::CMP);
  cpu.mem_controller->Load8(*cpu.xip + 2, EncodeTestFlags(HyperCPU::Mode::b16,  HyperCPU::Mode::b16, HyperCPU::OperandTypes::RM_M))
;
  cpu.mem_controller->Load8(*cpu.xip + 3, HyperCPU::Reg::X0);
  cpu.mem_controller->Load64(*cpu.xip + 4, 1536);
  cpu.mem_controller->Load16(*cpu.xip + 12, HyperCPU::Opcode::HALT);
  cpu.mem_controller->Load8(*cpu.xip + 14, HyperCPU::OperandTypes::NONE);
  cpu.mem_controller->Load16(1024, 0x0F);
  cpu.mem_controller->Load16(1536, 0x0F);
  *cpu.x0 = 1024;

  cpu.Run();

  ASSERT_TRUE(cpu.zrf);
  ASSERT_FALSE(cpu.crf);
}

TEST_F(CPU_TEST, INSTR_CMP_RM_M_b32_LE) {
  cpu.mem_controller->Load16(*cpu.xip, HyperCPU::Opcode::CMP);
  cpu.mem_controller->Load8(*cpu.xip + 2, EncodeTestFlags(HyperCPU::Mode::b32,  HyperCPU::Mode::b32, HyperCPU::OperandTypes::RM_M))
;
  cpu.mem_controller->Load8(*cpu.xip + 3, HyperCPU::Reg::X0);
  cpu.mem_controller->Load64(*cpu.xip + 4, 1536);
  cpu.mem_controller->Load16(*cpu.xip + 12, HyperCPU::Opcode::HALT);
  cpu.mem_controller->Load8(*cpu.xip + 14, HyperCPU::OperandTypes::NONE);
  cpu.mem_controller->Load32(1024, 0x0F);
  cpu.mem_controller->Load32(1536, 0x1F);
  *cpu.x0 = 1024;

  cpu.Run();

  ASSERT_FALSE(cpu.zrf);
  ASSERT_TRUE(cpu.crf);
}

TEST_F(CPU_TEST, INSTR_CMP_RM_M_b32_GR) {
  cpu.mem_controller->Load16(*cpu.xip, HyperCPU::Opcode::CMP);
  cpu.mem_controller->Load8(*cpu.xip + 2, EncodeTestFlags(HyperCPU::Mode::b32,  HyperCPU::Mode::b32, HyperCPU::OperandTypes::RM_M))
;
  cpu.mem_controller->Load8(*cpu.xip + 3, HyperCPU::Reg::X0);
  cpu.mem_controller->Load64(*cpu.xip + 4, 1536);
  cpu.mem_controller->Load16(*cpu.xip + 12, HyperCPU::Opcode::HALT);
  cpu.mem_controller->Load8(*cpu.xip + 14, HyperCPU::OperandTypes::NONE);
  cpu.mem_controller->Load32(1024, 0x1F);
  cpu.mem_controller->Load32(1536, 0x0F);
  *cpu.x0 = 1024;

  cpu.Run();

  ASSERT_FALSE(cpu.zrf);
  ASSERT_FALSE(cpu.crf);
}

TEST_F(CPU_TEST, INSTR_CMP_RM_M_b32_EQ) {
  cpu.mem_controller->Load16(*cpu.xip, HyperCPU::Opcode::CMP);
  cpu.mem_controller->Load8(*cpu.xip + 2, EncodeTestFlags(HyperCPU::Mode::b32,  HyperCPU::Mode::b32, HyperCPU::OperandTypes::RM_M))
;
  cpu.mem_controller->Load8(*cpu.xip + 3, HyperCPU::Reg::X0);
  cpu.mem_controller->Load64(*cpu.xip + 4, 1536);
  cpu.mem_controller->Load16(*cpu.xip + 12, HyperCPU::Opcode::HALT);
  cpu.mem_controller->Load8(*cpu.xip + 14, HyperCPU::OperandTypes::NONE);
  cpu.mem_controller->Load32(1024, 0x0F);
  cpu.mem_controller->Load32(1536, 0x0F);
  *cpu.x0 = 1024;

  cpu.Run();

  ASSERT_TRUE(cpu.zrf);
  ASSERT_FALSE(cpu.crf);
}

TEST_F(CPU_TEST, INSTR_CMP_RM_M_b64_LE) {
  cpu.mem_controller->Load16(*cpu.xip, HyperCPU::Opcode::CMP);
  cpu.mem_controller->Load8(*cpu.xip + 2, EncodeTestFlags(HyperCPU::Mode::b64,  HyperCPU::Mode::b64, HyperCPU::OperandTypes::RM_M))
;
  cpu.mem_controller->Load8(*cpu.xip + 3, HyperCPU::Reg::X0);
  cpu.mem_controller->Load64(*cpu.xip + 4, 1536);
  cpu.mem_controller->Load16(*cpu.xip + 12, HyperCPU::Opcode::HALT);
  cpu.mem_controller->Load8(*cpu.xip + 14, HyperCPU::OperandTypes::NONE);
  cpu.mem_controller->Load64(1024, 0x0F);
  cpu.mem_controller->Load64(1536, 0x1F);
  *cpu.x0 = 1024;

  cpu.Run();

  ASSERT_FALSE(cpu.zrf);
  ASSERT_TRUE(cpu.crf);
}

TEST_F(CPU_TEST, INSTR_CMP_RM_M_b64_GR) {
  cpu.mem_controller->Load16(*cpu.xip, HyperCPU::Opcode::CMP);
  cpu.mem_controller->Load8(*cpu.xip + 2, EncodeTestFlags(HyperCPU::Mode::b64,  HyperCPU::Mode::b64, HyperCPU::OperandTypes::RM_M))
;
  cpu.mem_controller->Load8(*cpu.xip + 3, HyperCPU::Reg::X0);
  cpu.mem_controller->Load64(*cpu.xip + 4, 1536);
  cpu.mem_controller->Load16(*cpu.xip + 12, HyperCPU::Opcode::HALT);
  cpu.mem_controller->Load8(*cpu.xip + 14, HyperCPU::OperandTypes::NONE);
  cpu.mem_controller->Load64(1024, 0x1F);
  cpu.mem_controller->Load64(1536, 0x0F);
  *cpu.x0 = 1024;

  cpu.Run();

  ASSERT_FALSE(cpu.zrf);
  ASSERT_FALSE(cpu.crf);
}

TEST_F(CPU_TEST, INSTR_CMP_M_R_b8_LE) {
  cpu.mem_controller->Load16(*cpu.xip, HyperCPU::Opcode::CMP);
  cpu.mem_controller->Load8(*cpu.xip + 2, EncodeTestFlags(HyperCPU::Mode::b8, HyperCPU::OperandTypes::M_R));
  cpu.mem_controller->Load64(*cpu.xip + 3, 1024);
  cpu.mem_controller->Load8(*cpu.xip + 11, HyperCPU::Reg::XLLL0);
  cpu.mem_controller->Load16(*cpu.xip + 12, HyperCPU::Opcode::HALT);
  cpu.mem_controller->Load8(*cpu.xip + 14, HyperCPU::OperandTypes::NONE);
  cpu.mem_controller->Load8(1024, 0x0F);
  *cpu.xlll0 = 0x1F;

  cpu.Run();

  ASSERT_FALSE(cpu.zrf);
  ASSERT_TRUE(cpu.crf);
}

TEST_F(CPU_TEST, INSTR_CMP_M_R_b8_GR) {
  cpu.mem_controller->Load16(*cpu.xip, HyperCPU::Opcode::CMP);
  cpu.mem_controller->Load8(*cpu.xip + 2, EncodeTestFlags(HyperCPU::Mode::b8, HyperCPU::OperandTypes::M_R));
  cpu.mem_controller->Load64(*cpu.xip + 3, 1024);
  cpu.mem_controller->Load8(*cpu.xip + 11, HyperCPU::Reg::XLLL0);
  cpu.mem_controller->Load16(*cpu.xip + 12, HyperCPU::Opcode::HALT);
  cpu.mem_controller->Load8(*cpu.xip + 14, HyperCPU::OperandTypes::NONE);
  cpu.mem_controller->Load8(1024, 0x1F);
  *cpu.xlll0 = 0x0F;

  cpu.Run();

  ASSERT_FALSE(cpu.zrf);
  ASSERT_FALSE(cpu.crf);
}

TEST_F(CPU_TEST, INSTR_CMP_M_R_b8_EQ) {
  cpu.mem_controller->Load16(*cpu.xip, HyperCPU::Opcode::CMP);
  cpu.mem_controller->Load8(*cpu.xip + 2, EncodeTestFlags(HyperCPU::Mode::b8, HyperCPU::OperandTypes::M_R));
  cpu.mem_controller->Load64(*cpu.xip + 3, 1024);
  cpu.mem_controller->Load8(*cpu.xip + 11, HyperCPU::Reg::XLLL0);
  cpu.mem_controller->Load16(*cpu.xip + 12, HyperCPU::Opcode::HALT);
  cpu.mem_controller->Load8(*cpu.xip + 14, HyperCPU::OperandTypes::NONE);
  cpu.mem_controller->Load8(1024, 0x0F);
  *cpu.xlll0 = 0x0F;

  cpu.Run();

  ASSERT_TRUE(cpu.zrf);
  ASSERT_FALSE(cpu.crf);
}

TEST_F(CPU_TEST, INSTR_CMP_M_R_b16_LE) {
  cpu.mem_controller->Load16(*cpu.xip, HyperCPU::Opcode::CMP);
  cpu.mem_controller->Load8(*cpu.xip + 2, EncodeTestFlags(HyperCPU::Mode::b16, HyperCPU::OperandTypes::M_R));
  cpu.mem_controller->Load64(*cpu.xip + 3, 1024);
  cpu.mem_controller->Load8(*cpu.xip + 11, HyperCPU::Reg::XLL0);
  cpu.mem_controller->Load16(*cpu.xip + 12, HyperCPU::Opcode::HALT);
  cpu.mem_controller->Load8(*cpu.xip + 14, HyperCPU::OperandTypes::NONE);
  cpu.mem_controller->Load16(1024, 0x0F);
  *cpu.xll0 = 0x1F;

  cpu.Run();

  ASSERT_FALSE(cpu.zrf);
  ASSERT_TRUE(cpu.crf);
}

TEST_F(CPU_TEST, INSTR_CMP_M_R_b16_GR) {
  cpu.mem_controller->Load16(*cpu.xip, HyperCPU::Opcode::CMP);
  cpu.mem_controller->Load8(*cpu.xip + 2, EncodeTestFlags(HyperCPU::Mode::b16, HyperCPU::OperandTypes::M_R));
  cpu.mem_controller->Load64(*cpu.xip + 3, 1024);
  cpu.mem_controller->Load8(*cpu.xip + 11, HyperCPU::Reg::XLL0);
  cpu.mem_controller->Load16(*cpu.xip + 12, HyperCPU::Opcode::HALT);
  cpu.mem_controller->Load8(*cpu.xip + 14, HyperCPU::OperandTypes::NONE);
  cpu.mem_controller->Load16(1024, 0x1F);
  *cpu.xll0 = 0x0F;

  cpu.Run();

  ASSERT_FALSE(cpu.zrf);
  ASSERT_FALSE(cpu.crf);
}

TEST_F(CPU_TEST, INSTR_CMP_M_R_b16_EQ) {
  cpu.mem_controller->Load16(*cpu.xip, HyperCPU::Opcode::CMP);
  cpu.mem_controller->Load8(*cpu.xip + 2, EncodeTestFlags(HyperCPU::Mode::b16, HyperCPU::OperandTypes::M_R));
  cpu.mem_controller->Load64(*cpu.xip + 3, 1024);
  cpu.mem_controller->Load8(*cpu.xip + 11, HyperCPU::Reg::XLL0);
  cpu.mem_controller->Load16(*cpu.xip + 12, HyperCPU::Opcode::HALT);
  cpu.mem_controller->Load8(*cpu.xip + 14, HyperCPU::OperandTypes::NONE);
  cpu.mem_controller->Load16(1024, 0x0F);
  *cpu.xll0 = 0x0F;

  cpu.Run();

  ASSERT_TRUE(cpu.zrf);
  ASSERT_FALSE(cpu.crf);
}

TEST_F(CPU_TEST, INSTR_CMP_M_R_b32_LE) {
  cpu.mem_controller->Load16(*cpu.xip, HyperCPU::Opcode::CMP);
  cpu.mem_controller->Load8(*cpu.xip + 2, EncodeTestFlags(HyperCPU::Mode::b32, HyperCPU::OperandTypes::M_R));
  cpu.mem_controller->Load64(*cpu.xip + 3, 1024);
  cpu.mem_controller->Load8(*cpu.xip + 11, HyperCPU::Reg::XL0);
  cpu.mem_controller->Load16(*cpu.xip + 12, HyperCPU::Opcode::HALT);
  cpu.mem_controller->Load8(*cpu.xip + 14, HyperCPU::OperandTypes::NONE);
  cpu.mem_controller->Load32(1024, 0x0F);
  *cpu.xl0 = 0x1F;

  cpu.Run();

  ASSERT_FALSE(cpu.zrf);
  ASSERT_TRUE(cpu.crf);
}

TEST_F(CPU_TEST, INSTR_CMP_M_R_b32_GR) {
  cpu.mem_controller->Load16(*cpu.xip, HyperCPU::Opcode::CMP);
  cpu.mem_controller->Load8(*cpu.xip + 2, EncodeTestFlags(HyperCPU::Mode::b32, HyperCPU::OperandTypes::M_R));
  cpu.mem_controller->Load64(*cpu.xip + 3, 1024);
  cpu.mem_controller->Load8(*cpu.xip + 11, HyperCPU::Reg::XL0);
  cpu.mem_controller->Load16(*cpu.xip + 12, HyperCPU::Opcode::HALT);
  cpu.mem_controller->Load8(*cpu.xip + 14, HyperCPU::OperandTypes::NONE);
  cpu.mem_controller->Load32(1024, 0x1F);
  *cpu.xl0 = 0x0F;

  cpu.Run();

  ASSERT_FALSE(cpu.zrf);
  ASSERT_FALSE(cpu.crf);
}

TEST_F(CPU_TEST, INSTR_CMP_M_R_b32_EQ) {
  cpu.mem_controller->Load16(*cpu.xip, HyperCPU::Opcode::CMP);
  cpu.mem_controller->Load8(*cpu.xip + 2, EncodeTestFlags(HyperCPU::Mode::b32, HyperCPU::OperandTypes::M_R));
  cpu.mem_controller->Load64(*cpu.xip + 3, 1024);
  cpu.mem_controller->Load8(*cpu.xip + 11, HyperCPU::Reg::XL0);
  cpu.mem_controller->Load16(*cpu.xip + 12, HyperCPU::Opcode::HALT);
  cpu.mem_controller->Load8(*cpu.xip + 14, HyperCPU::OperandTypes::NONE);
  cpu.mem_controller->Load32(1024, 0x0F);
  *cpu.xl0 = 0x0F;

  cpu.Run();

  ASSERT_TRUE(cpu.zrf);
  ASSERT_FALSE(cpu.crf);
}

TEST_F(CPU_TEST, INSTR_CMP_M_R_b64_LE) {
  cpu.mem_controller->Load16(*cpu.xip, HyperCPU::Opcode::CMP);
  cpu.mem_controller->Load8(*cpu.xip + 2, EncodeTestFlags(HyperCPU::Mode::b64, HyperCPU::OperandTypes::M_R));
  cpu.mem_controller->Load64(*cpu.xip + 3, 1024);
  cpu.mem_controller->Load8(*cpu.xip + 11, HyperCPU::Reg::X0);
  cpu.mem_controller->Load16(*cpu.xip + 12, HyperCPU::Opcode::HALT);
  cpu.mem_controller->Load8(*cpu.xip + 14, HyperCPU::OperandTypes::NONE);
  cpu.mem_controller->Load64(1024, 0x0F);
  *cpu.x0 = 0x1F;

  cpu.Run();

  ASSERT_FALSE(cpu.zrf);
  ASSERT_TRUE(cpu.crf);
}

TEST_F(CPU_TEST, INSTR_CMP_M_R_b64_GR) {
  cpu.mem_controller->Load16(*cpu.xip, HyperCPU::Opcode::CMP);
  cpu.mem_controller->Load8(*cpu.xip + 2, EncodeTestFlags(HyperCPU::Mode::b64, HyperCPU::OperandTypes::M_R));
  cpu.mem_controller->Load64(*cpu.xip + 3, 1024);
  cpu.mem_controller->Load8(*cpu.xip + 11, HyperCPU::Reg::X0);
  cpu.mem_controller->Load16(*cpu.xip + 12, HyperCPU::Opcode::HALT);
  cpu.mem_controller->Load8(*cpu.xip + 14, HyperCPU::OperandTypes::NONE);
  cpu.mem_controller->Load64(1024, 0x1F);
  *cpu.x0 = 0x0F;

  cpu.Run();

  ASSERT_FALSE(cpu.zrf);
  ASSERT_FALSE(cpu.crf);
}

TEST_F(CPU_TEST, INSTR_CMP_M_R_b64_EQ) {
  cpu.mem_controller->Load16(*cpu.xip, HyperCPU::Opcode::CMP);
  cpu.mem_controller->Load8(*cpu.xip + 2, EncodeTestFlags(HyperCPU::Mode::b64, HyperCPU::OperandTypes::M_R));
  cpu.mem_controller->Load64(*cpu.xip + 3, 1024);
  cpu.mem_controller->Load8(*cpu.xip + 11, HyperCPU::Reg::X0);
  cpu.mem_controller->Load16(*cpu.xip + 12, HyperCPU::Opcode::HALT);
  cpu.mem_controller->Load8(*cpu.xip + 14, HyperCPU::OperandTypes::NONE);
  cpu.mem_controller->Load64(1024, 0x0F);
  *cpu.x0 = 0x0F;

  cpu.Run();

  ASSERT_TRUE(cpu.zrf);
  ASSERT_FALSE(cpu.crf);
}
