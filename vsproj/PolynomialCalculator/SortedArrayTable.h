#pragma once
#include "Table.h"


class SortedArrayTable : public Table
{
protected:
	struct Node {
		std::string name;
		Polynomial data;;
	};
	std::vector<Node> table;

	size_t binarySearch(std::string x, bool& suc)
	{
		size_t low = 1, high = table.size(), mid = 0;
		while (low <= high) {
			mid = (high + low) / 2;
			if (table[mid - 1].name == x) {
				suc = true;
				return mid - 1;
			}

			if (table[mid - 1].name < x)
				low = mid + 1;
			else
				high = mid - 1;
		}
		return low - 1; // потому что выход low за пределы high покажет место, на которое нужно поместить элемент
		// в конц предпоследней итерации (последн€€ - когда low становитьс€ = high) high "срезает" все числа между средним и предшествующим ему, 
		// а число, которое мы ищем, оказываетс€ между ними
		// x = 4: [3, 5] -> [3], 5
		// причина - предположение, что x = 4 есть в массиве, да оно должно быть на месте 3
		// значит когда 3], [5 ```low = {5}, high = {3}``` low покажет €чейку, в которой при возрастающем массиве (счЄт слева направо) должен быть x = 4 
		// 
		// крч x =4: 3, 5 - границы сход€тс€ на ближайшем меньшем (в силу +/- 1 в изменении границ?) -> даЄм low выйти на еденрицу вперЄд
		// x=6: 5,7 - сход€тс€ на ближайшем большем - low оп€ть покажет истинное положение
	}

public:
	SortedArrayTable(size_t sz = defaultSize) {
		table.resize(sz);
	}
	~SortedArrayTable() = default;

	// ƒобавл€ет полином pol в таблицу с ключем(именем) name
	virtual void addElement(const std::string& name, const Polynomial& pol) {
		bool suc = false;
		size_t num = binarySearch(name, suc);
		if (suc) { // €чейка с таким именем есть
			return;
		}
		else {
			table.push_back(table[table.size() - 1]);
			for (size_t i = table.size() - 1; i > num; i--) {
				table[i] = table[i - 1];
			}
			table[num] = { name, pol };
		}
	}

	// ”дал€ет из полином с именем name из таблицы
	virtual void deleteElement(const std::string& name) {
		bool suc = false;
		size_t num = binarySearch(name, suc);
		if (!suc) { // €чейки с таким именем нет
			return;
		}
		else {
			for (size_t i = num; i < table.size() - 1; i++) {
				table[i] = table[i + 1];
			}
			table.pop_back();
		}
	};

	// »щет в таблице полином с именем name
	virtual Polynomial* findElement(const std::string& name) {
		bool suc = false;
		size_t num = binarySearch(name, suc) - 1;
		if (!suc)
			return nullptr;
		else
			return &table[num].data;
	}
};