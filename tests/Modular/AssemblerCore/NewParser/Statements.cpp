#include "fixtures.hpp"

TEST(ASM_PARSER_STMT_TEST, ParseLabelNoAttributes) {
  std::string src = "lbl:";
  HCAsm::Tokenizer tokenizer(src);
  auto tokens = tokenizer.Tokenize();
  HCAsm::ASTBuilder builder(tokens);

  auto ast = builder.ParseProgram();

  ASSERT_EQ(ast.stmts.size(), 1);
  ASSERT_TRUE(std::holds_alternative<HCAsm::PtrType<HCAsm::NodeLabel>::type>(ast.stmts[0]->stmt));
  auto lbl = *std::get<HCAsm::PtrType<HCAsm::NodeLabel>::type>(ast.stmts[0]->stmt);
  ASSERT_FALSE(lbl.is_start_label);
  ASSERT_EQ(lbl.name.lexeme, "lbl");
}

TEST(ASM_PARSER_STMT_TEST, ParseLabelStartAttribute) {
  std::string src = ".attr(entry) lbl:";
  HCAsm::Tokenizer tokenizer(src);
  auto tokens = tokenizer.Tokenize();
  HCAsm::ASTBuilder builder(tokens);

  auto ast = builder.ParseProgram();

  ASSERT_EQ(ast.stmts.size(), 1);
  ASSERT_TRUE(std::holds_alternative<HCAsm::PtrType<HCAsm::NodeLabel>::type>(ast.stmts[0]->stmt));
  auto lbl = *std::get<HCAsm::PtrType<HCAsm::NodeLabel>::type>(ast.stmts[0]->stmt);
  ASSERT_TRUE(lbl.is_start_label);
  ASSERT_EQ(lbl.name.lexeme, "lbl");
}