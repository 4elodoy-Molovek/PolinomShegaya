#pragma once
#include "Table.h"

class SortedArrayTable : public Table
{
protected:
	Polynomial** data;
	size_t size;
	size_t bufferSize;

public:
	SortedArrayTable(size_t sz = defaultSize);
	~SortedArrayTable() override;

	// Добавляет полином pol в таблицу с ключем(именем) name
	virtual void addElement(const std::string& name, const Polynomial& pol) override;

	// Удаляет из полином с именем name из таблицы
	virtual void deleteElement(const std::string& name) override;

	// Ищет в таблице полином с именем name
	virtual const Polynomial& findElement(const std::string& name) override;
};