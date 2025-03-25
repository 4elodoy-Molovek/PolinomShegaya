#pragma once
#include "Table.h"

class SortedArrayTable : public Table
{
protected:
	Polynomial** data;
	size_t size;
	size_t bufferSize;

public:
	SortedArrayTable(size_t sz = defaultSize);
	~SortedArrayTable() override;

	// ��������� ������� pol � ������� � ������(������) name
	virtual void addElement(const std::string& name, const Polynomial& pol) override;

	// ������� �� ������� � ������ name �� �������
	virtual void deleteElement(const std::string& name) override;

	// ���� � ������� ������� � ������ name
	virtual const Polynomial& findElement(const std::string& name) override;
};