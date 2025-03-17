#pragma once
#include "Polynomial.h"


class Table 
{
protected:
	static const size_t defaultSize = 4;
	unsigned activeTableId;

public:
	Table();
	virtual ~Table() = 0;

	//pure virtual
	virtual void addElement(const Polynomial<polynomialData>& pol) = 0;
	virtual void deleteElement(const Polynomial<polynomialData>& pol) = 0;
	virtual void findElement(const Polynomial<polynomialData>& pol) = 0;
};
