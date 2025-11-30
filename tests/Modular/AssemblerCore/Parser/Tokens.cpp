#include <stdexcept>
#include "gtest/gtest.h"

#define private public
#include "Assembler/Tokenizer/Tokenizer.hpp"

// Single-character token tests
TEST(Tokenizer, SemicolonToken) {
  std::string test{";"};
  HCAsm::Tokenizer tokenizer(test);
  ASSERT_EQ(tokenizer.GetNextToken().type, HCAsm::TokenType::SEMICOLON);
}

TEST(Tokenizer, ColonToken) {
  std::string test{":"};
  HCAsm::Tokenizer tokenizer(test);
  ASSERT_EQ(tokenizer.GetNextToken().type, HCAsm::TokenType::COLON);
}

TEST(Tokenizer, OpenParenthesisToken) {
  std::string test{"("};
  HCAsm::Tokenizer tokenizer(test);
  ASSERT_EQ(tokenizer.GetNextToken().type, HCAsm::TokenType::OPEN_PARENTHESIS);
}

TEST(Tokenizer, CloseParenthesisToken) {
  std::string test{")"};
  HCAsm::Tokenizer tokenizer(test);
  ASSERT_EQ(tokenizer.GetNextToken().type, HCAsm::TokenType::CLOSE_PARENTHESIS);
}

TEST(Tokenizer, BackslashToken) {
  std::string test{"\\"};
  HCAsm::Tokenizer tokenizer(test);
  ASSERT_EQ(tokenizer.GetNextToken().type, HCAsm::TokenType::BACKSLASH);
}

TEST(Tokenizer, DotToken) {
  std::string test{"."};
  HCAsm::Tokenizer tokenizer(test);
  ASSERT_EQ(tokenizer.GetNextToken().type, HCAsm::TokenType::DOT);
}

TEST(Tokenizer, CommaToken) {
  std::string test{","};
  HCAsm::Tokenizer tokenizer(test);
  ASSERT_EQ(tokenizer.GetNextToken().type, HCAsm::TokenType::COMMA);
}

TEST(Tokenizer, EqualToken) {
  std::string test{"="};
  HCAsm::Tokenizer tokenizer(test);
  ASSERT_EQ(tokenizer.GetNextToken().type, HCAsm::TokenType::EQUAL);
}

TEST(Tokenizer, EndOfFileToken) {
  std::string test{""};
  HCAsm::Tokenizer tokenizer(test);
  ASSERT_EQ(tokenizer.GetNextToken().type, HCAsm::TokenType::END_OF_FILE);
}

// Instruction token tests (without whitespace)
TEST(Tokenizer, AdcToken) {
  std::string test{"adc"};
  HCAsm::Tokenizer tokenizer(test);
  ASSERT_EQ(tokenizer.GetNextToken().type, HCAsm::TokenType::ADC);
}

TEST(Tokenizer, AddToken) {
  std::string test{"add"};
  HCAsm::Tokenizer tokenizer(test);
  ASSERT_EQ(tokenizer.GetNextToken().type, HCAsm::TokenType::ADD);
}

TEST(Tokenizer, AndToken) {
  std::string test{"and"};
  HCAsm::Tokenizer tokenizer(test);
  ASSERT_EQ(tokenizer.GetNextToken().type, HCAsm::TokenType::AND);
}

TEST(Tokenizer, AndnToken) {
  std::string test{"andn"};
  HCAsm::Tokenizer tokenizer(test);
  ASSERT_EQ(tokenizer.GetNextToken().type, HCAsm::TokenType::ANDN);
}

TEST(Tokenizer, BswapToken) {
  std::string test{"bswap"};
  HCAsm::Tokenizer tokenizer(test);
  ASSERT_EQ(tokenizer.GetNextToken().type, HCAsm::TokenType::BSWAP);
}

TEST(Tokenizer, CallToken) {
  std::string test{"call"};
  HCAsm::Tokenizer tokenizer(test);
  ASSERT_EQ(tokenizer.GetNextToken().type, HCAsm::TokenType::CALL);
}

