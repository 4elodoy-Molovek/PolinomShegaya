#pragma once
#include "Table.h"
#include "ExpressionAnalyzer.h"
#include "Parser.h"

class PolynomialHandler 
{
private:
	Table* tableList[6];
	ExpressionAnalyzer analyzer;
	Parser pars;
public:
	void addPolynomial();
	void deletePolynomial();
	void findPolynomial();

	Polynomial calculatePolynomialExpression(const std::string expression);
};

