#pragma once
#include "Table.h"

class SortedArrayTable : public Table
{
protected:
	Polynomial<polynomialData>** data;
	size_t size;
	size_t bufferSize;

public:
	SortedArrayTable(size_t sz = defaultSize);
	~SortedArrayTable() override;

	void addElement(const Polynomial<polynomialData>& pol) override;
	void deleteElement(const Polynomial<polynomialData>& pol) override;
	void findELement(const Polynomial<polynomialData>& pol) override;
};