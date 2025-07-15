#include "tests/fixtures.hpp"

#ifdef __HCPU_DEBUG
#define HCPU_ASSERT_EXIT(statement, x, regex) ASSERT_DEATH(statement, regex)
#else
#define HCPU_ASSERT_EXIT(statement, x, regex) ASSERT_EXIT(statement, x, regex)
#endif

TEST_F(DECODER_TEST, ADD_INSTR_M_R_B8) {
  decoder.mem_controller->Load(counter, HyperCPU::Opcode::ADD);
  counter += 2;
  decoder.mem_controller->Load(counter, EncodeTestFlags(HyperCPU::Mode::b8, HyperCPU::OperandTypes::M_R));
  ++counter;
  decoder.mem_controller->Load(counter, MEM_PTR);
  counter += 8;
  decoder.mem_controller->Load(counter, HyperCPU::Reg::X7);
  counter = 0;

  HCPU_ASSERT_EXIT(decoder.FetchAndDecode(), ::testing::ExitedWithCode(1), "Invalid opcode!");
}

TEST_F(DECODER_TEST, ADD_INSTR_M_R_B16) {
  decoder.mem_controller->Load(counter, HyperCPU::Opcode::ADD);
  counter += 2;
  decoder.mem_controller->Load(counter, EncodeTestFlags(HyperCPU::Mode::b16, HyperCPU::OperandTypes::M_R));
  ++counter;
  decoder.mem_controller->Load(counter, MEM_PTR);
  counter += 8;
  decoder.mem_controller->Load(counter, HyperCPU::Reg::X7);
  counter = 0;

  HCPU_ASSERT_EXIT(decoder.FetchAndDecode(), ::testing::ExitedWithCode(1), "Invalid opcode!");
}

TEST_F(DECODER_TEST, ADD_INSTR_M_R_B32) {
  decoder.mem_controller->Load(counter, HyperCPU::Opcode::ADD);
  counter += 2;
  decoder.mem_controller->Load(counter, EncodeTestFlags(HyperCPU::Mode::b32, HyperCPU::OperandTypes::M_R));
  ++counter;
  decoder.mem_controller->Load(counter, MEM_PTR);
  counter += 8;
  decoder.mem_controller->Load(counter, HyperCPU::Reg::X7);
  counter = 0;

  HCPU_ASSERT_EXIT(decoder.FetchAndDecode(), ::testing::ExitedWithCode(1), "Invalid opcode!");
}

TEST_F(DECODER_TEST, ADD_INSTR_M_R_B64) {
  decoder.mem_controller->Load(counter, HyperCPU::Opcode::ADD);
  counter += 2;
  decoder.mem_controller->Load(counter, EncodeTestFlags(HyperCPU::Mode::b64, HyperCPU::OperandTypes::M_R));
  ++counter;
  decoder.mem_controller->Load(counter, MEM_PTR);
  counter += 8;
  decoder.mem_controller->Load(counter, HyperCPU::Reg::X7);
  counter = 0;

  HCPU_ASSERT_EXIT(decoder.FetchAndDecode(), ::testing::ExitedWithCode(1), "Invalid opcode!");
}

TEST_F(DECODER_TEST, ADD_INSTR_RM_R_B8) {
  decoder.mem_controller->Load(counter, HyperCPU::Opcode::ADD);
  counter += 2;
  decoder.mem_controller->Load(counter, EncodeTestFlags(HyperCPU::Mode::b8,  HyperCPU::Mode::b8, HyperCPU::OperandTypes::RM_R)));
  ++counter;
  decoder.mem_controller->Load(counter, HyperCPU::Reg::X3);
  ++counter;
  decoder.mem_controller->Load(counter, HyperCPU::Reg::X7);
  counter = 0;

  HCPU_ASSERT_EXIT(decoder.FetchAndDecode(), ::testing::ExitedWithCode(1), "Invalid opcode!");
}

TEST_F(DECODER_TEST, ADD_INSTR_RM_R_B16) {
  decoder.mem_controller->Load(counter, HyperCPU::Opcode::ADD);
  counter += 2;
  decoder.mem_controller->Load(counter, EncodeTestFlags(HyperCPU::Mode::b16,  HyperCPU::Mode::b16, HyperCPU::OperandTypes::RM_R)));
  ++counter;
  decoder.mem_controller->Load(counter, HyperCPU::Reg::X3);
  ++counter;
  decoder.mem_controller->Load(counter, HyperCPU::Reg::X7);
  counter = 0;

  HCPU_ASSERT_EXIT(decoder.FetchAndDecode(), ::testing::ExitedWithCode(1), "Invalid opcode!");
}

