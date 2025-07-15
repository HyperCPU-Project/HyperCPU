#include "tests/fixtures.hpp"

TEST_F(EXCEPTION_TEST, CPU_EXCEPTION_IO) {
  cpu.mem_controller->Load(*cpu.xip, 8273);

  cpu.Run();

  ASSERT_EQ(*cpu.xip, 1539);
}

TEST_F(EXCEPTION_TEST, CPU_EXCEPTION_ZRDIV) {
  cpu.mem_controller->Load(*cpu.xip, static_cast<std::uint16_t>(HyperCPU::Opcode::DIV));
  cpu.mem_controller->Load(*cpu.xip + 2, (static_cast<std::uint8_t>(HyperCPU::Mode::b8) << 4) | static_cast<std::uint8_t>(HyperCPU::OperandTypes::R));
  cpu.mem_controller->Load(*cpu.xip + 3, static_cast<std::uint8_t>(HyperCPU::Reg::XLLL0));
  *cpu.xlll0 = 0x55;
  *cpu.x2 = 0;

  cpu.Run();

  ASSERT_EQ(*cpu.xip, 1539);
}
