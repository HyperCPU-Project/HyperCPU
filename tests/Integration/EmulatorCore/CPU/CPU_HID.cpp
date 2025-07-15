#include "Emulator/Core/CPU/Version.hpp"

#include "tests/fixtures.hpp"

TEST_F(CPU_TEST, INSTR_HID_0) {
  cpu.mem_controller->Load(*cpu.xip, HyperCPU::Opcode::HID);
  cpu.mem_controller->Load(*cpu.xip + 2, HyperCPU::OperandTypes::NONE);
  cpu.mem_controller->Load(*cpu.xip + 3, HyperCPU::Opcode::HALT);
  cpu.mem_controller->Load(*cpu.xip + 5, HyperCPU::OperandTypes::NONE);
  *cpu.x0 = 0;

  cpu.Run();

  ASSERT_EQ(*cpu.x0, 2);
}

TEST_F(CPU_TEST, INSTR_HID_1) {
  cpu.mem_controller->Load(*cpu.xip, HyperCPU::Opcode::HID);
  cpu.mem_controller->Load(*cpu.xip + 2, HyperCPU::OperandTypes::NONE);
  cpu.mem_controller->Load(*cpu.xip + 3, HyperCPU::Opcode::HALT);
  cpu.mem_controller->Load(*cpu.xip + 5, HyperCPU::OperandTypes::NONE);
  *cpu.x0 = 1;

  cpu.Run();

  ASSERT_TRUE(!std::strcmp(std::bit_cast<char*>(&cpu.data), HID_CPU_NAME));
}

TEST_F(CPU_TEST, INSTR_HID_2) {
  cpu.mem_controller->Load(*cpu.xip, HyperCPU::Opcode::HID);
  cpu.mem_controller->Load(*cpu.xip + 2, HyperCPU::OperandTypes::NONE);
  cpu.mem_controller->Load(*cpu.xip + 3, HyperCPU::Opcode::HALT);
  cpu.mem_controller->Load(*cpu.xip + 5, HyperCPU::OperandTypes::NONE);
  *cpu.x0 = 2;

  cpu.Run();

  ASSERT_EQ(*cpu.x0, 0);
}
