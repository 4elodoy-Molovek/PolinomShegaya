#pragma once
#include "Table.h"
#include "ExpressionAnalyzer.h"
#include "Parser.h"

class PolynomialHandler 
{

private:

	Table* tableList[6];
	ExpressionAnalyzer* analyzer;
	Parser* pars;

public:

	PolynomialHandler()
	{
		// Инициализация (Создание) Таблиц, ExpressionAnalyzer и Parser
	}

	void addPolynomial()
	{
		pars->convertPolynomialToString();

	}
	void deletePolynomial();
	void findPolynomial();

	void calculatePolynomialExpression(const std::string expression);
};

