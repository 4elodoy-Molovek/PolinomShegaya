#pragma once
#include "Polynomial.h"

class Table 
{
protected:
	static const size_t defaultSize = 4;

public:
	Table();
	virtual ~Table() = 0;

	//pure virtual
	virtual void addElement(const Polynomial& pol) = 0;
	virtual void deleteElement(const Polynomial& pol) = 0;
	virtual void findELement(const Polynomial& pol) = 0;
};
