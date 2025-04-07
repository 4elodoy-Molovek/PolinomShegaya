#include <gtest.h>
#include "Polynomial.h"

// Вспомогательная функция для сравнения двух полиномов
bool polynomialsEqual(const Polynomial& a, const Polynomial& b) {
    return a == b;
}

TEST(PolynomialTest, ConstructorConstant) {
    Polynomial p(5);
    EXPECT_EQ(p.calculate(0, 0, 0), 5);
}

TEST(PolynomialTest, InsertMonomLast) {
    Polynomial p;
    p.insertMonomLast(3, 120); // 3x^1y^2z^0
    EXPECT_EQ(p.calculate(1, 2, 3), 3 * 1 * 4); // 3 * x^1 * y^2 = 12
}

TEST(PolynomialTest, OperatorAddition) {
    Polynomial a, b;
    a.insertMonomLast(2, 100); // 2x^1
    b.insertMonomLast(3, 100); // 3x^1

    Polynomial result;
    result = a + b;
    EXPECT_EQ(result.calculate(2, 0, 0), 10); // 5x^1 = 5*2 = 10
}

TEST(PolynomialTest, OperatorSubtraction) {
    Polynomial a, b;
    a.insertMonomLast(5, 10); // 5y^1
    b.insertMonomLast(2, 10); // 2y^1

    Polynomial result;
    result = a - b;
    EXPECT_EQ(result.calculate(0, 3, 0), 9); // 3y^1 = 3*3 = 9
}

TEST(PolynomialTest, OperatorMultiplicationScalar) {
    Polynomial p(2);
    Polynomial result;
    result = p * 3;
    EXPECT_EQ(result.calculate(0, 0, 0), 6);
}

TEST(PolynomialTest, OperatorMultiplicationPolynomials) {
    Polynomial a, b;
    a.insertMonomLast(2, 100); // 2x^1
    b.insertMonomLast(3, 1);   // 3z^1

    Polynomial result;
    result = a * b;
    EXPECT_EQ(result.calculate(2, 0, 2), 24); // (2x^1 * 3z^1) = 6xz = 6*2*2 = 24
}

TEST(PolynomialTest, Derivate) {
    Polynomial p;
    p.insertMonomLast(3, 210); // 3x^2y^1

    Polynomial dx;
    dx = p.derivate("x");
    EXPECT_EQ(dx.calculate(2, 3, 0), 36); // 6xy = 6*2*3 = 36

    Polynomial dy;
    dy = p.derivate("y");
    EXPECT_EQ(dy.calculate(2, 3, 0), 12); // 3x^2 = 3*4 = 12
}

TEST(PolynomialTest, Integrate) {
    Polynomial p;
    p.insertMonomLast(6, 100); // 6x^1

    Polynomial integral = p.integrate("x");
    EXPECT_EQ(integral.calculate(2, 0, 0), 8); // (6x^2)/2 = 3x^2 = 3*4 = 12
}

TEST(PolynomialTest, EqualityOperator) {
    Polynomial p1, p2;
    p1.insertMonomLast(2, 100);
    p2.insertMonomLast(2, 100);
    EXPECT_TRUE(p1 == p2);
}

TEST(PolynomialTest, ZeroPolynomial) {
    Polynomial p;
    EXPECT_EQ(p.calculate(10, 10, 10), 0);
}
