#pragma once
#include "Table.h"

struct ListTableString {
	std::string name;
	Polynomial<polynomialData> poly;
};

class LinearListTable : public Table
{
protected:
	List<ListTableString>* data;

public:
	LinearListTable(size_t sz = defaultSize);
	~LinearListTable() override;

	void addElement(const Polynomial<polynomialData>& pol) override;
	void deleteElement(const Polynomial<polynomialData>& pol) override;
	void findElement(const Polynomial<polynomialData>& pol) override;
};