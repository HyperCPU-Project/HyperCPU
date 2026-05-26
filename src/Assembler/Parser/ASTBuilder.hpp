#pragma once

#include <vector>

#include "Assembler/Misc.hpp"
#include "Assembler/Tokenizer/Tokenizer.hpp"
#include "Common/LanguageSpec/Registers.hpp"
#include "hpool.hpp"

namespace HCAsm {
  struct NodeOpRegister;
  struct NodeOpAddr;
  struct Node_Addr;
  struct Node_b8UImm;
  struct Node_b16UImm;
  struct Node_b32UImm;
  struct Node_b64UImm;
  struct Node_b8SImm;
  struct Node_b16SImm;
  struct Node_b32SImm;
  struct Node_b64SImm;
  struct Node_Register;
  struct NodeOperand;
  struct NodeInstruction;
  struct NodeLabel;
  struct NodeStatement;
  struct NodeProgram;

  template <typename T>
  struct PtrType {
    using type = HPool::Ptr<T,
                            std::variant<
                                NodeOpRegister,
                                NodeOpAddr,
                                Node_Addr,
                                Node_b8UImm,
                                Node_b16UImm,
                                Node_b32UImm,
                                Node_b64UImm,
                                Node_b8SImm,
                                Node_b16SImm,
                                Node_b32SImm,
                                Node_b64SImm,
                                Node_Register,
                                NodeOperand,
                                NodeInstruction,
                                NodeLabel,
                                NodeStatement,
                                NodeProgram>>;
  };

  template <typename T>
  using PtrTypeT = PtrType<T>::type;

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

  struct Node_Register {
    RegisterType reg;
  };

  struct Node_Addr {
    std::variant<
        PtrTypeT<Node_Register>,
        PtrTypeT<Node_b64UImm>>
        op;
  };

  struct NodeOperand {
    std::variant<
        PtrTypeT<Node_Register>,
        PtrTypeT<Node_Addr>,
        PtrTypeT<Node_b64UImm>,
        PtrTypeT<Node_b64SImm>,
        PtrTypeT<Node_b32UImm>,
        PtrTypeT<Node_b32SImm>,
        PtrTypeT<Node_b16UImm>,
        PtrTypeT<Node_b16SImm>,
        PtrTypeT<Node_b8UImm>,
        PtrTypeT<Node_b8SImm>>
        op;
  };

  struct NodeInstruction {
    TokenType opcode;
    PtrType<NodeOperand>::type operand1, operand2;
  };

  struct NodeLabel {
    Token name;
    bool is_start_label;
  };

  struct NodeStatement {
    std::variant<
        PtrType<NodeInstruction>::type,
        PtrType<NodeLabel>::type>
        stmt;
  };

  struct NodeProgram {
    std::vector<PtrType<NodeStatement>::type> stmts;
  };

  template <typename T>
  struct Pointer {
  };

  class ASTBuilder {
  public:
    ASTBuilder(std::vector<Token>& tokens) : m_tokens(tokens), pool(128) {
    }

    NodeProgram ParseProgram();

  private:
    std::vector<Token>& m_tokens;
    PtrType<NodeStatement>::type ParseStatement();
    PtrType<NodeLabel>::type ParseLabel();
    PtrType<NodeInstruction>::type ParseInstruction();
    PtrType<NodeOperand>::type ParseOperand();

    std::optional<Token> TryConsume(TokenType);
    const Token& Peek(std::uint8_t offset = 0);
    bool TryPeek(TokenType type, std::uint8_t offset = 0); // Is used only to verify if there is a specific token at specific offset
    Token Consume();
    void Skip(int tokens = 1);

    std::uint32_t m_current_token = 0;

    HPool::HPool<
        NodeOpRegister,
        NodeOpAddr,
        Node_Addr,
        Node_b8UImm,
        Node_b16UImm,
        Node_b32UImm,
        Node_b64UImm,
        Node_b8SImm,
        Node_b16SImm,
        Node_b32SImm,
        Node_b64SImm,
        Node_Register,
        NodeOperand,
        NodeInstruction,
        NodeLabel,
        NodeStatement,
        NodeProgram>
        pool;
  };
} // namespace HCAsm
