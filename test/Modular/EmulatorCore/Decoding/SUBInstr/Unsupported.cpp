#include <gtest/gtest.h>

#include <cstring>

#include <fixtures.hpp>

#ifdef __HCPU_DEBUG
# define HCPU_ASSERT_EXIT(statement, x, regex) ASSERT_DEATH(statement, regex)
#else
# define HCPU_ASSERT_EXIT(statement, x, regex) ASSERT_EXIT(statement, x, regex)
#endif

TEST_F(DECODER_TEST, SUB_INSTR_M_R_B8) {
  decoder.mem_controller->Load16(counter, HyperCPU::SUB);
  counter += 2;
  decoder.mem_controller->Load8(counter, (HyperCPU::Mode::b8 << 4) | HyperCPU::OperandTypes::M_R);
  ++counter;
  decoder.mem_controller->Load64(counter, MEM_PTR);
  counter += 8;
  decoder.mem_controller->Load8(counter, HyperCPU::Registers::X7);
  counter = 0;
  
  HCPU_ASSERT_EXIT(decoder.FetchAndDecode(), ::testing::ExitedWithCode(1), "Invalid opcode!");
}

TEST_F(DECODER_TEST, SUB_INSTR_M_R_B16) {
  decoder.mem_controller->Load16(counter, HyperCPU::SUB);
  counter += 2;
  decoder.mem_controller->Load8(counter, (HyperCPU::Mode::b16 << 4) | HyperCPU::OperandTypes::M_R);
  ++counter;
  decoder.mem_controller->Load64(counter, MEM_PTR);
  counter += 8;
  decoder.mem_controller->Load8(counter, HyperCPU::Registers::X7);
  counter = 0;
  
  HCPU_ASSERT_EXIT(decoder.FetchAndDecode(), ::testing::ExitedWithCode(1), "Invalid opcode!");
}

TEST_F(DECODER_TEST, SUB_INSTR_M_R_B32) {
  decoder.mem_controller->Load16(counter, HyperCPU::SUB);
  counter += 2;
  decoder.mem_controller->Load8(counter, (HyperCPU::Mode::b32 << 4) | HyperCPU::OperandTypes::M_R);
  ++counter;
  decoder.mem_controller->Load64(counter, MEM_PTR);
  counter += 8;
  decoder.mem_controller->Load8(counter, HyperCPU::Registers::X7);
  counter = 0;
  
  HCPU_ASSERT_EXIT(decoder.FetchAndDecode(), ::testing::ExitedWithCode(1), "Invalid opcode!");
}

TEST_F(DECODER_TEST, SUB_INSTR_M_R_B64) {
  decoder.mem_controller->Load16(counter, HyperCPU::SUB);
  counter += 2;
  decoder.mem_controller->Load8(counter, (HyperCPU::Mode::b64 << 4) | HyperCPU::OperandTypes::M_R);
  ++counter;
  decoder.mem_controller->Load64(counter, MEM_PTR);
  counter += 8;
  decoder.mem_controller->Load8(counter, HyperCPU::Registers::X7);
  counter = 0;
  
  HCPU_ASSERT_EXIT(decoder.FetchAndDecode(), ::testing::ExitedWithCode(1), "Invalid opcode!");
}

TEST_F(DECODER_TEST, SUB_INSTR_RM_R_B8) {
  decoder.mem_controller->Load16(counter, HyperCPU::SUB);
  counter += 2;
  decoder.mem_controller->Load8(counter, (HyperCPU::Mode::b8 << 4) | HyperCPU::OperandTypes::RM_R);
  ++counter;
  decoder.mem_controller->Load8(counter, HyperCPU::Registers::X3);
  ++counter;
  decoder.mem_controller->Load8(counter, HyperCPU::Registers::X7);
  counter = 0;
  
  HCPU_ASSERT_EXIT(decoder.FetchAndDecode(), ::testing::ExitedWithCode(1), "Invalid opcode!");
}

TEST_F(DECODER_TEST, SUB_INSTR_RM_R_B16) {
  decoder.mem_controller->Load16(counter, HyperCPU::SUB);
  counter += 2;
  decoder.mem_controller->Load8(counter, (HyperCPU::Mode::b16 << 4) | HyperCPU::OperandTypes::RM_R);
  ++counter;
  decoder.mem_controller->Load8(counter, HyperCPU::Registers::X3);
  ++counter;
  decoder.mem_controller->Load8(counter, HyperCPU::Registers::X7);
  counter = 0;
  
  HCPU_ASSERT_EXIT(decoder.FetchAndDecode(), ::testing::ExitedWithCode(1), "Invalid opcode!");
}

