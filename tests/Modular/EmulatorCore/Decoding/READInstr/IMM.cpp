#include "Core/CPU/Instructions/Registers.hpp"
#include <fixtures.hpp>

#include <Misc/bit_cast.hpp>

TEST_F(DECODER_TEST, READ_INSTR_IMM) {
  decoder.mem_controller->Load16(counter, HyperCPU::READ);
  counter += 2;
  decoder.mem_controller->Load8(counter, (HyperCPU::Mode::b8 << 4) | HyperCPU::OperandTypes::IMM);
  ++counter;
  decoder.mem_controller->Load8(counter, 0x55);
  counter = 0;
  
  HyperCPU::IInstruction instr = decoder.FetchAndDecode();

  ASSERT_EQ(instr.m_opcode, HyperCPU::Opcode::READ);
  ASSERT_EQ(instr.m_opcode_mode, HyperCPU::Mode::b8);
  ASSERT_EQ(instr.m_op_types, HyperCPU::OperandTypes::IMM);

  ASSERT_EQ(HyperCPU::bit_cast_from<std::uint8_t>(&instr.m_op1), 0x55);
}

TEST_F(DECODER_TEST, READ_INSTR_R) {
  decoder.mem_controller->Load16(counter, HyperCPU::READ);   counter += 2;
  decoder.mem_controller->Load8(counter, (HyperCPU::Mode::b8 << 4) | HyperCPU::OperandTypes::R);
  ++counter;
  decoder.mem_controller->Load8(counter, HyperCPU::Registers::XLLL0);
  counter = 0;

  HyperCPU::IInstruction instr = decoder.FetchAndDecode();

  ASSERT_EQ(instr.m_opcode, HyperCPU::Opcode::READ);
  ASSERT_EQ(instr.m_opcode_mode, HyperCPU::Mode::b8);
  ASSERT_EQ(instr.m_op_types, HyperCPU::OperandTypes::R);

  ASSERT_EQ(HyperCPU::bit_cast_from<std::uint8_t>(&instr.m_op1), HyperCPU::Registers::XLLL0);
}
