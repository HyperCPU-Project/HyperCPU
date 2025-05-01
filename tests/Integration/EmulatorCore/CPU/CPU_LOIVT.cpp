#include <Core/CPU/Instructions/Registers.hpp>
#include <Core/CPU/Instructions/Flags.hpp>

#include <fixtures.hpp>


TEST_F(CPU_TEST, INSTR_LOIVT_R_b64) {
  cpu.mem_controller->Load16(*cpu.xip, HyperCPU::Opcode::LOIVT);
  cpu.mem_controller->Load8(*cpu.xip + 2, HyperCPU::Mode::b64 << 4 | HyperCPU::OperandTypes::R);
  cpu.mem_controller->Load8(*cpu.xip + 3, HyperCPU::Registers::X1);
  cpu.mem_controller->Load16(*cpu.xip + 4, HyperCPU::Opcode::HALT);
  cpu.mem_controller->Load8(*cpu.xip + 6, HyperCPU::OperandTypes::NONE);
  *cpu.x1 = 2048;

  cpu.Run();

  ASSERT_EQ(*cpu.xivt, 2048);
}
