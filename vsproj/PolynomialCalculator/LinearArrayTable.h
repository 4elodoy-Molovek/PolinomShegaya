#pragma once
#include "Table.h"

class LinearArrayTable : public Table 
{
protected:
	Polynomial** data; // ???
	size_t size;
	size_t bufferSize;

public:
	LinearArrayTable(size_t sz = defaultSize);
	~LinearArrayTable() override;

	// Добавляет полином pol в таблицу с ключем(именем) name
	virtual void addElement(const std::string& name, const Polynomial& pol) override;

	// Удаляет из полином с именем name из таблицы
	virtual void deleteElement(const std::string& name) override;

	// Ищет в таблице полином с именем name
	virtual const Polynomial& findElement(const std::string& name) override;
};