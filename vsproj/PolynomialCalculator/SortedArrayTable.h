#pragma once
#include "Table.h"
#include <vector>


#pragma once
#include "Table.h"
#include <vector>


template<typename K, typename T>
class SortedArrayTable : public Table<K, T>
{
protected:
	struct Node 
	{
		K name;
		T data;
	};
	std::vector<Node> table;

	size_t binarySearch(const K& x, bool& suc)
	{
		size_t low = 1, high = table.size(), mid = 42;
		while (low <= high) 
		{
			mid = (high + low) / 2;
			if (table[mid - 1].name == x) 
			{
				suc = true;
				return mid - 1;
			}

			if (table[mid - 1].name < x)
				low = mid + 1;
			else
				high = mid - 1;
		}
		return low - 1; // потому что выход low за пределы high покажет место, на которое нужно поместить элемент
		// в конц предпоследней итерации (последняя - когда low становиться = high) high "срезает" все числа между средним и предшествующим ему, 
		// а число, которое мы ищем, оказывается между ними
		// x = 4: [3, 5] -> [3], 5
		// причина - предположение, что x = 4 есть в массиве, да оно должно быть на месте 3
		// значит когда 3], [5 ```low = {5}, high = {3}``` low покажет ячейку, в которой при возрастающем массиве (счёт слева направо) должен быть x = 4 
		// 
		// крч x =4: 3, 5 - границы сходятся на ближайшем меньшем (в силу +/- 1 в изменении границ?) -> даём low выйти на еденрицу вперёд
		// x=6: 5,7 - сходятся на ближайшем большем - low опять покажет истинное положение
	}

public:
	SortedArrayTable() = default;
	~SortedArrayTable() = default;

	// Добавляет полином pol в таблицу с ключем(именем) name
	virtual void addElement(const K& name, const T& pol) 
	{
		bool suc = false;
		size_t num = binarySearch(name, suc);
		if (suc) 
		{ // ячейка с таким именем есть
			return;
		}
		else 
		{
			table.push_back({ name, pol }); // чтобы не использовать констурктор по умолчанию для Node
			for (size_t i = table.size() - 1; i > num; i--) 
			{
				table[i] = table[i - 1];
			}
			table[num] = { name, pol };
		}
	}

	// Удаляет из полином с именем name из таблицы
	virtual void deleteElement(const K& name) 
	{
		bool suc = false;
		size_t num = binarySearch(name, suc);
		if (!suc) 
		{ // ячейки с таким именем нет
			return;
		}
		else 
		{
			for (size_t i = num; i < table.size() - 1; i++) {
				table[i] = table[i + 1];
			}
			table.pop_back();
		}
	};

	// Ищет в таблице полином с именем name
	virtual T* findElement(const K& name) 
	{
		bool suc = false;
		size_t num = binarySearch(name, suc);
		if (!suc)
			return nullptr;
		else
			return &table[num].data;
	}

	// В outElements помещает все элементы таблицы в некотором порядке
	virtual void getAllElements(std::vector<std::pair<const K&, const T&>>& outElements) override
	{
		for (size_t i = 0; i < table.size(); i++)
			outElements.push_back({ table[i].name, table[i].data });
	}
};