TEST(Tokenizer, CcrfToken) {
  std::string test{"ccrf"};
  HCAsm::Tokenizer tokenizer(test);
  ASSERT_EQ(tokenizer.GetNextToken().type, HCAsm::TokenType::CCRF);
}

TEST(Tokenizer, CovfToken) {
  std::string test{"covf"};
  HCAsm::Tokenizer tokenizer(test);
  ASSERT_EQ(tokenizer.GetNextToken().type, HCAsm::TokenType::COVF);
}

TEST(Tokenizer, CudfToken) {
  std::string test{"cudf"};
  HCAsm::Tokenizer tokenizer(test);
  ASSERT_EQ(tokenizer.GetNextToken().type, HCAsm::TokenType::CUDF);
}

TEST(Tokenizer, HidToken) {
  std::string test{"hid"};
  HCAsm::Tokenizer tokenizer(test);
  ASSERT_EQ(tokenizer.GetNextToken().type, HCAsm::TokenType::HID);
}

TEST(Tokenizer, IncToken) {
  std::string test{"inc"};
  HCAsm::Tokenizer tokenizer(test);
  ASSERT_EQ(tokenizer.GetNextToken().type, HCAsm::TokenType::INC);
}

TEST(Tokenizer, DecToken) {
  std::string test{"dec"};
  HCAsm::Tokenizer tokenizer(test);
  ASSERT_EQ(tokenizer.GetNextToken().type, HCAsm::TokenType::DEC);
}

TEST(Tokenizer, DivToken) {
  std::string test{"div"};
  HCAsm::Tokenizer tokenizer(test);
  ASSERT_EQ(tokenizer.GetNextToken().type, HCAsm::TokenType::DIV);
}

TEST(Tokenizer, MulToken) {
  std::string test{"mul"};
  HCAsm::Tokenizer tokenizer(test);
  ASSERT_EQ(tokenizer.GetNextToken().type, HCAsm::TokenType::MUL);
}

TEST(Tokenizer, SubToken) {
  std::string test{"sub"};
  HCAsm::Tokenizer tokenizer(test);
  ASSERT_EQ(tokenizer.GetNextToken().type, HCAsm::TokenType::SUB);
}

TEST(Tokenizer, ShfrToken) {
  std::string test{"shfr"};
  HCAsm::Tokenizer tokenizer(test);
  ASSERT_EQ(tokenizer.GetNextToken().type, HCAsm::TokenType::SHFR);
}

TEST(Tokenizer, ShflToken) {
  std:: string test{"shfl"};
  HCAsm::Tokenizer tokenizer(test);
  ASSERT_EQ(tokenizer.GetNextToken().type, HCAsm::TokenType::SHFL);
}

TEST(Tokenizer, OrToken) {
  std::string test{"or"};
  HCAsm::Tokenizer tokenizer(test);
  ASSERT_EQ(tokenizer.GetNextToken().type, HCAsm::TokenType::OR);
}

TEST(Tokenizer, HaltToken) {
  std::string test{"halt"};
  HCAsm::Tokenizer tokenizer(test);
  ASSERT_EQ(tokenizer.GetNextToken().type, HCAsm::TokenType::HALT);
}

TEST(Tokenizer, LoivtToken) {
  std::string test{"loivt"};
  HCAsm::Tokenizer tokenizer(test);
  ASSERT_EQ(tokenizer.GetNextToken().type, HCAsm::TokenType::LOIVT);
}

TEST(Tokenizer, IntrToken) {
  std::string test{"intr"};
  HCAsm::Tokenizer tokenizer(test);
  ASSERT_EQ(tokenizer.GetNextToken().type, HCAsm::TokenType::INTR);
}

TEST(Tokenizer, IretToken) {
  std::string test{"iret"};
  HCAsm::Tokenizer tokenizer(test);
  ASSERT_EQ(tokenizer.GetNextToken().type, HCAsm::TokenType::IRET);
}

