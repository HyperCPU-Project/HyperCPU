#include "tests/fixtures.hpp"

TEST_F(DECODER_TEST, MOV_INSTR_RM_M_B8) {
  decoder.mem_controller->Load16(counter, HyperCPU::Opcode::MOV);
  counter += 2;
  decoder.mem_controller->Load8(counter, EncodeTestFlags(HyperCPU::Mode::b8,  HyperCPU::Mode::b8, HyperCPU::OperandTypes::RM_M))
;
  ++counter;
  decoder.mem_controller->Load8(counter, HyperCPU::Reg::X3);
  ++counter;
  decoder.mem_controller->Load64(counter, MEM_PTR);
  counter = 0;

  HyperCPU::Reg reg1;
  std::size_t mem_ptr;
  HyperCPU::IInstruction instr = decoder.FetchAndDecode();

  ASSERT_EQ(instr.m_opcode, HyperCPU::Opcode::MOV);
  ASSERT_EQ(instr.m_opcode_mode, HyperCPU::Mode::b8);
  ASSERT_EQ(instr.m_op_types, HyperCPU::OperandTypes::RM_M);

  memcpy(&reg1, &instr.m_op1, sizeof(HyperCPU::Reg));
  memcpy(&mem_ptr, &instr.m_op2, sizeof(std::size_t));
  ASSERT_EQ(reg1, HyperCPU::Reg::X3);
  ASSERT_EQ(mem_ptr, MEM_PTR);
}

TEST_F(DECODER_TEST, MOV_INSTR_RM_M_B16) {
  decoder.mem_controller->Load16(counter, HyperCPU::Opcode::MOV);
  counter += 2;
  decoder.mem_controller->Load8(counter, EncodeTestFlags(HyperCPU::Mode::b16,  HyperCPU::Mode::b16, HyperCPU::OperandTypes::RM_M))
;
  ++counter;
  decoder.mem_controller->Load8(counter, HyperCPU::Reg::X3);
  ++counter;
  decoder.mem_controller->Load64(counter, MEM_PTR);
  counter = 0;

  HyperCPU::Reg reg1;
  std::size_t mem_ptr;
  HyperCPU::IInstruction instr = decoder.FetchAndDecode();

  ASSERT_EQ(instr.m_opcode, HyperCPU::Opcode::MOV);
  ASSERT_EQ(instr.m_opcode_mode, HyperCPU::Mode::b16);
  ASSERT_EQ(instr.m_op_types, HyperCPU::OperandTypes::RM_M);

  memcpy(&reg1, &instr.m_op1, sizeof(HyperCPU::Reg));
  memcpy(&mem_ptr, &instr.m_op2, sizeof(std::size_t));
  ASSERT_EQ(reg1, HyperCPU::Reg::X3);
  ASSERT_EQ(mem_ptr, MEM_PTR);
}

TEST_F(DECODER_TEST, MOV_INSTR_RM_M_B32) {
  decoder.mem_controller->Load16(counter, HyperCPU::Opcode::MOV);
  counter += 2;
  decoder.mem_controller->Load8(counter, EncodeTestFlags(HyperCPU::Mode::b32,  HyperCPU::Mode::b32, HyperCPU::OperandTypes::RM_M))
;
  ++counter;
  decoder.mem_controller->Load8(counter, HyperCPU::Reg::X3);
  ++counter;
  decoder.mem_controller->Load64(counter, MEM_PTR);
  counter = 0;

  HyperCPU::Reg reg1;
  std::size_t mem_ptr;
  HyperCPU::IInstruction instr = decoder.FetchAndDecode();

  ASSERT_EQ(instr.m_opcode, HyperCPU::Opcode::MOV);
  ASSERT_EQ(instr.m_opcode_mode, HyperCPU::Mode::b32);
  ASSERT_EQ(instr.m_op_types, HyperCPU::OperandTypes::RM_M);

  memcpy(&reg1, &instr.m_op1, sizeof(HyperCPU::Reg));
  memcpy(&mem_ptr, &instr.m_op2, sizeof(std::size_t));
  ASSERT_EQ(reg1, HyperCPU::Reg::X3);
  ASSERT_EQ(mem_ptr, MEM_PTR);
}

TEST_F(DECODER_TEST, MOV_INSTR_RM_M_B64) {
  decoder.mem_controller->Load16(counter, HyperCPU::Opcode::MOV);
  counter += 2;
  decoder.mem_controller->Load8(counter, EncodeTestFlags(HyperCPU::Mode::b64,  HyperCPU::Mode::b64, HyperCPU::OperandTypes::RM_M))
;
  ++counter;
  decoder.mem_controller->Load8(counter, HyperCPU::Reg::X3);
  ++counter;
  decoder.mem_controller->Load64(counter, MEM_PTR);
  counter = 0;

  HyperCPU::Reg reg1;
  std::size_t mem_ptr;
  HyperCPU::IInstruction instr = decoder.FetchAndDecode();

  ASSERT_EQ(instr.m_opcode, HyperCPU::Opcode::MOV);
  ASSERT_EQ(instr.m_opcode_mode, HyperCPU::Mode::b64);
  ASSERT_EQ(instr.m_op_types, HyperCPU::OperandTypes::RM_M);

  memcpy(&reg1, &instr.m_op1, sizeof(HyperCPU::Reg));
  memcpy(&mem_ptr, &instr.m_op2, sizeof(std::size_t));
  ASSERT_EQ(reg1, HyperCPU::Reg::X3);
  ASSERT_EQ(mem_ptr, MEM_PTR);
}
