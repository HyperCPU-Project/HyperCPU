#include "tests/fixtures.hpp"

TEST_F(DECODER_TEST, CUDF_INSTR_NONE) {
  decoder.mem_controller->Load16(counter, HyperCPU::Opcode::CUDF);
  counter += 2;
  decoder.mem_controller->Load8(counter, HyperCPU::OperandTypes::NONE);
  counter = 0;

  HyperCPU::IInstruction instr = decoder.FetchAndDecode();

  ASSERT_EQ(instr.m_opcode, HyperCPU::Opcode::CUDF);
  ASSERT_EQ(instr.m_op_types, HyperCPU::OperandTypes::NONE);
}
