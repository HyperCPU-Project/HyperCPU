#include <Common/LanguageSpec/Flags.hpp>
#include <Common/LanguageSpec/Registers.hpp>

#include "tests/fixtures.hpp"

TEST_F(CPU_TEST, INSTR_CALL_R) {
  cpu.mem_controller->Load(*cpu.xip, HyperCPU::Opcode::CALL);
  cpu.mem_controller->Load(*cpu.xip + 2, EncodeTestFlags(HyperCPU::Mode::b64, HyperCPU::OperandTypes::R));
  cpu.mem_controller->Load(*cpu.xip + 3, HyperCPU::Reg::X0);
  cpu.mem_controller->Load(1536, HyperCPU::Opcode::HALT);
  cpu.mem_controller->Load(1538, HyperCPU::OperandTypes::NONE);
  *cpu.xbp = 512;
  *cpu.xsp = *cpu.xbp;
  *cpu.x0 = 1536;

  cpu.Run();

  ASSERT_EQ(*cpu.xip, 1539);
}

TEST_F(CPU_TEST, INSTR_CALL_IMM) {
  cpu.mem_controller->Load(*cpu.xip, HyperCPU::Opcode::CALL);
  cpu.mem_controller->Load(*cpu.xip + 2, EncodeTestFlags(HyperCPU::Mode::b64, HyperCPU::OperandTypes::IMM));
  cpu.mem_controller->Load(*cpu.xip + 3, 1536);
  cpu.mem_controller->Load(1536, HyperCPU::Opcode::HALT);
  cpu.mem_controller->Load(1538, HyperCPU::OperandTypes::NONE);
  *cpu.xbp = 512;
  *cpu.xsp = *cpu.xbp;

  cpu.Run();

  ASSERT_EQ(*cpu.xip, 1539);
}
