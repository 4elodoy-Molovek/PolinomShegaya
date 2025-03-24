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
		// Node<polynomialData>* parent;
		// Node<polynomialData>* left;
		// Node<polynomialData>* right;
	};

public:
	TreeTable(size_t sz = defaultSize);
	~TreeTable() override;

	// ��������� ������� pol � ������� � ������(������) name
	virtual void addElement(const std::string& name, const Polynomial& pol) override;

	// ������� �� ������� � ������ name �� �������
	virtual void deleteElement(const std::string& name) override;

	// ���� � ������� ������� � ������ name
	virtual const Polynomial& findElement(const std::string& name) override;
};