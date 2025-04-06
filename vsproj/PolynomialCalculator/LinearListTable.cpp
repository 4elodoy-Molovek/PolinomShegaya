#include "LinearListTable.h"

LinearListTable::LinearListTable(size_t sz)
{
	data = new List<ListTableString>();
	size = 0;
}

LinearListTable::~LinearListTable()
{
	delete data;
}

// Добавляет полином pol в таблицу с ключом (именем) name
void LinearListTable::addElement(const std::string& name, const Polynomial& pol)
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
void LinearListTable::deleteElement(const std::string& name)
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
const Polynomial& LinearListTable::findElement(const std::string& name)
{
	for (size_t i = 0; i < data->size(); ++i)
	{
		if ((*data)[i].name == name)
			return (*data)[i].poly;
	}

	throw std::runtime_error("Element not found.");
}
