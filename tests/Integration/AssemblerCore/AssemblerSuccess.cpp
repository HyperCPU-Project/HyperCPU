#include "fixtures.hpp"

TEST_F(ASSEMBLER, ASM_R_R_b8) {
  std::string data = "mov xlll0, xlll1;";
  auto state(compiler.TransformToIR(data));

  auto binary = compiler.TransformToBinary(state);

  std::uint16_t opcode;
  std::uint8_t flags;
  std::uint8_t reg1;
  std::uint8_t reg2;

  std::memcpy(&opcode, binary.binary, sizeof(std::uint16_t));
  std::memcpy(&flags, binary.binary + 2, sizeof(std::uint8_t));
  std::memcpy(&reg1, binary.binary + 3, sizeof(std::uint8_t));
  std::memcpy(&reg2, binary.binary + 4, sizeof(std::uint8_t));

  EXPECT_EQ(static_cast<HyperCPU::Opcode>(opcode), HyperCPU::Opcode::MOV);

  EXPECT_EQ(flags & 0b11000000, 0);
  EXPECT_EQ(static_cast<HyperCPU::Mode>((flags & 0b00110000) >> 4), HyperCPU::Mode::b8);
  EXPECT_EQ(static_cast<HyperCPU::OperandTypes>(flags & 0b00001111), HyperCPU::OperandTypes::R_R);
  EXPECT_EQ(static_cast<HyperCPU::Reg>(reg1), HyperCPU::Reg::XLLL0);
  EXPECT_EQ(static_cast<HyperCPU::Reg>(reg2), HyperCPU::Reg::XLLL1);
}

TEST_F(ASSEMBLER, ASM_R_R_b16) {
  std::string data = "mov xll0, xll1;";

  auto state(compiler.TransformToIR(data));

  auto binary = compiler.TransformToBinary(state);

  std::uint16_t opcode;
  std::uint8_t flags;
  std::uint8_t reg1;
  std::uint8_t reg2;

  std::memcpy(&opcode, binary.binary, sizeof(std::uint16_t));
  std::memcpy(&flags, binary.binary + 2, sizeof(std::uint8_t));
  std::memcpy(&reg1, binary.binary + 3, sizeof(std::uint8_t));
  std::memcpy(&reg2, binary.binary + 4, sizeof(std::uint8_t));

  EXPECT_EQ(static_cast<HyperCPU::Opcode>(opcode), HyperCPU::Opcode::MOV);

  EXPECT_EQ(flags & 0b11000000, 0);
  EXPECT_EQ(static_cast<HyperCPU::Mode>((flags & 0b00110000) >> 4), HyperCPU::Mode::b16);
  EXPECT_EQ(static_cast<HyperCPU::OperandTypes>(flags & 0b00001111), HyperCPU::OperandTypes::R_R);
  EXPECT_EQ(static_cast<HyperCPU::Reg>(reg1), HyperCPU::Reg::XLL0);
  EXPECT_EQ(static_cast<HyperCPU::Reg>(reg2), HyperCPU::Reg::XLL1);
}

TEST_F(ASSEMBLER, ASM_R_R_b32) {
  std::string data = "mov xl0, xl1;";

  auto state(compiler.TransformToIR(data));

  auto binary = compiler.TransformToBinary(state);

  std::uint16_t opcode;
  std::uint8_t flags;
  std::uint8_t reg1;
  std::uint8_t reg2;

  std::memcpy(&opcode, binary.binary, sizeof(std::uint16_t));
  std::memcpy(&flags, binary.binary + 2, sizeof(std::uint8_t));
  std::memcpy(&reg1, binary.binary + 3, sizeof(std::uint8_t));
  std::memcpy(&reg2, binary.binary + 4, sizeof(std::uint8_t));

  EXPECT_EQ(static_cast<HyperCPU::Opcode>(opcode), HyperCPU::Opcode::MOV);

  EXPECT_EQ(flags & 0b11000000, 0);
  EXPECT_EQ(static_cast<HyperCPU::Mode>((flags & 0b00110000) >> 4), HyperCPU::Mode::b32);
  EXPECT_EQ(static_cast<HyperCPU::OperandTypes>(flags & 0b00001111), HyperCPU::OperandTypes::R_R);
  EXPECT_EQ(static_cast<HyperCPU::Reg>(reg1), HyperCPU::Reg::XL0);
  EXPECT_EQ(static_cast<HyperCPU::Reg>(reg2), HyperCPU::Reg::XL1);
}

TEST_F(ASSEMBLER, ASM_R_R_b64) {
  std::string data = "mov x0, x1;";

  auto state(compiler.TransformToIR(data));

  auto binary = compiler.TransformToBinary(state);

  std::uint16_t opcode;
  std::uint8_t flags;
  std::uint8_t reg1;
  std::uint8_t reg2;

  std::memcpy(&opcode, binary.binary, sizeof(std::uint16_t));
  std::memcpy(&flags, binary.binary + 2, sizeof(std::uint8_t));
  std::memcpy(&reg1, binary.binary + 3, sizeof(std::uint8_t));
  std::memcpy(&reg2, binary.binary + 4, sizeof(std::uint8_t));

  EXPECT_EQ(static_cast<HyperCPU::Opcode>(opcode), HyperCPU::Opcode::MOV);

  EXPECT_EQ(flags & 0b11000000, 0);
  EXPECT_EQ(static_cast<HyperCPU::Mode>((flags & 0b00110000) >> 4), HyperCPU::Mode::b64);
  EXPECT_EQ(static_cast<HyperCPU::OperandTypes>(flags & 0b00001111), HyperCPU::OperandTypes::R_R);
  EXPECT_EQ(static_cast<HyperCPU::Reg>(reg1), HyperCPU::Reg::X0);
  EXPECT_EQ(static_cast<HyperCPU::Reg>(reg2), HyperCPU::Reg::X1);
}

TEST_F(ASSEMBLER, ASM_R_RM_b8) {
  std::string data = "mov xlll0, [x1];";

  auto state(compiler.TransformToIR(data));

  auto binary = compiler.TransformToBinary(state);

  std::uint16_t opcode;
  std::uint8_t flags;
  std::uint8_t reg1;
  std::uint8_t reg2;

  std::memcpy(&opcode, binary.binary, sizeof(std::uint16_t));
  std::memcpy(&flags, binary.binary + 2, sizeof(std::uint8_t));
  std::memcpy(&reg1, binary.binary + 3, sizeof(std::uint8_t));
  std::memcpy(&reg2, binary.binary + 4, sizeof(std::uint8_t));

  EXPECT_EQ(static_cast<HyperCPU::Opcode>(opcode), HyperCPU::Opcode::MOV);

  EXPECT_EQ(flags & 0b11000000, 0);
  EXPECT_EQ(static_cast<HyperCPU::Mode>((flags & 0b00110000) >> 4), HyperCPU::Mode::b8);
  EXPECT_EQ(static_cast<HyperCPU::OperandTypes>(flags & 0b00001111), HyperCPU::OperandTypes::R_RM);
  EXPECT_EQ(static_cast<HyperCPU::Reg>(reg1), HyperCPU::Reg::XLLL0);
  EXPECT_EQ(static_cast<HyperCPU::Reg>(reg2), HyperCPU::Reg::X1);
}

