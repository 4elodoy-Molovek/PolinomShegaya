#pragma once
#include "Table.h"

template<typename K, typename T>
class SortedArrayTable : public Table<K, T>
{
protected:
	std::vector<T> data;
	size_t size;
	size_t bufferSize;

public:
	SortedArrayTable(size_t sz = defaultSize);
	~SortedArrayTable() override;

	// Добавляет в таблицу элемент с ключем key
	virtual void addElement(const K& key, const T& pol) override;

	// Удаляет из таблицы элемент с ключем key
	virtual void deleteElement(const K& key) override;

	// Ищет и возвращает ссылку на элемент с ключем K, в противном случае бросает исключение
	virtual T& findElement(const K& key) override;
};