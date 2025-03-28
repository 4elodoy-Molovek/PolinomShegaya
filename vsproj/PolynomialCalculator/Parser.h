#pragma once
#include "Polynomial.h"


class Parser 
{

public:

	Parser() {}
	virtual ~Parser() {}

   /* ����������� ��������� ������� �������� � ��� ���������� �������������
	* ��� ����������� ������ ������ ����������
	*/
	virtual Polynomial convertStringToPolynomial(const std::string poly_string) = 0;

	// ����������� ������� � ��������� �������
	virtual std::string convertPolynomialToString(const Polynomial& poly) = 0;

};