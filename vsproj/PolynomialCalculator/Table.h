#pragma once
#include "Polynomial.h"

class Table 
{

protected:

	static const size_t defaultSize = 4;
	unsigned activeTableId;

public:
	Table();
	virtual ~Table() = 0;

    // ��������� ������� pol � ������� � ������(������) name
	virtual void addElement(const std::string& name, const Polynomial& pol) = 0;

	// ������� �� ������� � ������ name �� �������
	virtual void deleteElement(const std::string& name) = 0;

	// ���� � ������� ������� � ������ name
	virtual const Polynomial& findElement(const std::string& name) = 0;
};
