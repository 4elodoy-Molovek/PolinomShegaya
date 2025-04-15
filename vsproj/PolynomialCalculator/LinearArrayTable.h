#pragma once
#include "Table.h"
#include <vector>

#define DSIZE 4

template<typename K, typename T>
class LinearArrayTable : public Table<K, T>
{
protected:
	std::vector<std::pair<K, T>> data; // ???
	size_t size;

public:
	LinearArrayTable(size_t sz = DSIZE) : size(0)
	{
		data.reserve(DSIZE);
	}

	~LinearArrayTable() override {}

	// Добавляет в таблицу элемент с ключем key
	virtual void addElement(const K& key, const T& pol) override
	{
		for (auto& pair : data)
			if (pair.first == key)
				throw std::runtime_error("ERROR: LinearArrayTable: element with key '" + key + "' already exists!");

		data.push_back(std::pair<K, T>(key, pol));
		size++;
	}

	// Удаляет из таблицы элемент с ключем key
	virtual void deleteElement(const K& key) override
	{
		for (auto& pair : data)
			if (pair.first == key)
			{
				pair = data[data.size() - 1];
				data.pop_back();
				size--;

				return;
			}

		throw std::runtime_error("ERROR: LinearArrayTable: element with key '" + key + "' does not exist!");
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
	virtual void getAllElements(std::vector<std::pair<const K&, const T&>>& outElements) override
	{
		for (size_t i = 0; i < data.size(); i++)
			outElements.push_back({ data[i].first, data[i].second });
	}
};