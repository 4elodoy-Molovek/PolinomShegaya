#pragma once
#include "Table.h"
#include <stdexcept>
#include <vector>

template<typename K, typename T>
struct ListTablePair
{
	K key;
	T value;
};

template<typename K, typename T>
class LinearListTable : public Table<K, T>
{
protected:
	List<ListTablePair<K, T>>* data;
	size_t size = 0;

public:
	LinearListTable(size_t sz = defaultSize)
	{
		data = new List<ListTablePair<K, T>>();
		size = sz;
	}

	~LinearListTable() override
	{
		delete data;
	}

	virtual void addElement(const K& key, const T& value) override
	{
		for (size_t i = 0; i < data->size(); ++i)
		{
			if ((*data)[i].key == key)
				throw std::runtime_error("Element with this key already exists.");
		}


		ListTablePair<K, T> entry;
		entry.key = key;
		entry.value = value;

		data->insertLast(entry);
		size++;
	}

	virtual void deleteElement(const K& key) override
	{
		bool found = false;

		for (size_t i = 0; i < data->size(); ++i)
		{
			if ((*data)[i].key == key)
			{
				List<ListTablePair<K, T>>* newList = new List<ListTablePair<K, T>>();

				for (size_t j = 0; j < data->size(); ++j)
				{
					if (j != i)
						newList->insertLast((*data)[j]);
				}

				delete data;
				data = newList;
				size--;

				found = true;
				break;
			}
		}

		if (!found)
			throw std::runtime_error("Element not found for deletion.");
	}

	virtual T* findElement(const K& key) override
	{
		for (size_t i = 0; i < data->size(); ++i)
		{
			if ((*data)[i].key == key)
				return &(*data)[i].value;
		}

		return nullptr;
	}

	virtual void getAllElements(std::vector<std::pair<const K&, const T&>>& outElements) override
	{
		for (size_t i = 0; i < data->size(); ++i)
		{
			outElements.emplace_back((*data)[i].key, (*data)[i].value);
		}
	}
};