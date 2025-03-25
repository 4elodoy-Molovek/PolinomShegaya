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
	void analyzeExpression(const std::string& expression, std::set<std::string>& outRequestedPolynomials);

	/*
	 * ��������� ��������� ���������� ������������������� ���������
	 * � polynomials �������� ��������, ����������� � outRequestedPolynomials, ���������� �� analyzeExpression
	 */
	Polynomial calculateSummaryPolynomial(const std::map<std::string, const Polynomial&> polynomials);

private:

	// ������ ����������� ����� ���������
	virtual std::vector<std::string> getPostfix(const std::string& expression) = 0;
};