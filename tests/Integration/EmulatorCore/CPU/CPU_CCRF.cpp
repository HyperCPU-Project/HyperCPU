#include <Common/LanguageSpec/Flags.hpp>
#include <Common/LanguageSpec/Registers.hpp>

#include "fixtures.hpp"

TEST_F(CPU_TEST, INSTR_CCRF_SET) {
  cpu.mem_controller->Load16(*cpu.xip, HyperCPU::Opcode::CCRF);
  cpu.mem_controller->Load8(*cpu.xip + 2, HyperCPU::OperandTypes::NONE);
  cpu.mem_controller->Load16(*cpu.xip + 3, HyperCPU::Opcode::HALT);
  cpu.mem_controller->Load8(*cpu.xip + 5, HyperCPU::OperandTypes::NONE);
  cpu.crf = true;

  cpu.Run();

  ASSERT_FALSE(cpu.crf);
}

TEST_F(CPU_TEST, INSTR_CCRF_NOTSET) {
  cpu.mem_controller->Load16(*cpu.xip, HyperCPU::Opcode::CCRF);
  cpu.mem_controller->Load8(*cpu.xip + 2, HyperCPU::OperandTypes::NONE);
  cpu.mem_controller->Load16(*cpu.xip + 3, HyperCPU::Opcode::HALT);
  cpu.mem_controller->Load8(*cpu.xip + 5, HyperCPU::OperandTypes::NONE);
  cpu.crf = false;

  cpu.Run();

  ASSERT_FALSE(cpu.crf);
}