TEST_F(DECODER_TEST, SUB_INSTR_RM_R_B32) {
  decoder.mem_controller->Load16(counter, HyperCPU::SUB);
  counter += 2;
  decoder.mem_controller->Load8(counter, (HyperCPU::Mode::b32 << 4) | HyperCPU::OperandTypes::RM_R);
  ++counter;
  decoder.mem_controller->Load8(counter, HyperCPU::Registers::X3);
  ++counter;
  decoder.mem_controller->Load8(counter, HyperCPU::Registers::X7);
  counter = 0;
  
  HCPU_ASSERT_EXIT(decoder.FetchAndDecode(), ::testing::ExitedWithCode(1), "Invalid opcode!");
}

TEST_F(DECODER_TEST, SUB_INSTR_RM_R_B64) {
  decoder.mem_controller->Load16(counter, HyperCPU::SUB);
  counter += 2;
  decoder.mem_controller->Load8(counter, (HyperCPU::Mode::b64 << 4) | HyperCPU::OperandTypes::RM_R);
  ++counter;
  decoder.mem_controller->Load8(counter, HyperCPU::Registers::X3);
  ++counter;
  decoder.mem_controller->Load8(counter, HyperCPU::Registers::X7);
  counter = 0;
  
  HCPU_ASSERT_EXIT(decoder.FetchAndDecode(), ::testing::ExitedWithCode(1), "Invalid opcode!");
}

TEST_F(DECODER_TEST, SUB_INSTR_RM_M_B8) {
  decoder.mem_controller->Load16(counter, HyperCPU::SUB);
  counter += 2;
  decoder.mem_controller->Load8(counter, (HyperCPU::Mode::b8 << 4) | HyperCPU::OperandTypes::RM_M);
  ++counter;
  decoder.mem_controller->Load8(counter, HyperCPU::Registers::X3);
  ++counter;
  decoder.mem_controller->Load64(counter, MEM_PTR);
  counter = 0;
  
  HCPU_ASSERT_EXIT(decoder.FetchAndDecode(), ::testing::ExitedWithCode(1), "Invalid opcode!");
}

TEST_F(DECODER_TEST, SUB_INSTR_RM_M_B16) {
  decoder.mem_controller->Load16(counter, HyperCPU::SUB);
  counter += 2;
  decoder.mem_controller->Load8(counter, (HyperCPU::Mode::b16 << 4) | HyperCPU::OperandTypes::RM_M);
  ++counter;
  decoder.mem_controller->Load8(counter, HyperCPU::Registers::X3);
  ++counter;
  decoder.mem_controller->Load64(counter, MEM_PTR);
  counter = 0;
  
  HCPU_ASSERT_EXIT(decoder.FetchAndDecode(), ::testing::ExitedWithCode(1), "Invalid opcode!");
}

TEST_F(DECODER_TEST, SUB_INSTR_RM_M_B32) {
  decoder.mem_controller->Load16(counter, HyperCPU::SUB);
  counter += 2;
  decoder.mem_controller->Load8(counter, (HyperCPU::Mode::b32 << 4) | HyperCPU::OperandTypes::RM_M);
  ++counter;
  decoder.mem_controller->Load8(counter, HyperCPU::Registers::X3);
  ++counter;
  decoder.mem_controller->Load64(counter, MEM_PTR);
  counter = 0;
  
  HCPU_ASSERT_EXIT(decoder.FetchAndDecode(), ::testing::ExitedWithCode(1), "Invalid opcode!");
}

TEST_F(DECODER_TEST, SUB_INSTR_RM_M_B64) {
  decoder.mem_controller->Load16(counter, HyperCPU::SUB);
  counter += 2;
  decoder.mem_controller->Load8(counter, (HyperCPU::Mode::b64 << 4) | HyperCPU::OperandTypes::RM_M);
  ++counter;
  decoder.mem_controller->Load8(counter, HyperCPU::Registers::X3);
  ++counter;
  decoder.mem_controller->Load64(counter, MEM_PTR);
  counter = 0;
  
  HCPU_ASSERT_EXIT(decoder.FetchAndDecode(), ::testing::ExitedWithCode(1), "Invalid opcode!");
}

TEST_F(DECODER_TEST, SUB_INSTR_RM_IMM_B8) {
  decoder.mem_controller->Load16(counter, HyperCPU::SUB);
  counter += 2;
  decoder.mem_controller->Load8(counter, (HyperCPU::Mode::b8 << 4) | HyperCPU::OperandTypes::RM_IMM);
  ++counter;
  decoder.mem_controller->Load8(counter, HyperCPU::Registers::X3);
  ++counter;
  decoder.mem_controller->Load8(counter, 0x55);
  counter = 0;
  
  HCPU_ASSERT_EXIT(decoder.FetchAndDecode(), ::testing::ExitedWithCode(1), "Invalid opcode!");
}

