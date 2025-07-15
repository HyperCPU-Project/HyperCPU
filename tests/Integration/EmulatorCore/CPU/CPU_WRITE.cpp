#include "tests/fixtures.hpp"

TEST_F(CPU_TEST, INSTR_WRITE) {
  std::uint8_t t = 0;
  cpu.write_io_handlers[1] = [&t](std::uint8_t arg) -> void {
    std::cout << "hehe " << arg << '\n';
    t = arg;
  };

  cpu.mem_controller->Load(*cpu.xip, HyperCPU::Opcode::WRITE);
  cpu.mem_controller->Load(*cpu.xip + 2, EncodeTestFlags(HyperCPU::Mode::b8,  HyperCPU::Mode::b8, HyperCPU::OperandTypes::R_IMM));
  cpu.mem_controller->Load(*cpu.xip + 3, HyperCPU::Reg::XLLL0);
  cpu.mem_controller->Load(*cpu.xip + 4, 0x55);
  cpu.mem_controller->Load(*cpu.xip + 5, HyperCPU::Opcode::HALT);
  cpu.mem_controller->Load(*cpu.xip + 7, HyperCPU::OperandTypes::NONE);
  *cpu.xlll0 = 1;

  cpu.Run();

  ASSERT_EQ(t, 0x55);
}
