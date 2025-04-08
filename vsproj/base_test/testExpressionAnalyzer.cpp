#include "gtest.h"
#include "EA_v1.h"


TEST(EA_v1, ea_Can_Get_Postfix)
{
    EA_v1 ea;
    std::set<std::string> orp;
    ea.analyzeExpression("a+b", orp);
    ASSERT_NO_THROW(ea.getCachedPurePostfix());
}

TEST(EA_v1, ea_Can_Analyze_expression)
{
    EA_v1 ea;
    std::set<std::string> orp;
    ASSERT_NO_THROW(ea.analyzeExpression("a+b", orp));
}

TEST(EA_v1, EA_can_analyze_plus_operation)
{
    EA_v1 ea;
    std::set<std::string> orp;
    std::string expression = "a+b";
    std::vector<std::string> verified = { "a", "b", "+" };

    ea.analyzeExpression(expression, orp);
    std::vector<std::string> pst = ea.getCachedPurePostfix();

    EXPECT_TRUE(pst == verified);
}

TEST(EA_v1, EA_can_analyze_minus_operation)
{
    EA_v1 ea;
    std::set<std::string> orp;
    std::string expression = "a-b";
    std::vector<std::string> verified = { "a", "b", "-" };

    ea.analyzeExpression(expression, orp);
    std::vector<std::string> pst = ea.getCachedPurePostfix();

    EXPECT_TRUE(pst == verified);

}

TEST(EA_v1, EA_can_analyze_multiply_operation)
{
    EA_v1 ea;
    std::set<std::string> orp;
    std::string expression = "a*b";
    std::vector<std::string> verified = { "a", "b", "*" };

    ea.analyzeExpression(expression, orp);
    std::vector<std::string> pst = ea.getCachedPurePostfix();

    EXPECT_TRUE(pst == verified);

}

TEST(EA_v1, EA_can_analyze_functions)
{
    EA_v1 ea;
    std::set<std::string> orp;
    std::string expression = "d_dx(a)";
    std::vector<std::string> verified = { "a", "d_dx" };

    ea.analyzeExpression(expression, orp);
    std::vector<std::string> pst = ea.getCachedPurePostfix();

    EXPECT_TRUE(pst == verified);
}

TEST(EA_v1, EA_can_analyze_minus_as_sign)
{
    EA_v1 ea;
    std::set<std::string> orp;
    std::string expression = "-a";
    std::vector<std::string> verified = { "-1", "a", "*" };

    ea.analyzeExpression(expression, orp);
    std::vector<std::string> pst = ea.getCachedPurePostfix();

    EXPECT_TRUE(pst == verified);
}

TEST(EA_v1, EA_can_analyze_constants_before_polynomial)
{
    EA_v1 ea;
    std::set<std::string> orp;
    std::string expression = "3*a";
    std::vector<std::string> verified = { "3", "a", "*" };

    ea.analyzeExpression(expression, orp);
    std::vector<std::string> pst = ea.getCachedPurePostfix();

    EXPECT_TRUE(pst == verified);
}

TEST(EA_v1, EA_can_analyze_constants_after_polynomial)
{
    EA_v1 ea;
    std::set<std::string> orp;
    std::string expression = "a*3";
    std::vector<std::string> verified = { "a", "3", "*" };

    ea.analyzeExpression(expression, orp);
    std::vector<std::string> pst = ea.getCachedPurePostfix();

    EXPECT_TRUE(pst == verified);
}

TEST(EA_v1, EA_can_analyze_brackets)
{
    EA_v1 ea;
    std::set<std::string> orp;
    std::string expression = "(a+b)";
    std::vector<std::string> verified = { "a", "b", "+" };

    ea.analyzeExpression(expression, orp);
    std::vector<std::string> pst = ea.getCachedPurePostfix();

    EXPECT_TRUE(pst == verified);
}


TEST(EA_v1, EA_brackets_have_maximum_priority)
{
    EA_v1 ea;
    std::set<std::string> orp;
    std::string expression = "a*(b+3)";
    std::vector<std::string> verified = { "a", "b", "3", "+", "*" };

    ea.analyzeExpression(expression, orp);
    std::vector<std::string> pst = ea.getCachedPurePostfix();

    EXPECT_TRUE(pst == verified);
}