TEST(Tokenizer, MovToken) {
  std::string test{"mov"};
  HCAsm::Tokenizer tokenizer(test);
  ASSERT_EQ(tokenizer.GetNextToken().type, HCAsm::TokenType::MOV);
}

TEST(Tokenizer, ReadToken) {
  std::string test{"read"};
  HCAsm::Tokenizer tokenizer(test);
  ASSERT_EQ(tokenizer.GetNextToken().type, HCAsm::TokenType::READ);
}

TEST(Tokenizer, WriteToken) {
  std::string test{"write"};
  HCAsm::Tokenizer tokenizer(test);
  ASSERT_EQ(tokenizer.GetNextToken().type, HCAsm::TokenType::WRITE);
}

TEST(Tokenizer, JmpToken) {
  std::string test{"jmp"};
  HCAsm::Tokenizer tokenizer(test);
  ASSERT_EQ(tokenizer.GetNextToken().type, HCAsm::TokenType::JMP);
}

TEST(Tokenizer, PushToken) {
  std::string test{"push"};
  HCAsm::Tokenizer tokenizer(test);
  ASSERT_EQ(tokenizer.GetNextToken().type, HCAsm::TokenType::PUSH);
}

TEST(Tokenizer, PopToken) {
  std::string test{"pop"};
  HCAsm::Tokenizer tokenizer(test);
  ASSERT_EQ(tokenizer.GetNextToken().type, HCAsm::TokenType::POP);
}

TEST(Tokenizer, CalleToken) {
  std::string test{"calle"};
  HCAsm::Tokenizer tokenizer(test);
  ASSERT_EQ(tokenizer.GetNextToken().type, HCAsm::TokenType::CALLE);
}

TEST(Tokenizer, CallgrToken) {
  std::string test{"callgr"};
  HCAsm::Tokenizer tokenizer(test);
  ASSERT_EQ(tokenizer.GetNextToken().type, HCAsm::TokenType::CALLGR);
}

TEST(Tokenizer, CalllToken) {
  std::string test{"calll"};
  HCAsm::Tokenizer tokenizer(test);
  ASSERT_EQ(tokenizer.GetNextToken().type, HCAsm::TokenType::CALLL);
}

TEST(Tokenizer, JmeToken) {
  std::string test{"jme"};
  HCAsm::Tokenizer tokenizer(test);
  ASSERT_EQ(tokenizer.GetNextToken().type, HCAsm::TokenType::JME);
}

TEST(Tokenizer, JmgrToken) {
  std::string test{"jmgr"};
  HCAsm::Tokenizer tokenizer(test);
  ASSERT_EQ(tokenizer.GetNextToken().type, HCAsm::TokenType::JMGR);
}

TEST(Tokenizer, JmlToken) {
  std::string test{"jml"};
  HCAsm::Tokenizer tokenizer(test);
  ASSERT_EQ(tokenizer.GetNextToken().type, HCAsm::TokenType::JML);
}

TEST(Tokenizer, CmpToken) {
  std::string test{"cmp"};
  HCAsm::Tokenizer tokenizer(test);
  ASSERT_EQ(tokenizer.GetNextToken().type, HCAsm::TokenType::CMP);
}

TEST(Tokenizer, LodsbToken) {
  std::string test{"lodsb"};
  HCAsm::Tokenizer tokenizer(test);
  ASSERT_EQ(tokenizer.GetNextToken().type, HCAsm::TokenType::LODSB);
}

TEST(Tokenizer, StdsbToken) {
  std::string test{"stdsb"};
  HCAsm::Tokenizer tokenizer(test);
  ASSERT_EQ(tokenizer.GetNextToken().type, HCAsm::TokenType::STDSB);
}

// Keyword token tests (without whitespace)
TEST(Tokenizer, AttrToken) {
  std::string test{"attr"};
  HCAsm::Tokenizer tokenizer(test);
  ASSERT_EQ(tokenizer.GetNextToken().type, HCAsm::TokenType::ATTR);
}

TEST(Tokenizer, AttrEntryToken) {
  std::string test{"entry"};
  HCAsm::Tokenizer tokenizer(test);
  ASSERT_EQ(tokenizer.GetNextToken().type, HCAsm::TokenType::IDENTIFIER);
}

