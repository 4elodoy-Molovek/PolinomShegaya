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


// Postfix Errors


























/*


// Тест на корректность постфиксной формы
TEST(EA_v1, PostfixConversion) {
    EA_v1 ea;
    std::set<std::string> requestedPOLYLOLs;

    // Простое выражение: a + b -> a b +
    ea.analyzeExpression("a + b", requestedPOLYLOLs);
    auto postfix = ea.getCachedPurePostfix();
    ASSERT_EQ(postfix, std::vector<std::string>({ "a", "b", "+" }));

    // Выражение с функциями: sin(a) -> a sin
    requestedPOLYLOLs.clear();
    ea.analyzeExpression("sin(a)", requestedPOLYLOLs);
    postfix = ea.getCachedPurePostfix();
    ASSERT_EQ(postfix, std::vector<std::string>({ "a", "sin" }));

    // Сложное выражение: cos(sin(b)) + (q * sin(word) * (a + c - f))
    // Ожидаемый постфикс: b sin cos q word sin * a c + f - * +
    requestedPOLYLOLs.clear();
    ea.analyzeExpression("cos(sin(b)) + (q * sin(word) * (a + c - f))", requestedPOLYLOLs);
    postfix = ea.getCachedPurePostfix();
    ASSERT_EQ(postfix, std::vector<std::string>({
        "b", "sin", "cos",
        "q", "word", "sin", "*",
        "a", "c", "+", "f", "-", "*", "+"
        }));
}

// Тест на запрос переменных
TEST(EA_v1, RequestedVariables) {
    EA_v1 ea;
    std::set<std::string> requestedPOLYLOLs;

    // Выражение: a + b * sin(c)
    ea.analyzeExpression("a + b * sin(c)", requestedPOLYLOLs);

    // Проверяем, что все переменные запрошены
    ASSERT_TRUE(requestedPOLYLOLs.count("a"));
    ASSERT_TRUE(requestedPOLYLOLs.count("b"));
    ASSERT_TRUE(requestedPOLYLOLs.count("c"));
    ASSERT_EQ(requestedPOLYLOLs.size(), 3);
}
/*
// Тест на вычисление выражения
TEST(EA_v1, ExpressionCalculation) {
    EA_v1 ea;
    std::set<std::string> requestedPOLYLOLs;

    // Подготовка тестовых данных
    std::map<std::string, POLYLOL&> POLYLOLs;
    POLYLOL a = createDummyPOLYLOL("a");
    POLYLOL b = createDummyPOLYLOL("b");
    POLYLOL c = createDummyPOLYLOL("c");

    // Здесь нужно добавить реальные полиномы в `POLYLOLs`
    // Например: POLYLOLs["a"] = a;

    // Тестируем выражение: a + b * c
    ea.analyzeExpression("a + b * c", requestedPOLYLOLs);
    POLYLOL result = ea.calculateSummaryPOLYLOL(POLYLOLs);

    // Здесь должна быть проверка результата
    // ASSERT_EQ(result, expectedResult);
}
*/

/*
int main(int argc, char** argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}

*/
