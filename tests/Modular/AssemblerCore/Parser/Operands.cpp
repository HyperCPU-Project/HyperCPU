#include "fixtures.hpp"

TEST_F(ASM_PARSER_TEST, OPERAND1) {
  std::string data = "[0x15FA]";
  parser.set_start_symbol("operand");

  parser.prepare();

  auto operand = std::get<HCAsm::Operand>(parser.parse(data)->val);

  EXPECT_EQ(operand.type, HCAsm::OperandType::memaddr_int);
  EXPECT_EQ(std::get<std::uint64_t>(operand.variant), static_cast<std::uint64_t>(0x15FA));
}

TEST_F(ASM_PARSER_TEST, OPERAND2) {
  std::string data = "[x0]";
  parser.set_start_symbol("operand");

  parser.prepare();

  auto operand = std::get<HCAsm::Operand>(parser.parse(data)->val);

  EXPECT_EQ(operand.type, HCAsm::OperandType::memaddr_reg);
  EXPECT_EQ(operand.reg, HyperCPU::Reg::X0);
}

TEST_F(ASM_PARSER_TEST, OPERAND3_1) {
  std::string data = "[x0 + 0u15]";
  parser.set_start_symbol("operand");

  parser.prepare();

  auto operand = std::get<HCAsm::Operand>(parser.parse(data)->val);

  EXPECT_EQ(operand.type, HCAsm::OperandType::mem_reg_add_int);
  EXPECT_EQ(operand.reg, HyperCPU::Reg::X0);
  EXPECT_EQ(std::get<std::uint64_t>(operand.variant), static_cast<std::uint64_t>(15));
}

TEST_F(ASM_PARSER_TEST, OPERAND3_2) {
  std::string data = "[x0 + 0x15]";
  parser.set_start_symbol("operand");

  parser.prepare();

  auto operand = std::get<HCAsm::Operand>(parser.parse(data)->val);

  EXPECT_EQ(operand.type, HCAsm::OperandType::mem_reg_add_int);
  EXPECT_EQ(operand.reg, HyperCPU::Reg::X0);
  EXPECT_EQ(std::get<std::uint64_t>(operand.variant), static_cast<std::uint64_t>(0x15));
}

TEST_F(ASM_PARSER_TEST, OPERAND3_3) {
  std::string data = "[x0 + 0b00110101]";
  parser.set_start_symbol("operand");

  parser.prepare();

  auto operand = std::get<HCAsm::Operand>(parser.parse(data)->val);

  EXPECT_EQ(operand.type, HCAsm::OperandType::mem_reg_add_int);
  EXPECT_EQ(operand.reg, HyperCPU::Reg::X0);
  EXPECT_EQ(std::get<std::uint64_t>(operand.variant), static_cast<std::uint64_t>(0b00110101));
}

TEST_F(ASM_PARSER_TEST, OPERAND4) {
  std::string data = "b8 ptr [0x15FA]";
  parser.set_start_symbol("operand");

  parser.prepare();

  auto operand = std::get<HCAsm::Operand>(parser.parse(data)->val);

  EXPECT_EQ(operand.type, HCAsm::OperandType::memaddr_int);
  EXPECT_EQ(operand.mode, HCAsm::Mode::b8);
  EXPECT_EQ(std::get<std::uint64_t>(operand.variant), static_cast<std::uint64_t>(0x15FA));
}

TEST_F(ASM_PARSER_TEST, OPERAND5) {
  std::string data = "b16 ptr [x0]";
  parser.set_start_symbol("operand");

  parser.prepare();

  auto operand = std::get<HCAsm::Operand>(parser.parse(data)->val);

  EXPECT_EQ(operand.type, HCAsm::OperandType::memaddr_reg);
  EXPECT_EQ(operand.mode, HCAsm::Mode::b16);
  EXPECT_EQ(operand.reg, HyperCPU::Reg::X0);
}

TEST_F(ASM_PARSER_TEST, OPERAND6_1) {
  std::string data = "b32 ptr [x0 + 0u15]";
  parser.set_start_symbol("operand");

  parser.prepare();

  auto operand = std::get<HCAsm::Operand>(parser.parse(data)->val);

  EXPECT_EQ(operand.type, HCAsm::OperandType::mem_reg_add_int);
  EXPECT_EQ(operand.reg, HyperCPU::Reg::X0);
  EXPECT_EQ(operand.mode, HCAsm::Mode::b32);
  EXPECT_EQ(std::get<std::uint64_t>(operand.variant), static_cast<std::uint64_t>(15));
}

