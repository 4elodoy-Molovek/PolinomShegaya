#pragma once
#include "Table.h"
#include "ExpressionAnalyzer.h"
#include "Parser.h"

class PolynomialHandler 
{

private:

	// ������ ���������� �� ��� ���� ������
	Table* tableList[6];

	// ������ �������� �������
	int activeTableID;

	/* ��������� �� ������ ������ ExpressionAnalyzer, 
	 * ���������� �� ��������� �������������� ��������� � ����������.
	 */
	ExpressionAnalyzer* analyzer;
	
	/* ��������� �� ������ ������ Parser, 
	 * ���������� �� ������� ��������� ������� �������� � ��� ����������� ������������� � ���� ������� ������ Polynomial
	 */
	Parser* parser;

public:

	PolynomialHandler()
	{
		// ������������� (��������) ������, ExpressionAnalyzer � Parser
	}

	void addPolynomial()
	{

	}
	void deletePolynomial();
	void findPolynomial();

	void calculatePolynomialExpression(const std::string expression);
};

