#pragma once
#include "Table.h"
#include <stdexcept>

struct ListTableString {
	std::string name;
	Polynomial poly;
};

class LinearListTable : public Table
{
protected:
	List<ListTableString>* data;
	size_t size = 0;

public:
	LinearListTable(size_t sz = defaultSize);
	~LinearListTable() override;

	// Добавляет полином pol в таблицу с ключем(именем) name
	virtual void addElement(const std::string& name, const Polynomial& pol) override;

	// Удаляет из полином с именем name из таблицы
	virtual void deleteElement(const std::string& name) override;

	// Ищет в таблице полином с именем name
	virtual const Polynomial& findElement(const std::string& name) override;
};