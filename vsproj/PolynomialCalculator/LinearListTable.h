#pragma once
#include "Table.h"

template<typename K, typename T>
class LinearListTable : public Table<K, T>
{
protected:

	template<typename K, typename T>
	struct ListTableString {
		K key;
		T value;
	};

	List<ListTableString> data;

public:
	LinearListTable(size_t sz = defaultSize);
	~LinearListTable() override;

	// Добавляет в таблицу элемент с ключем key
	virtual void addElement(const K& key, const T& pol) override;

	// Удаляет из таблицы элемент с ключем key
	virtual void deleteElement(const K& key) override;

	// Ищет и возвращает ссылку на элемент с ключем K, в противном случае бросает исключение
	virtual T& findElement(const K& key) override;
};