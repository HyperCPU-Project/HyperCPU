#include "fixtures.hpp"

TEST(ASM_PARSER_STMT_TEST, ParseLabelNoAttributes) {
  std::string src = "lbl:";
  HCAsm::Tokenizer tokenizer(src);
  auto tokens = tokenizer.Tokenize();
  HCAsm::ASTBuilder builder(tokens);

  auto ast = builder.ParseProgram();


}