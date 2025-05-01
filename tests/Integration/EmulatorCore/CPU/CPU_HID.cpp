#include <Core/CPU/Instructions/Registers.hpp>
#include <Core/CPU/Instructions/Flags.hpp>
#include <Core/CPU/Version.hpp>

#include <fixtures.hpp>


TEST_F(CPU_TEST, INSTR_HID_0) {
  cpu.mem_controller->Load16(*cpu.xip, HyperCPU::Opcode::HID);
  cpu.mem_controller->Load8(*cpu.xip + 2, HyperCPU::OperandTypes::NONE);
  cpu.mem_controller->Load16(*cpu.xip + 3, HyperCPU::Opcode::HALT);
  cpu.mem_controller->Load8(*cpu.xip + 5, HyperCPU::OperandTypes::NONE);
  *cpu.x0 = 0;

  cpu.Run();

  ASSERT_EQ(*cpu.x0, 2);
}

TEST_F(CPU_TEST, INSTR_HID_1) {
  cpu.mem_controller->Load16(*cpu.xip, HyperCPU::Opcode::HID);
  cpu.mem_controller->Load8(*cpu.xip + 2, HyperCPU::OperandTypes::NONE);
  cpu.mem_controller->Load16(*cpu.xip + 3, HyperCPU::Opcode::HALT);
  cpu.mem_controller->Load8(*cpu.xip + 5, HyperCPU::OperandTypes::NONE);
  *cpu.x0 = 1;

  cpu.Run();

  ASSERT_TRUE(!std::strcmp(std::bit_cast<char*>(&cpu.data), HID_CPU_NAME));
}

TEST_F(CPU_TEST, INSTR_HID_2) {
  cpu.mem_controller->Load16(*cpu.xip, HyperCPU::Opcode::HID);
  cpu.mem_controller->Load8(*cpu.xip + 2, HyperCPU::OperandTypes::NONE);
  cpu.mem_controller->Load16(*cpu.xip + 3, HyperCPU::Opcode::HALT);
  cpu.mem_controller->Load8(*cpu.xip + 5, HyperCPU::OperandTypes::NONE);
  *cpu.x0 = 2;

  cpu.Run();

  ASSERT_EQ(*cpu.x0, 0);
}