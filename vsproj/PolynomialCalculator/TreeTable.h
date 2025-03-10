#pragma once
#include <Polynomial.h>
#include <Table.h>

class TreeTable : public Table
{
protected:
	struct TreeNode
	{
		Polynomial* data;
		int color;
		Node* parent;
		Node* left;
		Node* right;
	};

public:
	TreeTable(size_t sz = defaultSize);
	~TreeTable() override;

	void addElement(const Polynomial& pol) override;
	void deleteElement(const Polynomial& pol) override;
	void findELement(const Polynomial& pol) override;
};