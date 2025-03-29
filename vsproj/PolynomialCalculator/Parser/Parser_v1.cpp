#include "Parser_v1.h"
#include <sstream>

Polynomial Parser_v1::convertStringToPolynomial(const std::string poly_string)
{
    std::regex term_pattern(R"(([+-]?\d*)\*?([a-zA-Z])?\^?(\d*)?)");
    std::sregex_iterator iter(poly_string.begin(), poly_string.end(), term_pattern);
    std::sregex_iterator end;

    Polynomial result;
    while (iter != end)
    {
        std::smatch match = *iter;
        int coefficient = match[1].str().empty() ? 1 : std::stoi(match[1].str());
        unsigned exponent = match[3].str().empty() ? 1 : std::stoi(match[3].str());

        Polynomial::polynomialData term{ coefficient, exponent };
        result.insertMonom(term);
        ++iter;
    }
    return result;
}

std::string Parser_v1::convertPolynomialToString(const Polynomial& poly)
{
    std::ostringstream oss;
    for (const auto& term : poly.monoms)
    {
        if (!oss.str().empty() && term.c > 0) oss << " + ";
        if (term.c < 0) oss << " - ";
        oss << abs(term.c) << "x^" << term.grades;
    }
    return oss.str();
}
