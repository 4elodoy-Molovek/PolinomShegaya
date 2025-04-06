#pragma once
#include "Table.h"

template<typename K, typename T>
class HashTableTwo : public Table<K, T>
{
protected:
	struct Node
	{
		T data;
		bool deleted;
	};
	int size; // сколько элементов у нас сейчас в массиве (без учета deleted)
	int bufferSize; // размер самого массива, сколько памяти выделено под хранение нашей таблицы
	int sizeAllNonNullptr; // сколько элементов у нас сейчас в массиве (с учетом deleted)

public:
	HashTableTwo(size_t sz = defaultSize);
	~HashTableTwo() override;

	// Добавляет в таблицу элемент с ключем key
	virtual void addElement(const K& key, const T& pol) override;

	// Удаляет из таблицы элемент с ключем key
	virtual void deleteElement(const K& key) override;

	// Ищет и возвращает ссылку на элемент с ключем K, в противном случае бросает исключение
	virtual T& findElement(const K& key) override;
};