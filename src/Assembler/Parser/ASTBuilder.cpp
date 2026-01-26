#include "ASTBuilder.hpp"

HCAsm::NodeProgram HCAsm::ASTBuilder::ParseProgram() {
  NodeProgram prog;

  while (true) {
    auto stmt = ParseStatement();
    if (!stmt) {
      break;
    }
    prog.stmts.push_back(stmt);
  }

  return prog;
}

HCAsm::PtrType<HCAsm::NodeStatement>::type HCAsm::ASTBuilder::ParseStatement() {
  if (auto label = ParseLabel()) {
    NodeStatement stmt = {
      std::move(label)
    };
    return pool.allocate<NodeStatement>(std::move(stmt));
  }
  return PtrType<NodeStatement>::type{nullptr};
}

HCAsm::PtrType<HCAsm::NodeLabel>::type HCAsm::ASTBuilder::ParseLabel() {
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
    Consume();
    auto label = Consume();
    Consume();
    NodeLabel lbl = {
      .name=std::move(label),
      .is_start_label=attr.lexeme == "entry"
    };
    return pool.allocate<NodeLabel>(std::move(lbl));
  }

  if (TryPeek(TokenType::IDENTIFIER) &&
      TryPeek(TokenType::COLON, 1)) {
    auto label = Consume();
    Consume();
    NodeLabel lbl = {
      .name = std::move(label),
      .is_start_label = false
    };
    return pool.allocate<NodeLabel>(std::move(lbl));
  }

  return PtrType<NodeLabel>::type{nullptr};
}

HCAsm::PtrType<HCAsm::NodeInstruction>::type HCAsm::ASTBuilder::ParseInstruction() {

}

HCAsm::PtrType<HCAsm::NodeOperand>::type HCAsm::ASTBuilder::ParseOperand() {
  const Token& tok = Peek();
  if (static_cast<std::uint16_t>(tok.type) >= static_cast<std::uint16_t>(TokenType::X0) &&
      static_cast<std::uint16_t>(tok.type) <= static_cast<std::uint16_t>(TokenType::XFST))
  {
    auto reg = pool.allocate<Node_Register>();
    reg->reg = static_cast<RegisterType>(tok.type);
    auto op = pool.allocate<NodeOperand>();
    op->op = reg;
    return op;
  } else
}

std::optional<HCAsm::Token> HCAsm::ASTBuilder::TryConsume(TokenType type) {
  if (Peek().type == type) {
    return Consume();
  }
  return std::nullopt;
}

const HCAsm::Token& HCAsm::ASTBuilder::Peek(std::uint8_t offset) {
  return m_tokens.at(m_current_token + offset);
}

bool HCAsm::ASTBuilder::TryPeek(TokenType type, std::uint8_t offset) {
  return !(m_current_token + offset >= m_tokens.size() || m_tokens[m_current_token + offset].type != type);
}


HCAsm::Token HCAsm::ASTBuilder::Consume() {
  return m_tokens[m_current_token++];
}
