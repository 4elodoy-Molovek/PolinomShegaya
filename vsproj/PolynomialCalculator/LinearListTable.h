#pragma once
#include "Table.h"

struct ListTableString {
	std::string name;
	Polynomial poly;
};

class LinearListTable : public Table
{
protected:
	List<ListTableString>* data;

public:
	LinearListTable(size_t sz = defaultSize);
	~LinearListTable() override;

	// ��������� ������� pol � ������� � ������(������) name
	virtual void addElement(const std::string& name, const Polynomial& pol) override;

	// ������� �� ������� � ������ name �� �������
	virtual void deleteElement(const std::string& name) override;

	// ���� � ������� ������� � ������ name
	virtual const Polynomial& findElement(const std::string& name) override;
};