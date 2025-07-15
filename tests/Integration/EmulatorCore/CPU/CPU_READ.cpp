#include "tests/fixtures.hpp"

TEST_F(CPU_TEST, INSTR_READ) {
  cpu.read_io_handlers[1] = []() -> std::uint8_t {
    return 0x55;
  };

  cpu.mem_controller->Load(*cpu.xip, HyperCPU::Opcode::READ);
  cpu.mem_controller->Load(*cpu.xip + 2, EncodeTestFlags(HyperCPU::Mode::b8, HyperCPU::OperandTypes::IMM));
  cpu.mem_controller->Load(*cpu.xip + 3, 1);
  cpu.mem_controller->Load(*cpu.xip + 4, HyperCPU::Opcode::HALT);
  cpu.mem_controller->Load(*cpu.xip + 6, HyperCPU::OperandTypes::NONE);

  cpu.Run();

  ASSERT_EQ(*cpu.xlll0, 0x55);
}