TEST_F(DECODER_TEST, ADD_INSTR_RM_R_B32) {
  decoder.mem_controller->Load(counter, HyperCPU::Opcode::ADD);
  counter += 2;
  decoder.mem_controller->Load(counter, EncodeTestFlags(HyperCPU::Mode::b32,  HyperCPU::Mode::b32, HyperCPU::OperandTypes::RM_R)));
  ++counter;
  decoder.mem_controller->Load(counter, HyperCPU::Reg::X3);
  ++counter;
  decoder.mem_controller->Load(counter, HyperCPU::Reg::X7);
  counter = 0;

  HCPU_ASSERT_EXIT(decoder.FetchAndDecode(), ::testing::ExitedWithCode(1), "Invalid opcode!");
}

TEST_F(DECODER_TEST, ADD_INSTR_RM_R_B64) {
  decoder.mem_controller->Load(counter, HyperCPU::Opcode::ADD);
  counter += 2;
  decoder.mem_controller->Load(counter, EncodeTestFlags(HyperCPU::Mode::b64,  HyperCPU::Mode::b64, HyperCPU::OperandTypes::RM_R)));
  ++counter;
  decoder.mem_controller->Load(counter, HyperCPU::Reg::X3);
  ++counter;
  decoder.mem_controller->Load(counter, HyperCPU::Reg::X7);
  counter = 0;

  HCPU_ASSERT_EXIT(decoder.FetchAndDecode(), ::testing::ExitedWithCode(1), "Invalid opcode!");
}

TEST_F(DECODER_TEST, ADD_INSTR_RM_M_B8) {
  decoder.mem_controller->Load(counter, HyperCPU::Opcode::ADD);
  counter += 2;
  decoder.mem_controller->Load(counter, EncodeTestFlags(HyperCPU::Mode::b8,  HyperCPU::Mode::b8, HyperCPU::OperandTypes::RM_M)));
  ++counter;
  decoder.mem_controller->Load(counter, HyperCPU::Reg::X3);
  ++counter;
  decoder.mem_controller->Load(counter, MEM_PTR);
  counter = 0;

  HCPU_ASSERT_EXIT(decoder.FetchAndDecode(), ::testing::ExitedWithCode(1), "Invalid opcode!");
}

TEST_F(DECODER_TEST, ADD_INSTR_RM_M_B16) {
  decoder.mem_controller->Load(counter, HyperCPU::Opcode::ADD);
  counter += 2;
  decoder.mem_controller->Load(counter, EncodeTestFlags(HyperCPU::Mode::b16,  HyperCPU::Mode::b16, HyperCPU::OperandTypes::RM_M)));
  ++counter;
  decoder.mem_controller->Load(counter, HyperCPU::Reg::X3);
  ++counter;
  decoder.mem_controller->Load(counter, MEM_PTR);
  counter = 0;

  HCPU_ASSERT_EXIT(decoder.FetchAndDecode(), ::testing::ExitedWithCode(1), "Invalid opcode!");
}

TEST_F(DECODER_TEST, ADD_INSTR_RM_M_B32) {
  decoder.mem_controller->Load(counter, HyperCPU::Opcode::ADD);
  counter += 2;
  decoder.mem_controller->Load(counter, EncodeTestFlags(HyperCPU::Mode::b32,  HyperCPU::Mode::b32, HyperCPU::OperandTypes::RM_M)));
  ++counter;
  decoder.mem_controller->Load(counter, HyperCPU::Reg::X3);
  ++counter;
  decoder.mem_controller->Load(counter, MEM_PTR);
  counter = 0;

  HCPU_ASSERT_EXIT(decoder.FetchAndDecode(), ::testing::ExitedWithCode(1), "Invalid opcode!");
}

TEST_F(DECODER_TEST, ADD_INSTR_RM_M_B64) {
  decoder.mem_controller->Load(counter, HyperCPU::Opcode::ADD);
  counter += 2;
  decoder.mem_controller->Load(counter, EncodeTestFlags(HyperCPU::Mode::b64,  HyperCPU::Mode::b64, HyperCPU::OperandTypes::RM_M)));
  ++counter;
  decoder.mem_controller->Load(counter, HyperCPU::Reg::X3);
  ++counter;
  decoder.mem_controller->Load(counter, MEM_PTR);
  counter = 0;

  HCPU_ASSERT_EXIT(decoder.FetchAndDecode(), ::testing::ExitedWithCode(1), "Invalid opcode!");
}

TEST_F(DECODER_TEST, ADD_INSTR_RM_IMM_B8) {
  decoder.mem_controller->Load(counter, HyperCPU::Opcode::ADD);
  counter += 2;
  decoder.mem_controller->Load(counter, EncodeTestFlags(HyperCPU::Mode::b8,  HyperCPU::Mode::b8, HyperCPU::OperandTypes::RM_IMM)));
  ++counter;
  decoder.mem_controller->Load(counter, HyperCPU::Reg::X3);
  ++counter;
  decoder.mem_controller->Load(counter, 0x55);
  counter = 0;

  HCPU_ASSERT_EXIT(decoder.FetchAndDecode(), ::testing::ExitedWithCode(1), "Invalid opcode!");
}

