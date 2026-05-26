#include "fixtures.hpp"

#include <gtest/gtest.h>
#include <string>
#include <vector>

struct RegisterTestParam {
  std::string src;
  HCAsm::RegisterType expected_reg;
};

class ASMParserRegisterTest : public ::testing::TestWithParam<RegisterTestParam> {
protected:
  void SetUp() override {
    const auto& param = GetParam();
    src = param.src;
    expected_reg = param.expected_reg;
  }

  std::string src;
  HCAsm::RegisterType expected_reg;
};

class ASMParserAddrRegisterTest : public ::testing::TestWithParam<RegisterTestParam> {
protected:
  void SetUp() override {
    const auto& param = GetParam();
    src = param.src;
    expected_reg = param.expected_reg;
  }

  std::string src;
  HCAsm::RegisterType expected_reg;
};

TEST_P(ASMParserRegisterTest, ParseRegister) {
  HCAsm::Tokenizer tokenizer(src);
  auto tokens = tokenizer.Tokenize();
  HCAsm::ASTBuilder builder(tokens);

  auto op = builder.ParseOperand();

  ASSERT_NE(op, nullptr);
  ASSERT_TRUE(std::holds_alternative<HCAsm::PtrTypeT<HCAsm::Node_Register>>(op->op));
  auto reg = std::get<HCAsm::PtrTypeT<HCAsm::Node_Register>>(op->op);
  ASSERT_EQ(reg->reg, expected_reg);
}

TEST_P(ASMParserAddrRegisterTest, ParseAddrRegister) {
  HCAsm::Tokenizer tokenizer(src);
  auto tokens = tokenizer.Tokenize();
  HCAsm::ASTBuilder builder(tokens);

  auto op = builder.ParseOperand();

  ASSERT_NE(op, nullptr);
  ASSERT_TRUE(std::holds_alternative<HCAsm::PtrTypeT<HCAsm::Node_Addr>>(op->op));
  auto addr = std::get<HCAsm::PtrTypeT<HCAsm::Node_Addr>>(op->op);
  ASSERT_TRUE(std::holds_alternative<HCAsm::PtrTypeT<HCAsm::Node_Register>>(addr->op));
  auto reg = std::get<HCAsm::PtrTypeT<HCAsm::Node_Register>>(addr->op);
  ASSERT_EQ(reg->reg, expected_reg);
}

const std::vector<RegisterTestParam> kRegisterParams = {
    {"x0", HCAsm::RegisterType::X0},
    {"x1", HCAsm::RegisterType::X1},
    {"x2", HCAsm::RegisterType::X2},
    {"x3", HCAsm::RegisterType::X3},
    {"x4", HCAsm::RegisterType::X4},
    {"x5", HCAsm::RegisterType::X5},
    {"x6", HCAsm::RegisterType::X6},
    {"x7", HCAsm::RegisterType::X7},
    {"xh0", HCAsm::RegisterType::XH0},
    {"xh1", HCAsm::RegisterType::XH1},
    {"xh2", HCAsm::RegisterType::XH2},
    {"xh3", HCAsm::RegisterType::XH3},
    {"xh4", HCAsm::RegisterType::XH4},
    {"xh5", HCAsm::RegisterType::XH5},
    {"xh6", HCAsm::RegisterType::XH6},
    {"xh7", HCAsm::RegisterType::XH7},
    {"xl0", HCAsm::RegisterType::XL0},
    {"xl1", HCAsm::RegisterType::XL1},
    {"xl2", HCAsm::RegisterType::XL2},
    {"xl3", HCAsm::RegisterType::XL3},
    {"xl4", HCAsm::RegisterType::XL4},
    {"xl5", HCAsm::RegisterType::XL5},
    {"xl6", HCAsm::RegisterType::XL6},
    {"xl7", HCAsm::RegisterType::XL7},
    {"xll0", HCAsm::RegisterType::XLL0},
    {"xll1", HCAsm::RegisterType::XLL1},
    {"xll2", HCAsm::RegisterType::XLL2},
    {"xll3", HCAsm::RegisterType::XLL3},
    {"xllh0", HCAsm::RegisterType::XLLH0},
    {"xllh1", HCAsm::RegisterType::XLLH1},
    {"xllh2", HCAsm::RegisterType::XLLH2},
    {"xllh3", HCAsm::RegisterType::XLLH3},
    {"xlll0", HCAsm::RegisterType::XLLL0},
    {"xlll1", HCAsm::RegisterType::XLLL1},
    {"xlll2", HCAsm::RegisterType::XLLL2},
    {"xlll3", HCAsm::RegisterType::XLLL3},
    {"xbp", HCAsm::RegisterType::XBP},
    {"xsp", HCAsm::RegisterType::XSP},
    {"xip", HCAsm::RegisterType::XIP},
    {"xgdp", HCAsm::RegisterType::XGDP},
    {"xivt", HCAsm::RegisterType::XIVT},
    {"xfst", HCAsm::RegisterType::XFST}};

