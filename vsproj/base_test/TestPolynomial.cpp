#include <gtest.h>
#include "Polynomial.h"

// Вспомогательная функция для сравнения двух полиномов
bool polynomialsEqual(const Polynomial& a, const Polynomial& b) {
    return a == b;
}

TEST(PolynomialTest, ConstructorConstant) {
    Polynomial p(5);
    EXPECT_DOUBLE_EQ(p.calculate(0, 0, 0), 5);
}

TEST(PolynomialTest, InsertMonomLast) {
    Polynomial p;
    p.insertMonomLast(3.0, 10200); // 3x^1y^2z^0
    EXPECT_DOUBLE_EQ(p.calculate(1, 2, 3), 3.0 * 1 * 4); // 3 * x^1 * y^2 = 12
}

TEST(PolynomialTest, OperatorAddition) {
    Polynomial a, b;
    a.insertMonom(2.0, 10000); // 2x^1
    b.insertMonom(3.0, 10000); // 3x^1

    Polynomial result = a + b;
    EXPECT_DOUBLE_EQ(result.calculate(2, 0, 0), 10.0); // 5x^1 = 5*2 = 10
}

TEST(PolynomialTest, OperatorSubtraction) {
    Polynomial a, b;
    a.insertMonom(5.0, 100); // 5y^1
    b.insertMonom(2.0, 100); // 2y^1

    Polynomial result = a - b;
    EXPECT_DOUBLE_EQ(result.calculate(0, 3, 0), 9.0); // 3y^1 = 3*3 = 9
}

TEST(PolynomialTest, OperatorMultiplicationScalar) {
    Polynomial p(2);
    Polynomial result;
    result = p * 3;
    EXPECT_DOUBLE_EQ(result.calculate(0, 0, 0), 6);
}

TEST(PolynomialTest, OperatorMultiplicationPolynomials) {
    Polynomial a, b;
    a.insertMonom(2.0, 10000); // 2x^1
    b.insertMonom(3.0, 1);   // 3z^1

    Polynomial result = a * b;
    EXPECT_DOUBLE_EQ(result.calculate(2, 0, 2), 24.0); // 6xz = 6*2*2 = 24
}

TEST(PolynomialTest, Derivate) {
    Polynomial p;
    p.insertMonom(3.0, 20100); // 3x^2y^1

    Polynomial dx = p.derivate("x");
    EXPECT_DOUBLE_EQ(dx.calculate(2, 3, 0), 36.0); // 6xy = 6*2*3 = 36

    Polynomial dy = p.derivate("y");
    EXPECT_DOUBLE_EQ(dy.calculate(2, 3, 0), 12.0); // 3x^2 = 3*4 = 12
}

TEST(PolynomialTest, Integrate) {
    Polynomial p;
    p.insertMonom(6.0, 10000); // 6x^1

    Polynomial integral = p.integrate("x");
    EXPECT_DOUBLE_EQ(integral.calculate(2, 0, 0), 12.0); // (6x^2)/2 = 3x^2 = 3*4 = 12
}

TEST(PolynomialTest, EqualityOperator) {
    Polynomial p1, p2;
    p1.insertMonom(2, 100);
    p2.insertMonom(2, 100);
    EXPECT_TRUE(p1 == p2);
}

TEST(PolynomialTest, ZeroPolynomial) {
    Polynomial p;
    EXPECT_DOUBLE_EQ(p.calculate(10, 10, 10), 0);
}

TEST(PolynomialEqualityTest, SameOrderSameMonoms)
{
    Polynomial p1;
    p1.insertMonom(-3, 10); // -3y
    p1.insertMonom(2, 0);   // +2

    Polynomial p2;
    p2.insertMonom(-3, 10); // -3y
    p2.insertMonom(2, 0);   // +2

    EXPECT_TRUE(p1 == p2);
}

TEST(PolynomialEqualityTest, DifferentOrderSameMonoms)
{
    Polynomial p1;
    p1.insertMonom(-3.0, 10); // -3y
    p1.insertMonom(2.0, 0);   // +2

    Polynomial p2;
    p2.insertMonom(2.0, 0);   // +2
    p2.insertMonom(-3.0, 10); // -3y

    EXPECT_TRUE(p1 == p2);
}

TEST(PolynomialEqualityTest, DifferentMonoms)
{
    Polynomial p1;
    p1.insertMonom(5, 0);   // 5

    Polynomial p2;
    p2.insertMonom(3, 0);   // 3

    EXPECT_FALSE(p1 == p2);
}

TEST(PolynomialEqualityTest, ZeroPolynomials)
{
    Polynomial p1;
    Polynomial p2;

    EXPECT_TRUE(p1 == p2);
}

TEST(PolynomialEqualityTest, MonomCancellation)
{
    Polynomial p1;
    p1.insertMonom(3, 100);   // 3x
    p1.insertMonom(-3, 100);  // -3x → cancelled

    Polynomial p2;

    EXPECT_TRUE(p1 == p2);
}

TEST(PolynomialEqualityTest, CommutativeAddition)
{
    Polynomial p1;
    p1.insertMonom(1.0, 100);   // x
    p1.insertMonom(2.0, 10);    // 2y

    Polynomial p2;
    p2.insertMonom(2.0, 10);    // 2y
    p2.insertMonom(1.0, 100);   // x

    EXPECT_TRUE(p1 == p2);
}