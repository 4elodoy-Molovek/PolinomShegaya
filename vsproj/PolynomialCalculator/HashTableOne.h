#pragma once
#include "Table.h"

template<typename K, typename T>
class HashTableOne : public Table 
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
	HashTableOne(size_t sz = defaultSize) : size(0), bufferSize(sz), sizeAllNonNullptr(0)
	{
		table.resize(bufferSize);
	}

	~HashTableOne() override;

	// Добавляет полином pol в таблицу с ключем(именем) name
	virtual void addElement(const K& key, const T& pol) override
	{
		size_t index = hashFunction(key);
		for (auto& pair : table[index])
		{
			if (pair.first == key)
			{
				pair.second.data = pol;
				pair.second.deleted = false;
				return;
			}
		}
		table[index].emplace_back(key, Node{ pol, false });
		++size;
		++sizeAllNonNullptr;
	}

	// Удаляет из полином с именем name из таблицы
	virtual void deleteElement(const K& key) override
{
    size_t index = hashFunction(key);
    for (auto& pair : table[index])
    {
        if (pair.first == key && !pair.second.deleted)
        {
            pair.second.deleted = true;
            --size;
            return;
        }
    }
}

	// Ищет в таблице полином с именем name
	virtual const T* findElement(const K& key) override
	{
		size_t index = hashFunction(key);
		for (auto& pair : table[index])
		{
			if (pair.first == key && !pair.second.deleted)
			{
				return &pair.second.data;
			}
		}
		return nullptr;
	}

	virtual void getAllElements(std::vector<std::pair<const K&, const T&>>& outElements) override
	{
		for (int index = 0; index < sizeAllNonNullptr; index++)
		{
			for (auto& pair : table[index])
			{
				if (pair.first == key && !pair.second.deleted)
					outElements.emplace_back((*data)[i].key, (*data)[i].value);
			}
		}
	}
};