#include "fixtures.hpp"

TEST_F(ASM_PARSER_STMT_TEST, STMT1) {
  std::string data = "adc x0, x1;";
  HCAsm::CompilerState state(compiler.TransformToIR(data));

  EXPECT_EQ(state.ir.size(), 1);
  EXPECT_EQ(state.labels.size(), 0);

  auto& instr = std::get<HCAsm::Instruction>(state.ir[0]);
  EXPECT_EQ(instr.opcode, HyperCPU::Opcode::ADC);

  EXPECT_EQ(instr.op1.type, HCAsm::OperandType::reg);
  EXPECT_EQ(instr.op1.reg, HyperCPU::Reg::X0);

  EXPECT_EQ(instr.op2.type, HCAsm::OperandType::reg);
  EXPECT_EQ(instr.op2.reg, HyperCPU::Reg::X1);
}

TEST_F(ASM_PARSER_STMT_TEST, STMT2) {
  std::string data = "adc x0;";
  HCAsm::CompilerState state(compiler.TransformToIR(data));

  EXPECT_EQ(state.ir.size(), 1);
  EXPECT_EQ(state.labels.size(), 0);

  auto& instr = std::get<HCAsm::Instruction>(state.ir[0]);
  EXPECT_EQ(instr.opcode, HyperCPU::Opcode::ADC);

  EXPECT_EQ(instr.op1.type, HCAsm::OperandType::reg);
  EXPECT_EQ(instr.op1.reg, HyperCPU::Reg::X0);

  EXPECT_EQ(instr.op2.type, HCAsm::OperandType::none);
}

TEST_F(ASM_PARSER_STMT_TEST, STMT3) {
  std::string data = "adc;";
  HCAsm::CompilerState state(compiler.TransformToIR(data));

  EXPECT_EQ(state.ir.size(), 1);
  EXPECT_EQ(state.labels.size(), 0);

  auto& instr = std::get<HCAsm::Instruction>(state.ir[0]);
  EXPECT_EQ(instr.opcode, HyperCPU::Opcode::ADC);

  EXPECT_EQ(instr.op1.type, HCAsm::OperandType::none);

  EXPECT_EQ(instr.op2.type, HCAsm::OperandType::none);
}

TEST_F(ASM_PARSER_STMT_TEST, LABEL) {
  std::string data = "test:";
  HCAsm::CompilerState state(compiler.TransformToIR(data));

  EXPECT_EQ(state.ir.size(), 1);
  EXPECT_EQ(state.labels.size(), 1);

  EXPECT_EQ(std::get<HCAsm::Label>(state.ir[0]).index, 0);
}

TEST_F(ASM_PARSER_STMT_TEST, LABEL_REFERENCE_RESOLVE) {
  std::string data = "_start:\n\tcall main;\nmain:\n\tintr x0;";
  HCAsm::CompilerState state(compiler.TransformToIR(data));

  auto binary = compiler.TransformToBinary(state);

  EXPECT_EQ(binary.binary[0x03], 0x0B);
}

TEST_F(ASM_PARSER_STMT_TEST, SINGLELINE_COMMENT) {
  std::string data = "_start:\n\tcall main; //comment\nmain:\n\tintr x0;";
  HCAsm::CompilerState state(compiler.TransformToIR(data));

  auto binary = compiler.TransformToBinary(state);

  EXPECT_EQ(binary.binary[0x03], 0x0B);
}

TEST_F(ASM_PARSER_STMT_TEST, MULTILINE_COMMENT) {
  std::string data = "_start:\n\tcall main;/*line 1\nline2*/\nmain:\n\tintr x0;";
  HCAsm::CompilerState state(compiler.TransformToIR(data));

  auto binary = compiler.TransformToBinary(state);

  EXPECT_EQ(binary.binary[0x03], 0x0B);
}
