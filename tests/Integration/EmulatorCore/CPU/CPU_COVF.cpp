#include <Common/LanguageSpec/Flags.hpp>
#include <Common/LanguageSpec/Registers.hpp>

#include "fixtures.hpp"

TEST_F(CPU_TEST, INSTR_COVF_SET) {
  cpu.mem_controller->Load16(*cpu.xip, HyperCPU::Opcode::COVF);
  cpu.mem_controller->Load8(*cpu.xip + 2, HyperCPU::OperandTypes::NONE);
  cpu.mem_controller->Load16(*cpu.xip + 3, HyperCPU::Opcode::HALT);
  cpu.mem_controller->Load8(*cpu.xip + 5, HyperCPU::OperandTypes::NONE);
  cpu.ovf = true;

  cpu.Run();

  ASSERT_FALSE(cpu.ovf);
}

TEST_F(CPU_TEST, INSTR_COVF_NOTSET) {
  cpu.mem_controller->Load16(*cpu.xip, HyperCPU::Opcode::COVF);
  cpu.mem_controller->Load8(*cpu.xip + 2, HyperCPU::OperandTypes::NONE);
  cpu.mem_controller->Load16(*cpu.xip + 3, HyperCPU::Opcode::HALT);
  cpu.mem_controller->Load8(*cpu.xip + 5, HyperCPU::OperandTypes::NONE);
  cpu.ovf = false;

  cpu.Run();

  ASSERT_FALSE(cpu.ovf);
}