TEST_F(ASSEMBLER, ASM_R_RM_b16) {
  std::string data = "mov xll0, [x1];";

  auto state(compiler.TransformToIR(data));

  auto binary = compiler.TransformToBinary(state);

  std::uint16_t opcode;
  std::uint8_t flags;
  std::uint8_t reg1;
  std::uint8_t reg2;

  std::memcpy(&opcode, binary.binary, sizeof(std::uint16_t));
  std::memcpy(&flags, binary.binary + 2, sizeof(std::uint8_t));
  std::memcpy(&reg1, binary.binary + 3, sizeof(std::uint8_t));
  std::memcpy(&reg2, binary.binary + 4, sizeof(std::uint8_t));

  EXPECT_EQ(static_cast<HyperCPU::Opcode>(opcode), HyperCPU::Opcode::MOV);

  EXPECT_EQ(flags & 0b11000000, 0);
  EXPECT_EQ(static_cast<HyperCPU::Mode>((flags & 0b00110000) >> 4), HyperCPU::Mode::b16);
  EXPECT_EQ(static_cast<HyperCPU::OperandTypes>(flags & 0b00001111), HyperCPU::OperandTypes::R_RM);
  EXPECT_EQ(static_cast<HyperCPU::Reg>(reg1), HyperCPU::Reg::XLL0);
  EXPECT_EQ(static_cast<HyperCPU::Reg>(reg2), HyperCPU::Reg::X1);
}

TEST_F(ASSEMBLER, ASM_R_RM_b32) {
  std::string data = "mov xl0, [x1];";

  auto state(compiler.TransformToIR(data));

  auto binary = compiler.TransformToBinary(state);

  std::uint16_t opcode;
  std::uint8_t flags;
  std::uint8_t reg1;
  std::uint8_t reg2;

  std::memcpy(&opcode, binary.binary, sizeof(std::uint16_t));
  std::memcpy(&flags, binary.binary + 2, sizeof(std::uint8_t));
  std::memcpy(&reg1, binary.binary + 3, sizeof(std::uint8_t));
  std::memcpy(&reg2, binary.binary + 4, sizeof(std::uint8_t));

  EXPECT_EQ(static_cast<HyperCPU::Opcode>(opcode), HyperCPU::Opcode::MOV);

  EXPECT_EQ(flags & 0b11000000, 0);
  EXPECT_EQ(static_cast<HyperCPU::Mode>((flags & 0b00110000) >> 4), HyperCPU::Mode::b32);
  EXPECT_EQ(static_cast<HyperCPU::OperandTypes>(flags & 0b00001111), HyperCPU::OperandTypes::R_RM);
  EXPECT_EQ(static_cast<HyperCPU::Reg>(reg1), HyperCPU::Reg::XL0);
  EXPECT_EQ(static_cast<HyperCPU::Reg>(reg2), HyperCPU::Reg::X1);
}

TEST_F(ASSEMBLER, ASM_R_RM_b64) {
  std::string data = "mov x0, [x1];";

  auto state(compiler.TransformToIR(data));

  auto binary = compiler.TransformToBinary(state);

  std::uint16_t opcode;
  std::uint8_t flags;
  std::uint8_t reg1;
  std::uint8_t reg2;

  std::memcpy(&opcode, binary.binary, sizeof(std::uint16_t));
  std::memcpy(&flags, binary.binary + 2, sizeof(std::uint8_t));
  std::memcpy(&reg1, binary.binary + 3, sizeof(std::uint8_t));
  std::memcpy(&reg2, binary.binary + 4, sizeof(std::uint8_t));

  EXPECT_EQ(static_cast<HyperCPU::Opcode>(opcode), HyperCPU::Opcode::MOV);

  EXPECT_EQ(flags & 0b11000000, 0);
  EXPECT_EQ(static_cast<HyperCPU::Mode>((flags & 0b00110000) >> 4), HyperCPU::Mode::b64);
  EXPECT_EQ(static_cast<HyperCPU::OperandTypes>(flags & 0b00001111), HyperCPU::OperandTypes::R_RM);
  EXPECT_EQ(static_cast<HyperCPU::Reg>(reg1), HyperCPU::Reg::X0);
  EXPECT_EQ(static_cast<HyperCPU::Reg>(reg2), HyperCPU::Reg::X1);
}

TEST_F(ASSEMBLER, ASM_R_M_b8) {
  std::string data = "mov xlll0, [0x0];";

  auto state(compiler.TransformToIR(data));

  auto binary = compiler.TransformToBinary(state);

  std::uint16_t opcode;
  std::uint8_t flags;
  std::uint64_t addr;
  std::uint8_t reg;

  std::memcpy(&opcode, binary.binary, sizeof(std::uint16_t));
  std::memcpy(&flags, binary.binary + 2, sizeof(std::uint8_t));
  std::memcpy(&reg, binary.binary + 3, sizeof(std::uint8_t));
  std::memcpy(&addr, binary.binary + 4, sizeof(std::uint64_t));

  EXPECT_EQ(static_cast<HyperCPU::Opcode>(opcode), HyperCPU::Opcode::MOV);

  EXPECT_EQ(flags & 0b11000000, 0);
  EXPECT_EQ(static_cast<HyperCPU::Mode>((flags & 0b00110000) >> 4), HyperCPU::Mode::b8);
  EXPECT_EQ(static_cast<HyperCPU::OperandTypes>(flags & 0b00001111), HyperCPU::OperandTypes::R_M);
  EXPECT_EQ(addr, 0);
  EXPECT_EQ(static_cast<HyperCPU::Reg>(reg), HyperCPU::Reg::XLLL0);
}

