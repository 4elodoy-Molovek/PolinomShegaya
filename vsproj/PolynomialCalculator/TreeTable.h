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

	// Добавляет полином pol в таблицу с ключем(именем) name
	virtual void addElement(const std::string& name, const Polynomial& pol) override;

	// Удаляет из полином с именем name из таблицы
	virtual void deleteElement(const std::string& name) override;

	// Ищет в таблице полином с именем name
	virtual const Polynomial& findElement(const std::string& name) override;
};