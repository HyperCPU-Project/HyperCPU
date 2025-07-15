#include "tests/fixtures.hpp"

TEST_F(DECODER_TEST, ADDR_ADDITION_DISABLED) {
  decoder.mem_controller->Load(counter, HyperCPU::Opcode::MOV);
  counter += 2;
  decoder.mem_controller->Load(counter, EncodeTestFlags(HyperCPU::Mode::b8,  HyperCPU::Mode::b8, HyperCPU::OperandTypes::RM_IMM)));
  ++counter;
  decoder.mem_controller->Load(counter, HyperCPU::Reg::X3);
  ++counter;
  decoder.mem_controller->Load(counter, 0x55);
  counter = 0;

  HyperCPU::Reg reg1;
  std::uint8_t data;
  HyperCPU::IInstruction instr = decoder.FetchAndDecode();

  ASSERT_EQ(instr.m_opcode, HyperCPU::Opcode::MOV);
  ASSERT_EQ(instr.m_opcode_mode, HyperCPU::Mode::b8);
  ASSERT_EQ(instr.m_op_types, HyperCPU::OperandTypes::RM_IMM);
  ASSERT_EQ(instr.addr_extension_status, HyperCPU::AddrExtensionStatus::Disabled);

  memcpy(&reg1, &instr.m_op1, sizeof(HyperCPU::Reg));
  memcpy(&data, &instr.m_op2, sizeof(std::uint8_t));
  ASSERT_EQ(reg1, HyperCPU::Reg::X3);
  ASSERT_EQ(data, 0x55);
}

TEST_F(DECODER_TEST, ADDR_ADDITION_OP1) {
  decoder.mem_controller->Load(counter, HyperCPU::Opcode::MOV);
  counter += 2;
  decoder.mem_controller->Load(counter, (0b10 << 6) | EncodeTestFlags(HyperCPU::Mode::b8,  HyperCPU::Mode::b8, HyperCPU::OperandTypes::RM_IMM)));
  ++counter;
  decoder.mem_controller->Load(counter, 16);
  ++counter;
  decoder.mem_controller->Load(counter, HyperCPU::Reg::X3);
  ++counter;
  decoder.mem_controller->Load(counter, 0x55);
  counter = 0;

  HyperCPU::Reg reg1;
  std::uint8_t data;
  HyperCPU::IInstruction instr = decoder.FetchAndDecode();

  ASSERT_EQ(instr.m_opcode, HyperCPU::Opcode::MOV);
  ASSERT_EQ(instr.m_opcode_mode, HyperCPU::Mode::b8);
  ASSERT_EQ(instr.m_op_types, HyperCPU::OperandTypes::RM_IMM);
  ASSERT_EQ(instr.addr_extension_status, HyperCPU::AddrExtensionStatus::EnabledOp1);
  ASSERT_EQ(instr.extension, 16);

  memcpy(&reg1, &instr.m_op1, sizeof(HyperCPU::Reg));
  memcpy(&data, &instr.m_op2, sizeof(std::uint8_t));
  ASSERT_EQ(reg1, HyperCPU::Reg::X3);
  ASSERT_EQ(data, 0x55);
}

TEST_F(DECODER_TEST, ADDR_ADDITION_OP2) {
  decoder.mem_controller->Load(counter, HyperCPU::Opcode::MOV);
  counter += 2;
  decoder.mem_controller->Load(counter, (0b11 << 6) | EncodeTestFlags(HyperCPU::Mode::b8,  HyperCPU::Mode::b8, HyperCPU::OperandTypes::R_RM));
  ++counter;
  decoder.mem_controller->Load(counter, 16);
  ++counter;
  decoder.mem_controller->Load(counter, HyperCPU::Reg::X3);
  ++counter;
  decoder.mem_controller->Load(counter, HyperCPU::Reg::X7);
  counter = 0;

  HyperCPU::Reg reg1, reg2;
  HyperCPU::IInstruction instr = decoder.FetchAndDecode();

  ASSERT_EQ(instr.m_opcode, HyperCPU::Opcode::MOV);
  ASSERT_EQ(instr.m_opcode_mode, HyperCPU::Mode::b8);
  ASSERT_EQ(instr.m_op_types, HyperCPU::OperandTypes::R_RM);
  ASSERT_EQ(instr.addr_extension_status, HyperCPU::AddrExtensionStatus::EnabledOp2);
  ASSERT_EQ(instr.extension, 16);

  memcpy(&reg1, &instr.m_op1, sizeof(HyperCPU::Reg));
  memcpy(&reg2, &instr.m_op2, sizeof(HyperCPU::Reg));
  ASSERT_EQ(reg1, HyperCPU::Reg::X3);
  ASSERT_EQ(reg2, HyperCPU::Reg::X7);
}
