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

  // Parse regular register, like: x0
  if (static_cast<std::uint16_t>(tok.type) >= static_cast<std::uint16_t>(TokenType::X0) &&
      static_cast<std::uint16_t>(tok.type) <= static_cast<std::uint16_t>(TokenType::XFST))
  {
    auto reg = pool.allocate<Node_Register>();
    reg->reg = static_cast<RegisterType>(tok.type);
    auto op = pool.allocate<NodeOperand>();
    op->op = reg;
    Skip();
    return op;
  }

  // Parse register like address, like: [x0]
  if (tok.type == TokenType::OPEN_BRACKET &&
    static_cast<std::uint16_t>(Peek(1).type) >= static_cast<std::uint16_t>(TokenType::X0) &&
    static_cast<std::uint16_t>(Peek(1).type) <= static_cast<std::uint16_t>(TokenType::XFST) &&
    Peek(2).type == TokenType::CLOSE_BRACKET) {
    auto reg = pool.allocate<Node_Register>();
    reg->reg = static_cast<RegisterType>(Peek(1).type);
    auto addr_reg = pool.allocate<Node_Addr>();
    addr_reg->op = reg;
    auto op = pool.allocate<NodeOperand>();
    op->op = addr_reg;
    Skip(3);
    return op;
  }

  // Parse imm value like address, like: [0x0]
  if (tok.type == TokenType::OPEN_BRACKET &&
    Peek(1).type == TokenType::UINT_LITERAL &&
    Peek(2).type == TokenType::CLOSE_BRACKET) {
    auto uint = pool.allocate<Node_b64UImm>();
    uint->imm = std::stoull(Peek(1).lexeme);
    auto addr = pool.allocate<Node_Addr>();
    addr->op = uint;
    auto op = pool.allocate<NodeOperand>();
    op->op = addr;
    Skip(3);
    return op;
  }
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

void HCAsm::ASTBuilder::Skip(int tokens) {
  m_current_token += tokens;
}