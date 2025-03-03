#pragma once
#include <Polynomial.h>
#include <Table.h>

class LinearListTable : public Table
{
protected:
	List* data;

public:
	LinearListTable(size_t sz = defaultSize);
	~LinearListTable() override;

	void addElement(const Polynomial& pol) override;
	void deleteElement(const Polynomial& pol) override;
	void findELement(const Polynomial& pol) override;
};