TEST(EA_v1, EA_functions_could_take_expressions_as_args)
{
    EA_v1 ea;
    std::set<std::string> orp;
    std::string expression = "d_dx(b+3*a)";
    std::vector<std::string> verified = { "b", "3", "a", "*", "+", "d_dx" };

    ea.analyzeExpression(expression, orp);
    std::vector<std::string> pst = ea.getCachedPurePostfix();

    EXPECT_TRUE(pst == verified);
}


TEST(EA_v1, EA_functions_could_take_functions_as_args)
{
    EA_v1 ea;
    std::set<std::string> orp;
    std::string expression = "d_dy(d_dx(b+3*a))";
    std::vector<std::string> verified = { "b", "3", "a", "*", "+", "d_dx", "d_dy" };

    ea.analyzeExpression(expression, orp);
    std::vector<std::string> pst = ea.getCachedPurePostfix();

    EXPECT_TRUE(pst == verified);
}


TEST(EA_v1, EA_functions_could_take_expressions_with_functions_as_args)
{
    EA_v1 ea;
    std::set<std::string> orp;
    std::string expression = "d_dy(3+d_dx(b+3*a)*i)";
    std::vector<std::string> verified = { "3", "b", "3", "a", "*", "+", "d_dx", "i", "*", "+", "d_dy" };

    ea.analyzeExpression(expression, orp);
    std::vector<std::string> pst = ea.getCachedPurePostfix();

    EXPECT_TRUE(pst == verified);
}

TEST(EA_v1, EA_functions_could_work_with_negative_constants)
{
    EA_v1 ea;
    std::set<std::string> orp;
    std::string expression = "-3*(-3)*a";
    std::vector<std::string> verified = { "-1", "3", "*", "-1", "3", "*", "*", "a", "*" };

    ea.analyzeExpression(expression, orp);
    std::vector<std::string> pst = ea.getCachedPurePostfix();

    EXPECT_TRUE(pst == verified);
}

TEST(EA_v1, EA_can_analyze_complex_expression1) {
    EA_v1 ea;
    std::set<std::string> orp;
    std::string expression = "(a+b)*(c+d)";
    std::vector<std::string> verified = { "a", "b", "+", "c", "d", "+", "*" };
    ea.analyzeExpression(expression, orp);
    EXPECT_EQ(ea.getCachedPurePostfix(), verified);
}

TEST(EA_v1, EA_can_analyze_expressions_with_multiple_open_brackets) {
    EA_v1 ea;
    std::set<std::string> orp;
    std::string expression = "((a+b)*c)-d";
    std::vector<std::string> verified = { "a", "b", "+", "c", "*", "d", "-" };
    ea.analyzeExpression(expression, orp);
    EXPECT_EQ(ea.getCachedPurePostfix(), verified);
}

TEST(EA_v1, EA_can_analyze_expressions_with_multiple_back_brackets) {
    EA_v1 ea;
    std::set<std::string> orp;
    std::string expression = "(a+(b-c))";
    std::vector<std::string> verified = { "a", "b", "c", "-", "+" };
    ea.analyzeExpression(expression, orp);
    EXPECT_EQ(ea.getCachedPurePostfix(), verified);
}

TEST(EA_v1, EmptyExpression) {
    EA_v1 ea;
    std::set<std::string> orp;
    std::string expression = "";
    EXPECT_ANY_THROW(ea.analyzeExpression(expression, orp));
}

TEST(EA_v1, OnlySpaces) {
    EA_v1 ea;
    std::set<std::string> orp;
    std::string expression = "   ";
    EXPECT_ANY_THROW(ea.analyzeExpression(expression, orp));
}

TEST(EA_v1, InvalidCharacters) {
    EA_v1 ea;
    std::set<std::string> orp;
    std::string expression = "a + b $ c";
    EXPECT_ANY_THROW(ea.analyzeExpression(expression, orp));
}

TEST(EA_v1, DoubleOperator) {
    EA_v1 ea;
    std::set<std::string> orp;
    std::string expression = "a++b";
    EXPECT_ANY_THROW(ea.analyzeExpression(expression, orp));
}

TEST(EA_v1, MissingOperandLeft) {
    EA_v1 ea;
    std::set<std::string> orp;
    std::string expression = "+b";
    EXPECT_ANY_THROW(ea.analyzeExpression(expression, orp));
}

TEST(EA_v1, MissingOperandRight) {
    EA_v1 ea;
    std::set<std::string> orp;
    std::string expression = "a+";
    EXPECT_ANY_THROW(ea.analyzeExpression(expression, orp));
}