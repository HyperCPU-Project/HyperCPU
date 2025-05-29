#include "tests/fixtures.hpp"

TEST_F(DECODER_TEST, WRITE_INSTR_R_R_B8) {
  decoder.mem_controller->Load16(counter, HyperCPU::Opcode::WRITE);
  counter += 2;
  decoder.mem_controller->Load8(counter, EncodeTestFlags(HyperCPU::Mode::b8,  HyperCPU::Mode::b8, HyperCPU::OperandTypes::R_R));
  ++counter;
  decoder.mem_controller->Load8(counter, HyperCPU::Reg::X3);
  ++counter;
  decoder.mem_controller->Load8(counter, HyperCPU::Reg::X1);
  counter = 0;

  HyperCPU::Reg reg1;
  HyperCPU::Reg reg2;
  HyperCPU::IInstruction instr = decoder.FetchAndDecode();

  ASSERT_EQ(instr.m_opcode, HyperCPU::Opcode::WRITE);
  ASSERT_EQ(instr.m_opcode_mode, HyperCPU::Mode::b8);
  ASSERT_EQ(instr.m_op_types, HyperCPU::OperandTypes::R_R);

  memcpy(&reg1, &instr.m_op1, sizeof(HyperCPU::Reg));
  memcpy(&reg2, &instr.m_op2, sizeof(HyperCPU::Reg));
  ASSERT_EQ(reg1, HyperCPU::Reg::X3);
  ASSERT_EQ(reg2, HyperCPU::Reg::X1);
}
