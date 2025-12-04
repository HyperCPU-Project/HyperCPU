#pragma once

#include <vector>

#include "Assembler/Tokenizer/Tokenizer.hpp"
#include "Common/LanguageSpec/Registers.hpp"
#include "hpool.hpp"

namespace HCAsm {
  struct NodeOpRegister;
  struct NodeOpAddr;
  struct Node_b8UImm;
  struct Node_b16UImm;
  struct Node_b32UImm;
  struct Node_b64UImm;
  struct Node_b8SImm;
  struct Node_b16SImm;
  struct Node_b32SImm;
  struct Node_b64SImm;
  struct NodeOperand;
  struct NodeInstruction;
  struct NodeLabel;
  struct NodeStatement;
  struct NodeProgram;

  template<typename T>
  struct PtrType {
    using type = HPool::Ptr<T,
      std::variant<
        NodeOpRegister,
        NodeOpAddr,
        Node_b8UImm,
        Node_b16UImm,
        Node_b32UImm,
        Node_b64UImm,
        Node_b8SImm,
        Node_b16SImm,
        Node_b32SImm,
        Node_b64SImm,
        NodeOperand,
        NodeInstruction,
        NodeLabel,
        NodeStatement,
        NodeProgram>>;
  };

  struct NodeOpRegister {
    HyperCPU::Reg reg;
  };

  struct NodeOpAddr {
    std::variant<HyperCPU::Reg, std::string, std::uint64_t> var;
  };

  struct Node_b8UImm {
    std::uint8_t imm;
  };

  struct Node_b16UImm {
    std::uint16_t imm;
  };

  struct Node_b32UImm {
    std::uint32_t imm;
  };

  struct Node_b64UImm {
    std::uint64_t imm;
  };

  struct Node_b8SImm {
    std::int8_t imm;
  };

  struct Node_b16SImm {
    std::int16_t imm;
  };

  struct Node_b32SImm {
    std::int32_t imm;
  };

  struct Node_b64SImm {
    std::int64_t imm;
  };

  struct NodeOperand {
    std::variant<
      PtrType<NodeOpRegister>::type,
      PtrType<Node_b8UImm>::type,
      PtrType<Node_b16UImm>::type,
      PtrType<Node_b32UImm>::type,
      PtrType<Node_b64UImm>::type,
      PtrType<Node_b8SImm>::type,
      PtrType<Node_b16SImm>::type,
      PtrType<Node_b32SImm>::type,
      PtrType<Node_b64SImm>::type> op;
  };

  struct NodeInstruction {
    TokenType opcode;

  };

  struct NodeLabel {
    Token name;
    bool is_start_label;
  };

  struct NodeStatement {
    std::variant<
      PtrType<NodeInstruction>::type,
      PtrType<NodeLabel>::type> stmt;
  };

  struct NodeProgram {
    std::vector<PtrType<NodeStatement>::type> stmts;
  };

  template<typename T>
  struct Pointer {
  };

  class ASTBuilder {
  public:
    ASTBuilder(std::vector<Token>& tokens) : m_tokens(tokens), pool(128) { }

    NodeProgram ParseProgram();
  private:
    std::vector<Token>& m_tokens;
    PtrType<NodeStatement>::type ParseStatement();
    PtrType<NodeLabel>::type ParseLabel();

    std::optional<Token> TryConsume(TokenType);
    Token Peek(std::uint8_t offset = 0);
    bool TryPeek(TokenType type, std::uint8_t offset = 0); // Is used only to verify if there is a specific token at specific offset
    Token Consume();

    std::uint32_t m_current_token = 0;

    HPool::HPool<
      NodeOpRegister,
      NodeOpAddr,
      Node_b8UImm,
      Node_b16UImm,
      Node_b32UImm,
      Node_b64UImm,
      Node_b8SImm,
      Node_b16SImm,
      Node_b32SImm,
      Node_b64SImm,
      NodeOperand,
      NodeInstruction,
      NodeLabel,
      NodeStatement,
      NodeProgram> pool;
  };
}