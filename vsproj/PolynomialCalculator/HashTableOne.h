#pragma once
#include "Table.h"


class HashTableOne : public Table 
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
	HashTableOne(size_t sz = defaultSize);
	~HashTableOne() override;

	// ��������� ������� pol � ������� � ������(������) name
	virtual void addElement(const std::string& name, const Polynomial& pol) override;

	// ������� �� ������� � ������ name �� �������
	virtual void deleteElement(const std::string& name) override;

	// ���� � ������� ������� � ������ name
	virtual const Polynomial& findElement(const std::string& name) override;
};