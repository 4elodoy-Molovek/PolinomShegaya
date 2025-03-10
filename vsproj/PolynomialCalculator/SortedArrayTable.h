#pragma once
#include <Polynomial.h>
#include <Table.h>

class SortedArrayTable : public Table
{
protected:
	Polynomial** data;
	size_t size;
	size_t bufferSize;

public:
	SortedArrayTable(size_t sz = defaultSize);
	~SortedArrayTable() override;

	void addElement(const Polynomial& pol) override;
	void deleteElement(const Polynomial& pol) override;
	void findELement(const Polynomial& pol) override;
};