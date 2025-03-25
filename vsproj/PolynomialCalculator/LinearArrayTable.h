#pragma once
#include "Table.h"

class LinearArrayTable : public Table 
{
protected:
	Polynomial* data; // ???
	size_t size;
	size_t bufferSize;

public:
	LinearArrayTable(size_t sz = defaultSize);
	~LinearArrayTable() override;

	// ��������� ������� pol � ������� � ������(������) name
	virtual void addElement(const std::string& name, const Polynomial& pol) override;

	// ������� �� ������� � ������ name �� �������
	virtual void deleteElement(const std::string& name) override;

	// ���� � ������� ������� � ������ name
	virtual const Polynomial& findElement(const std::string& name) override;
};