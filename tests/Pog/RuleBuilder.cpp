#include "Pog/RuleBuilder.hpp"

#include "PCH/CStd.hpp"
#include "gtest.hpp"

using namespace pog;

class TestRuleBuilder : public ::testing::Test {
public:
  Grammar<int> grammar;
};

TEST_F(TestRuleBuilder,
       Initialization) {
  RuleBuilder<int> rb(&grammar, "A");

  EXPECT_EQ(grammar.get_symbols().size(), 2u); // start and end symbol
  EXPECT_TRUE(grammar.get_rules().empty());
}

TEST_F(TestRuleBuilder,
       NoProductions) {
  RuleBuilder<int> rb(&grammar, "A");
  rb.done();

  EXPECT_EQ(grammar.get_symbols().size(), 2u);
  EXPECT_TRUE(grammar.get_rules().empty());
}

TEST_F(TestRuleBuilder,
       SingleProductionWithoutAction) {
  RuleBuilder<int> rb(&grammar, "A");
  rb.production("a");
  rb.done();

  EXPECT_EQ(grammar.get_symbols().size(), 4u);
  EXPECT_EQ(grammar.get_rules().size(), 1u);
  EXPECT_EQ(grammar.get_rules()[0]->to_string(), "A -> a");
  EXPECT_FALSE(grammar.get_rules()[0]->has_action());
}

TEST_F(TestRuleBuilder,
       SingleProductionWithAction) {
  RuleBuilder<int> rb(&grammar, "A");
  rb.production("a", [](Parser<int>&, auto&&) { return 42; });
  rb.done();

  EXPECT_EQ(grammar.get_symbols().size(), 4u);
  EXPECT_EQ(grammar.get_rules().size(), 1u);
  EXPECT_EQ(grammar.get_rules()[0]->to_string(), "A -> a");
  EXPECT_TRUE(grammar.get_rules()[0]->has_action());
}

TEST_F(TestRuleBuilder,
       MultipleProductionsWithActions) {
  RuleBuilder<int> rb(&grammar, "A");
  rb.production("A", "a", [](Parser<int>&, auto&&) { return 42; })
      .production("a", [](Parser<int>&, auto&&) { return 42; });
  rb.done();

  EXPECT_EQ(grammar.get_symbols().size(), 4u);
  EXPECT_EQ(grammar.get_rules().size(), 2u);
  EXPECT_EQ(grammar.get_rules()[0]->to_string(), "A -> A a");
  EXPECT_EQ(grammar.get_rules()[1]->to_string(), "A -> a");
  EXPECT_TRUE(grammar.get_rules()[0]->has_action());
  EXPECT_TRUE(grammar.get_rules()[1]->has_action());
}
