#include "tests/fixtures.hpp"

TEST_F(DECODER_TEST, JML_INSTR_IMM) {
  decoder.mem_controller->Load(counter, HyperCPU::Opcode::JML);
  counter += 2;
  decoder.mem_controller->Load(counter, EncodeTestFlags(HyperCPU::Mode::b64, HyperCPU::OperandTypes::IMM));
  ++counter;
  decoder.mem_controller->Load(counter, MEM_PTR);
  counter = 0;

  std::uint64_t mem_ptr;
  HyperCPU::IInstruction instr = decoder.FetchAndDecode();

  ASSERT_EQ(instr.m_opcode, HyperCPU::Opcode::JML);
  ASSERT_EQ(instr.m_op_types, HyperCPU::OperandTypes::IMM);

  memcpy(&mem_ptr, &instr.m_op1, sizeof(std::uint64_t));
  ASSERT_EQ(mem_ptr, MEM_PTR);
}