TEST_F(ASSEMBLER, ASM_R_M_b16) {
  std::string data = "mov xll0, [0x0];";

  auto state(compiler.TransformToIR(data));

  auto binary = compiler.TransformToBinary(state);

  std::uint16_t opcode;
  std::uint8_t flags;
  std::uint64_t addr;
  std::uint8_t reg;

  std::memcpy(&opcode, binary.binary, sizeof(std::uint16_t));
  std::memcpy(&flags, binary.binary + 2, sizeof(std::uint8_t));
  std::memcpy(&reg, binary.binary + 3, sizeof(std::uint8_t));
  std::memcpy(&addr, binary.binary + 4, sizeof(std::uint64_t));

  EXPECT_EQ(static_cast<HyperCPU::Opcode>(opcode), HyperCPU::Opcode::MOV);

  EXPECT_EQ(flags & 0b11000000, 0);
  EXPECT_EQ(static_cast<HyperCPU::Mode>((flags & 0b00110000) >> 4), HyperCPU::Mode::b16);
  EXPECT_EQ(static_cast<HyperCPU::OperandTypes>(flags & 0b00001111), HyperCPU::OperandTypes::R_M);
  EXPECT_EQ(addr, 0);
  EXPECT_EQ(static_cast<HyperCPU::Reg>(reg), HyperCPU::Reg::XLL0);
}

TEST_F(ASSEMBLER, ASM_R_M_b32) {
  std::string data = "mov xl0, [0x0];";

  auto state(compiler.TransformToIR(data));

  auto binary = compiler.TransformToBinary(state);

  std::uint16_t opcode;
  std::uint8_t flags;
  std::uint64_t addr;
  std::uint8_t reg;

  std::memcpy(&opcode, binary.binary, sizeof(std::uint16_t));
  std::memcpy(&flags, binary.binary + 2, sizeof(std::uint8_t));
  std::memcpy(&reg, binary.binary + 3, sizeof(std::uint8_t));
  std::memcpy(&addr, binary.binary + 4, sizeof(std::uint64_t));

  EXPECT_EQ(static_cast<HyperCPU::Opcode>(opcode), HyperCPU::Opcode::MOV);

  EXPECT_EQ(flags & 0b11000000, 0);
  EXPECT_EQ(static_cast<HyperCPU::Mode>((flags & 0b00110000) >> 4), HyperCPU::Mode::b32);
  EXPECT_EQ(static_cast<HyperCPU::OperandTypes>(flags & 0b00001111), HyperCPU::OperandTypes::R_M);
  EXPECT_EQ(addr, 0);
  EXPECT_EQ(static_cast<HyperCPU::Reg>(reg), HyperCPU::Reg::XL0);
}

TEST_F(ASSEMBLER, ASM_R_M_b64) {
  std::string data = "mov x0, [0x0];";

  auto state(compiler.TransformToIR(data));

  auto binary = compiler.TransformToBinary(state);

  std::uint16_t opcode;
  std::uint8_t flags;
  std::uint64_t addr;
  std::uint8_t reg;

  std::memcpy(&opcode, binary.binary, sizeof(std::uint16_t));
  std::memcpy(&flags, binary.binary + 2, sizeof(std::uint8_t));
  std::memcpy(&reg, binary.binary + 3, sizeof(std::uint8_t));
  std::memcpy(&addr, binary.binary + 4, sizeof(std::uint64_t));

  EXPECT_EQ(static_cast<HyperCPU::Opcode>(opcode), HyperCPU::Opcode::MOV);

  EXPECT_EQ(flags & 0b11000000, 0);
  EXPECT_EQ(static_cast<HyperCPU::Mode>((flags & 0b00110000) >> 4), HyperCPU::Mode::b64);
  EXPECT_EQ(static_cast<HyperCPU::OperandTypes>(flags & 0b00001111), HyperCPU::OperandTypes::R_M);
  EXPECT_EQ(addr, 0);
  EXPECT_EQ(static_cast<HyperCPU::Reg>(reg), HyperCPU::Reg::X0);
}

TEST_F(ASSEMBLER, ASM_R_IMM_b8) {
  std::string data = "mov xlll0, 0u16;";

  auto state(compiler.TransformToIR(data));

  auto binary = compiler.TransformToBinary(state);

  std::uint16_t opcode;
  std::uint8_t flags;
  std::uint8_t num;
  std::uint8_t reg;

  std::memcpy(&opcode, binary.binary, sizeof(std::uint16_t));
  std::memcpy(&flags, binary.binary + 2, sizeof(std::uint8_t));
  std::memcpy(&reg, binary.binary + 3, sizeof(std::uint8_t));
  std::memcpy(&num, binary.binary + 4, sizeof(std::uint8_t));

  EXPECT_EQ(static_cast<HyperCPU::Opcode>(opcode), HyperCPU::Opcode::MOV);

  EXPECT_EQ(flags & 0b11000000, 0);
  EXPECT_EQ(static_cast<HyperCPU::Mode>((flags & 0b00110000) >> 4), HyperCPU::Mode::b8);
  EXPECT_EQ(static_cast<HyperCPU::OperandTypes>(flags & 0b00001111), HyperCPU::OperandTypes::R_IMM);
  EXPECT_EQ(num, 16);
  EXPECT_EQ(static_cast<HyperCPU::Reg>(reg), HyperCPU::Reg::XLLL0);
}

TEST_F(ASSEMBLER, ASM_R_IMM_b16) {
  std::string data = "mov xll0, 0u16;";

  auto state(compiler.TransformToIR(data));

  auto binary = compiler.TransformToBinary(state);

  std::uint16_t opcode;
  std::uint8_t flags;
  std::uint16_t num;
  std::uint8_t reg;

  std::memcpy(&opcode, binary.binary, sizeof(std::uint16_t));
  std::memcpy(&flags, binary.binary + 2, sizeof(std::uint8_t));
  std::memcpy(&reg, binary.binary + 3, sizeof(std::uint8_t));
  std::memcpy(&num, binary.binary + 4, sizeof(std::uint16_t));

  EXPECT_EQ(static_cast<HyperCPU::Opcode>(opcode), HyperCPU::Opcode::MOV);

  EXPECT_EQ(flags & 0b11000000, 0);
  EXPECT_EQ(static_cast<HyperCPU::Mode>((flags & 0b00110000) >> 4), HyperCPU::Mode::b16);
  EXPECT_EQ(static_cast<HyperCPU::OperandTypes>(flags & 0b00001111), HyperCPU::OperandTypes::R_IMM);
  EXPECT_EQ(num, 16);
  EXPECT_EQ(static_cast<HyperCPU::Reg>(reg), HyperCPU::Reg::XLL0);
}

