#include <gtest/gtest.h>

#include <fixtures.hpp>

#define private public
#include <Core/MemoryController/MemoryControllerST.hpp>


static constexpr std::uint8_t BYTE = 0x55;
static constexpr std::uint16_t WORD = 0x5555;
static constexpr std::uint32_t DWORD = 0x55555555;
static constexpr std::uint64_t QWORD = 0x5555555555555555;

#ifdef __HCPU_DEBUG
# define HCPU_ASSERT_EXIT(statement, x, regex) ASSERT_EXIT(statement, x, regex)
#else
# define HCPU_ASSERT_EXIT(statement, x, regex) ASSERT_DEATH(statement, regex)
#endif

TEST_F(MC_ST_TEST, LOAD8) {
  for (std::size_t i = 0; i < MEM_FIXTURE_MEM_SIZE; ++i, ++counter)
    mcmt.Load8(counter, BYTE);

  ASSERT_TRUE(std::memcmp(mcmt.memory,&tmp_buffer, MEM_FIXTURE_MEM_SIZE) == 0);
}

TEST_F(MC_ST_TEST, LOAD16) {
  for (std::size_t i = 0; i < MEM_FIXTURE_MEM_SIZE / 2; ++i, counter += 2)
    mcmt.Load16(counter, WORD);

  ASSERT_TRUE(std::memcmp(mcmt.memory, tmp_buffer, MEM_FIXTURE_MEM_SIZE) == 0);
}

TEST_F(MC_ST_TEST, LOAD32) {
  for (std::size_t i = 0; i < MEM_FIXTURE_MEM_SIZE / 4; ++i, counter += 4)
    mcmt.Load32(counter, DWORD);

  ASSERT_TRUE(std::memcmp(mcmt.memory, tmp_buffer, MEM_FIXTURE_MEM_SIZE) == 0);
}

TEST_F(MC_ST_TEST, LOAD64) {
  for (std::size_t i = 0; i < MEM_FIXTURE_MEM_SIZE / 8; ++i, counter += 8)
    mcmt.Load64(counter, QWORD);

  ASSERT_TRUE(std::memcmp(mcmt.memory, tmp_buffer, MEM_FIXTURE_MEM_SIZE) == 0);
}

TEST_F(MC_ST_TEST, FETCH8) {
  mcmt.Load64(counter, QWORD);

  for (std::size_t i = 0; i < 8; ++i)
    ASSERT_EQ(mcmt.Fetch8(counter), BYTE);
}

TEST_F(MC_ST_TEST, FETCH16) {
  mcmt.Load64(counter, QWORD);

  for (std::size_t i = 0; i < 4; ++i)
    ASSERT_EQ(mcmt.Fetch16(counter), WORD);
}

TEST_F(MC_ST_TEST, FETCH32) {
  mcmt.Load64(counter, QWORD);

  for (std::size_t i = 0; i < 2; ++i)
    ASSERT_EQ(mcmt.Fetch32(counter), DWORD);
}

TEST_F(MC_ST_TEST, FETCH64) {
  mcmt.Load64(counter, QWORD);

  ASSERT_EQ(mcmt.Fetch64(counter), QWORD);
}

TEST_F(MC_ST_TEST, READ8) {
  mcmt.Load64(counter, QWORD);

  for (std::size_t i = 0; i < 8; ++i, ++counter)
    ASSERT_EQ(mcmt.Read8(counter), BYTE);
}

TEST_F(MC_ST_TEST, READ16) {
  mcmt.Load64(counter, QWORD);

  for (std::size_t i = 0; i < 4; ++i, counter += 2)
    ASSERT_EQ(mcmt.Read16(counter), WORD);
}

TEST_F(MC_ST_TEST, READ32) {
  mcmt.Load64(counter, QWORD);

  for (std::size_t i = 0; i < 2; ++i, counter += 4)
    ASSERT_EQ(mcmt.Read32(counter), DWORD);
}

TEST_F(MC_ST_TEST, READ64) {
  mcmt.Load64(counter, QWORD);

  ASSERT_EQ(mcmt.Read64(counter), QWORD);
}

TEST_F(MC_ST_FAILTEST, LOAD8) {
  HCPU_ASSERT_EXIT(mcmt.Load8(counter, BYTE), ::testing::KilledBySignal(SIGABRT), "");
}

TEST_F(MC_ST_FAILTEST, LOAD16) {
  HCPU_ASSERT_EXIT(mcmt.Load16(counter, WORD), ::testing::KilledBySignal(SIGABRT), "");
}

TEST_F(MC_ST_FAILTEST, LOAD32) {
  HCPU_ASSERT_EXIT(mcmt.Load32(counter, DWORD), ::testing::KilledBySignal(SIGABRT), "");
}

TEST_F(MC_ST_FAILTEST, LOAD64) {
  HCPU_ASSERT_EXIT(mcmt.Load64(counter, QWORD), ::testing::KilledBySignal(SIGABRT), "");
}

TEST_F(MC_ST_FAILTEST, FETCH8) {
  HCPU_ASSERT_EXIT(mcmt.Fetch8(counter), ::testing::KilledBySignal(SIGABRT), "");
}

TEST_F(MC_ST_FAILTEST, FETCH16) {
  HCPU_ASSERT_EXIT(mcmt.Fetch16(counter), ::testing::KilledBySignal(SIGABRT), "");
}

TEST_F(MC_ST_FAILTEST, FETCH32) {
  HCPU_ASSERT_EXIT(mcmt.Fetch32(counter), ::testing::KilledBySignal(SIGABRT), "");
}

TEST_F(MC_ST_FAILTEST, FETCH64) {
  HCPU_ASSERT_EXIT(mcmt.Fetch64(counter), ::testing::KilledBySignal(SIGABRT), "");
}

