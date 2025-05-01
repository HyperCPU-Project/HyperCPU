#include <pch.hpp>

#include <cstring>

#include <fixtures.hpp>

TEST_F(DECODER_TEST, CCRF_INSTR_NONE) {
  decoder.mem_controller->Load16(counter, HyperCPU::CCRF);
  counter += 2;
  decoder.mem_controller->Load8(counter, HyperCPU::OperandTypes::NONE);
  counter = 0;
  
  HyperCPU::IInstruction instr = decoder.FetchAndDecode();

  ASSERT_EQ(instr.m_opcode, HyperCPU::Opcode::CCRF);
  ASSERT_EQ(instr.m_op_types, HyperCPU::OperandTypes::NONE);
}