TEST_F(DECODER_TEST, SUB_INSTR_RM_IMM_B16) {
  decoder.mem_controller->Load16(counter, HyperCPU::SUB);
  counter += 2;
  decoder.mem_controller->Load8(counter, (HyperCPU::Mode::b16 << 4) | HyperCPU::OperandTypes::RM_IMM);
  ++counter;
  decoder.mem_controller->Load8(counter, HyperCPU::Registers::X3);
  ++counter;
  decoder.mem_controller->Load16(counter, 0x5555);
  counter = 0;
  
  HCPU_ASSERT_EXIT(decoder.FetchAndDecode(), ::testing::ExitedWithCode(1), "Invalid opcode!");
}

TEST_F(DECODER_TEST, SUB_INSTR_RM_IMM_B32) {
  decoder.mem_controller->Load16(counter, HyperCPU::SUB);
  counter += 2;
  decoder.mem_controller->Load8(counter, (HyperCPU::Mode::b32 << 4) | HyperCPU::OperandTypes::RM_IMM);
  ++counter;
  decoder.mem_controller->Load8(counter, HyperCPU::Registers::X3);
  ++counter;
  decoder.mem_controller->Load32(counter, 0x55555555);
  counter = 0;
  
  HCPU_ASSERT_EXIT(decoder.FetchAndDecode(), ::testing::ExitedWithCode(1), "Invalid opcode!");
}

TEST_F(DECODER_TEST, SUB_INSTR_RM_IMM_B64) {
  decoder.mem_controller->Load16(counter, HyperCPU::SUB);
  counter += 2;
  decoder.mem_controller->Load8(counter, (HyperCPU::Mode::b64 << 4) | HyperCPU::OperandTypes::RM_IMM);
  ++counter;
  decoder.mem_controller->Load8(counter, HyperCPU::Registers::X3);
  ++counter;
  decoder.mem_controller->Load64(counter, 0x5555555555555555);
  counter = 0;
  
  HCPU_ASSERT_EXIT(decoder.FetchAndDecode(), ::testing::ExitedWithCode(1), "Invalid opcode!");
}

TEST_F(DECODER_TEST, SUB_INSTR_R) {
  decoder.mem_controller->Load16(counter, HyperCPU::SUB);
  counter += 2;
  decoder.mem_controller->Load8(counter, HyperCPU::OperandTypes::R);
  ++counter;
  decoder.mem_controller->Load8(counter, HyperCPU::Registers::X3);
  ++counter;
  decoder.mem_controller->Load8(counter, HyperCPU::Registers::X7);
  counter = 0;
  
  HCPU_ASSERT_EXIT(decoder.FetchAndDecode(), ::testing::ExitedWithCode(1), "Invalid opcode!");
}

TEST_F(DECODER_TEST, SUB_INSTR_M) {
  decoder.mem_controller->Load16(counter, HyperCPU::SUB);
  counter += 2;
  decoder.mem_controller->Load8(counter, HyperCPU::OperandTypes::M);
  ++counter;
  decoder.mem_controller->Load8(counter, HyperCPU::Registers::X3);
  ++counter;
  decoder.mem_controller->Load8(counter, HyperCPU::Registers::X7);
  counter = 0;
  
  HCPU_ASSERT_EXIT(decoder.FetchAndDecode(), ::testing::ExitedWithCode(1), "Invalid opcode!");
}

TEST_F(DECODER_TEST, SUB_INSTR_IMM) {
  decoder.mem_controller->Load16(counter, HyperCPU::SUB);
  counter += 2;
  decoder.mem_controller->Load8(counter, HyperCPU::OperandTypes::IMM);
  ++counter;
  decoder.mem_controller->Load8(counter, HyperCPU::Registers::X3);
  ++counter;
  decoder.mem_controller->Load8(counter, HyperCPU::Registers::X7);
  counter = 0;
  
  HCPU_ASSERT_EXIT(decoder.FetchAndDecode(), ::testing::ExitedWithCode(1), "Invalid opcode!");
}

TEST_F(DECODER_TEST, SUB_INSTR_NONE) {
  decoder.mem_controller->Load16(counter, HyperCPU::SUB);
  counter += 2;
  decoder.mem_controller->Load8(counter, HyperCPU::OperandTypes::NONE);
  ++counter;
  decoder.mem_controller->Load8(counter, HyperCPU::Registers::X3);
  ++counter;
  decoder.mem_controller->Load8(counter, HyperCPU::Registers::X7);
  counter = 0;
  
  HCPU_ASSERT_EXIT(decoder.FetchAndDecode(), ::testing::ExitedWithCode(1), "Invalid opcode!");
}