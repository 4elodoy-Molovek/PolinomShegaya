#include "gtest.h"
#include "EA_v1.h"
#include "Parser_v1.h"


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

TEST(EA_v1, EA_empty_expression_arent_allowed) {
    EA_v1 ea;
    std::set<std::string> orp;
    std::string expression = "";
    EXPECT_ANY_THROW(ea.analyzeExpression(expression, orp));
}

TEST(EA_v1, EA_only_spaces_expressions_arent_allowed) {
    EA_v1 ea;
    std::set<std::string> orp;
    std::string expression = "   ";
    EXPECT_ANY_THROW(ea.analyzeExpression(expression, orp));
}

TEST(EA_v1, EA_spaces_doesnt_matter) {
    EA_v1 ea1, ea2;
    std::set<std::string> orp1, orp2;
    std::string expression1 = "a + d_dx(   -d-c)";
    std::string expression2 = "a+d_dx(-d-c)";
    ea1.analyzeExpression(expression1, orp1);
    ea2.analyzeExpression(expression2, orp2);
    EXPECT_TRUE((orp1 == orp2) && (ea1.getCachedPostfix() == ea2.getCachedPostfix()));
}


TEST(EA_v1, EA_Invalid_Characters_arent_allowed) {
    EA_v1 ea;
    std::set<std::string> orp;
    std::string expression = "a + b $ c";
    EXPECT_ANY_THROW(ea.analyzeExpression(expression, orp));
}

TEST(EA_v1, EA_double_operator_arent_allowed) {
    EA_v1 ea;
    std::set<std::string> orp;
    std::string expression = "a++b";
    EXPECT_ANY_THROW(ea.analyzeExpression(expression, orp));
}

TEST(EA_v1, EA_detects_Missing_Operand_Left) {
    EA_v1 ea;
    std::set<std::string> orp;
    std::string expression = "+b";
    EXPECT_ANY_THROW(ea.analyzeExpression(expression, orp));
}

TEST(EA_v1, EA_Detects_Missing_Operand_Right) {
    EA_v1 ea;
    std::set<std::string> orp;
    std::string expression = "a+";
    EXPECT_ANY_THROW(ea.analyzeExpression(expression, orp));
}

TEST(EA_v1, EA_Detects_Missing_Closing_Bracket) {
    EA_v1 ea;
    std::set<std::string> orp;
    std::string expression = "(a+b";
    EXPECT_ANY_THROW(ea.analyzeExpression(expression, orp));
}

TEST(EA_v1, EA_Detects_Missing_Openning_Bracket) {
    EA_v1 ea;
    std::set<std::string> orp;
    std::string expression = "a+b)";
    EXPECT_ANY_THROW(ea.analyzeExpression(expression, orp));
}

TEST(EA_v1, EA_Functions_Without_Args_Arent_Allowed) {
    EA_v1 ea;
    std::set<std::string> orp;
    std::string expression = "a+d_dx()";
    EXPECT_ANY_THROW(ea.analyzeExpression(expression, orp));
}

TEST(EA_v1, EA_Unrecognized_Functions_Arent_Allowed) {
    EA_v1 ea;
    std::set<std::string> orp;
    std::string expression = "a+sin(b)";
    EXPECT_ANY_THROW(ea.analyzeExpression(expression, orp));
}

TEST(EA_v1, EA_return_correct_set_of_variables) {
    EA_v1 ea;
    std::set<std::string> orp;
    std::set<std::string> verSet = { "a", "b" };
    std::string expression = "a+d_dx(b)";
    ea.analyzeExpression(expression, orp);
    EXPECT_TRUE(verSet == orp);
}

TEST(EA_v1, EA_Can_Calculte_Expression) {
    EA_v1 ea;
    std::set<std::string> orp;
    Parser_v1 ps;
    Polynomial a = ps.convertStringToPolynomial("xyz+3x");
    Polynomial b = ps.convertStringToPolynomial("2y-4z+6");
    Polynomial ans = ps.convertStringToPolynomial("xyz+3x+2y-4z+6");

    std::map<std::string, const Polynomial&> polyMap = { {"a", a},  { "b", b} };
    std::string expression = "a+b";
    ea.analyzeExpression(expression, orp);
    ea.calculateSummaryPolynomial(polyMap);

    EXPECT_TRUE(ea.calculateSummaryPolynomial(polyMap) == ans);
}

TEST(EA_v1, Can_Calculte_Expression_With_More_Variables_Than_Need) {
    EA_v1 ea;
    std::set<std::string> orp;
    Parser_v1 ps;
    Polynomial a = ps.convertStringToPolynomial("xyz+3x");
    Polynomial b = ps.convertStringToPolynomial("2y-4z+6");
    Polynomial c = ps.convertStringToPolynomial("6");

    Polynomial ans = ps.convertStringToPolynomial("xyz+3x+2y-4z+6");

    std::map<std::string, const Polynomial&> polyMap = { {"a", a},  { "b", b}, { "c", c} };
    std::string expression = "a+b";
    ea.analyzeExpression(expression, orp);
    ea.calculateSummaryPolynomial(polyMap);

    EXPECT_TRUE(ea.calculateSummaryPolynomial(polyMap) == ans);
}

TEST(EA_v1, EA_Throws_Error_when_not_given_neded_polynmial) {
    EA_v1 ea;
    std::set<std::string> orp;
    Parser_v1 ps;
    Polynomial a = ps.convertStringToPolynomial("xyz+3x");
    // Polynomial b = ps.convertStringToPolynomial("2y-4z+6");
    Polynomial c = ps.convertStringToPolynomial("6");

    Polynomial ans = ps.convertStringToPolynomial("xyz+3x+2y-4z+6");

    std::map<std::string, const Polynomial&> polyMap = { {"a", a}, { "c", c} };
    std::string expression = "a+b";
    ea.analyzeExpression(expression, orp);

    EXPECT_ANY_THROW(ea.calculateSummaryPolynomial(polyMap));
}

TEST(EA_v1, EA_could_calc_expressions_with_functions) {
    EA_v1 ea;
    std::set<std::string> orp;
    Parser_v1 ps;
    Polynomial a = ps.convertStringToPolynomial("xyz+3x");
    Polynomial c = ps.convertStringToPolynomial("6");

    Polynomial ans = ps.convertStringToPolynomial("-yz+3");

    std::map<std::string, const Polynomial&> polyMap = { {"a", a}, { "c", c} };
    std::string expression = "-d_dx(a)+c";
    ea.analyzeExpression(expression, orp);
    Polynomial hh = ea.calculateSummaryPolynomial(polyMap);

    EXPECT_TRUE(hh == ans);
}
