#include "ASTBuilder.hpp"

HCAsm::NodeProgram HCAsm::ASTBuilder::ParseProgram() {
  NodeProgram prog;

  while (true) {
    auto stmt = ParseStatement();
    if (!stmt) {
      break;
    }
    prog.stmts.push_back(stmt.value());
  }

  return prog;
}

std::optional<HCAsm::NodeStatement*> HCAsm::ASTBuilder::ParseStatement() {

}

std::optional<HCAsm::NodeLabel*> HCAsm::ASTBuilder::ParseLabel() {
  if (TryPeek(TokenType::DOT) &&
      TryPeek(TokenType::ATTR, 1) &&
      TryPeek(TokenType::OPEN_PARENTHESIS, 2) &&
      TryPeek(TokenType::IDENTIFIER, 3) &&
      TryPeek(TokenType::CLOSE_PARENTHESIS, 4) &&
      TryPeek(TokenType::IDENTIFIER, 5) &&
      TryPeek(TokenType::COLON, 6)) {
    Consume();
    Consume();
    Consume();
    auto attr = Consume();
  }
}

std::optional<HCAsm::Token> HCAsm::ASTBuilder::TryConsume(TokenType type) {
  if (Peek().type == type) {
    return Consume();
  }
  return std::nullopt;
}

HCAsm::Token HCAsm::ASTBuilder::Peek(std::uint8_t offset) {
  return m_tokens[m_current_token + offset];
}

bool HCAsm::ASTBuilder::TryPeek(TokenType type, std::uint8_t offset) {
  return !(m_current_token + offset >= m_tokens.size() || m_tokens[m_current_token + offset].type != type);
}


HCAsm::Token HCAsm::ASTBuilder::Consume() {
  return m_tokens[m_current_token++];
}
