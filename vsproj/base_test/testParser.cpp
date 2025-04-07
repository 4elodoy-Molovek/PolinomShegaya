#include <gtest.h>
#include "Parser_v1.h"

TEST(ParserV1Test, ParseSimplePolynomial) 
{
    Parser_v1 parser;
    std::string input = "2x^2y + 3z - 5";
    Polynomial poly = parser.convertStringToPolynomial(input);

    EXPECT_EQ(poly.calculate(1, 1, 1), 2 + 3 - 5); // 0
    EXPECT_EQ(poly.calculate(2, 3, 4), 2 * 4 * 3 + 3 * 4 - 5); // 24 + 12 - 5 = 31
}

TEST(ParserV1Test, ParseNegativeCoefficients) 
{
    Parser_v1 parser;
    std::string input = "-x^2 - 2y^2 + z";
    Polynomial poly = parser.convertStringToPolynomial(input);

    EXPECT_EQ(poly.calculate(2, 3, 1), -4 - 18 + 1); // -21
}

TEST(ParserV1Test, ParseImpliedPowers) 
{
    Parser_v1 parser;
    std::string input = "x + y + z";
    Polynomial poly = parser.convertStringToPolynomial(input);

    EXPECT_EQ(poly.calculate(1, 2, 3), 1 + 2 + 3);
}

TEST(ParserV1Test, ParseImpliedCoefficientOne) 
{
    Parser_v1 parser;
    std::string input = "x^2y - yz + z";
    Polynomial poly = parser.convertStringToPolynomial(input);

    EXPECT_EQ(poly.calculate(2, 3, 4), 2 * 2 * 3 - 3 * 4 + 4); // 12 - 12 + 4 = 4
}

TEST(ParserV1Test, ToStringSimple) 
{
    Parser_v1 parser;
    Polynomial p;
    p.insertMonomLast(2, 210); // 2x^2y
    p.insertMonomLast(-1, 1);  // -z
    p.insertMonomLast(5, 0);   // +5

    std::string result = parser.convertPolynomialToString(p);
    EXPECT_EQ(result, "2x^2y-z+5");
}

TEST(ParserV1Test, ConvertBackAndForth) 
{
    Parser_v1 parser;
    std::string input = "3x^2y - 4y^2 + 7z - 1";
    Polynomial poly = parser.convertStringToPolynomial(input);
    std::string output = parser.convertPolynomialToString(poly);

    Polynomial reparsed = parser.convertStringToPolynomial(output);

    EXPECT_TRUE(poly == reparsed);
}

TEST(ParserV1Test, ParseZero) 
{
    Parser_v1 parser;
    std::string input = "0";
    Polynomial poly = parser.convertStringToPolynomial(input);
    EXPECT_EQ(poly.calculate(10, 10, 10), 0);
    EXPECT_EQ(parser.convertPolynomialToString(poly), "0");
}

TEST(ParserV1Test, ParseWithSpacesAndSigns) 
{
    Parser_v1 parser;
    std::string input = " + 2x^2  -  3 y +  z ";
    Polynomial poly = parser.convertStringToPolynomial(input);
    EXPECT_EQ(poly.calculate(2, 1, 3), 2 * 4 - 3 * 1 + 3); // 8 - 3 + 3 = 8
}
