#pragma once
#include "Table.h"
#include <vector>

// добавить рехещ для sizeAllNonNull
// offset test

template <typename type>
class HashTableTwo : public Table
{
protected:
	struct Node
	{
		std::string name; // = key
		type data;
		int deleted; // 1 - занята, 0 - пустая, -1 - удалена
	};
	size_t  bufferSize; // фактический размер таблицы
	size_t sizeh; //  реальных строк
	size_t sizeAllNonNull; // реальные + удаленные
	Node* table = nullptr;
	size_t tableOffset;


	size_t setOffset() {
		std::vector<bool> prime(bufferSize + 1, true);
		size_t p = 2;
		for (p = 2; p * p <= bufferSize; p++)
			if (prime[p] == true) {
				tableOffset = p;
				for (int i = p * p; i <= bufferSize; i += p)
					prime[i] = false;
			}
		for (p = bufferSize; prime[p] != true; p--);
		tableOffset = p;
		return tableOffset;
	}

	size_t hashFuncMain(std::string& s) {
		size_t summary = 0;
		for (size_t i = 0; i < s.length(); i ++) {
			summary += s[i]; 
		}
		return summary % bufferSize;
	}

	void Resize() {
		size_t pastBufferSize = bufferSize;
		bufferSize *= 2;
		setOffset();
		sizeAllNonNull = 0; // потому что удалённые не переносим
		sizeh = 0;
		Node* newTable = new Node[bufferSize];
		for (size_t i = 0; i < bufferSize; ++i)
			newTable[i].deleted = 0;
		swap(table, newTable);

		for (int i = 0; i < pastBufferSize; ++i)
		{
			if (newTable[i].deleted == 1)
				addElement(newTable[i].name, newTable[i].data); // добавляем элементы в новый массив
		}
		// удаление предыдущего массива
		delete[] newTable;

	}

public:
	HashTableTwo(size_t sz = defaultSize) : sizeh(0), sizeAllNonNull(0) {
		bufferSize = (sz > 1 ? sz * 2 : 4);
		table = new Node[bufferSize];
		for (size_t i = 0; i < bufferSize; i++)
			table[i].deleted = 0;

		setOffset();
	}

	~HashTableTwo() {
		delete[] table;
	}

	// Добавляет полином pol в таблицу с ключем(именем) name
	virtual void addElement(std::string& name, const type& pol) override  {
		// проверка заполненности на 75%

		/*  if (size + 1 > int(rehash_size * bufferSize))
			Resize();
		else if (sizeAllNonNull > 2 * size)
			Rehash(); // происходит рехеш, так как слишком много deleted-элементов*/

		if (5 * sizeh > bufferSize * 4) {
			Resize();
		}


		size_t hash = hashFuncMain(name), offset = tableOffset;
		size_t pos = hash;
		for (; table[pos].deleted == 1; pos = (pos + offset) % bufferSize) {
			if (table[pos].name == name)
				return;
		}
		table[pos] = { name, pol, 1 };
		sizeh++;
	};

	// Удаляет полином с именем name из таблицы
	virtual void deleteElement(std::string& name) override {
		size_t hash = hashFuncMain(name), offset = tableOffset;
		size_t pos = hash;

		for (; table[pos].deleted != 0; pos = (pos + offset) % bufferSize) {
			if (table[pos].name == name) {
				table[pos].deleted = -1;
				return;
			}
		}
	}

	// Ищет в таблице полином с именем name
	virtual type* findElement(std::string& name) override {
		type* ans = nullptr;
		size_t hash = hashFuncMain(name), offset = tableOffset;
		size_t pos = hash, initialPos = pos;
		bool firstRound = true;
		for (; table[pos].deleted != 0; pos = (pos + offset) % bufferSize) {
			if ((table[pos].name == name) && (table[pos].deleted == 1)) {
				ans = &table[pos].data;
				break;
			}
			if ((initialPos == pos) && (!firstRound)) {
				break;
			}
			firstRound = false; // я думаю, первый обход лучше вынести из цикла и не делать постоянного присваивания
		}
		return ans;
	}
};
