#include <pch.hpp>

#include <cstring>

#include <fixtures.hpp>

TEST_F(DECODER_TEST, CMP_INSTR_R_RM_B8) {
  decoder.mem_controller->Load16(counter, HyperCPU::CMP);
  counter += 2;
  decoder.mem_controller->Load8(counter, (HyperCPU::Mode::b8 << 4) | HyperCPU::OperandTypes::R_RM);
  ++counter;
  decoder.mem_controller->Load8(counter, HyperCPU::Registers::X3);
  ++counter;
  decoder.mem_controller->Load8(counter, HyperCPU::Registers::X7);
  counter = 0;
  
  HyperCPU::Registers reg1, reg2;
  HyperCPU::IInstruction instr = decoder.FetchAndDecode();

  ASSERT_EQ(instr.m_opcode, HyperCPU::Opcode::CMP);
  ASSERT_EQ(instr.m_opcode_mode, HyperCPU::Mode::b8);
  ASSERT_EQ(instr.m_op_types, HyperCPU::OperandTypes::R_RM);

  memcpy(&reg1, &instr.m_op1, sizeof(HyperCPU::Registers));
  memcpy(&reg2, &instr.m_op2, sizeof(HyperCPU::Registers));
  ASSERT_EQ(reg1, HyperCPU::Registers::X3);
  ASSERT_EQ(reg2, HyperCPU::Registers::X7);
}

TEST_F(DECODER_TEST, CMP_INSTR_R_RM_B16) {
  decoder.mem_controller->Load16(counter, HyperCPU::CMP);
  counter += 2;
  decoder.mem_controller->Load8(counter, (HyperCPU::Mode::b16 << 4) | HyperCPU::OperandTypes::R_RM);
  ++counter;
  decoder.mem_controller->Load8(counter, HyperCPU::Registers::X3);
  ++counter;
  decoder.mem_controller->Load8(counter, HyperCPU::Registers::X7);
  counter = 0;
  
  HyperCPU::Registers reg1, reg2;
  HyperCPU::IInstruction instr = decoder.FetchAndDecode();

  ASSERT_EQ(instr.m_opcode, HyperCPU::Opcode::CMP);
  ASSERT_EQ(instr.m_opcode_mode, HyperCPU::Mode::b16);
  ASSERT_EQ(instr.m_op_types, HyperCPU::OperandTypes::R_RM);

  memcpy(&reg1, &instr.m_op1, sizeof(HyperCPU::Registers));
  memcpy(&reg2, &instr.m_op2, sizeof(HyperCPU::Registers));
  ASSERT_EQ(reg1, HyperCPU::Registers::X3);
  ASSERT_EQ(reg2, HyperCPU::Registers::X7);
}

TEST_F(DECODER_TEST, CMP_INSTR_R_RM_B32) {
  decoder.mem_controller->Load16(counter, HyperCPU::CMP);
  counter += 2;
  decoder.mem_controller->Load8(counter, (HyperCPU::Mode::b32 << 4) | HyperCPU::OperandTypes::R_RM);
  ++counter;
  decoder.mem_controller->Load8(counter, HyperCPU::Registers::X3);
  ++counter;
  decoder.mem_controller->Load8(counter, HyperCPU::Registers::X7);
  counter = 0;
  
  HyperCPU::Registers reg1, reg2;
  HyperCPU::IInstruction instr = decoder.FetchAndDecode();

  ASSERT_EQ(instr.m_opcode, HyperCPU::Opcode::CMP);
  ASSERT_EQ(instr.m_opcode_mode, HyperCPU::Mode::b32);
  ASSERT_EQ(instr.m_op_types, HyperCPU::OperandTypes::R_RM);

  memcpy(&reg1, &instr.m_op1, sizeof(HyperCPU::Registers));
  memcpy(&reg2, &instr.m_op2, sizeof(HyperCPU::Registers));
  ASSERT_EQ(reg1, HyperCPU::Registers::X3);
  ASSERT_EQ(reg2, HyperCPU::Registers::X7);
}

TEST_F(DECODER_TEST, CMP_INSTR_R_RM_B64) {
  decoder.mem_controller->Load16(counter, HyperCPU::CMP);
  counter += 2;
  decoder.mem_controller->Load8(counter, (HyperCPU::Mode::b64 << 4) | HyperCPU::OperandTypes::R_RM);
  ++counter;
  decoder.mem_controller->Load8(counter, HyperCPU::Registers::X3);
  ++counter;
  decoder.mem_controller->Load8(counter, HyperCPU::Registers::X7);
  counter = 0;
  
  HyperCPU::Registers reg1, reg2;
  HyperCPU::IInstruction instr = decoder.FetchAndDecode();

  ASSERT_EQ(instr.m_opcode, HyperCPU::Opcode::CMP);
  ASSERT_EQ(instr.m_opcode_mode, HyperCPU::Mode::b64);
  ASSERT_EQ(instr.m_op_types, HyperCPU::OperandTypes::R_RM);

  memcpy(&reg1, &instr.m_op1, sizeof(HyperCPU::Registers));
  memcpy(&reg2, &instr.m_op2, sizeof(HyperCPU::Registers));
  ASSERT_EQ(reg1, HyperCPU::Registers::X3);
  ASSERT_EQ(reg2, HyperCPU::Registers::X7);
}