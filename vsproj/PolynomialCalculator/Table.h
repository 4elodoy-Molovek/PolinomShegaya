#pragma once
#include <vector>

class Table 
{
protected:
	static const size_t defaultSize = 4;
	unsigned activeTableId;

public:
	Table() {}
	virtual ~Table() = 0;

    // Добавляет полином pol в таблицу с ключем(именем) name
	virtual void addElement(const std::string& name, const Polynomial& pol) = 0;

	// Удаляет из полином с именем name из таблицы
	virtual void deleteElement(const std::string& name) = 0;

	// Ищет и возвращает ссылку на элемент с ключем K, в противном случае бросает исключение
	virtual T* findElement(const K& key) = 0;

	// В outElements помещает все элементы таблицы в некотором порядке
	virtual void getAllElements(std::vector<std::pair<const K&, const T&>>& outElements) = 0;
};
