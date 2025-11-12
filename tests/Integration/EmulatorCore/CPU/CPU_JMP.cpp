#include <Common/LanguageSpec/Flags.hpp>
#include <Common/LanguageSpec/Registers.hpp>

#include "fixtures.hpp"

TEST_F(CPU_TEST, INSTR_JMP_R) {
  cpu.mem_controller->Load16(*cpu.xip, HyperCPU::Opcode::JMP);
  cpu.mem_controller->Load8(*cpu.xip + 2, EncodeTestFlags(HyperCPU::Mode::b64, HyperCPU::OperandTypes::R));
  cpu.mem_controller->Load8(*cpu.xip + 3, HyperCPU::Reg::X0);
  cpu.mem_controller->Load16(1536, HyperCPU::Opcode::HALT);
  cpu.mem_controller->Load8(1538, HyperCPU::OperandTypes::NONE);
  *cpu.x0 = 1536;

  cpu.Run();

  ASSERT_EQ(*cpu.xip, 1539);
}

TEST_F(CPU_TEST, INSTR_JMP_IMM) {
  cpu.mem_controller->Load16(*cpu.xip, HyperCPU::Opcode::JMP);
  cpu.mem_controller->Load8(*cpu.xip + 2, EncodeTestFlags(HyperCPU::Mode::b64, HyperCPU::OperandTypes::IMM));
  cpu.mem_controller->Load64(*cpu.xip + 3, 1536);
  cpu.mem_controller->Load16(1536, HyperCPU::Opcode::HALT);
  cpu.mem_controller->Load8(1538, HyperCPU::OperandTypes::NONE);

  cpu.Run();

  ASSERT_EQ(*cpu.xip, 1539);
}
