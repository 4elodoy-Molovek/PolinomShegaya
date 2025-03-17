#pragma once
#include "Table.h"

class LinearArrayTable : public Table 
{
protected:
	Polynomial<polynomialData>** data; // ???
	size_t size;
	size_t bufferSize;

public:
	LinearArrayTable(size_t sz = defaultSize);
	~LinearArrayTable() override;

	void addElement(const Polynomial<polynomialData>& pol) override;
	void deleteElement(const Polynomial<polynomialData>& pol) override;
	void findELement(const Polynomial<polynomialData>& pol) override;
};