TEST_F(ASSEMBLER, ASM_R_IMM_b32) {
  std::string data = "mov xl0, 0u16;";

  auto state(compiler.TransformToIR(data));

  auto binary = compiler.TransformToBinary(state);

  std::uint16_t opcode;
  std::uint8_t flags;
  std::uint32_t num;
  std::uint8_t reg;

  std::memcpy(&opcode, binary.binary, sizeof(std::uint16_t));
  std::memcpy(&flags, binary.binary + 2, sizeof(std::uint8_t));
  std::memcpy(&reg, binary.binary + 3, sizeof(std::uint8_t));
  std::memcpy(&num, binary.binary + 4, sizeof(std::uint32_t));

  EXPECT_EQ(static_cast<HyperCPU::Opcode>(opcode), HyperCPU::Opcode::MOV);

  EXPECT_EQ(flags & 0b11000000, 0);
  EXPECT_EQ(static_cast<HyperCPU::Mode>((flags & 0b00110000) >> 4), HyperCPU::Mode::b32);
  EXPECT_EQ(static_cast<HyperCPU::OperandTypes>(flags & 0b00001111), HyperCPU::OperandTypes::R_IMM);
  EXPECT_EQ(num, 16);
  EXPECT_EQ(static_cast<HyperCPU::Reg>(reg), HyperCPU::Reg::XL0);
}

TEST_F(ASSEMBLER, ASM_R_IMM_b64) {
  std::string data = "mov x0, 0u16;";

  auto state(compiler.TransformToIR(data));

  auto binary = compiler.TransformToBinary(state);

  std::uint16_t opcode;
  std::uint8_t flags;
  std::uint64_t num;
  std::uint8_t reg;

  std::memcpy(&opcode, binary.binary, sizeof(std::uint16_t));
  std::memcpy(&flags, binary.binary + 2, sizeof(std::uint8_t));
  std::memcpy(&reg, binary.binary + 3, sizeof(std::uint8_t));
  std::memcpy(&num, binary.binary + 4, sizeof(std::uint64_t));

  EXPECT_EQ(static_cast<HyperCPU::Opcode>(opcode), HyperCPU::Opcode::MOV);

  EXPECT_EQ(flags & 0b11000000, 0);
  EXPECT_EQ(static_cast<HyperCPU::Mode>((flags & 0b00110000) >> 4), HyperCPU::Mode::b64);
  EXPECT_EQ(static_cast<HyperCPU::OperandTypes>(flags & 0b00001111), HyperCPU::OperandTypes::R_IMM);
  EXPECT_EQ(num, 16);
  EXPECT_EQ(static_cast<HyperCPU::Reg>(reg), HyperCPU::Reg::X0);
}

TEST_F(ASSEMBLER, ASM_RM_R_b8) {
  std::string data = "mov [x0], xlll1;";

  auto state(compiler.TransformToIR(data));

  auto binary = compiler.TransformToBinary(state);

  std::uint16_t opcode;
  std::uint8_t flags;
  std::uint8_t reg1;
  std::uint8_t reg2;

  std::memcpy(&opcode, binary.binary, sizeof(std::uint16_t));
  std::memcpy(&flags, binary.binary + 2, sizeof(std::uint8_t));
  std::memcpy(&reg1, binary.binary + 3, sizeof(std::uint8_t));
  std::memcpy(&reg2, binary.binary + 4, sizeof(std::uint8_t));

  EXPECT_EQ(static_cast<HyperCPU::Opcode>(opcode), HyperCPU::Opcode::MOV);

  EXPECT_EQ(flags & 0b11000000, 0);
  EXPECT_EQ(static_cast<HyperCPU::Mode>((flags & 0b00110000) >> 4), HyperCPU::Mode::b8);
  EXPECT_EQ(static_cast<HyperCPU::OperandTypes>(flags & 0b00001111), HyperCPU::OperandTypes::RM_R);
  EXPECT_EQ(static_cast<HyperCPU::Reg>(reg1), HyperCPU::Reg::X0);
  EXPECT_EQ(static_cast<HyperCPU::Reg>(reg2), HyperCPU::Reg::XLLL1);
}

TEST_F(ASSEMBLER, ASM_RM_R_b16) {
  std::string data = "mov [x0], xll1;";

  auto state(compiler.TransformToIR(data));

  auto binary = compiler.TransformToBinary(state);

  std::uint16_t opcode;
  std::uint8_t flags;
  std::uint8_t reg1;
  std::uint8_t reg2;

  std::memcpy(&opcode, binary.binary, sizeof(std::uint16_t));
  std::memcpy(&flags, binary.binary + 2, sizeof(std::uint8_t));
  std::memcpy(&reg1, binary.binary + 3, sizeof(std::uint8_t));
  std::memcpy(&reg2, binary.binary + 4, sizeof(std::uint8_t));

  EXPECT_EQ(static_cast<HyperCPU::Opcode>(opcode), HyperCPU::Opcode::MOV);

  EXPECT_EQ(flags & 0b11000000, 0);
  EXPECT_EQ(static_cast<HyperCPU::Mode>((flags & 0b00110000) >> 4), HyperCPU::Mode::b16);
  EXPECT_EQ(static_cast<HyperCPU::OperandTypes>(flags & 0b00001111), HyperCPU::OperandTypes::RM_R);
  EXPECT_EQ(static_cast<HyperCPU::Reg>(reg1), HyperCPU::Reg::X0);
  EXPECT_EQ(static_cast<HyperCPU::Reg>(reg2), HyperCPU::Reg::XLL1);
}

TEST_F(ASSEMBLER, ASM_RM_R_b32) {
  std::string data = "mov [x0], xl1;";

  auto state(compiler.TransformToIR(data));

  auto binary = compiler.TransformToBinary(state);

  std::uint16_t opcode;
  std::uint8_t flags;
  std::uint8_t reg1;
  std::uint8_t reg2;

  std::memcpy(&opcode, binary.binary, sizeof(std::uint16_t));
  std::memcpy(&flags, binary.binary + 2, sizeof(std::uint8_t));
  std::memcpy(&reg1, binary.binary + 3, sizeof(std::uint8_t));
  std::memcpy(&reg2, binary.binary + 4, sizeof(std::uint8_t));

  EXPECT_EQ(static_cast<HyperCPU::Opcode>(opcode), HyperCPU::Opcode::MOV);

  EXPECT_EQ(flags & 0b11000000, 0);
  EXPECT_EQ(static_cast<HyperCPU::Mode>((flags & 0b00110000) >> 4), HyperCPU::Mode::b32);
  EXPECT_EQ(static_cast<HyperCPU::OperandTypes>(flags & 0b00001111), HyperCPU::OperandTypes::RM_R);
  EXPECT_EQ(static_cast<HyperCPU::Reg>(reg1), HyperCPU::Reg::X0);
  EXPECT_EQ(static_cast<HyperCPU::Reg>(reg2), HyperCPU::Reg::XL1);
}

