#pragma once
#include <string>
#include "List.h"


class Polynomial 
{
private:

	// �������� ������ �� ����� ������
	struct polynomialData {
		int c;
		unsigned grades;
	};

	// ���� ���� ������� ��������
	List<polynomialData> monoms;

	// ������� ������ � ���������� ������� (������������ ����������������� ��������)
	void insertMonom(polynomialData& el);

	// ������� ������ � ����� ������ (����������� ������� �� ������� ������������)
	void insertMonomLast(polynomialData& el);


public:

	// ����������� �� ���������
	Polynomial();

	// ����������� �����������
	Polynomial(const Polynomial& pl);

	// ����������
	~Polynomial();

	// �������� �������������
	Polynomial* operator= (const Polynomial& poly);

	// �������� ��������� ���������
	bool operator==(const Polynomial& pl);

	// �������� ���������
	Polynomial operator+ (const Polynomial& rhs);
	// ��������� ���������
	Polynomial operator- (const Polynomial& rhs);
	// ��������� ���������
	Polynomial operator* (const Polynomial& rhs);
	// ��������� �������� �� ���������
	Polynomial operator* (const float scalar);

	// ������ ����������� ��������
	Polynomial derivate(const std::string& var);
	// �������������� ��������
	Polynomial integrate(const std::string& var);

	// ��������� �������� �������� � �����
	long calculate(const int px, const int py, const int pz);

	friend std::ostream& operator<<(std::ostream& os, const Polynomial& pl);
};

