#pragma once
#include "Table.h"


class HashTableOne : public Table 
{
protected:
	struct Node
	{
		Polynomial<polynomialData> data;
		bool deleted;
	};
	int size; // сколько элементов у нас сейчас в массиве (без учета deleted)
	int bufferSize; // размер самого массива, сколько памяти выделено под хранение нашей таблицы
	int sizeAllNonNullptr; // сколько элементов у нас сейчас в массиве (с учетом deleted)

public:
	HashTableOne(size_t sz = defaultSize);
	~HashTableOne() override;

	void addElement(const Polynomial<polynomialData>& pol) override;
	void deleteElement(const Polynomial<polynomialData>& pol) override;
	void findElement(const Polynomial<polynomialData>& pol) override;
};