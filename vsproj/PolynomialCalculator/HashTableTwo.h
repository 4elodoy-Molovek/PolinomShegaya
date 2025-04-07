#pragma once
#include <vector>
#include "Table.h"
// const size_t defaultSize = 4;
const size_t OFFSET_CONST = 1;

template<typename K, typename T>
class HashTableTwo : public Table<K, T>
{
protected:
	struct Node
	{
		K name; // = key
		T data;
		int deleted; // 1 - çàíÿòà, 0 - ïóñòàÿ, -1 - óäàëåíà
	};
	size_t  bufferSize; // ôàêòè÷åñêèé ðàçìåð òàáëèöû
	size_t sizeh; //  ðåàëüíûõ ñòðîê
	size_t sizeAllNonNull; // ðåàëüíûå + óäàëåííûå
	Node* table = nullptr;

	size_t tableOffset;

	size_t setOffset()
	{
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

	size_t hashFuncMain(const K& s)
	{
		size_t summary = 0;
		for (size_t i = 0; i < s.length(); i++) {
			summary += (s[i] * (i + 1)) % bufferSize; //âîçìæíî íå ñòîèò êàæäûé ðàç äåëèòü, äîëãî ïîëó÷àåòñÿ
		}
		return summary % bufferSize;
	}


	void Resize()
	{
		size_t pastBufferSize = bufferSize;
		bufferSize *= 2;
		setOffset();
		sizeAllNonNull = 0; // ïîòîìó ÷òî óäàë¸ííûå íå ïåðåíîñèì
		sizeh = 0;
		Node* newTable = new Node[bufferSize];
		for (size_t i = 0; i < bufferSize; ++i)
			newTable[i].deleted = 0;
		std::swap(table, newTable);

		for (int i = 0; i < pastBufferSize; ++i)
		{
			if (newTable[i].deleted == 1)
				addElement(newTable[i].name, newTable[i].data); // äîáàâëÿåì ýëåìåíòû â íîâûé ìàññèâ
		}
		// óäàëåíèå ïðåäûäóùåãî ìàññèâà
		delete[] newTable;
	}

public:
	HashTableTwo(size_t sz = defaultSize) : sizeh(0), sizeAllNonNull(0)
	{
		bufferSize = (sz > 1 ? sz * 2 : 4);
		table = new Node[bufferSize];
		for (size_t i = 0; i < bufferSize; i++)
			table[i].deleted = 0;
		setOffset();
	}

	~HashTableTwo() {
		delete[] table;
	}


	// Äîáàâëÿåò ïîëèíîì pol â òàáëèöó ñ êëþ÷åì(èìåíåì) name
	virtual void addElement(const K& name, const T& pol)
	{
		if (findElement(name) != nullptr) throw std::runtime_error("Element with the same key already exists.");

		// ïðîâåðêà çàïîëíåííîñòè íà 75%
		if (5 * sizeh > bufferSize * 4) {
			Resize();
		}


		size_t hash = hashFuncMain(name);
		size_t pos = hash;
		for (; table[pos].deleted == 1; pos = (pos + tableOffset) % bufferSize)
		{
			if (table[pos].name == name)
				return;
		}
		table[pos] = { name, pol, 1 };
		sizeh++;
	};

	// Óäàëÿåò èç ïîëèíîì ñ èìåíåì name èç òàáëèöû
	virtual void deleteElement(const K& name)
	{
		if (findElement(name) == nullptr) throw std::runtime_error("Element not found.");

		size_t hash = hashFuncMain(name), offset = OFFSET_CONST;
		size_t pos = hash;

		for (; table[pos].deleted != 0; pos = (pos + offset) % bufferSize)
		{
			if (table[pos].name == name)
			{
				table[pos].deleted = -1;
				return;
			}
		}
	}

	// Èùåò â òàáëèöå ïîëèíîì ñ èìåíåì name
	virtual T* findElement(const K& name)
	{
		T* ans = nullptr;
		size_t hash = hashFuncMain(name);
		setOffset();
		size_t pos = hash, initialPos = pos;
		bool firstRound = true;
		for (; table[pos].deleted != 0; pos = (pos + tableOffset) % bufferSize)
		{
			if ((table[pos].name == name) && (table[pos].deleted == 1))
			{
				ans = &table[pos].data;
				break;
			}
			if ((initialPos == pos) && (!firstRound))
			{
				break;
			}
			firstRound = false; // ÿ äóìàþ, ïåðâûé îáõîä ëó÷øå âûíåñòè èç öèêëà è íå äåëàòü ïîñòîÿííîãî ïðèñâàèâàíèÿ
		}
		return ans;
	}

	virtual void getAllElements(std::vector<std::pair<const K&, const T&>>& outElements) override
	{
		for (size_t i = 0; i < sizeh; i++)
			outElements.push_back({ table[i].name, table[i].data });
	}
};