TEST_F(MC_ST_FAILTEST, READ8) {
  HCPU_ASSERT_EXIT(mcmt.Read8(counter), ::testing::KilledBySignal(SIGABRT), "");
}

TEST_F(MC_ST_FAILTEST, READ16) {
  HCPU_ASSERT_EXIT(mcmt.Read16(counter), ::testing::KilledBySignal(SIGABRT), "");
}

TEST_F(MC_ST_FAILTEST, READ32) {
  HCPU_ASSERT_EXIT(mcmt.Read32(counter), ::testing::KilledBySignal(SIGABRT), "");
}

TEST_F(MC_ST_FAILTEST, READ64) {
  HCPU_ASSERT_EXIT(mcmt.Read64(counter), ::testing::KilledBySignal(SIGABRT), "");
}

TEST_F(MC_ST_NEARFAILTEST, LOAD8) {
  counter = 1023;
  ASSERT_EXIT({mcmt.Load8(counter, BYTE); exit(0); }, ::testing::ExitedWithCode(0), "");
  ++counter;
  HCPU_ASSERT_EXIT({mcmt.Load8(counter, BYTE); exit(0); }, ::testing::KilledBySignal(SIGABRT), "");
}

TEST_F(MC_ST_NEARFAILTEST, LOAD16) {
  counter = 1022;
  ASSERT_EXIT({mcmt.Load16(counter, WORD); exit(0); }, ::testing::ExitedWithCode(0), "");
  counter = 1023;
  HCPU_ASSERT_EXIT({mcmt.Load16(counter, WORD); exit(0); }, ::testing::KilledBySignal(SIGABRT), "");
}

TEST_F(MC_ST_NEARFAILTEST, LOAD32) {
  counter = 1020;
  ASSERT_EXIT({mcmt.Load32(counter, DWORD); exit(0); }, ::testing::ExitedWithCode(0), "");
  counter = 1021;
  HCPU_ASSERT_EXIT({mcmt.Load32(counter, DWORD); exit(0); }, ::testing::KilledBySignal(SIGABRT), "");
}

TEST_F(MC_ST_NEARFAILTEST, LOAD64) {
  counter = 1016;
  ASSERT_EXIT({mcmt.Load64(counter, QWORD); exit(0); }, ::testing::ExitedWithCode(0), "");
  counter = 1017;
  HCPU_ASSERT_EXIT({mcmt.Load64(counter, QWORD); exit(0); }, ::testing::KilledBySignal(SIGABRT), "");
}

TEST_F(MC_ST_NEARFAILTEST, FETCH8) {
  counter = 1023;
  ASSERT_EXIT({mcmt.Fetch8(counter); exit(0); }, ::testing::ExitedWithCode(0), "");
  counter = 1024;
  HCPU_ASSERT_EXIT({mcmt.Fetch8(counter); exit(0); }, ::testing::KilledBySignal(SIGABRT), "");
}

TEST_F(MC_ST_NEARFAILTEST, FETCH16) {
  counter = 1022;
  ASSERT_EXIT({mcmt.Fetch16(counter); exit(0); }, ::testing::ExitedWithCode(0), "");
  counter = 1023;
  HCPU_ASSERT_EXIT({mcmt.Fetch16(counter); exit(0); }, ::testing::KilledBySignal(SIGABRT), "");
}

TEST_F(MC_ST_NEARFAILTEST, FETCH32) {
  counter = 1020;
  ASSERT_EXIT({mcmt.Fetch32(counter); exit(0); }, ::testing::ExitedWithCode(0), "");
  counter = 1021;
  HCPU_ASSERT_EXIT({mcmt.Fetch32(counter); exit(0); }, ::testing::KilledBySignal(SIGABRT), "");
}

TEST_F(MC_ST_NEARFAILTEST, FETCH64) {
  counter = 1016;
  ASSERT_EXIT({mcmt.Fetch64(counter); exit(0); }, ::testing::ExitedWithCode(0), "");
  counter = 1017;
  HCPU_ASSERT_EXIT({mcmt.Fetch64(counter); exit(0); }, ::testing::KilledBySignal(SIGABRT), "");
}

TEST_F(MC_ST_NEARFAILTEST, READ8) {
  counter = 1023;
  ASSERT_EXIT({mcmt.Read8(counter); exit(0); }, ::testing::ExitedWithCode(0), "");
  counter = 1024;
  HCPU_ASSERT_EXIT({mcmt.Read8(counter); exit(0); }, ::testing::KilledBySignal(SIGABRT), "");
}

TEST_F(MC_ST_NEARFAILTEST, READ16) {
  counter = 1022;
  ASSERT_EXIT({mcmt.Read16(counter); exit(0); }, ::testing::ExitedWithCode(0), "");
  counter = 1023;
  HCPU_ASSERT_EXIT({mcmt.Read16(counter); exit(0); }, ::testing::KilledBySignal(SIGABRT), "");
}

TEST_F(MC_ST_NEARFAILTEST, READ32) {
  counter = 1020;
  ASSERT_EXIT({mcmt.Read32(counter); exit(0); }, ::testing::ExitedWithCode(0), "");
  counter = 1021;
  HCPU_ASSERT_EXIT({mcmt.Read32(counter); exit(0); }, ::testing::KilledBySignal(SIGABRT), "");
}

TEST_F(MC_ST_NEARFAILTEST, READ64) {
  counter = 1016;
  ASSERT_EXIT({mcmt.Read64(counter); exit(0); }, ::testing::ExitedWithCode(0), "");
  counter = 1017;
  HCPU_ASSERT_EXIT({mcmt.Read64(counter); exit(0); }, ::testing::KilledBySignal(SIGABRT), "");
}