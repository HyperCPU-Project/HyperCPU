#include "fixtures.hpp"

TEST_F(TWO_OPERANDS_SUCCESS, OPERANDS_R_R_b8) {
  std::string data = "mov xlll0, xlll1;";
  std::uint32_t code_size;
  ASSERT_NO_FATAL_FAILURE(compiler.Compile(data, code_size));
}

TEST_F(TWO_OPERANDS_SUCCESS, OPERANDS_R_R_b16) {
  std::string data = "mov xll0, xll1;";
  std::uint32_t code_size;
  ASSERT_NO_FATAL_FAILURE(compiler.Compile(data, code_size));
}

TEST_F(TWO_OPERANDS_SUCCESS, OPERANDS_R_R_b32) {
  std::string data = "mov xl0, xl1;";
  std::uint32_t code_size;
  ASSERT_NO_FATAL_FAILURE(compiler.Compile(data, code_size));
}

TEST_F(TWO_OPERANDS_SUCCESS, OPERANDS_R_R_b64) {
  std::string data = "mov x0, x1;";
  std::uint32_t code_size;
  ASSERT_NO_FATAL_FAILURE(compiler.Compile(data, code_size));
}

TEST_F(TWO_OPERANDS_SUCCESS, OPERANDS_R_RM_b8) {
  std::string data = "mov xlll0, [x1];";
  std::uint32_t code_size;
  ASSERT_NO_FATAL_FAILURE(compiler.Compile(data, code_size));
}

TEST_F(TWO_OPERANDS_SUCCESS, OPERANDS_R_RM_b16) {
  std::string data = "mov xll0, [x1];";
  std::uint32_t code_size;
  ASSERT_NO_FATAL_FAILURE(compiler.Compile(data, code_size));
}

TEST_F(TWO_OPERANDS_SUCCESS, OPERANDS_R_RM_b32) {
  std::string data = "mov xl0, [x1];";
  std::uint32_t code_size;
  ASSERT_NO_FATAL_FAILURE(compiler.Compile(data, code_size));
}

TEST_F(TWO_OPERANDS_SUCCESS, OPERANDS_R_RM_b64) {
  std::string data = "mov x0, [x1];";
  std::uint32_t code_size;
  ASSERT_NO_FATAL_FAILURE(compiler.Compile(data, code_size));
}

TEST_F(TWO_OPERANDS_SUCCESS, OPERANDS_R_M_b8) {
  std::string data = "mov xlll0, [0x0];";
  std::uint32_t code_size;
  ASSERT_NO_FATAL_FAILURE(compiler.Compile(data, code_size));
}

TEST_F(TWO_OPERANDS_SUCCESS, OPERANDS_R_M_b16) {
  std::string data = "mov xll0, [0x0];";
  std::uint32_t code_size;
  ASSERT_NO_FATAL_FAILURE(compiler.Compile(data, code_size));
}

TEST_F(TWO_OPERANDS_SUCCESS, OPERANDS_R_M_b32) {
  std::string data = "mov xl0, [0x0];";
  std::uint32_t code_size;
  ASSERT_NO_FATAL_FAILURE(compiler.Compile(data, code_size));
}

TEST_F(TWO_OPERANDS_SUCCESS, OPERANDS_R_M_b64) {
  std::string data = "mov x0, [0x0];";
  std::uint32_t code_size;
  ASSERT_NO_FATAL_FAILURE(compiler.Compile(data, code_size));
}

TEST_F(TWO_OPERANDS_SUCCESS, OPERANDS_R_IMM_b8) {
  std::string data = "mov xlll0, 0u0;";
  std::uint32_t code_size;
  ASSERT_NO_FATAL_FAILURE(compiler.Compile(data, code_size));
}

TEST_F(TWO_OPERANDS_SUCCESS, OPERANDS_R_IMM_b16) {
  std::string data = "mov xll0, 0u0;";
  std::uint32_t code_size;
  ASSERT_NO_FATAL_FAILURE(compiler.Compile(data, code_size));
}

TEST_F(TWO_OPERANDS_SUCCESS, OPERANDS_R_IMM_b32) {
  std::string data = "mov xl0, 0u0;";
  std::uint32_t code_size;
  ASSERT_NO_FATAL_FAILURE(compiler.Compile(data, code_size));
}

TEST_F(TWO_OPERANDS_SUCCESS, OPERANDS_R_IMM_b64) {
  std::string data = "mov x0, 0u0;";
  std::uint32_t code_size;
  ASSERT_NO_FATAL_FAILURE(compiler.Compile(data, code_size));
}