const std::vector<RegisterTestParam> kAddrRegisterParams = {
    {"[x0]", HCAsm::RegisterType::X0},
    {"[x1]", HCAsm::RegisterType::X1},
    {"[x2]", HCAsm::RegisterType::X2},
    {"[x3]", HCAsm::RegisterType::X3},
    {"[x4]", HCAsm::RegisterType::X4},
    {"[x5]", HCAsm::RegisterType::X5},
    {"[x6]", HCAsm::RegisterType::X6},
    {"[x7]", HCAsm::RegisterType::X7},
    {"[xh0]", HCAsm::RegisterType::XH0},
    {"[xh1]", HCAsm::RegisterType::XH1},
    {"[xh2]", HCAsm::RegisterType::XH2},
    {"[xh3]", HCAsm::RegisterType::XH3},
    {"[xh4]", HCAsm::RegisterType::XH4},
    {"[xh5]", HCAsm::RegisterType::XH5},
    {"[xh6]", HCAsm::RegisterType::XH6},
    {"[xh7]", HCAsm::RegisterType::XH7},
    {"[xl0]", HCAsm::RegisterType::XL0},
    {"[xl1]", HCAsm::RegisterType::XL1},
    {"[xl2]", HCAsm::RegisterType::XL2},
    {"[xl3]", HCAsm::RegisterType::XL3},
    {"[xl4]", HCAsm::RegisterType::XL4},
    {"[xl5]", HCAsm::RegisterType::XL5},
    {"[xl6]", HCAsm::RegisterType::XL6},
    {"[xl7]", HCAsm::RegisterType::XL7},
    {"[xll0]", HCAsm::RegisterType::XLL0},
    {"[xll1]", HCAsm::RegisterType::XLL1},
    {"[xll2]", HCAsm::RegisterType::XLL2},
    {"[xll3]", HCAsm::RegisterType::XLL3},
    {"[xllh0]", HCAsm::RegisterType::XLLH0},
    {"[xllh1]", HCAsm::RegisterType::XLLH1},
    {"[xllh2]", HCAsm::RegisterType::XLLH2},
    {"[xllh3]", HCAsm::RegisterType::XLLH3},
    {"[xlll0]", HCAsm::RegisterType::XLLL0},
    {"[xlll1]", HCAsm::RegisterType::XLLL1},
    {"[xlll2]", HCAsm::RegisterType::XLLL2},
    {"[xlll3]", HCAsm::RegisterType::XLLL3},
    {"[xbp]", HCAsm::RegisterType::XBP},
    {"[xsp]", HCAsm::RegisterType::XSP},
    {"[xip]", HCAsm::RegisterType::XIP},
    {"[xgdp]", HCAsm::RegisterType::XGDP},
    {"[xivt]", HCAsm::RegisterType::XIVT},
    {"[xfst]", HCAsm::RegisterType::XFST}};