TEST_F(ASSEMBLER, ASM_RM_R_b64) {
  std::string data = "mov [x0], x1;";

  auto state(compiler.TransformToIR(data));

  auto binary = compiler.TransformToBinary(state);

  std::uint16_t opcode;
  std::uint8_t flags;
  std::uint8_t reg1;
  std::uint8_t reg2;

  std::memcpy(&opcode, binary.binary, sizeof(std::uint16_t));
  std::memcpy(&flags, binary.binary + 2, sizeof(std::uint8_t));
  std::memcpy(&reg1, binary.binary + 3, sizeof(std::uint8_t));
  std::memcpy(&reg2, binary.binary + 4, sizeof(std::uint8_t));

  EXPECT_EQ(static_cast<HyperCPU::Opcode>(opcode), HyperCPU::Opcode::MOV);

  EXPECT_EQ(flags & 0b11000000, 0);
  EXPECT_EQ(static_cast<HyperCPU::Mode>((flags & 0b00110000) >> 4), HyperCPU::Mode::b64);
  EXPECT_EQ(static_cast<HyperCPU::OperandTypes>(flags & 0b00001111), HyperCPU::OperandTypes::RM_R);
  EXPECT_EQ(static_cast<HyperCPU::Reg>(reg1), HyperCPU::Reg::X0);
  EXPECT_EQ(static_cast<HyperCPU::Reg>(reg2), HyperCPU::Reg::X1);
}

TEST_F(ASSEMBLER, ASM_RM_M_b8) {
  std::string data = "mov b8 ptr [x0], [0x0];";

  auto state(compiler.TransformToIR(data));

  auto binary = compiler.TransformToBinary(state);

  std::uint16_t opcode;
  std::uint8_t flags;
  std::uint64_t addr;
  std::uint8_t reg;

  std::memcpy(&opcode, binary.binary, sizeof(std::uint16_t));
  std::memcpy(&flags, binary.binary + 2, sizeof(std::uint8_t));
  std::memcpy(&reg, binary.binary + 3, sizeof(std::uint8_t));
  std::memcpy(&addr, binary.binary + 4, sizeof(std::uint64_t));

  EXPECT_EQ(static_cast<HyperCPU::Opcode>(opcode), HyperCPU::Opcode::MOV);

  EXPECT_EQ(flags & 0b11000000, 0);
  EXPECT_EQ(static_cast<HyperCPU::Mode>((flags & 0b00110000) >> 4), HyperCPU::Mode::b8);
  EXPECT_EQ(static_cast<HyperCPU::OperandTypes>(flags & 0b00001111), HyperCPU::OperandTypes::RM_M);
  EXPECT_EQ(addr, 0);
  EXPECT_EQ(static_cast<HyperCPU::Reg>(reg), HyperCPU::Reg::X0);
}

TEST_F(ASSEMBLER, ASM_RM_M_b16) {
  std::string data = "mov b16 ptr [x0], [0x0];";

  auto state(compiler.TransformToIR(data));

  auto binary = compiler.TransformToBinary(state);

  std::uint16_t opcode;
  std::uint8_t flags;
  std::uint64_t addr;
  std::uint8_t reg;

  std::memcpy(&opcode, binary.binary, sizeof(std::uint16_t));
  std::memcpy(&flags, binary.binary + 2, sizeof(std::uint8_t));
  std::memcpy(&reg, binary.binary + 3, sizeof(std::uint8_t));
  std::memcpy(&addr, binary.binary + 4, sizeof(std::uint64_t));

  EXPECT_EQ(static_cast<HyperCPU::Opcode>(opcode), HyperCPU::Opcode::MOV);

  EXPECT_EQ(flags & 0b11000000, 0);
  EXPECT_EQ(static_cast<HyperCPU::Mode>((flags & 0b00110000) >> 4), HyperCPU::Mode::b16);
  EXPECT_EQ(static_cast<HyperCPU::OperandTypes>(flags & 0b00001111), HyperCPU::OperandTypes::RM_M);
  EXPECT_EQ(addr, 0);
  EXPECT_EQ(static_cast<HyperCPU::Reg>(reg), HyperCPU::Reg::X0);
}

TEST_F(ASSEMBLER, ASM_RM_M_b32) {
  std::string data = "mov b32 ptr [x0], [0x0];";

  auto state(compiler.TransformToIR(data));

  auto binary = compiler.TransformToBinary(state);

  std::uint16_t opcode;
  std::uint8_t flags;
  std::uint64_t addr;
  std::uint8_t reg;

  std::memcpy(&opcode, binary.binary, sizeof(std::uint16_t));
  std::memcpy(&flags, binary.binary + 2, sizeof(std::uint8_t));
  std::memcpy(&reg, binary.binary + 3, sizeof(std::uint8_t));
  std::memcpy(&addr, binary.binary + 4, sizeof(std::uint64_t));

  EXPECT_EQ(static_cast<HyperCPU::Opcode>(opcode), HyperCPU::Opcode::MOV);

  EXPECT_EQ(flags & 0b11000000, 0);
  EXPECT_EQ(static_cast<HyperCPU::Mode>((flags & 0b00110000) >> 4), HyperCPU::Mode::b32);
  EXPECT_EQ(static_cast<HyperCPU::OperandTypes>(flags & 0b00001111), HyperCPU::OperandTypes::RM_M);
  EXPECT_EQ(addr, 0);
  EXPECT_EQ(static_cast<HyperCPU::Reg>(reg), HyperCPU::Reg::X0);
}

TEST_F(ASSEMBLER, ASM_RM_M_b64) {
  std::string data = "mov b64 ptr [x0], [0x0];";

  auto state(compiler.TransformToIR(data));

  auto binary = compiler.TransformToBinary(state);

  std::uint16_t opcode;
  std::uint8_t flags;
  std::uint64_t addr;
  std::uint8_t reg;

  std::memcpy(&opcode, binary.binary, sizeof(std::uint16_t));
  std::memcpy(&flags, binary.binary + 2, sizeof(std::uint8_t));
  std::memcpy(&reg, binary.binary + 3, sizeof(std::uint8_t));
  std::memcpy(&addr, binary.binary + 4, sizeof(std::uint64_t));

  EXPECT_EQ(static_cast<HyperCPU::Opcode>(opcode), HyperCPU::Opcode::MOV);

  EXPECT_EQ(flags & 0b11000000, 0);
  EXPECT_EQ(static_cast<HyperCPU::Mode>((flags & 0b00110000) >> 4), HyperCPU::Mode::b64);
  EXPECT_EQ(static_cast<HyperCPU::OperandTypes>(flags & 0b00001111), HyperCPU::OperandTypes::RM_M);
  EXPECT_EQ(addr, 0);
  EXPECT_EQ(static_cast<HyperCPU::Reg>(reg), HyperCPU::Reg::X0);
}