TEST_F(ASM_PARSER_TEST, OPERAND6_2) {
  std::string data = "b8 ptr [x0 + 0x15]";
  parser.set_start_symbol("operand");

  parser.prepare();

  auto operand = std::get<HCAsm::Operand>(parser.parse(data)->val);

  EXPECT_EQ(operand.type, HCAsm::OperandType::mem_reg_add_int);
  EXPECT_EQ(operand.reg, HyperCPU::Reg::X0);
  EXPECT_EQ(operand.mode, HCAsm::Mode::b8);
  EXPECT_EQ(std::get<std::uint64_t>(operand.variant), static_cast<std::uint64_t>(0x15));
}

TEST_F(ASM_PARSER_TEST, OPERAND6_3) {
  std::string data = "b32 ptr [x0 + 0b00110101]";
  parser.set_start_symbol("operand");

  parser.prepare();

  auto operand = std::get<HCAsm::Operand>(parser.parse(data)->val);

  EXPECT_EQ(operand.type, HCAsm::OperandType::mem_reg_add_int);
  EXPECT_EQ(operand.reg, HyperCPU::Reg::X0);
  EXPECT_EQ(operand.mode, HCAsm::Mode::b32);
  EXPECT_EQ(std::get<std::uint64_t>(operand.variant), static_cast<std::uint64_t>(0b00110101));
}

TEST_F(ASM_PARSER_TEST, OPERAND7) {
  std::string data = "0s15";
  parser.set_start_symbol("operand");

  parser.prepare();

  auto operand = std::get<HCAsm::Operand>(parser.parse(data)->val);

  EXPECT_EQ(operand.type, HCAsm::OperandType::sint);
  EXPECT_EQ(operand.mode, HCAsm::Mode::none);
  EXPECT_EQ(std::get<std::int64_t>(operand.variant), static_cast<std::int64_t>(15));
}

TEST_F(ASM_PARSER_TEST, OPERAND8_1) {
  std::string data = "0u15";
  parser.set_start_symbol("operand");

  parser.prepare();

  auto operand = std::get<HCAsm::Operand>(parser.parse(data)->val);

  EXPECT_EQ(operand.type, HCAsm::OperandType::uint);
  EXPECT_EQ(operand.mode, HCAsm::Mode::none);
  EXPECT_EQ(std::get<std::uint64_t>(operand.variant), static_cast<std::uint64_t>(15));
}

TEST_F(ASM_PARSER_TEST, OPERAND8_2) {
  std::string data = "0x15";
  parser.set_start_symbol("operand");

  parser.prepare();

  auto operand = std::get<HCAsm::Operand>(parser.parse(data)->val);

  EXPECT_EQ(operand.type, HCAsm::OperandType::uint);
  EXPECT_EQ(operand.mode, HCAsm::Mode::none);
  EXPECT_EQ(std::get<std::uint64_t>(operand.variant), static_cast<std::uint64_t>(0x15));
}

TEST_F(ASM_PARSER_TEST, OPERAND8_3) {
  std::string data = "0b00110101";
  parser.set_start_symbol("operand");

  parser.prepare();

  auto operand = std::get<HCAsm::Operand>(parser.parse(data)->val);

  EXPECT_EQ(operand.type, HCAsm::OperandType::uint);
  EXPECT_EQ(operand.mode, HCAsm::Mode::none);
  EXPECT_EQ(std::get<std::uint64_t>(operand.variant), static_cast<std::uint64_t>(0b00110101));
}

TEST_F(ASM_PARSER_TEST, OPERAND8_4) {
  std::string data = "'c'";
  parser.set_start_symbol("operand");

  parser.prepare();

  auto operand = std::get<HCAsm::Operand>(parser.parse(data)->val);

  EXPECT_EQ(operand.type, HCAsm::OperandType::uint);
  EXPECT_EQ(operand.mode, HCAsm::Mode::none);
  EXPECT_EQ(std::get<std::uint64_t>(operand.variant), static_cast<std::uint64_t>('c'));
}

TEST_F(ASM_PARSER_TEST, OPERAND9) {
  std::string data = "x0";
  parser.set_start_symbol("operand");

  parser.prepare();

  auto operand = std::get<HCAsm::Operand>(parser.parse(data)->val);

  EXPECT_EQ(operand.type, HCAsm::OperandType::reg);
  EXPECT_EQ(operand.mode, HCAsm::Mode::b64);
  EXPECT_EQ(operand.reg, HyperCPU::Reg::X0);
}

