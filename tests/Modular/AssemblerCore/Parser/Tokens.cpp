#include "fixtures.hpp"

TEST_F(ASM_PARSER_TEST, TOKEN_STRING) {
  std::string str = "this is a string to test parser\\n\\r\\\"\\\'\\a\\\\";
  std::string data = fmt::format("\"{}\" \\", str);

  // Token, created only for testing
  parser.token("\\\\")
      .symbol("\\");

  parser.set_start_symbol("string_test");
  parser.rule("string_test")
      .production("string", "\\", [](pog::Parser<HCAsm::Value>&, std::vector<pog::TokenWithLineSpec<HCAsm::Value>> args) -> HCAsm::Value {
        return std::move(args[0].value);
      });

  parser.prepare();

  EXPECT_EQ(std::get<std::string>(parser.parse(data).value().val), "this is a string to test parser\n\r\"\'a\\");
}

TEST_F(ASM_PARSER_TEST, TOKEN_SINT) {
  std::string data = "0s1234 \\";

  // Token, created only for testing
  parser.token("\\\\")
      .symbol("\\");

  parser.set_start_symbol("sint_test");
  parser.rule("sint_test")
      .production("sint", "\\", [](pog::Parser<HCAsm::Value>&, std::vector<pog::TokenWithLineSpec<HCAsm::Value>> args) -> HCAsm::Value {
        return std::move(args[0].value);
      });

  parser.prepare();

  EXPECT_EQ(std::get<std::int64_t>(parser.parse(data).value().val), static_cast<std::int64_t>(1234));
}

TEST_F(ASM_PARSER_TEST, TOKEN_UINT) {
  std::string data = "0u1234 \\";

  // Token, created only for testing
  parser.token("\\\\")
      .symbol("\\");

  parser.set_start_symbol("uint_test");
  parser.rule("uint_test")
      .production("uint", "\\", [](pog::Parser<HCAsm::Value>&, std::vector<pog::TokenWithLineSpec<HCAsm::Value>> args) -> HCAsm::Value {
        return std::move(args[0].value);
      });

  parser.prepare();

  EXPECT_EQ(std::get<std::uint64_t>(parser.parse(data).value().val), static_cast<std::uint64_t>(1234));
}

TEST_F(ASM_PARSER_TEST, TOKEN_HEX) {
  std::string data = "0x15FA \\";

  // Token, created only for testing
  parser.token("\\\\")
      .symbol("\\");

  parser.set_start_symbol("hex_test");
  parser.rule("hex_test")
      .production("hex", "\\", [](pog::Parser<HCAsm::Value>&, std::vector<pog::TokenWithLineSpec<HCAsm::Value>> args) -> HCAsm::Value {
        return std::move(args[0].value);
      });

  parser.prepare();

  EXPECT_EQ(std::get<std::uint64_t>(parser.parse(data).value().val), static_cast<std::uint64_t>(0x15FA));
}

TEST_F(ASM_PARSER_TEST, TOKEN_BINARY) {
  std::string data = "0b0001010111111010 \\";

  // Token, created only for testing
  parser.token("\\\\")
      .symbol("\\");

  parser.set_start_symbol("binary_test");
  parser.rule("binary_test")
      .production("binary", "\\", [](pog::Parser<HCAsm::Value>&, std::vector<pog::TokenWithLineSpec<HCAsm::Value>> args) -> HCAsm::Value {
        return std::move(args[0].value);
      });

  parser.prepare();

  EXPECT_EQ(std::get<std::uint64_t>(parser.parse(data).value().val), static_cast<std::uint64_t>(0b0001010111111010));
}

TEST_F(ASM_PARSER_TEST, TOKEN_CHAR) {
  std::string data = "'c' \\";

  // Token, created only for testing
  parser.token("\\\\")
      .symbol("\\");

  parser.set_start_symbol("char_test");
  parser.rule("char_test")
      .production("char", "\\", [](pog::Parser<HCAsm::Value>&, std::vector<pog::TokenWithLineSpec<HCAsm::Value>> args) -> HCAsm::Value {
        return std::move(args[0].value);
      });

  parser.prepare();

  EXPECT_EQ(std::get<std::uint64_t>(parser.parse(data).value().val), static_cast<std::uint64_t>('c'));
}
