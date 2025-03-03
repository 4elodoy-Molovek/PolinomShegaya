#pragma once
#include <Polynomial.h>
#include <Table.h>

class HashTableTwo : public Table
{
protected:
	struct Node
	{
		Polynomial data;
		bool deleted;
	};
	int size; // ������� ��������� � ��� ������ � ������� (��� ����� deleted)
	int bufferSize; // ������ ������ �������, ������� ������ �������� ��� �������� ����� �������
	int sizeAllNonNullptr; // ������� ��������� � ��� ������ � ������� (� ������ deleted)

public:
	HashTableTwo(size_t sz = defaultSize);
	~HashTableTwo() override;

	void addElement(const Polynomial& pol) override;
	void deleteElement(const Polynomial& pol) override;
	void findELement(const Polynomial& pol) override;
};