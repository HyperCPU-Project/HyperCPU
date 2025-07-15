#include <bit>

#include "Emulator/Misc/byteswap.hpp"
#include <Common/LanguageSpec/Flags.hpp>
#include <Common/LanguageSpec/Registers.hpp>

#include "tests/fixtures.hpp"

static constexpr std::uint8_t BYTE_DATA1 = 0x12;
static constexpr std::uint8_t BYTE_RESULT = BYTE_DATA1;
static constexpr std::uint16_t WORD_DATA1 = 0x1234;
static std::uint16_t WORD_RESULT = HyperCPU::byteswap(WORD_DATA1);
static constexpr std::uint32_t DWORD_DATA1 = 0x12345678;
static std::uint32_t DWORD_RESULT = HyperCPU::byteswap(DWORD_DATA1);
static constexpr std::uint64_t QWORD_DATA1 = 0x1234567812345678;
static std::uint64_t QWORD_RESULT = HyperCPU::byteswap(QWORD_DATA1);

TEST_F(CPU_TEST, INSTR_BSWAP_R_b8) {
  cpu.mem_controller->Load(*cpu.xip, HyperCPU::Opcode::BSWAP);
  cpu.mem_controller->Load(*cpu.xip + 2, EncodeTestFlags(HyperCPU::Mode::b8, HyperCPU::OperandTypes::R));
  cpu.mem_controller->Load(*cpu.xip + 3, HyperCPU::Reg::XLLL0);
  cpu.mem_controller->Load(*cpu.xip + 4, HyperCPU::Opcode::HALT);
  cpu.mem_controller->Load(*cpu.xip + 6, HyperCPU::OperandTypes::NONE);
  *cpu.xlll0 = BYTE_DATA1;

  cpu.Run();

  ASSERT_EQ(*cpu.xlll0, BYTE_RESULT);
}

TEST_F(CPU_TEST, INSTR_BSWAP_R_b16) {
  cpu.mem_controller->Load(*cpu.xip, HyperCPU::Opcode::BSWAP);
  cpu.mem_controller->Load(*cpu.xip + 2, EncodeTestFlags(HyperCPU::Mode::b16, HyperCPU::OperandTypes::R));
  cpu.mem_controller->Load(*cpu.xip + 3, HyperCPU::Reg::XLL0);
  cpu.mem_controller->Load(*cpu.xip + 4, HyperCPU::Opcode::HALT);
  cpu.mem_controller->Load(*cpu.xip + 6, HyperCPU::OperandTypes::NONE);
  *cpu.xll0 = WORD_DATA1;

  cpu.Run();

  ASSERT_EQ(*cpu.xll0, WORD_RESULT);
}

TEST_F(CPU_TEST, INSTR_BSWAP_R_b32) {
  cpu.mem_controller->Load(*cpu.xip, HyperCPU::Opcode::BSWAP);
  cpu.mem_controller->Load(*cpu.xip + 2, EncodeTestFlags(HyperCPU::Mode::b32, HyperCPU::OperandTypes::R));
  cpu.mem_controller->Load(*cpu.xip + 3, HyperCPU::Reg::XL0);
  cpu.mem_controller->Load(*cpu.xip + 4, HyperCPU::Opcode::HALT);
  cpu.mem_controller->Load(*cpu.xip + 6, HyperCPU::OperandTypes::NONE);
  *cpu.xl0 = DWORD_DATA1;

  cpu.Run();

  ASSERT_EQ(*cpu.xl0, DWORD_RESULT);
}

TEST_F(CPU_TEST, INSTR_BSWAP_R_b64) {
  cpu.mem_controller->Load(*cpu.xip, HyperCPU::Opcode::BSWAP);
  cpu.mem_controller->Load(*cpu.xip + 2, EncodeTestFlags(HyperCPU::Mode::b64, HyperCPU::OperandTypes::R));
  cpu.mem_controller->Load(*cpu.xip + 3, HyperCPU::Reg::X0);
  cpu.mem_controller->Load(*cpu.xip + 4, HyperCPU::Opcode::HALT);
  cpu.mem_controller->Load(*cpu.xip + 6, HyperCPU::OperandTypes::NONE);
  *cpu.x0 = QWORD_DATA1;

  cpu.Run();

  ASSERT_EQ(*cpu.x0, QWORD_RESULT);
}