// Instruction/keyword tests with whitespace
TEST(Tokenizer, MovToken_WithWhitespace) {
  std::string test{"   \n\tmov"};
  HCAsm::Tokenizer tokenizer(test);
  ASSERT_EQ(tokenizer.GetNextToken().type, HCAsm::TokenType::MOV);
}

TEST(Tokenizer, AttrToken_WithWhitespace) {
  std::string test{"   \n\tattr"};
  HCAsm::Tokenizer tokenizer(test);
  ASSERT_EQ(tokenizer.GetNextToken().type, HCAsm::TokenType::ATTR);
}

// Literal tests
TEST(Tokenizer, StringLit) {
  std::string test{"\"test\""};
  HCAsm::Tokenizer tokenizer(test);
  auto tok = tokenizer.GetNextToken();
  ASSERT_EQ(tok.type, HCAsm::TokenType::STRING_LITERAL);
  ASSERT_EQ(tok.lexeme, "test");
}

TEST(Tokenizer, StringLit_WithWhitespace) {
  std::string test{"   \n\t\"test\""};
  HCAsm::Tokenizer tokenizer(test);
  auto tok = tokenizer.GetNextToken();
  ASSERT_EQ(tok.type, HCAsm::TokenType::STRING_LITERAL);
  ASSERT_EQ(tok.lexeme, "test");
}

TEST(Tokenizer, IntLit) {
  std::string test{"42069"};
  HCAsm::Tokenizer tokenizer(test);
  auto tok = tokenizer.GetNextToken();
  ASSERT_EQ(tok.type, HCAsm::TokenType::INT_LITERAL);
  ASSERT_EQ(tok.lexeme, "42069");
}

TEST(Tokenizer, IntLit_WithWhitespace) {
  std::string test{"   \n\t42069"};
  HCAsm::Tokenizer tokenizer(test);
  auto tok = tokenizer.GetNextToken();
  ASSERT_EQ(tok.type, HCAsm::TokenType::INT_LITERAL);
  ASSERT_EQ(tok.lexeme, "42069");
}

TEST(Tokenizer, UIntLit) {
  std::string test{"42069u"};
  HCAsm::Tokenizer tokenizer(test);
  auto tok = tokenizer.GetNextToken();
  ASSERT_EQ(tok.type, HCAsm::TokenType::INT_LITERAL);
  ASSERT_EQ(tok.lexeme, "42069u");
}

TEST(Tokenizer, FloatLit) {
  std::string test{"420.69"};
  HCAsm::Tokenizer tokenizer(test);
  auto tok = tokenizer.GetNextToken();
  ASSERT_EQ(tok.type, HCAsm::TokenType::FLOAT_LITERAL);
  ASSERT_EQ(tok.lexeme, "420.69");
}

TEST(Tokenizer, FloatLit_WithWhitespace) {
  std::string test{"   \n\t420.69"};
  HCAsm::Tokenizer tokenizer(test);
  auto tok = tokenizer.GetNextToken();
  ASSERT_EQ(tok.type, HCAsm::TokenType::FLOAT_LITERAL);
  ASSERT_EQ(tok.lexeme, "420.69");
}

TEST(Tokenizer, FloatLitMultipleDots) {
  std::string test{"420.6.9"};
  HCAsm::Tokenizer tokenizer(test);
  ASSERT_THROW({
    try {
      tokenizer.GetNextToken();
    } catch (std::runtime_error& err) {
      ASSERT_STREQ(err.what(), "Multiple dots in a float literal");
      throw;
    }
  }, std::runtime_error);
}

// Identifier test (unknown token)
TEST(Tokenizer, UnknownIdentifier) {
  std::string test{"unknown_token"};
  HCAsm::Tokenizer tokenizer(test);
  auto tok = tokenizer.GetNextToken();
  ASSERT_EQ(tok.type, HCAsm::TokenType::IDENTIFIER);
  ASSERT_EQ(tok.lexeme, "unknown_token");
}