TEST_F(DECODER_TEST, ADD_INSTR_RM_IMM_B16) {
  decoder.mem_controller->Load(counter, HyperCPU::Opcode::ADD);
  counter += 2;
  decoder.mem_controller->Load(counter, EncodeTestFlags(HyperCPU::Mode::b16,  HyperCPU::Mode::b16, HyperCPU::OperandTypes::RM_IMM)));
  ++counter;
  decoder.mem_controller->Load(counter, HyperCPU::Reg::X3);
  ++counter;
  decoder.mem_controller->Load(counter, 0x5555);
  counter = 0;

  HCPU_ASSERT_EXIT(decoder.FetchAndDecode(), ::testing::ExitedWithCode(1), "Invalid opcode!");
}

TEST_F(DECODER_TEST, ADD_INSTR_RM_IMM_B32) {
  decoder.mem_controller->Load(counter, HyperCPU::Opcode::ADD);
  counter += 2;
  decoder.mem_controller->Load(counter, EncodeTestFlags(HyperCPU::Mode::b32,  HyperCPU::Mode::b32, HyperCPU::OperandTypes::RM_IMM)));
  ++counter;
  decoder.mem_controller->Load(counter, HyperCPU::Reg::X3);
  ++counter;
  decoder.mem_controller->Load(counter, 0x55555555);
  counter = 0;

  HCPU_ASSERT_EXIT(decoder.FetchAndDecode(), ::testing::ExitedWithCode(1), "Invalid opcode!");
}

TEST_F(DECODER_TEST, ADD_INSTR_RM_IMM_B64) {
  decoder.mem_controller->Load(counter, HyperCPU::Opcode::ADD);
  counter += 2;
  decoder.mem_controller->Load(counter, EncodeTestFlags(HyperCPU::Mode::b64,  HyperCPU::Mode::b64, HyperCPU::OperandTypes::RM_IMM)));
  ++counter;
  decoder.mem_controller->Load(counter, HyperCPU::Reg::X3);
  ++counter;
  decoder.mem_controller->Load(counter, 0x5555555555555555);
  counter = 0;

  HCPU_ASSERT_EXIT(decoder.FetchAndDecode(), ::testing::ExitedWithCode(1), "Invalid opcode!");
}

TEST_F(DECODER_TEST, ADD_INSTR_R) {
  decoder.mem_controller->Load(counter, HyperCPU::Opcode::ADD);
  counter += 2;
  decoder.mem_controller->Load(counter, HyperCPU::OperandTypes::R);
  ++counter;
  decoder.mem_controller->Load(counter, HyperCPU::Reg::X3);
  ++counter;
  decoder.mem_controller->Load(counter, HyperCPU::Reg::X7);
  counter = 0;

  HCPU_ASSERT_EXIT(decoder.FetchAndDecode(), ::testing::ExitedWithCode(1), "Invalid opcode!");
}

TEST_F(DECODER_TEST, ADD_INSTR_M) {
  decoder.mem_controller->Load(counter, HyperCPU::Opcode::ADD);
  counter += 2;
  decoder.mem_controller->Load(counter, HyperCPU::OperandTypes::M);
  ++counter;
  decoder.mem_controller->Load(counter, HyperCPU::Reg::X3);
  ++counter;
  decoder.mem_controller->Load(counter, HyperCPU::Reg::X7);
  counter = 0;

  HCPU_ASSERT_EXIT(decoder.FetchAndDecode(), ::testing::ExitedWithCode(1), "Invalid opcode!");
}

TEST_F(DECODER_TEST, ADD_INSTR_IMM) {
  decoder.mem_controller->Load(counter, HyperCPU::Opcode::ADD);
  counter += 2;
  decoder.mem_controller->Load(counter, HyperCPU::OperandTypes::IMM);
  ++counter;
  decoder.mem_controller->Load(counter, HyperCPU::Reg::X3);
  ++counter;
  decoder.mem_controller->Load(counter, HyperCPU::Reg::X7);
  counter = 0;

  HCPU_ASSERT_EXIT(decoder.FetchAndDecode(), ::testing::ExitedWithCode(1), "Invalid opcode!");
}

TEST_F(DECODER_TEST, ADD_INSTR_NONE) {
  decoder.mem_controller->Load(counter, HyperCPU::Opcode::ADD);
  counter += 2;
  decoder.mem_controller->Load(counter, HyperCPU::OperandTypes::NONE);
  ++counter;
  decoder.mem_controller->Load(counter, HyperCPU::Reg::X3);
  ++counter;
  decoder.mem_controller->Load(counter, HyperCPU::Reg::X7);
  counter = 0;

  HCPU_ASSERT_EXIT(decoder.FetchAndDecode(), ::testing::ExitedWithCode(1), "Invalid opcode!");
}
