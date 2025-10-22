#include "PCH/CStd.hpp"
#include "fixtures.hpp"

#ifdef NDEBUG
#define HCPU_ASSERT_EXIT(statement, x, regex) ASSERT_DEATH(statement, regex)
#else
#define HCPU_ASSERT_EXIT(statement, x, regex) ASSERT_EXIT(statement, x, regex)
#endif

TEST_F(ASSEMBLER, ASM_INVALID_INSTRUCTION_TWO_OPERANDS) {
  std::string data = "miv xlll0, xlll1;";
  HCPU_ASSERT_EXIT({
    auto state(compiler.TransformToIR(data));
    auto binary = compiler.TransformToBinary(state); }, ::testing::ExitedWithCode(1), ".*");
}

TEST_F(ASSEMBLER, ASM_INVALID_INSTRUCTION_ONE_OPERAND) {
  std::string data = "miv xlll0;";
  HCPU_ASSERT_EXIT({
    auto state(compiler.TransformToIR(data));
    auto binary = compiler.TransformToBinary(state); }, ::testing::ExitedWithCode(1), ".*");
}

TEST_F(ASSEMBLER, ASM_INVALID_INSTRUCTION_NO_OPERANDS) {
  std::string data = "miv;";
  HCPU_ASSERT_EXIT({
    auto state(compiler.TransformToIR(data));
    auto binary = compiler.TransformToBinary(state); }, ::testing::ExitedWithCode(1), ".*");
}

TEST_F(ASSEMBLER, ASM_CANT_USE_RESERVED_IDENT_AS_LABEL) {
  std::string data = "mov:";
  HCPU_ASSERT_EXIT({
    auto state(compiler.TransformToIR(data));
    auto binary = compiler.TransformToBinary(state); }, ::testing::ExitedWithCode(1), ".*");
}

TEST_F(ASSEMBLER, ASM_LABEL_REDEFINITION) {
  std::string data = "foo:\nfoo:";
  HCPU_ASSERT_EXIT({
    auto state(compiler.TransformToIR(data));
    auto binary = compiler.TransformToBinary(state); }, ::testing::ExitedWithCode(1), ".*");
}

TEST_F(ASSEMBLER, ASM_ENTRY_LABEL_REDEFINITION) {
  std::string data = "foo:\n.attr(entry) foo:";
  HCPU_ASSERT_EXIT({
    auto state(compiler.TransformToIR(data));
    auto binary = compiler.TransformToBinary(state); }, ::testing::ExitedWithCode(1), ".*");
}

TEST_F(ASSEMBLER, RAWVALUEb8_CANT_USE_LABEL) {
  std::string data = ".b8 foo;";
  HCPU_ASSERT_EXIT({
    auto state(compiler.TransformToIR(data));
    auto binary = compiler.TransformToBinary(state); }, ::testing::ExitedWithCode(1), ".*");
}

TEST_F(ASSEMBLER, RAWVALUEb16_CANT_USE_LABEL) {
  std::string data = ".b16 foo;";
  HCPU_ASSERT_EXIT({
    auto state(compiler.TransformToIR(data));
    auto binary = compiler.TransformToBinary(state); }, ::testing::ExitedWithCode(1), ".*");
}

TEST_F(ASSEMBLER, RAWVALUEb32_CANT_USE_LABEL) {
  std::string data = ".b32 foo;";
  HCPU_ASSERT_EXIT({
    auto state(compiler.TransformToIR(data));
    auto binary = compiler.TransformToBinary(state); }, ::testing::ExitedWithCode(1), ".*");
}