TEST_F(TWO_OPERANDS_SUCCESS, OPERANDS_RM_R_b8) {
  std::string data = "mov [x0], xlll1;";
  std::uint32_t code_size;
  ASSERT_NO_FATAL_FAILURE(compiler.Compile(data, code_size));
}

TEST_F(TWO_OPERANDS_SUCCESS, OPERANDS_RM_R_b16) {
  std::string data = "mov [x0], xll1;";
  std::uint32_t code_size;
  ASSERT_NO_FATAL_FAILURE(compiler.Compile(data, code_size));
}

TEST_F(TWO_OPERANDS_SUCCESS, OPERANDS_RM_R_b32) {
  std::string data = "mov [x0], xl1;";
  std::uint32_t code_size;
  ASSERT_NO_FATAL_FAILURE(compiler.Compile(data, code_size));
}

TEST_F(TWO_OPERANDS_SUCCESS, OPERANDS_RM_R_b64) {
  std::string data = "mov [x0], x1;";
  std::uint32_t code_size;
  ASSERT_NO_FATAL_FAILURE(compiler.Compile(data, code_size));
}

TEST_F(TWO_OPERANDS_SUCCESS, OPERANDS_RM_M_b8) {
  std::string data = "mov b8 ptr [x0], [0x0];";
  std::uint32_t code_size;
  ASSERT_NO_FATAL_FAILURE(compiler.Compile(data, code_size));
}

TEST_F(TWO_OPERANDS_SUCCESS, OPERANDS_RM_M_b16) {
  std::string data = "mov b16 ptr [x0], [0x0];";
  std::uint32_t code_size;
  ASSERT_NO_FATAL_FAILURE(compiler.Compile(data, code_size));
}

TEST_F(TWO_OPERANDS_SUCCESS, OPERANDS_RM_M_b32) {
  std::string data = "mov b32 ptr [x0], [0x0];";
  std::uint32_t code_size;
  ASSERT_NO_FATAL_FAILURE(compiler.Compile(data, code_size));
}

TEST_F(TWO_OPERANDS_SUCCESS, OPERANDS_RM_M_b64) {
  std::string data = "mov b64 ptr [x0], [0x0];";
  std::uint32_t code_size;
  ASSERT_NO_FATAL_FAILURE(compiler.Compile(data, code_size));
}

TEST_F(TWO_OPERANDS_SUCCESS, OPERANDS_RM_IMM_b8) {
  std::string data = "mov b8 ptr [x0], 0u0;";
  std::uint32_t code_size;
  ASSERT_NO_FATAL_FAILURE(compiler.Compile(data, code_size));
}

TEST_F(TWO_OPERANDS_SUCCESS, OPERANDS_RM_IMM_b16) {
  std::string data = "mov b16 ptr [x0], 0u0;";
  std::uint32_t code_size;
  ASSERT_NO_FATAL_FAILURE(compiler.Compile(data, code_size));
}

TEST_F(TWO_OPERANDS_SUCCESS, OPERANDS_RM_IMM_b32) {
  std::string data = "mov b32 ptr [x0], 0u0;";
  std::uint32_t code_size;
  ASSERT_NO_FATAL_FAILURE(compiler.Compile(data, code_size));
}

TEST_F(TWO_OPERANDS_SUCCESS, OPERANDS_RM_IMM_b64) {
  std::string data = "mov b64 ptr [x0], 0u0;";
  std::uint32_t code_size;
  ASSERT_NO_FATAL_FAILURE(compiler.Compile(data, code_size));
}

TEST_F(TWO_OPERANDS_SUCCESS, OPERANDS_M_R_b8) {
  std::string data = "mov [x0], xlll0;";
  std::uint32_t code_size;
  ASSERT_NO_FATAL_FAILURE(compiler.Compile(data, code_size));
}

TEST_F(TWO_OPERANDS_SUCCESS, OPERANDS_M_R_b16) {
  std::string data = "mov [x0], xll0;";
  std::uint32_t code_size;
  ASSERT_NO_FATAL_FAILURE(compiler.Compile(data, code_size));
}

TEST_F(TWO_OPERANDS_SUCCESS, OPERANDS_M_R_b32) {
  std::string data = "mov [x0], xl0;";
  std::uint32_t code_size;
  ASSERT_NO_FATAL_FAILURE(compiler.Compile(data, code_size));
}

TEST_F(TWO_OPERANDS_SUCCESS, OPERANDS_M_R_b64) {
  std::string data = "mov [x0], x0;";
  std::uint32_t code_size;
  ASSERT_NO_FATAL_FAILURE(compiler.Compile(data, code_size));
}
