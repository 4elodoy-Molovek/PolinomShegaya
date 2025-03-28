#pragma once
#include <string>
#include <vector>
#include <map>
#include <set>
#include "Polynomial.h"


/*
 * �������� �� ��������� �������������� ��������� � ����������
 */

class ExpressionAnalyzer 
{
	// ����������� ����� ���������� ������������������� ���������
	std::vector<std::string> cachedPostfix;

public:

	ExpressionAnalyzer() {}
	virtual ~ExpressionAnalyzer() {}

	/* 
	 * ����������� ��������� ����� ��� ����������� ����� � ��������� � � cachedPostfix
	 * � outRequestedPolynomials ����� ������� ����� ���������, ������� ���������� �������� �� ������
	 * 
	 * �����������:
	 *		1) ��������� �������� '+', '-', '* �� �������', '* �� ���������';
	 *		2) ��������� ������ '(' � ')';
	 *		3) ������� ��������� ������������� �� ���� � ����� �������������� ��� ���������;
	 *		4) ����� ������ ������� �������������� ��� ����� ���������;
	 *		5) ��������� ������ ����� ���� '*';
	 *		6) ��� ����������� ������ ������� ����������
	 */
	virtual void analyzeExpression(const std::string& expression, std::set<std::string>& outRequestedPolynomials) = 0;

	/*
	 * ��������� ��������� ���������� ������������������� ���������
	 * � polynomials �������� ��������, ����������� � outRequestedPolynomials, ���������� �� analyzeExpression
	 */
	virtual Polynomial calculateSummaryPolynomial(const std::map<std::string, const Polynomial&> polynomials) = 0;

private:

	// ������ ����������� ����� ���������
	virtual std::vector<std::string> getPostfix(const std::string& expression) = 0;
};