TEST_F(ASM_PARSER_TEST, OPERAND10) {
  std::string data = "0s15";
  parser.set_start_symbol("operand");

  parser.prepare();

  auto operand = std::get<HCAsm::Operand>(parser.parse(data)->val);

  EXPECT_EQ(operand.type, HCAsm::OperandType::sint);
  EXPECT_EQ(operand.mode, HCAsm::Mode::none);
  EXPECT_EQ(std::get<std::int64_t>(operand.variant), static_cast<std::int64_t>(15));
}

TEST_F(ASM_PARSER_TEST, OPERAND11_1_b8) {
  std::string data = "b8 0u15";
  parser.set_start_symbol("operand");

  parser.prepare();

  auto operand = std::get<HCAsm::Operand>(parser.parse(data)->val);

  EXPECT_EQ(operand.type, HCAsm::OperandType::uint);
  EXPECT_EQ(operand.mode, HCAsm::Mode::b8);
  EXPECT_EQ(std::get<std::uint64_t>(operand.variant), static_cast<std::uint64_t>(15));
}

TEST_F(ASM_PARSER_TEST, OPERAND11_1_b16) {
  std::string data = "b16 0u15";
  parser.set_start_symbol("operand");

  parser.prepare();

  auto operand = std::get<HCAsm::Operand>(parser.parse(data)->val);

  EXPECT_EQ(operand.type, HCAsm::OperandType::uint);
  EXPECT_EQ(operand.mode, HCAsm::Mode::b16);
  EXPECT_EQ(std::get<std::uint64_t>(operand.variant), static_cast<std::uint64_t>(15));
}

TEST_F(ASM_PARSER_TEST, OPERAND11_1_b32) {
  std::string data = "b32 0u15";
  parser.set_start_symbol("operand");

  parser.prepare();

  auto operand = std::get<HCAsm::Operand>(parser.parse(data)->val);

  EXPECT_EQ(operand.type, HCAsm::OperandType::uint);
  EXPECT_EQ(operand.mode, HCAsm::Mode::b32);
  EXPECT_EQ(std::get<std::uint64_t>(operand.variant), static_cast<std::uint64_t>(15));
}

TEST_F(ASM_PARSER_TEST, OPERAND11_1_b64) {
  std::string data = "b64 0u15";
  parser.set_start_symbol("operand");

  parser.prepare();

  auto operand = std::get<HCAsm::Operand>(parser.parse(data)->val);

  EXPECT_EQ(operand.type, HCAsm::OperandType::uint);
  EXPECT_EQ(operand.mode, HCAsm::Mode::b64);
  EXPECT_EQ(std::get<std::uint64_t>(operand.variant), static_cast<std::uint64_t>(15));
}

TEST_F(ASM_PARSER_TEST, OPERAND11_2_b8) {
  std::string data = "b8 0x15";
  parser.set_start_symbol("operand");

  parser.prepare();

  auto operand = std::get<HCAsm::Operand>(parser.parse(data)->val);

  EXPECT_EQ(operand.type, HCAsm::OperandType::uint);
  EXPECT_EQ(operand.mode, HCAsm::Mode::b8);
  EXPECT_EQ(std::get<std::uint64_t>(operand.variant), static_cast<std::uint64_t>(0x15));
}

TEST_F(ASM_PARSER_TEST, OPERAND11_2_b16) {
  std::string data = "b16 0x15";
  parser.set_start_symbol("operand");

  parser.prepare();

  auto operand = std::get<HCAsm::Operand>(parser.parse(data)->val);

  EXPECT_EQ(operand.type, HCAsm::OperandType::uint);
  EXPECT_EQ(operand.mode, HCAsm::Mode::b16);
  EXPECT_EQ(std::get<std::uint64_t>(operand.variant), static_cast<std::uint64_t>(0x15));
}

TEST_F(ASM_PARSER_TEST, OPERAND11_2_b32) {
  std::string data = "b32 0x15";
  parser.set_start_symbol("operand");

  parser.prepare();

  auto operand = std::get<HCAsm::Operand>(parser.parse(data)->val);

  EXPECT_EQ(operand.type, HCAsm::OperandType::uint);
  EXPECT_EQ(operand.mode, HCAsm::Mode::b32);
  EXPECT_EQ(std::get<std::uint64_t>(operand.variant), static_cast<std::uint64_t>(0x15));
}

TEST_F(ASM_PARSER_TEST, OPERAND11_2_b64) {
  std::string data = "b64 0x15";
  parser.set_start_symbol("operand");

  parser.prepare();

  auto operand = std::get<HCAsm::Operand>(parser.parse(data)->val);

  EXPECT_EQ(operand.type, HCAsm::OperandType::uint);
  EXPECT_EQ(operand.mode, HCAsm::Mode::b64);
  EXPECT_EQ(std::get<std::uint64_t>(operand.variant), static_cast<std::uint64_t>(0x15));
}