TEST_F(ASSEMBLER, ASM_RM_IMM_b8) {
  std::string data = "mov b8 ptr [x0], 0u16;";

  auto state(compiler.TransformToIR(data));

  auto binary = compiler.TransformToBinary(state);

  std::uint16_t opcode;
  std::uint8_t flags;
  std::uint8_t num;
  std::uint8_t reg;

  std::memcpy(&opcode, binary.binary, sizeof(std::uint16_t));
  std::memcpy(&flags, binary.binary + 2, sizeof(std::uint8_t));
  std::memcpy(&reg, binary.binary + 3, sizeof(std::uint8_t));
  std::memcpy(&num, binary.binary + 4, sizeof(std::uint8_t));

  EXPECT_EQ(static_cast<HyperCPU::Opcode>(opcode), HyperCPU::Opcode::MOV);

  EXPECT_EQ(flags & 0b11000000, 0);
  EXPECT_EQ(static_cast<HyperCPU::Mode>((flags & 0b00110000) >> 4), HyperCPU::Mode::b8);
  EXPECT_EQ(static_cast<HyperCPU::OperandTypes>(flags & 0b00001111), HyperCPU::OperandTypes::RM_IMM);
  EXPECT_EQ(num, 16);
  EXPECT_EQ(static_cast<HyperCPU::Reg>(reg), HyperCPU::Reg::X0);
}

TEST_F(ASSEMBLER, ASM_RM_IMM_b16) {
  std::string data = "mov b16 ptr [x0], 0u16;";

  auto state(compiler.TransformToIR(data));

  auto binary = compiler.TransformToBinary(state);

  std::uint16_t opcode;
  std::uint8_t flags;
  std::uint16_t num;
  std::uint8_t reg;

  std::memcpy(&opcode, binary.binary, sizeof(std::uint16_t));
  std::memcpy(&flags, binary.binary + 2, sizeof(std::uint8_t));
  std::memcpy(&reg, binary.binary + 3, sizeof(std::uint8_t));
  std::memcpy(&num, binary.binary + 4, sizeof(std::uint16_t));

  EXPECT_EQ(static_cast<HyperCPU::Opcode>(opcode), HyperCPU::Opcode::MOV);

  EXPECT_EQ(flags & 0b11000000, 0);
  EXPECT_EQ(static_cast<HyperCPU::Mode>((flags & 0b00110000) >> 4), HyperCPU::Mode::b16);
  EXPECT_EQ(static_cast<HyperCPU::OperandTypes>(flags & 0b00001111), HyperCPU::OperandTypes::RM_IMM);
  EXPECT_EQ(num, 16);
  EXPECT_EQ(static_cast<HyperCPU::Reg>(reg), HyperCPU::Reg::X0);
}

TEST_F(ASSEMBLER, ASM_RM_IMM_b32) {
  std::string data = "mov b32 ptr [x0], 0u16;";

  auto state(compiler.TransformToIR(data));

  auto binary = compiler.TransformToBinary(state);

  std::uint16_t opcode;
  std::uint8_t flags;
  std::uint32_t num;
  std::uint8_t reg;

  std::memcpy(&opcode, binary.binary, sizeof(std::uint16_t));
  std::memcpy(&flags, binary.binary + 2, sizeof(std::uint8_t));
  std::memcpy(&reg, binary.binary + 3, sizeof(std::uint8_t));
  std::memcpy(&num, binary.binary + 4, sizeof(std::uint32_t));

  EXPECT_EQ(static_cast<HyperCPU::Opcode>(opcode), HyperCPU::Opcode::MOV);

  EXPECT_EQ(flags & 0b11000000, 0);
  EXPECT_EQ(static_cast<HyperCPU::Mode>((flags & 0b00110000) >> 4), HyperCPU::Mode::b32);
  EXPECT_EQ(static_cast<HyperCPU::OperandTypes>(flags & 0b00001111), HyperCPU::OperandTypes::RM_IMM);
  EXPECT_EQ(num, 16);
  EXPECT_EQ(static_cast<HyperCPU::Reg>(reg), HyperCPU::Reg::X0);
}

TEST_F(ASSEMBLER, ASM_RM_IMM_b64) {
  std::string data = "mov b64 ptr [x0], 0u16;";

  auto state(compiler.TransformToIR(data));

  auto binary = compiler.TransformToBinary(state);

  std::uint16_t opcode;
  std::uint8_t flags;
  std::uint64_t num;
  std::uint8_t reg;

  std::memcpy(&opcode, binary.binary, sizeof(std::uint16_t));
  std::memcpy(&flags, binary.binary + 2, sizeof(std::uint8_t));
  std::memcpy(&reg, binary.binary + 3, sizeof(std::uint8_t));
  std::memcpy(&num, binary.binary + 4, sizeof(std::uint64_t));

  EXPECT_EQ(static_cast<HyperCPU::Opcode>(opcode), HyperCPU::Opcode::MOV);

  EXPECT_EQ(flags & 0b11000000, 0);
  EXPECT_EQ(static_cast<HyperCPU::Mode>((flags & 0b00110000) >> 4), HyperCPU::Mode::b64);
  EXPECT_EQ(static_cast<HyperCPU::OperandTypes>(flags & 0b00001111), HyperCPU::OperandTypes::RM_IMM);
  EXPECT_EQ(num, 16);
  EXPECT_EQ(static_cast<HyperCPU::Reg>(reg), HyperCPU::Reg::X0);
}

TEST_F(ASSEMBLER, ASM_M_R_b8) {
  std::string data = "mov [0x0], xlll1;";

  auto state(compiler.TransformToIR(data));

  auto binary = compiler.TransformToBinary(state);

  std::uint16_t opcode;
  std::uint8_t flags;
  std::uint64_t addr;
  std::uint8_t reg;

  std::memcpy(&opcode, binary.binary, sizeof(std::uint16_t));
  std::memcpy(&flags, binary.binary + 2, sizeof(std::uint8_t));
  std::memcpy(&addr, binary.binary + 3, sizeof(std::uint64_t));
  std::memcpy(&reg, binary.binary + 11, sizeof(std::uint8_t));

  EXPECT_EQ(static_cast<HyperCPU::Opcode>(opcode), HyperCPU::Opcode::MOV);

  EXPECT_EQ(flags & 0b11000000, 0);
  EXPECT_EQ(static_cast<HyperCPU::Mode>((flags & 0b00110000) >> 4), HyperCPU::Mode::b8);
  EXPECT_EQ(static_cast<HyperCPU::OperandTypes>(flags & 0b00001111), HyperCPU::OperandTypes::M_R);
  EXPECT_EQ(addr, 0);
  EXPECT_EQ(static_cast<HyperCPU::Reg>(reg), HyperCPU::Reg::XLLL1);
}

