#pragma once
#include <string>
#include <vector>
#include "Polynomial.h"

class ExpressionAnalyzer 
{
public:
	Polynomial<polynomialData> calculateSummaryPolynomial();
private:
	std::vector<std::string> getPostfix(const std::string expression);
	bool check(const std::string poly_string);
};