TEST_F(ASM_PARSER_TEST, OPERAND11_3_b8) {
  std::string data = "b8 0b00110101";
  parser.set_start_symbol("operand");

  parser.prepare();

  auto operand = std::get<HCAsm::Operand>(parser.parse(data)->val);

  EXPECT_EQ(operand.type, HCAsm::OperandType::uint);
  EXPECT_EQ(operand.mode, HCAsm::Mode::b8);
  EXPECT_EQ(std::get<std::uint64_t>(operand.variant), static_cast<std::uint64_t>(0b00110101));
}

TEST_F(ASM_PARSER_TEST, OPERAND11_3_b16) {
  std::string data = "b16 0b00110101";
  parser.set_start_symbol("operand");

  parser.prepare();

  auto operand = std::get<HCAsm::Operand>(parser.parse(data)->val);

  EXPECT_EQ(operand.type, HCAsm::OperandType::uint);
  EXPECT_EQ(operand.mode, HCAsm::Mode::b16);
  EXPECT_EQ(std::get<std::uint64_t>(operand.variant), static_cast<std::uint64_t>(0b00110101));
}

TEST_F(ASM_PARSER_TEST, OPERAND11_3_b32) {
  std::string data = "b32 0b00110101";
  parser.set_start_symbol("operand");

  parser.prepare();

  auto operand = std::get<HCAsm::Operand>(parser.parse(data)->val);

  EXPECT_EQ(operand.type, HCAsm::OperandType::uint);
  EXPECT_EQ(operand.mode, HCAsm::Mode::b32);
  EXPECT_EQ(std::get<std::uint64_t>(operand.variant), static_cast<std::uint64_t>(0b00110101));
}

TEST_F(ASM_PARSER_TEST, OPERAND11_3_b64) {
  std::string data = "b64 0b00110101";
  parser.set_start_symbol("operand");

  parser.prepare();

  auto operand = std::get<HCAsm::Operand>(parser.parse(data)->val);

  EXPECT_EQ(operand.type, HCAsm::OperandType::uint);
  EXPECT_EQ(operand.mode, HCAsm::Mode::b64);
  EXPECT_EQ(std::get<std::uint64_t>(operand.variant), static_cast<std::uint64_t>(0b00110101));
}

TEST_F(ASM_PARSER_TEST, OPERAND11_4_b8) {
  std::string data = "b8 'c'";
  parser.set_start_symbol("operand");

  parser.prepare();

  auto operand = std::get<HCAsm::Operand>(parser.parse(data)->val);

  EXPECT_EQ(operand.type, HCAsm::OperandType::uint);
  EXPECT_EQ(operand.mode, HCAsm::Mode::b8);
  EXPECT_EQ(std::get<std::uint64_t>(operand.variant), static_cast<std::uint64_t>('c'));
}

TEST_F(ASM_PARSER_TEST, OPERAND11_4_b16) {
  std::string data = "b16 'c'";
  parser.set_start_symbol("operand");

  parser.prepare();

  auto operand = std::get<HCAsm::Operand>(parser.parse(data)->val);

  EXPECT_EQ(operand.type, HCAsm::OperandType::uint);
  EXPECT_EQ(operand.mode, HCAsm::Mode::b16);
  EXPECT_EQ(std::get<std::uint64_t>(operand.variant), static_cast<std::uint64_t>('c'));
}

TEST_F(ASM_PARSER_TEST, OPERAND11_4_b32) {
  std::string data = "b32 'c'";
  parser.set_start_symbol("operand");

  parser.prepare();

  auto operand = std::get<HCAsm::Operand>(parser.parse(data)->val);

  EXPECT_EQ(operand.type, HCAsm::OperandType::uint);
  EXPECT_EQ(operand.mode, HCAsm::Mode::b32);
  EXPECT_EQ(std::get<std::uint64_t>(operand.variant), static_cast<std::uint64_t>('c'));
}

TEST_F(ASM_PARSER_TEST, OPERAND11_4_b64) {
  std::string data = "b64 'c'";
  parser.set_start_symbol("operand");

  parser.prepare();

  auto operand = std::get<HCAsm::Operand>(parser.parse(data)->val);

  EXPECT_EQ(operand.type, HCAsm::OperandType::uint);
  EXPECT_EQ(operand.mode, HCAsm::Mode::b64);
  EXPECT_EQ(std::get<std::uint64_t>(operand.variant), static_cast<std::uint64_t>('c'));
}
