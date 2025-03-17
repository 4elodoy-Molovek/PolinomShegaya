#pragma once
#include "Polynomial.h"
class Parser 
{
public:
	Polynomial<polynomialData> convertStringToPolynomial(const std::string poly_string);
	std::string convertPolynomialToString(const Polynomial<polynomialData>& poly);

private:
	bool check(const std::string poly_string);
};