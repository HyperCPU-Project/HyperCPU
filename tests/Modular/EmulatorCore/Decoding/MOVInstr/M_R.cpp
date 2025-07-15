#include "tests/fixtures.hpp"

TEST_F(DECODER_TEST, MOV_INSTR_M_R_B8) {
  decoder.mem_controller->Load(counter, HyperCPU::Opcode::MOV);
  counter += 2;
  decoder.mem_controller->Load(counter, EncodeTestFlags(HyperCPU::Mode::b8, HyperCPU::OperandTypes::M_R));
  ++counter;
  decoder.mem_controller->Load(counter, MEM_PTR);
  counter += 8;
  decoder.mem_controller->Load(counter, HyperCPU::Reg::X7);
  counter = 0;

  HyperCPU::Reg reg2;
  std::size_t mem_ptr;
  HyperCPU::IInstruction instr = decoder.FetchAndDecode();

  ASSERT_EQ(instr.m_opcode, HyperCPU::Opcode::MOV);
  ASSERT_EQ(instr.m_opcode_mode, HyperCPU::Mode::b8);
  ASSERT_EQ(instr.m_op_types, HyperCPU::OperandTypes::M_R);

  memcpy(&mem_ptr, &instr.m_op1, sizeof(std::size_t));
  memcpy(&reg2, &instr.m_op2, sizeof(HyperCPU::Reg));
  ASSERT_EQ(mem_ptr, MEM_PTR);
  ASSERT_EQ(reg2, HyperCPU::Reg::X7);
}

TEST_F(DECODER_TEST, MOV_INSTR_M_R_B16) {
  decoder.mem_controller->Load(counter, HyperCPU::Opcode::MOV);
  counter += 2;
  decoder.mem_controller->Load(counter, EncodeTestFlags(HyperCPU::Mode::b16, HyperCPU::OperandTypes::M_R));
  ++counter;
  decoder.mem_controller->Load(counter, MEM_PTR);
  counter += 8;
  decoder.mem_controller->Load(counter, HyperCPU::Reg::X7);
  counter = 0;

  HyperCPU::Reg reg2;
  std::size_t mem_ptr;
  HyperCPU::IInstruction instr = decoder.FetchAndDecode();

  ASSERT_EQ(instr.m_opcode, HyperCPU::Opcode::MOV);
  ASSERT_EQ(instr.m_opcode_mode, HyperCPU::Mode::b16);
  ASSERT_EQ(instr.m_op_types, HyperCPU::OperandTypes::M_R);

  memcpy(&mem_ptr, &instr.m_op1, sizeof(std::size_t));
  memcpy(&reg2, &instr.m_op2, sizeof(HyperCPU::Reg));
  ASSERT_EQ(mem_ptr, MEM_PTR);
  ASSERT_EQ(reg2, HyperCPU::Reg::X7);
}

TEST_F(DECODER_TEST, MOV_INSTR_M_R_B32) {
  decoder.mem_controller->Load(counter, HyperCPU::Opcode::MOV);
  counter += 2;
  decoder.mem_controller->Load(counter, EncodeTestFlags(HyperCPU::Mode::b32, HyperCPU::OperandTypes::M_R));
  ++counter;
  decoder.mem_controller->Load(counter, MEM_PTR);
  counter += 8;
  decoder.mem_controller->Load(counter, HyperCPU::Reg::X7);
  counter = 0;

  HyperCPU::Reg reg2;
  std::size_t mem_ptr;
  HyperCPU::IInstruction instr = decoder.FetchAndDecode();

  ASSERT_EQ(instr.m_opcode, HyperCPU::Opcode::MOV);
  ASSERT_EQ(instr.m_opcode_mode, HyperCPU::Mode::b32);
  ASSERT_EQ(instr.m_op_types, HyperCPU::OperandTypes::M_R);

  memcpy(&mem_ptr, &instr.m_op1, sizeof(std::size_t));
  memcpy(&reg2, &instr.m_op2, sizeof(HyperCPU::Reg));
  ASSERT_EQ(mem_ptr, MEM_PTR);
  ASSERT_EQ(reg2, HyperCPU::Reg::X7);
}

TEST_F(DECODER_TEST, MOV_INSTR_M_R_B64) {
  decoder.mem_controller->Load(counter, HyperCPU::Opcode::MOV);
  counter += 2;
  decoder.mem_controller->Load(counter, EncodeTestFlags(HyperCPU::Mode::b64, HyperCPU::OperandTypes::M_R));
  ++counter;
  decoder.mem_controller->Load(counter, MEM_PTR);
  counter += 8;
  decoder.mem_controller->Load(counter, HyperCPU::Reg::X7);
  counter = 0;

  HyperCPU::Reg reg2;
  std::size_t mem_ptr;
  HyperCPU::IInstruction instr = decoder.FetchAndDecode();

  ASSERT_EQ(instr.m_opcode, HyperCPU::Opcode::MOV);
  ASSERT_EQ(instr.m_opcode_mode, HyperCPU::Mode::b64);
  ASSERT_EQ(instr.m_op_types, HyperCPU::OperandTypes::M_R);

  memcpy(&mem_ptr, &instr.m_op1, sizeof(std::size_t));
  memcpy(&reg2, &instr.m_op2, sizeof(HyperCPU::Reg));
  ASSERT_EQ(mem_ptr, MEM_PTR);
  ASSERT_EQ(reg2, HyperCPU::Reg::X7);
}
