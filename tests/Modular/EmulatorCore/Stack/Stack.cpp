#include "fixtures.hpp"

static constexpr std::uint8_t BYTE_DATA = 0x55;
static constexpr std::uint16_t WORD_DATA = 0x5555;
static constexpr std::uint32_t DWORD_DATA = 0x55555555;
static constexpr std::uint64_t QWORD_DATA = 0x555555555555555;

TEST_F(STACK_TEST, STACK_PUSH8) {
  cpu.StackPush8(BYTE_DATA);

  ASSERT_EQ(*cpu.xsp, 1023);
  ASSERT_EQ(cpu.mem_controller->Read8(*cpu.xsp), BYTE_DATA);
}

TEST_F(STACK_TEST, STACK_PUSH16) {
  cpu.StackPush16(WORD_DATA);

  ASSERT_EQ(*cpu.xsp, 1022);
  ASSERT_EQ(cpu.mem_controller->Read16(*cpu.xsp), WORD_DATA);
}

TEST_F(STACK_TEST, STACK_PUSH32) {
  cpu.StackPush32(DWORD_DATA);

  ASSERT_EQ(*cpu.xsp, 1020);
  ASSERT_EQ(cpu.mem_controller->Read32(*cpu.xsp), DWORD_DATA);
}

TEST_F(STACK_TEST, STACK_PUSH64) {
  cpu.StackPush64(QWORD_DATA);

  ASSERT_EQ(*cpu.xsp, 1016);
  ASSERT_EQ(cpu.mem_controller->Read64(*cpu.xsp), QWORD_DATA);
}

TEST_F(STACK_TEST, STACK_POP8) {
  cpu.StackPush8(BYTE_DATA);
  std::uint8_t val = cpu.StackPop8();

  ASSERT_EQ(*cpu.xsp, 1024);
  ASSERT_EQ(val, BYTE_DATA);
}

TEST_F(STACK_TEST, STACK_POP16) {
  cpu.StackPush16(WORD_DATA);
  std::uint16_t val = cpu.StackPop16();

  ASSERT_EQ(*cpu.xsp, 1024);
  ASSERT_EQ(val, WORD_DATA);
}

TEST_F(STACK_TEST, STACK_POP32) {
  cpu.StackPush32(DWORD_DATA);
  std::uint32_t val = cpu.StackPop32();

  ASSERT_EQ(*cpu.xsp, 1024);
  ASSERT_EQ(val, DWORD_DATA);
}

TEST_F(STACK_TEST, STACK_POP64) {
  cpu.StackPush64(QWORD_DATA);
  std::uint64_t val = cpu.StackPop64();

  ASSERT_EQ(*cpu.xsp, 1024);
  ASSERT_EQ(val, QWORD_DATA);
}