INSTANTIATE_TEST_SUITE_P(
    AllRegisters,
    ASMParserRegisterTest,
    ::testing::ValuesIn(kRegisterParams));

INSTANTIATE_TEST_SUITE_P(
    AllAddrRegisters,
    ASMParserAddrRegisterTest,
    ::testing::ValuesIn(kAddrRegisterParams));

TEST(ASMParserAddrImmTest, ParseAddrImmHex) {
  std::string src = "[0x45]";
  HCAsm::Tokenizer tokenizer(src);
  auto tokens = tokenizer.Tokenize();
  HCAsm::ASTBuilder builder(tokens);

  auto op = builder.ParseOperand();

  ASSERT_NE(op, nullptr);
  ASSERT_TRUE(std::holds_alternative<HCAsm::PtrTypeT<HCAsm::Node_Addr>>(op->op));
  auto addr = std::get<HCAsm::PtrTypeT<HCAsm::Node_Addr>>(op->op);
  ASSERT_TRUE(std::holds_alternative<HCAsm::PtrTypeT<HCAsm::Node_b64UImm>>(addr->op));
  auto uint = std::get<HCAsm::PtrTypeT<HCAsm::Node_b64UImm>>(addr->op);
  ASSERT_EQ(uint->imm, 69);
}

TEST(ASMParserAddrImmTest, ParseAddrImmUint) {
  std::string src = "[0u69]";
  HCAsm::Tokenizer tokenizer(src);
  auto tokens = tokenizer.Tokenize();
  HCAsm::ASTBuilder builder(tokens);

  auto op = builder.ParseOperand();

  ASSERT_NE(op, nullptr);
  ASSERT_TRUE(std::holds_alternative<HCAsm::PtrTypeT<HCAsm::Node_Addr>>(op->op));
  auto addr = std::get<HCAsm::PtrTypeT<HCAsm::Node_Addr>>(op->op);
  ASSERT_TRUE(std::holds_alternative<HCAsm::PtrTypeT<HCAsm::Node_b64UImm>>(addr->op));
  auto uint = std::get<HCAsm::PtrTypeT<HCAsm::Node_b64UImm>>(addr->op);
  ASSERT_EQ(uint->imm, 69);
}

TEST(ASMParserImmTest, ParseImmUintb8) {
  std::string src = "b8 0u69";
  HCAsm::Tokenizer tokenizer(src);
  auto tokens = tokenizer.Tokenize();
  HCAsm::ASTBuilder builder(tokens);

  auto op = builder.ParseOperand();

  ASSERT_NE(op, nullptr);
  ASSERT_TRUE(std::holds_alternative<HCAsm::PtrTypeT<HCAsm::Node_b8UImm>>(op->op));
  auto uint = std::get<HCAsm::PtrTypeT<HCAsm::Node_b8UImm>>(op->op);
  ASSERT_EQ(uint->imm, 69);
}

TEST(ASMParserImmTest, ParseImmUintb16) {
  std::string src = "b16 0u12345";
  HCAsm::Tokenizer tokenizer(src);
  auto tokens = tokenizer.Tokenize();
  HCAsm::ASTBuilder builder(tokens);

  auto op = builder.ParseOperand();

  ASSERT_NE(op, nullptr);
  ASSERT_TRUE(std::holds_alternative<HCAsm::PtrTypeT<HCAsm::Node_b16UImm>>(op->op));
  auto uint = std::get<HCAsm::PtrTypeT<HCAsm::Node_b16UImm>>(op->op);
  ASSERT_EQ(uint->imm, 12345);
}

