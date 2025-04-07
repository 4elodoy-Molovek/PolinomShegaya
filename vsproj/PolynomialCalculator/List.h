#pragma once
#include <string>

template <typename T>
struct ListNode
{
	T data;
	ListNode<T>* pNext;

	ListNode() : pNext(nullptr) {}
	ListNode(const T& value) : data(value), pNext(nullptr) {}
};


template <typename L>
class List
{
	ListNode<L>* pFirst;
	ListNode<L>* pLast;

	size_t sz;

private:

	void destroyNode(ListNode<L>* node)
	{
		while (node)
		{
			ListNode<L>* temp = node;
			node = node->pNext;
			delete temp;
		}
	}

public:

	// Конструктор по умолчанию
	List() : pFirst(nullptr), pLast(nullptr), sz(0) {}

	// Конструктор из указателя на первую Node
	List(ListNode<L>* fst) : pFirst(fst), sz(0)
	{
		ListNode<L>* node = fst;
		while (node)
		{
			sz++;
			node = node->pNext;
		}

		pLast = node;
	}

	// Конструктор копирования
	List(const List<L>& list)
	{
		sz = 0;
		pFirst = nullptr;
		pLast = nullptr;

		ListNode<L>* node = list.pFirst;
		while (node)
		{
			insertLast(node->data);
			node = node->pNext;
		}
	}

	void clearList()
	{
		if (pFirst) destroyNode(pFirst);
	}

	// Деструктор
	~List()
	{
		clearList();
	}

	// Utility функции

	// Возвращает число элементов в списке
	size_t size() const { return sz; }
	// Пуст ли список?
	bool empty() const { return sz == 0; }


	// Вставка в начало
	void insertFirst(const L& data)
	{
		ListNode<L>* newNode = new ListNode<L>(data);

		if (!pFirst)
		{
			pFirst = newNode;
			pLast = newNode;
		}

		else
		{
			newNode->pNext = pFirst;
			pFirst = newNode;
		}

		sz++;
	}

	// Вставка в конец
	void insertLast(const L& data)
	{
		ListNode<L>* newNode = new ListNode<L>(data);

		if (!pFirst)
		{
			pFirst = newNode;
			pLast = newNode;
		}

		else
		{
			pLast->pNext = newNode;
			pLast = newNode;
		}

		sz++;
	}

	// Вставляет в произвольную позицию списка
	void insert(int index, const L& data)
	{
		ListNode<L>* newNode = new ListNode<L>(data);

		if (!pFirst)
		{
			if (index != 0) throw(std::exception("LIST: Trying to insert at invalid index into an EMPTY list!"));

			pFirst = newNode;
			pLast = newNode;
		}

		else if (index == sz)
		{
			insertLast(data);
			return;
		}

		else if (index > sz || index < 0) throw(std::exception("LIST: Trying to insert at invalid index!"));

		else
		{
			int i = 0;

			ListNode<L>* prevNode = nullptr;
			ListNode<L>* node = pFirst;

			while (i < index)
			{
				prevNode = node;
				node = node->pNext;
				i++;
			}

			if (!prevNode)
				pFirst = newNode;

			else
				prevNode->pNext = newNode;

			newNode->pNext = node;
		}

		sz++;
	}

	void remove(int index)
	{
		// Step 1: Check if the index is valid before modifying anything
		if (index < 0 || index >= sz)
			throw std::exception("LIST: Trying to remove at an invalid index!");  // Invalid index

		// Step 2: Check for empty list before removal
		if (empty())
			throw std::exception("LIST: Trying to remove from an empty list!");  // Empty list

		// Step 3: If the index is 0, we remove the first element
		if (index == 0)
		{
			ListNode<L>* temp = pFirst;
			pFirst = pFirst->pNext;
			delete temp;

			// If the list becomes empty, reset the last pointer
			if (pFirst == nullptr)
				pLast = nullptr;
		}
		else
		{
			ListNode<L>* prevNode = nullptr;
			ListNode<L>* node = pFirst;

			for (int i = 0; i < index; i++) // Traverse to the node at the specified index
			{
				prevNode = node;
				node = node->pNext;
			}

			if (node == pLast)  // If we're deleting the last node, update pLast
			{
				pLast = prevNode;
			}

			if (prevNode != nullptr)
				prevNode->pNext = node->pNext;

			delete node;
		}

		sz--;  // Decrement size after successful removal
	}


	// Получение значения первого элемента
	L& getFirst()
	{
		if (pFirst)
			return pFirst->data;

		throw(std::exception("LIST: getFirst in an empty list!"));
	}

	// Получение значения последнего элемента
	L& getLast()
	{
		if (pLast)
			return pLast->data;

		throw(std::exception("LIST: getLast in an empty list!"));
	}

	// Получение произвольного элемента
	L& operator[](int index)
	{
		if (!pFirst) throw(std::exception("LIST: operator[] in an empty list!"));
		if (index >= sz) throw(std::exception("LIST: operator[] with an invalid index!"));

		int i = 0;
		ListNode<L>* node = pFirst;

		while (i < index)
		{
			node = node->pNext;
			i++;
		}

		return node->data;
	}

	const L& operator[](int index) const
	{
		if (!pFirst) throw(std::exception("LIST: operator[] in an empty list!"));
		if (index >= sz) throw(std::exception("LIST: operator[] with an invalid index!"));

		int i = 0;
		ListNode<L>* node = pFirst;

		while (i < index)
		{
			node = node->pNext;
			i++;
		}

		return node->data;
	}

	bool operator==(const List<L>& list) const
	{
		if (size() != list.size()) return false;

		ListNode<L>* node_1 = pFirst, * node_2 = list.pFirst;

		while (node_1)
		{
			if (node_1->data != node_2->data) return false;
			node_1 = node_1->pNext;
			node_2 = node_2->pNext;
		}

		return true;
	}

	List<L>& operator=(const List<L>& list)
	{
		if (this == &list)
			return *this;

		clearList();
		pFirst = nullptr;
		pLast = nullptr;
		sz = 0;

		ListNode<L>* node = list.pFirst;
		while (node)
		{
			insertLast(node->data);
			node = node->pNext;
		}

		return *this;
	}
};

