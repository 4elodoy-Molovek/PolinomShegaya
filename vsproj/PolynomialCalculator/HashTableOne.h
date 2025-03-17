#pragma once
#include "Table.h"


class HashTableOne : public Table 
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
	HashTableOne(size_t sz = defaultSize);
	~HashTableOne() override;

	void addElement(const Polynomial<polynomialData>& pol) override;
	void deleteElement(const Polynomial<polynomialData>& pol) override;
	void findElement(const Polynomial<polynomialData>& pol) override;
};