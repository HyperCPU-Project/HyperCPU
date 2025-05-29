#include "tests/fixtures.hpp"

TEST_F(DECODER_TEST, SHFL_INSTR_R_R_B8) {
  decoder.mem_controller->Load16(counter, HyperCPU::Opcode::SHFL);
  counter += 3;
  decoder.mem_controller->Load8(counter, HyperCPU::Reg::X3);
  ++counter;
  decoder.mem_controller->Load8(counter, HyperCPU::Reg::X7);
  counter = 0;

  HyperCPU::Reg reg1, reg2;
  HyperCPU::IInstruction instr = decoder.FetchAndDecode();

  ASSERT_EQ(instr.m_opcode, HyperCPU::Opcode::SHFL);
  ASSERT_EQ(instr.m_opcode_mode, HyperCPU::Mode::b8);
  ASSERT_EQ(instr.m_op_types, HyperCPU::OperandTypes::R_R);

  memcpy(&reg1, &instr.m_op1, sizeof(HyperCPU::Reg));
  memcpy(&reg2, &instr.m_op2, sizeof(HyperCPU::Reg));
  ASSERT_EQ(reg1, HyperCPU::Reg::X3);
  ASSERT_EQ(reg2, HyperCPU::Reg::X7);
}

TEST_F(DECODER_TEST, SHFL_INSTR_R_R_B16) {
  decoder.mem_controller->Load16(counter, HyperCPU::Opcode::SHFL);
  counter += 2;
  decoder.mem_controller->Load8(counter, EncodeTestFlags(HyperCPU::Mode::b16,  HyperCPU::Mode::b16, HyperCPU::OperandTypes::R_R));
  ++counter;
  decoder.mem_controller->Load8(counter, HyperCPU::Reg::X3);
  ++counter;
  decoder.mem_controller->Load8(counter, HyperCPU::Reg::X7);
  counter = 0;

  HyperCPU::Reg reg1, reg2;
  HyperCPU::IInstruction instr = decoder.FetchAndDecode();

  ASSERT_EQ(instr.m_opcode, HyperCPU::Opcode::SHFL);
  ASSERT_EQ(instr.m_opcode_mode, HyperCPU::Mode::b16);
  ASSERT_EQ(instr.m_op_types, HyperCPU::OperandTypes::R_R);

  memcpy(&reg1, &instr.m_op1, sizeof(HyperCPU::Reg));
  memcpy(&reg2, &instr.m_op2, sizeof(HyperCPU::Reg));
  ASSERT_EQ(reg1, HyperCPU::Reg::X3);
  ASSERT_EQ(reg2, HyperCPU::Reg::X7);
}

TEST_F(DECODER_TEST, SHFL_INSTR_R_R_B32) {
  decoder.mem_controller->Load16(counter, HyperCPU::Opcode::SHFL);
  counter += 2;
  decoder.mem_controller->Load8(counter, EncodeTestFlags(HyperCPU::Mode::b32,  HyperCPU::Mode::b32, HyperCPU::OperandTypes::R_R));
  ++counter;
  decoder.mem_controller->Load8(counter, HyperCPU::Reg::X3);
  ++counter;
  decoder.mem_controller->Load8(counter, HyperCPU::Reg::X7);
  counter = 0;

  HyperCPU::Reg reg1, reg2;
  HyperCPU::IInstruction instr = decoder.FetchAndDecode();

  ASSERT_EQ(instr.m_opcode, HyperCPU::Opcode::SHFL);
  ASSERT_EQ(instr.m_opcode_mode, HyperCPU::Mode::b32);
  ASSERT_EQ(instr.m_op_types, HyperCPU::OperandTypes::R_R);

  memcpy(&reg1, &instr.m_op1, sizeof(HyperCPU::Reg));
  memcpy(&reg2, &instr.m_op2, sizeof(HyperCPU::Reg));
  ASSERT_EQ(reg1, HyperCPU::Reg::X3);
  ASSERT_EQ(reg2, HyperCPU::Reg::X7);
}

TEST_F(DECODER_TEST, SHFL_INSTR_R_R_B64) {
  decoder.mem_controller->Load16(counter, HyperCPU::Opcode::SHFL);
  counter += 2;
  decoder.mem_controller->Load8(counter, EncodeTestFlags(HyperCPU::Mode::b64,  HyperCPU::Mode::b64, HyperCPU::OperandTypes::R_R));
  ++counter;
  decoder.mem_controller->Load8(counter, HyperCPU::Reg::X3);
  ++counter;
  decoder.mem_controller->Load8(counter, HyperCPU::Reg::X7);
  counter = 0;

  HyperCPU::Reg reg1, reg2;
  HyperCPU::IInstruction instr = decoder.FetchAndDecode();

  ASSERT_EQ(instr.m_opcode, HyperCPU::Opcode::SHFL);
  ASSERT_EQ(instr.m_opcode_mode, HyperCPU::Mode::b64);
  ASSERT_EQ(instr.m_op_types, HyperCPU::OperandTypes::R_R);

  memcpy(&reg1, &instr.m_op1, sizeof(HyperCPU::Reg));
  memcpy(&reg2, &instr.m_op2, sizeof(HyperCPU::Reg));
  ASSERT_EQ(reg1, HyperCPU::Reg::X3);
  ASSERT_EQ(reg2, HyperCPU::Reg::X7);
}
