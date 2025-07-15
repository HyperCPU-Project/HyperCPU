#include "tests/fixtures.hpp"

TEST_F(DECODER_TEST, READ_INSTR_IMM) {
  decoder.mem_controller->Load(counter, HyperCPU::Opcode::READ);
  counter += 2;
  decoder.mem_controller->Load(counter, EncodeTestFlags(HyperCPU::Mode::b8, HyperCPU::OperandTypes::IMM));
  ++counter;
  decoder.mem_controller->Load(counter, 0x55);
  counter = 0;

  HyperCPU::IInstruction instr = decoder.FetchAndDecode();

  ASSERT_EQ(instr.m_opcode, HyperCPU::Opcode::READ);
  ASSERT_EQ(instr.m_opcode_mode, HyperCPU::Mode::b8);
  ASSERT_EQ(instr.m_op_types, HyperCPU::OperandTypes::IMM);

  ASSERT_EQ(HyperCPU::bit_cast_from<std::uint8_t>(&instr.m_op1), 0x55);
}

TEST_F(DECODER_TEST, READ_INSTR_R) {
  decoder.mem_controller->Load(counter, HyperCPU::Opcode::READ);
  counter += 2;
  decoder.mem_controller->Load(counter, EncodeTestFlags(HyperCPU::Mode::b8, HyperCPU::OperandTypes::R));
  ++counter;
  decoder.mem_controller->Load(counter, HyperCPU::Reg::XLLL0);
  counter = 0;

  HyperCPU::IInstruction instr = decoder.FetchAndDecode();

  ASSERT_EQ(instr.m_opcode, HyperCPU::Opcode::READ);
  ASSERT_EQ(instr.m_opcode_mode, HyperCPU::Mode::b8);
  ASSERT_EQ(instr.m_op_types, HyperCPU::OperandTypes::R);

  ASSERT_EQ(HyperCPU::bit_cast_from<HyperCPU::Reg>(&instr.m_op1), HyperCPU::Reg::XLLL0);
}