TEST(ASMParserImmTest, ParseImmUintb32) {
  std::string src = "b32 0u987654321";
  HCAsm::Tokenizer tokenizer(src);
  auto tokens = tokenizer.Tokenize();
  HCAsm::ASTBuilder builder(tokens);

  auto op = builder.ParseOperand();

  ASSERT_NE(op, nullptr);
  ASSERT_TRUE(std::holds_alternative<HCAsm::PtrTypeT<HCAsm::Node_b32UImm>>(op->op));
  auto uint = std::get<HCAsm::PtrTypeT<HCAsm::Node_b32UImm>>(op->op);
  ASSERT_EQ(uint->imm, 987654321);
}

TEST(ASMParserImmTest, ParseImmUintb64) {
  std::string src = "b64 0u18446744073709551615";
  HCAsm::Tokenizer tokenizer(src);
  auto tokens = tokenizer.Tokenize();
  HCAsm::ASTBuilder builder(tokens);

  auto op = builder.ParseOperand();

  ASSERT_NE(op, nullptr);
  ASSERT_TRUE(std::holds_alternative<HCAsm::PtrTypeT<HCAsm::Node_b64UImm>>(op->op));
  auto uint = std::get<HCAsm::PtrTypeT<HCAsm::Node_b64UImm>>(op->op);
  ASSERT_EQ(uint->imm, 18446744073709551615ULL);
}

TEST(ASMParserImmTest, ParseImmSintb8) {
  std::string src = "b8 0s-69";
  HCAsm::Tokenizer tokenizer(src);
  auto tokens = tokenizer.Tokenize();
  HCAsm::ASTBuilder builder(tokens);

  auto op = builder.ParseOperand();

  ASSERT_NE(op, nullptr);
  ASSERT_TRUE(std::holds_alternative<HCAsm::PtrTypeT<HCAsm::Node_b8SImm>>(op->op));
  auto sint = std::get<HCAsm::PtrTypeT<HCAsm::Node_b8SImm>>(op->op);
  ASSERT_EQ(sint->imm, -69);
}

TEST(ASMParserImmTest, ParseImmSintb16) {
  std::string src = "b16 0s-12345";
  HCAsm::Tokenizer tokenizer(src);
  auto tokens = tokenizer.Tokenize();
  HCAsm::ASTBuilder builder(tokens);

  auto op = builder.ParseOperand();

  ASSERT_NE(op, nullptr);
  ASSERT_TRUE(std::holds_alternative<HCAsm::PtrTypeT<HCAsm::Node_b16SImm>>(op->op));
  auto sint = std::get<HCAsm::PtrTypeT<HCAsm::Node_b16SImm>>(op->op);
  ASSERT_EQ(sint->imm, -12345);
}

TEST(ASMParserImmTest, ParseImmSintb32) {
  std::string src = "b32 0s-987654321";
  HCAsm::Tokenizer tokenizer(src);
  auto tokens = tokenizer.Tokenize();
  HCAsm::ASTBuilder builder(tokens);

  auto op = builder.ParseOperand();

  ASSERT_NE(op, nullptr);
  ASSERT_TRUE(std::holds_alternative<HCAsm::PtrTypeT<HCAsm::Node_b32SImm>>(op->op));
  auto sint = std::get<HCAsm::PtrTypeT<HCAsm::Node_b32SImm>>(op->op);
  ASSERT_EQ(sint->imm, -987654321);
}

TEST(ASMParserImmTest, ParseImmSintb64) {
  std::string src = "b64 0s-9223372036854775807";
  HCAsm::Tokenizer tokenizer(src);
  auto tokens = tokenizer.Tokenize();
  HCAsm::ASTBuilder builder(tokens);

  auto op = builder.ParseOperand();

  ASSERT_NE(op, nullptr);
  ASSERT_TRUE(std::holds_alternative<HCAsm::PtrTypeT<HCAsm::Node_b64SImm>>(op->op));
  auto sint = std::get<HCAsm::PtrTypeT<HCAsm::Node_b64SImm>>(op->op);
  ASSERT_EQ(sint->imm, -9223372036854775807LL);
}