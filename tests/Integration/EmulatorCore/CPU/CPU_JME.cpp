#include <Common/LanguageSpec/Flags.hpp>
#include <Common/LanguageSpec/Registers.hpp>

#include "tests/fixtures.hpp"

TEST_F(CPU_TEST, INSTR_JME_R_TRUE) {
  cpu.mem_controller->Load(*cpu.xip, HyperCPU::Opcode::JME);
  cpu.mem_controller->Load(*cpu.xip + 2, EncodeTestFlags(HyperCPU::Mode::b64, HyperCPU::OperandTypes::R));
  cpu.mem_controller->Load(*cpu.xip + 3, HyperCPU::Reg::X0);
  cpu.mem_controller->Load(1536, HyperCPU::Opcode::HALT);
  cpu.mem_controller->Load(1538, HyperCPU::OperandTypes::NONE);
  *cpu.x0 = 1536;
  cpu.zrf = 1;

  cpu.Run();

  ASSERT_EQ(*cpu.xip, 1539);
}

TEST_F(CPU_TEST, INSTR_JME_R_FALSE) {
  cpu.mem_controller->Load(*cpu.xip, HyperCPU::Opcode::JME);
  cpu.mem_controller->Load(*cpu.xip + 2, EncodeTestFlags(HyperCPU::Mode::b64, HyperCPU::OperandTypes::R));
  cpu.mem_controller->Load(*cpu.xip + 3, HyperCPU::Reg::X0);
  cpu.mem_controller->Load(*cpu.xip + 4, HyperCPU::Opcode::HALT);
  cpu.mem_controller->Load(*cpu.xip + 6, HyperCPU::OperandTypes::NONE);
  cpu.mem_controller->Load(1536, HyperCPU::Opcode::HALT);
  cpu.mem_controller->Load(1538, HyperCPU::OperandTypes::NONE);
  *cpu.x0 = 1536;

  cpu.Run();

  ASSERT_EQ(*cpu.xip, 7);
}

TEST_F(CPU_TEST, INSTR_JME_IMM_TRUE) {
  cpu.mem_controller->Load(*cpu.xip, HyperCPU::Opcode::JME);
  cpu.mem_controller->Load(*cpu.xip + 2, EncodeTestFlags(HyperCPU::Mode::b64, HyperCPU::OperandTypes::IMM));
  cpu.mem_controller->Load(*cpu.xip + 3, 1536);
  cpu.mem_controller->Load(1536, HyperCPU::Opcode::HALT);
  cpu.mem_controller->Load(1538, HyperCPU::OperandTypes::NONE);
  cpu.zrf = 1;

  cpu.Run();

  ASSERT_EQ(*cpu.xip, 1539);
}

TEST_F(CPU_TEST, INSTR_JME_IMM_FALSE) {
  cpu.mem_controller->Load(*cpu.xip, HyperCPU::Opcode::JME);
  cpu.mem_controller->Load(*cpu.xip + 2, EncodeTestFlags(HyperCPU::Mode::b64, HyperCPU::OperandTypes::IMM));
  cpu.mem_controller->Load(*cpu.xip + 3, 1536);
  cpu.mem_controller->Load(*cpu.xip + 11, HyperCPU::Opcode::HALT);
  cpu.mem_controller->Load(*cpu.xip + 13, HyperCPU::OperandTypes::NONE);
  cpu.mem_controller->Load(1536, HyperCPU::Opcode::HALT);
  cpu.mem_controller->Load(1538, HyperCPU::OperandTypes::NONE);

  cpu.Run();

  ASSERT_EQ(*cpu.xip, 14);
}
