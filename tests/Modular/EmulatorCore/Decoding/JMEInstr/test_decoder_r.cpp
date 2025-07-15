#include "tests/fixtures.hpp"

TEST_F(DECODER_TEST, JME_INSTR_R) {
  decoder.mem_controller->Load(counter, HyperCPU::Opcode::JME);
  counter += 2;
  decoder.mem_controller->Load(counter, EncodeTestFlags(HyperCPU::Mode::b64, HyperCPU::OperandTypes::R));
  ++counter;
  decoder.mem_controller->Load(counter, HyperCPU::Reg::X3);
  ++counter;
  decoder.mem_controller->Load(counter, HyperCPU::Reg::X7);
  counter = 0;

  HyperCPU::IInstruction instr = decoder.FetchAndDecode();

  ASSERT_EQ(instr.m_opcode, HyperCPU::Opcode::JME);
  ASSERT_EQ(instr.m_opcode_mode, HyperCPU::Mode::b64);
  ASSERT_EQ(instr.m_op_types, HyperCPU::OperandTypes::R);
}
