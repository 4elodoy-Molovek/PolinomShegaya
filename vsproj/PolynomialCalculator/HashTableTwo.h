#pragma once
#include <Polynomial.h>
#include <Table.h>

class HashTableTwo : public Table
{
protected:
	struct Node
	{
		Polynomial data;
		bool deleted;
	};
	int size; // сколько элементов у нас сейчас в массиве (без учета deleted)
	int bufferSize; // размер самого массива, сколько памяти выделено под хранение нашей таблицы
	int sizeAllNonNullptr; // сколько элементов у нас сейчас в массиве (с учетом deleted)

public:
	HashTableTwo(size_t sz = defaultSize);
	~HashTableTwo() override;

	void addElement(const Polynomial& pol) override;
	void deleteElement(const Polynomial& pol) override;
	void findELement(const Polynomial& pol) override;
};