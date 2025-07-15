#include "tests/fixtures.hpp"

#ifdef __HCPU_DEBUG
#define HCPU_ASSERT_EXIT(statement, x, regex) ASSERT_DEATH(statement, regex)
#else
#define HCPU_ASSERT_EXIT(statement, x, regex) ASSERT_EXIT(statement, x, regex)
#endif

TEST_F(DECODER_TEST, CMP_INSTR_R) {
  decoder.mem_controller->Load(counter, HyperCPU::Opcode::CMP);
  counter += 2;
  decoder.mem_controller->Load(counter, HyperCPU::OperandTypes::R);
  ++counter;
  decoder.mem_controller->Load(counter, HyperCPU::Reg::X3);
  ++counter;
  decoder.mem_controller->Load(counter, HyperCPU::Reg::X7);
  counter = 0;

  HCPU_ASSERT_EXIT(decoder.FetchAndDecode(), ::testing::ExitedWithCode(1), "Invalid opcode!");
}

TEST_F(DECODER_TEST, CMP_INSTR_M) {
  decoder.mem_controller->Load(counter, HyperCPU::Opcode::CMP);
  counter += 2;
  decoder.mem_controller->Load(counter, HyperCPU::OperandTypes::M);
  ++counter;
  decoder.mem_controller->Load(counter, HyperCPU::Reg::X3);
  ++counter;
  decoder.mem_controller->Load(counter, HyperCPU::Reg::X7);
  counter = 0;

  HCPU_ASSERT_EXIT(decoder.FetchAndDecode(), ::testing::ExitedWithCode(1), "Invalid opcode!");
}

TEST_F(DECODER_TEST, CMP_INSTR_IMM) {
  decoder.mem_controller->Load(counter, HyperCPU::Opcode::CMP);
  counter += 2;
  decoder.mem_controller->Load(counter, HyperCPU::OperandTypes::IMM);
  ++counter;
  decoder.mem_controller->Load(counter, HyperCPU::Reg::X3);
  ++counter;
  decoder.mem_controller->Load(counter, HyperCPU::Reg::X7);
  counter = 0;

  HCPU_ASSERT_EXIT(decoder.FetchAndDecode(), ::testing::ExitedWithCode(1), "Invalid opcode!");
}

TEST_F(DECODER_TEST, CMP_INSTR_NONE) {
  decoder.mem_controller->Load(counter, HyperCPU::Opcode::CMP);
  counter += 2;
  decoder.mem_controller->Load(counter, HyperCPU::OperandTypes::NONE);
  ++counter;
  decoder.mem_controller->Load(counter, HyperCPU::Reg::X3);
  ++counter;
  decoder.mem_controller->Load(counter, HyperCPU::Reg::X7);
  counter = 0;

  HCPU_ASSERT_EXIT(decoder.FetchAndDecode(), ::testing::ExitedWithCode(1), "Invalid opcode!");
}
