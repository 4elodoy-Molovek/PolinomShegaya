#include "LinearListTable.h"

template<typename K, typename T>
LinearListTable<K, T>::LinearListTable(size_t sz)
{
	data = new List<ListTableString>();
	size = 0; /// ???
}

template<typename K, typename T>
LinearListTable<K, T>::~LinearListTable()
{
	delete data;
}

// Добавляет полином pol в таблицу с ключом (именем) name
template<typename K, typename T>
void LinearListTable<K, T>::addElement(const K& name, const T& pol)
{
	// Проверка на существование элемента
	for (size_t i = 0; i < data->size(); ++i)
	{
		if ((*data)[i].name == name)
			throw std::runtime_error("Element with this name already exists.");
	}

	ListTableString entry;
	entry.name = name;
	entry.poly = pol;

	data->insertLast(entry);
	size++;
}

// Удаляет полином с именем name из таблицы
template<typename K, typename T>
void LinearListTable<K, T>::deleteElement(const K& name)
{
	bool found = false;

	for (size_t i = 0; i < data->size(); ++i)
	{
		if ((*data)[i].name == name)
		{
			// Удаление элемента
			List<ListTableString>* newList = new List<ListTableString>();

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

// Ищет в таблице полином с именем name
template<typename K, typename T>
T* LinearListTable<K, T>::findElement(const K& name)
{
	for (size_t i = 0; i < data->size(); ++i)
	{
		if ((*data)[i].name == name)
			return (*data)[i].poly;
	}

	throw std::runtime_error("Element not found.");
}
/// must return pointer
/// delete throw