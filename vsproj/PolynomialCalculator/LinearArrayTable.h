#pragma once
#include "Table.h"
#include <vector>

template<typename K, typename T>
class LinearArrayTable : public Table<K, T>
{
protected:
	std::vector<std::pair<K, T>> data; // ???
	size_t size;

public:
	LinearArrayTable(size_t sz = defaultSize): size(0)
	{
		data.resize(sz);
	}

	~LinearArrayTable() override {}

	// Добавляет в таблицу элемент с ключем key
	virtual void addElement(const K& key, const T& pol) override
	{
		for (auto& pair : data)
			if (pair.first == key)
				throw("ERROR: LinearArrayTable: element with key '" + key + "' already exists!");

		data.push_back(std::pair<K, T>(key, pol));
		sz++;
	}

	// Удаляет из таблицы элемент с ключем key
	virtual void deleteElement(const K& key) override
	{
		for (auto& pair : data)
			if (pair.first == key)
			{
				pair = data[data.size() - 1];
				data.pop_back();
				sz--;

				return;
			}

		throw("ERROR: LinearArrayTable: element with key '" + key + "' already exists!");
	}

	// Ищет и возвращает ссылку на элемент с ключем K, в противном случае бросает исключение
	virtual T* findElement(const K& key) override
	{
		for (auto& pair : data)
			if (pair.first == key)
				return &pair.second;

		return nullptr;
	}

	// В outElements помещает все элементы таблицы в некотором порядке
	virtual void getAllElements(std::vector<std::pair<const K&, const T&>>& outElements) override { outElements = data; }
};