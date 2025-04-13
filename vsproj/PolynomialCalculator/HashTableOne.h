#pragma once
#include "Table.h"

#define DSIZE 4

template<typename K, typename T>
class HashTableOne : public Table<K, T>
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

	std::vector<std::vector<std::pair<K, Node>>> table;

	size_t hashFunction(const K& s)
	{
		size_t summary = 0;
		for (size_t i = 0; i < s.length(); i++)
		{
			summary += (s[i] * (i + 1));
		}
		return summary % bufferSize;
	}

public:
	HashTableOne(size_t sz = DSIZE) : size(0), bufferSize(sz), sizeAllNonNullptr(0)
	{
		table.resize(bufferSize);
	}

	~HashTableOne() override {}

	// Добавляет полином pol в таблицу с ключем(именем) name
	virtual void addElement(const K& key, const T& pol) override
	{
		if (findElement(key) != nullptr) throw std::runtime_error("Element with the same key already exists.");

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
		if (findElement(key) == nullptr) throw std::runtime_error("Element not found.");

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
	virtual T* findElement(const K& key) override
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
		for (int index = 0; index < table.size(); index++)
		{
			for (int i = 0; i < table[index].size(); i++)
			{
				if (!table[index][i].second.deleted)
					outElements.push_back({ table[index][i].first, table[index][i].second.data });
			}
		}
	}
};
