#pragma once
#include "Polynomial.h"


class Table 
{
protected:
	static const size_t defaultSize = 4;
	unsigned activeTableId;

public:
	Table();
	virtual ~Table() = 0;

    // Добавляет полином pol в таблицу с ключем(именем) name
	virtual void addElement(const std::string& name, const Polynomial& pol) = 0;

	// Удаляет из полином с именем name из таблицы
	virtual void deleteElement(const std::string& name) = 0;

	// Ищет в таблице полином с именем name
	virtual const Polynomial& findElement(const std::string& name) = 0;
};
