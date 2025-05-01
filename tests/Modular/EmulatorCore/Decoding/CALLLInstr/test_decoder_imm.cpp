#include <pch.hpp>

#include <cstring>

#include <fixtures.hpp>

TEST_F(DECODER_TEST, CALLL_INSTR_IMM) {
  decoder.mem_controller->Load16(counter, HyperCPU::Opcode::CALLL);
  counter += 2;
  decoder.mem_controller->Load8(counter, (HyperCPU::Mode::b64 << 4) | HyperCPU::OperandTypes::IMM);
  ++counter;
  decoder.mem_controller->Load64(counter, MEM_PTR);
  counter = 0;
  
  std::uint64_t mem_ptr;
  HyperCPU::IInstruction instr = decoder.FetchAndDecode();

  ASSERT_EQ(instr.m_opcode, HyperCPU::Opcode::CALLL);
  ASSERT_EQ(instr.m_op_types, HyperCPU::OperandTypes::IMM);

  memcpy(&mem_ptr, &instr.m_op1, sizeof(std::uint64_t));
  ASSERT_EQ(mem_ptr, MEM_PTR);
}