TEST_F(ASSEMBLER, ASM_M_R_b16) {
  std::string data = "mov [0x0], xll1;";

  auto state(compiler.TransformToIR(data));

  auto binary = compiler.TransformToBinary(state);

  std::uint16_t opcode;
  std::uint8_t flags;
  std::uint64_t addr;
  std::uint8_t reg;

  std::memcpy(&opcode, binary.binary, sizeof(std::uint16_t));
  std::memcpy(&flags, binary.binary + 2, sizeof(std::uint8_t));
  std::memcpy(&addr, binary.binary + 3, sizeof(std::uint64_t));
  std::memcpy(&reg, binary.binary + 11, sizeof(std::uint8_t));

  EXPECT_EQ(static_cast<HyperCPU::Opcode>(opcode), HyperCPU::Opcode::MOV);

  EXPECT_EQ(flags & 0b11000000, 0);
  EXPECT_EQ(static_cast<HyperCPU::Mode>((flags & 0b00110000) >> 4), HyperCPU::Mode::b16);
  EXPECT_EQ(static_cast<HyperCPU::OperandTypes>(flags & 0b00001111), HyperCPU::OperandTypes::M_R);
  EXPECT_EQ(addr, 0);
  EXPECT_EQ(static_cast<HyperCPU::Reg>(reg), HyperCPU::Reg::XLL1);
}

TEST_F(ASSEMBLER, ASM_M_R_b32) {
  std::string data = "mov [0x0], xl1;";

  auto state(compiler.TransformToIR(data));

  auto binary = compiler.TransformToBinary(state);

  std::uint16_t opcode;
  std::uint8_t flags;
  std::uint64_t addr;
  std::uint8_t reg;

  std::memcpy(&opcode, binary.binary, sizeof(std::uint16_t));
  std::memcpy(&flags, binary.binary + 2, sizeof(std::uint8_t));
  std::memcpy(&addr, binary.binary + 3, sizeof(std::uint64_t));
  std::memcpy(&reg, binary.binary + 11, sizeof(std::uint8_t));

  EXPECT_EQ(static_cast<HyperCPU::Opcode>(opcode), HyperCPU::Opcode::MOV);

  EXPECT_EQ(flags & 0b11000000, 0);
  EXPECT_EQ(static_cast<HyperCPU::Mode>((flags & 0b00110000) >> 4), HyperCPU::Mode::b32);
  EXPECT_EQ(static_cast<HyperCPU::OperandTypes>(flags & 0b00001111), HyperCPU::OperandTypes::M_R);
  EXPECT_EQ(addr, 0);
  EXPECT_EQ(static_cast<HyperCPU::Reg>(reg), HyperCPU::Reg::XL1);
}

TEST_F(ASSEMBLER, ASM_M_R_b64) {
  std::string data = "mov [0x0], x1;";

  auto state(compiler.TransformToIR(data));

  auto binary = compiler.TransformToBinary(state);

  std::uint16_t opcode;
  std::uint8_t flags;
  std::uint64_t addr;
  std::uint8_t reg;

  std::memcpy(&opcode, binary.binary, sizeof(std::uint16_t));
  std::memcpy(&flags, binary.binary + 2, sizeof(std::uint8_t));
  std::memcpy(&addr, binary.binary + 3, sizeof(std::uint64_t));
  std::memcpy(&reg, binary.binary + 11, sizeof(std::uint8_t));

  EXPECT_EQ(static_cast<HyperCPU::Opcode>(opcode), HyperCPU::Opcode::MOV);

  EXPECT_EQ(flags & 0b11000000, 0);
  EXPECT_EQ(static_cast<HyperCPU::Mode>((flags & 0b00110000) >> 4), HyperCPU::Mode::b64);
  EXPECT_EQ(static_cast<HyperCPU::OperandTypes>(flags & 0b00001111), HyperCPU::OperandTypes::M_R);
  EXPECT_EQ(addr, 0);
  EXPECT_EQ(static_cast<HyperCPU::Reg>(reg), HyperCPU::Reg::X1);
}

TEST_F(ASSEMBLER, ASM_IMM_b64) {
  std::string data = "call b64 0x16;";

  auto state(compiler.TransformToIR(data));

  auto binary = compiler.TransformToBinary(state);

  std::uint16_t opcode;
  std::uint8_t flags;
  std::uint64_t addr;

  std::memcpy(&opcode, binary.binary, sizeof(std::uint16_t));
  std::memcpy(&flags, binary.binary + 2, sizeof(std::uint8_t));
  std::memcpy(&addr, binary.binary + 3, sizeof(std::uint64_t));

  EXPECT_EQ(static_cast<HyperCPU::Opcode>(opcode), HyperCPU::Opcode::CALL);

  EXPECT_EQ(flags & 0b11000000, 0);
  EXPECT_EQ(static_cast<HyperCPU::Mode>((flags & 0b00110000) >> 4), HyperCPU::Mode::b64);
  EXPECT_EQ(static_cast<HyperCPU::OperandTypes>(flags & 0b00001111), HyperCPU::OperandTypes::IMM);
  EXPECT_EQ(addr, 0x16);
}

TEST_F(ASSEMBLER, ASM_REFERENCE_LABEL) {
  std::string data = "\tmov x1, x0;\nlabel:\n\tmov x0, label;";

  auto state(compiler.TransformToIR(data));

  auto binary = compiler.TransformToBinary(state);

  std::uint16_t opcode;
  std::uint8_t flags;
  std::uint64_t num;
  std::uint8_t reg;

  std::memcpy(&opcode, binary.binary + 5, sizeof(std::uint16_t));
  std::memcpy(&flags, binary.binary + 7, sizeof(std::uint8_t));
  std::memcpy(&reg, binary.binary + 8, sizeof(std::uint8_t));
  std::memcpy(&num, binary.binary + 9, sizeof(std::uint64_t));

  EXPECT_EQ(static_cast<HyperCPU::Opcode>(opcode), HyperCPU::Opcode::MOV);

  EXPECT_EQ(flags & 0b11000000, 0);
  EXPECT_EQ(static_cast<HyperCPU::Mode>((flags & 0b00110000) >> 4), HyperCPU::Mode::b64);
  EXPECT_EQ(static_cast<HyperCPU::OperandTypes>(flags & 0b00001111), HyperCPU::OperandTypes::R_IMM);
  EXPECT_EQ(num, 5);
  EXPECT_EQ(static_cast<HyperCPU::Reg>(reg), HyperCPU::Reg::X0);
}

