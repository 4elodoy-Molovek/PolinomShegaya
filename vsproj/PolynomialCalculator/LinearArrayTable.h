#pragma once
#include <Polynomial.h>
#include <Table.h>

class LinearArrayTable : public Table 
{
protected:
	Polynomial** data;
	size_t size;
	size_t bufferSize;

public:
	LinearArrayTable(size_t sz = defaultSize);
	~LinearArrayTable() override;

	void addElement(const Polynomial& pol) override;
	void deleteElement(const Polynomial& pol) override;
	void findELement(const Polynomial& pol) override;
};