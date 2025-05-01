#include <pch.hpp>

#include <cstring>

#include <fixtures.hpp>

TEST_F(DECODER_TEST, CMP_INSTR_R_IMM_B8) {
  decoder.mem_controller->Load16(counter, HyperCPU::Opcode::CMP);
  counter += 2;
  decoder.mem_controller->Load8(counter, (HyperCPU::Mode::b8 << 4) | HyperCPU::OperandTypes::R_IMM);
  ++counter;
  decoder.mem_controller->Load8(counter, HyperCPU::Registers::X3);
  ++counter;
  decoder.mem_controller->Load8(counter, 0x55);
  counter = 0;
  
  HyperCPU::Registers reg1;
  std::uint8_t data;
  HyperCPU::IInstruction instr = decoder.FetchAndDecode();

  ASSERT_EQ(instr.m_opcode, HyperCPU::Opcode::CMP);
  ASSERT_EQ(instr.m_opcode_mode, HyperCPU::Mode::b8);
  ASSERT_EQ(instr.m_op_types, HyperCPU::OperandTypes::R_IMM);

  memcpy(&reg1, &instr.m_op1, sizeof(HyperCPU::Registers));
  memcpy(&data, &instr.m_op2, sizeof(std::uint8_t));
  ASSERT_EQ(reg1, HyperCPU::Registers::X3);
  ASSERT_EQ(data, 0x55);
}

TEST_F(DECODER_TEST, CMP_INSTR_R_IMM_B16) {
  decoder.mem_controller->Load16(counter, HyperCPU::CMP);
  counter += 2;
  decoder.mem_controller->Load8(counter, (HyperCPU::Mode::b16 << 4) | HyperCPU::OperandTypes::R_IMM);
  ++counter;
  decoder.mem_controller->Load8(counter, HyperCPU::Registers::X3);
  ++counter;
  decoder.mem_controller->Load16(counter, 0x5555);
  counter = 0;
  
  HyperCPU::Registers reg1;
  std::uint16_t data;
  HyperCPU::IInstruction instr = decoder.FetchAndDecode();

  ASSERT_EQ(instr.m_opcode, HyperCPU::Opcode::CMP);
  ASSERT_EQ(instr.m_opcode_mode, HyperCPU::Mode::b16);
  ASSERT_EQ(instr.m_op_types, HyperCPU::OperandTypes::R_IMM);

  memcpy(&reg1, &instr.m_op1, sizeof(HyperCPU::Registers));
  memcpy(&data, &instr.m_op2, sizeof(std::uint16_t));
  ASSERT_EQ(reg1, HyperCPU::Registers::X3);
  ASSERT_EQ(data, 0x5555);
}

TEST_F(DECODER_TEST, CMP_INSTR_R_IMM_B32) {
  decoder.mem_controller->Load16(counter, HyperCPU::CMP);
  counter += 2;
  decoder.mem_controller->Load8(counter, (HyperCPU::Mode::b32 << 4) | HyperCPU::OperandTypes::R_IMM);
  ++counter;
  decoder.mem_controller->Load8(counter, HyperCPU::Registers::X3);
  ++counter;
  decoder.mem_controller->Load32(counter, 0x55555555);
  counter = 0;
  
  HyperCPU::Registers reg1;
  std::uint32_t data;
  HyperCPU::IInstruction instr = decoder.FetchAndDecode();

  ASSERT_EQ(instr.m_opcode, HyperCPU::Opcode::CMP);
  ASSERT_EQ(instr.m_opcode_mode, HyperCPU::Mode::b32);
  ASSERT_EQ(instr.m_op_types, HyperCPU::OperandTypes::R_IMM);

  memcpy(&reg1, &instr.m_op1, sizeof(HyperCPU::Registers));
  memcpy(&data, &instr.m_op2, sizeof(std::uint32_t));
  ASSERT_EQ(reg1, HyperCPU::Registers::X3);
  ASSERT_EQ(data, 0x55555555);
}

TEST_F(DECODER_TEST, CMP_INSTR_R_IMM_B64) {
  decoder.mem_controller->Load16(counter, HyperCPU::CMP);
  counter += 2;
  decoder.mem_controller->Load8(counter, (HyperCPU::Mode::b64 << 4) | HyperCPU::OperandTypes::R_IMM);
  ++counter;
  decoder.mem_controller->Load8(counter, HyperCPU::Registers::X3);
  ++counter;
  decoder.mem_controller->Load64(counter, 0x5555555555555555);
  counter = 0;
  
  HyperCPU::Registers reg1;
  std::uint64_t data;
  HyperCPU::IInstruction instr = decoder.FetchAndDecode();

  ASSERT_EQ(instr.m_opcode, HyperCPU::Opcode::CMP);
  ASSERT_EQ(instr.m_opcode_mode, HyperCPU::Mode::b64);
  ASSERT_EQ(instr.m_op_types, HyperCPU::OperandTypes::R_IMM);

  memcpy(&reg1, &instr.m_op1, sizeof(HyperCPU::Registers));
  memcpy(&data, &instr.m_op2, sizeof(std::uint64_t));
  ASSERT_EQ(reg1, HyperCPU::Registers::X3);
  ASSERT_EQ(data, 0x5555555555555555);
}
