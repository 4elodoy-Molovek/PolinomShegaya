#pragma once
#include <string>
#include <vector>
#include "Polynomial.h"

class ExpressionAnalyzer 
{
public:
	Polynomial<polynomialData> calculateSummaryPolynomial();
private:
	virtual std::vector<std::string> getPostfix(const std::string expression) = 0;
	virtual bool check(const std::string poly_string) = 0;
};