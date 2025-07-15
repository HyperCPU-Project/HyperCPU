#include <Common/LanguageSpec/Flags.hpp>
#include <Common/LanguageSpec/Registers.hpp>

#include "tests/fixtures.hpp"

TEST_F(CPU_TEST, INSTR_CCRF_SET) {
  cpu.mem_controller->Load(*cpu.xip, HyperCPU::Opcode::CCRF);
  cpu.mem_controller->Load(*cpu.xip + 2, HyperCPU::OperandTypes::NONE);
  cpu.mem_controller->Load(*cpu.xip + 3, HyperCPU::Opcode::HALT);
  cpu.mem_controller->Load(*cpu.xip + 5, HyperCPU::OperandTypes::NONE);
  cpu.crf = true;

  cpu.Run();

  ASSERT_FALSE(cpu.crf);
}

TEST_F(CPU_TEST, INSTR_CCRF_NOTSET) {
  cpu.mem_controller->Load(*cpu.xip, HyperCPU::Opcode::CCRF);
  cpu.mem_controller->Load(*cpu.xip + 2, HyperCPU::OperandTypes::NONE);
  cpu.mem_controller->Load(*cpu.xip + 3, HyperCPU::Opcode::HALT);
  cpu.mem_controller->Load(*cpu.xip + 5, HyperCPU::OperandTypes::NONE);
  cpu.crf = false;

  cpu.Run();

  ASSERT_FALSE(cpu.crf);
}
