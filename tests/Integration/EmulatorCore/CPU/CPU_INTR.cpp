#include <Common/LanguageSpec/Flags.hpp>
#include <Common/LanguageSpec/Registers.hpp>

#include "tests/fixtures.hpp"

TEST_F(CPU_TEST, INSTR_INTR_R_b64) {
  // Setup stack
  *cpu.xbp = 512;
  *cpu.xsp = 512;
  // Setup IVT
  cpu.mem_controller->Load(2048, 1536);                   // First IVT entry
  cpu.mem_controller->Load(1536, HyperCPU::Opcode::HALT); // Code for interrupt handler
  cpu.mem_controller->Load(1538, HyperCPU::OperandTypes::NONE);
  cpu.mem_controller->Load(*cpu.xip, HyperCPU::Opcode::LOIVT);
  cpu.mem_controller->Load(*cpu.xip + 2, EncodeTestFlags(HyperCPU::Mode::b64, HyperCPU::OperandTypes::R));
  cpu.mem_controller->Load(*cpu.xip + 3, HyperCPU::Reg::X0);
  cpu.mem_controller->Load(*cpu.xip + 4, HyperCPU::Opcode::INTR);
  cpu.mem_controller->Load(*cpu.xip + 6, EncodeTestFlags(HyperCPU::Mode::b64, HyperCPU::OperandTypes::R));
  cpu.mem_controller->Load(*cpu.xip + 7, HyperCPU::Reg::X1);
  *cpu.x0 = 2048;
  *cpu.x1 = 0;

  cpu.Run();

  ASSERT_EQ(*cpu.xip, 1539);
}
