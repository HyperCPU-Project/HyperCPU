#include <Common/LanguageSpec/Flags.hpp>
#include <Common/LanguageSpec/Registers.hpp>

#include "fixtures.hpp"

TEST_F(CPU_TEST, INSTR_IRET_NONE) {
  *cpu.xbp = 512;
  *cpu.xsp = 512;
  cpu.StackPush64(1536);
  cpu.mem_controller->Load16(*cpu.xip, HyperCPU::Opcode::IRET);
  cpu.mem_controller->Load8(*cpu.xip + 2, 0);
  cpu.mem_controller->Load16(1536, HyperCPU::Opcode::HALT);
  cpu.mem_controller->Load8(1538, HyperCPU::OperandTypes::NONE);
  *cpu.x0 = 1536;

  cpu.Run();

  ASSERT_EQ(*cpu.xip, 1539);
}
