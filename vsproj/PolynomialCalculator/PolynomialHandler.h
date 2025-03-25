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
	size_t activeTableID;

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

	void addPolynomial(const std::string& name, const std::string& notation)
	{

	}

	void deletePolynomial(const std::string& name);

	Polynomial calculatePolynomialExpression(const std::string expression);

	const Polynomial& findPolynomial(const std::string& name);

	void setActiveTable(size_t newActiveTable);
	size_t GetActiveTable();
};

