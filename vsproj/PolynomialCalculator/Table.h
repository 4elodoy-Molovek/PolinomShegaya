#pragma once

#include <vector>

template<typename K, typename T>
class Table 
{

protected:

	static const size_t defaultSize = 4;

public:
	Table() {}
	virtual ~Table() = 0;

	// Добавляет в таблицу элемент с ключем key
	virtual void addElement(const K& key, const T& pol) = 0;

	// Удаляет из таблицы элемент с ключем key
	virtual void deleteElement(const K& key) = 0;

	// Ищет и возвращает ссылку на элемент с ключем K, в противном случае бросает исключение
	virtual T* findElement(const K& key) = 0;

	// В outElements помещает все элементы таблицы в некотором порядке
	virtual void getAllElements(std::vector<std::pair<const K&, const T&>>& outElements) = 0;
};
