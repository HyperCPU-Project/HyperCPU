#include <Common/LanguageSpec/Flags.hpp>
#include <Common/LanguageSpec/Registers.hpp>

#include "tests/fixtures.hpp"

TEST_F(CPU_TEST, INSTR_CUDF_SET) {
  cpu.mem_controller->Load(*cpu.xip, HyperCPU::Opcode::CUDF);
  cpu.mem_controller->Load(*cpu.xip + 2, HyperCPU::OperandTypes::NONE);
  cpu.mem_controller->Load(*cpu.xip + 3, HyperCPU::Opcode::HALT);
  cpu.mem_controller->Load(*cpu.xip + 5, HyperCPU::OperandTypes::NONE);
  cpu.udf = true;

  cpu.Run();

  ASSERT_FALSE(cpu.udf);
}

TEST_F(CPU_TEST, INSTR_CUDF_NOTSET) {
  cpu.mem_controller->Load(*cpu.xip, HyperCPU::Opcode::CUDF);
  cpu.mem_controller->Load(*cpu.xip + 2, HyperCPU::OperandTypes::NONE);
  cpu.mem_controller->Load(*cpu.xip + 3, HyperCPU::Opcode::HALT);
  cpu.mem_controller->Load(*cpu.xip + 5, HyperCPU::OperandTypes::NONE);
  cpu.udf = false;

  cpu.Run();

  ASSERT_FALSE(cpu.udf);
}
