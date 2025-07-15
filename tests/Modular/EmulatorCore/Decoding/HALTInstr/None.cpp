#include "tests/fixtures.hpp"

TEST_F(DECODER_TEST, HALT_INSTR_NONE) {
  decoder.mem_controller->Load(counter, HyperCPU::Opcode::HALT);
  counter += 2;
  decoder.mem_controller->Load(counter, HyperCPU::OperandTypes::NONE);
  counter = 0;

  HyperCPU::IInstruction instr = decoder.FetchAndDecode();

  ASSERT_EQ(instr.m_opcode, HyperCPU::Opcode::HALT);
  ASSERT_EQ(instr.m_op_types, HyperCPU::OperandTypes::NONE);
}
