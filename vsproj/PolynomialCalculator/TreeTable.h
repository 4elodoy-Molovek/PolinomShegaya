#pragma once
#include <Polynomial.h>
#include <Table.h>

class TreeTable : public Table
{
protected:
	struct TreeNode
	{
		Polynomial<polynomialData>* data;
		int color;
		Node<polynomialData>* parent;
		Node<polynomialData>* left;
		Node<polynomialData>* right;
	};

public:
	TreeTable(size_t sz = defaultSize);
	~TreeTable() override;

	void addElement(const Polynomial<polynomialData>& pol) override;
	void deleteElement(const Polynomial<polynomialData>& pol) override;
	void findELement(const Polynomial<polynomialData>& pol) override;
};