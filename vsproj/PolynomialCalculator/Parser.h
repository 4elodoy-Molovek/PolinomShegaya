#pragma once
#include "Polynomial.h"
class Parser 
{
public:
	Polynomial convertStringToPolynomial(const std::string poly_string);
	std::string convertPolynomialToString(const Polynomial& poly);

private:
	bool check(const std::string poly_string);
};