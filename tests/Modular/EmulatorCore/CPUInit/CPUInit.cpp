#include "fixtures.hpp"

static constexpr std::uint64_t FULL_CONST = 0x0001020304050607;
static constexpr std::uint32_t CONSTH = 0x00010203;
static constexpr std::uint32_t CONSTL = 0x04050607;
static constexpr std::uint16_t CONSTLL = 0x0607;
static constexpr std::uint8_t CONSTLLH = 0x06;
static constexpr std::uint8_t CONSTLLL = 0x07;

TEST(cpu_init, REGS_ARE_INITIALIZED) {
  HyperCPU::CPU cpu{1, 4096};
  for (std::size_t i = 0; i < 13; ++i)
    cpu.data[i] = FULL_CONST;

  ASSERT_EQ(*cpu.x0, FULL_CONST);
  ASSERT_EQ(*cpu.x1, FULL_CONST);
  ASSERT_EQ(*cpu.x2, FULL_CONST);
  ASSERT_EQ(*cpu.x3, FULL_CONST);
  ASSERT_EQ(*cpu.x4, FULL_CONST);
  ASSERT_EQ(*cpu.x5, FULL_CONST);
  ASSERT_EQ(*cpu.x6, FULL_CONST);
  ASSERT_EQ(*cpu.x7, FULL_CONST);

  ASSERT_EQ(*cpu.xh0, CONSTH);
  ASSERT_EQ(*cpu.xh1, CONSTH);
  ASSERT_EQ(*cpu.xh2, CONSTH);
  ASSERT_EQ(*cpu.xh3, CONSTH);
  ASSERT_EQ(*cpu.xh4, CONSTH);
  ASSERT_EQ(*cpu.xh5, CONSTH);
  ASSERT_EQ(*cpu.xh6, CONSTH);
  ASSERT_EQ(*cpu.xh7, CONSTH);

  ASSERT_EQ(*cpu.xl0, CONSTL);
  ASSERT_EQ(*cpu.xl1, CONSTL);
  ASSERT_EQ(*cpu.xl2, CONSTL);
  ASSERT_EQ(*cpu.xl3, CONSTL);
  ASSERT_EQ(*cpu.xl4, CONSTL);
  ASSERT_EQ(*cpu.xl5, CONSTL);
  ASSERT_EQ(*cpu.xl6, CONSTL);
  ASSERT_EQ(*cpu.xl7, CONSTL);

  ASSERT_EQ(*cpu.xll0, CONSTLL);
  ASSERT_EQ(*cpu.xll1, CONSTLL);
  ASSERT_EQ(*cpu.xll2, CONSTLL);
  ASSERT_EQ(*cpu.xll3, CONSTLL);

  ASSERT_EQ(*cpu.xllh0, CONSTLLH);
  ASSERT_EQ(*cpu.xllh1, CONSTLLH);
  ASSERT_EQ(*cpu.xllh2, CONSTLLH);
  ASSERT_EQ(*cpu.xllh3, CONSTLLH);

  ASSERT_EQ(*cpu.xlll0, CONSTLLL);
  ASSERT_EQ(*cpu.xlll1, CONSTLLL);
  ASSERT_EQ(*cpu.xlll2, CONSTLLL);
  ASSERT_EQ(*cpu.xlll3, CONSTLLL);
}