TEST_F(ASSEMBLER, ASM_REFERENCE_ENTRY_LABEL) {
  std::string data = "\tmov x1, x0;\n.attr(entry) label:\n\tmov x0, label;";

  auto state(compiler.TransformToIR(data));

  auto binary = compiler.TransformToBinary(state);

  std::uint16_t opcode;
  std::uint8_t flags;
  std::uint64_t num;
  std::uint8_t reg;

  std::memcpy(&opcode, binary.binary + 5, sizeof(std::uint16_t));
  std::memcpy(&flags, binary.binary + 7, sizeof(std::uint8_t));
  std::memcpy(&reg, binary.binary + 8, sizeof(std::uint8_t));
  std::memcpy(&num, binary.binary + 9, sizeof(std::uint64_t));

  EXPECT_EQ(static_cast<HyperCPU::Opcode>(opcode), HyperCPU::Opcode::MOV);

  EXPECT_EQ(flags & 0b11000000, 0);
  EXPECT_EQ(static_cast<HyperCPU::Mode>((flags & 0b00110000) >> 4), HyperCPU::Mode::b64);
  EXPECT_EQ(static_cast<HyperCPU::OperandTypes>(flags & 0b00001111), HyperCPU::OperandTypes::R_IMM);
  EXPECT_EQ(num, 5);
  EXPECT_EQ(static_cast<HyperCPU::Reg>(reg), HyperCPU::Reg::X0);
}

TEST_F(ASSEMBLER, ASM_COMPILE) {
  std::string data = "\tmov x1, x0;\nlabel:\n\tmov x0, label;";
  std::uint32_t code_size;

  auto binary = compiler.Compile(data, code_size);

  std::uint16_t opcode;
  std::uint8_t flags;
  std::uint64_t num;
  std::uint8_t reg;
  std::memcpy(&opcode, binary.binary + 5, sizeof(std::uint16_t));
  std::memcpy(&flags, binary.binary + 7, sizeof(std::uint8_t));
  std::memcpy(&reg, binary.binary + 8, sizeof(std::uint8_t));
  std::memcpy(&num, binary.binary + 9, sizeof(std::uint64_t));

  EXPECT_EQ(static_cast<HyperCPU::Opcode>(opcode), HyperCPU::Opcode::MOV);
  EXPECT_EQ(code_size, 17);

  EXPECT_EQ(flags & 0b11000000, 0);
  EXPECT_EQ(static_cast<HyperCPU::Mode>((flags & 0b00110000) >> 4), HyperCPU::Mode::b64);
  EXPECT_EQ(static_cast<HyperCPU::OperandTypes>(flags & 0b00001111), HyperCPU::OperandTypes::R_IMM);
  EXPECT_EQ(num, 5);
  EXPECT_EQ(static_cast<HyperCPU::Reg>(reg), HyperCPU::Reg::X0);
}

TEST_F(ASSEMBLER, ASM_b8_str_DIRECTIVE) {
  std::string data = ".b8 \"test!\\\"\\n\\r\\\\\";";
  auto str = "test!\"\n\r\\";
  std::uint32_t code_size;

  auto binary = compiler.Compile(data, code_size);

  EXPECT_FALSE(std::memcmp(binary.binary, str, std::strlen(str)));
}

TEST_F(ASSEMBLER, ASM_b8_DIRECTIVE) {
  std::string data = ".b8 0x12;";
  std::uint32_t code_size;

  auto binary = compiler.Compile(data, code_size);

  EXPECT_EQ(HyperCPU::bit_cast_from<std::uint8_t>(binary.binary), 0x12);
}

TEST_F(ASSEMBLER, ASM_b16_DIRECTIVE) {
  std::string data = ".b16 0x1234;";
  std::uint32_t code_size;

  auto binary = compiler.Compile(data, code_size);

  EXPECT_EQ(HyperCPU::bit_cast_from<std::uint16_t>(binary.binary), 0x1234);
}

TEST_F(ASSEMBLER, ASM_b32_DIRECTIVE) {
  std::string data = ".b32 0x12345678;";
  std::uint32_t code_size;

  auto binary = compiler.Compile(data, code_size);

  EXPECT_EQ(HyperCPU::bit_cast_from<std::uint32_t>(binary.binary), 0x12345678);
}

TEST_F(ASSEMBLER, ASM_b64_DIRECTIVE) {
  std::string data = ".b64 0x1234567812345678;";
  std::uint32_t code_size;

  auto binary = compiler.Compile(data, code_size);

  EXPECT_EQ(HyperCPU::bit_cast_from<std::uint64_t>(binary.binary), 0x1234567812345678);
}

TEST_F(ASSEMBLER, ASM_b64_DIRECTIVE_USE_LABEL) {
  std::string data = "mov x0, x1;\nfoo:\n.b64 foo;";
  std::uint32_t code_size;

  auto binary = compiler.Compile(data, code_size);

  EXPECT_EQ(HyperCPU::bit_cast_from<std::uint64_t>(binary.binary + 5), 5);
}

TEST_F(ASSEMBLER, ASM_ENTRY_LABEL) {
  std::string data = "\tmov x1, x0;\n.attr(entry) label:\n\tmov x0, label;";

  auto state(compiler.TransformToIR(data));

  auto binary = compiler.TransformToBinary(state);

  std::uint16_t opcode;
  std::uint8_t flags;
  std::uint64_t num;
  std::uint8_t reg;

  std::memcpy(&opcode, binary.binary + 5, sizeof(std::uint16_t));
  std::memcpy(&flags, binary.binary + 7, sizeof(std::uint8_t));
  std::memcpy(&reg, binary.binary + 8, sizeof(std::uint8_t));
  std::memcpy(&num, binary.binary + 9, sizeof(std::uint64_t));

  EXPECT_EQ(binary.entry_point, 5);

  EXPECT_EQ(static_cast<HyperCPU::Opcode>(opcode), HyperCPU::Opcode::MOV);
  EXPECT_EQ(flags & 0b11000000, 0);
  EXPECT_EQ(static_cast<HyperCPU::Mode>((flags & 0b00110000) >> 4), HyperCPU::Mode::b64);
  EXPECT_EQ(static_cast<HyperCPU::OperandTypes>(flags & 0b00001111), HyperCPU::OperandTypes::R_IMM);
  EXPECT_EQ(num, 5);
  EXPECT_EQ(static_cast<HyperCPU::Reg>(reg), HyperCPU::Reg::X0);
}
