#pragma once
#include "Table.h"

class HashTableTwo : public Table
{
protected:
	struct Node
	{
		Polynomial<polynomialData> data;
		bool deleted;
	};
	int size; // ������� ��������� � ��� ������ � ������� (��� ����� deleted)
	int bufferSize; // ������ ������ �������, ������� ������ �������� ��� �������� ����� �������
	int sizeAllNonNullptr; // ������� ��������� � ��� ������ � ������� (� ������ deleted)

public:
	HashTableTwo(size_t sz = defaultSize);
	~HashTableTwo() override;

	void addElement(const Polynomial<polynomialData>& pol) override;
	void deleteElement(const Polynomial<polynomialData>& pol) override;
	void findELement(const Polynomial<polynomialData>& pol) override;
};