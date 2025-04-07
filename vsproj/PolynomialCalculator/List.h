#pragma once
#include <string>

template <typename T>
struct ListNode
{
	T data;
	ListNode<T>* pNext;

	ListNode(): pNext(nullptr) {}
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
		if (!node) return;
		if (node->pNext) 
			destroyNode(node->pNext);
		delete node;
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
		sz = list.sz;

		if (sz > 0)
		{
			ListNode<L>* node = list.pFirst;
			while (node)
			{
				ListNode<L>* newNode = new ListNode<L>(node->data);

				if (!pFirst)
				{
					pFirst = newNode;
					pLast = newNode;
				}

				pLast->pNext = newNode;
				pLast = newNode;

				node = node->pNext;
			}
		}
	}


	// Деструктор
	~List()
	{
		if (pFirst) destroyNode(pFirst);
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

		else if (index >= sz) throw(std::exception("LIST: Trying to insert at invalid index!"));

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

		ListNode<L> *node_1 = pFirst, *node_2 = list.pFirst;

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
		ListNode<L>* node = pFirst;

		// Удаление текущего списка
		destroyNode(pFirst);

		// Копирование
		sz = list.sz;

		if (sz > 0)
		{
			node = list.pFirst;
			while (node)
			{
				ListNode<L>* newNode = new ListNode<L>(node->data);

				if (!pFirst)
				{
					pFirst = newNode;
					pLast = newNode;
				}

				pLast->pNext = newNode;
				pLast = newNode;

				node = node->pNext;
			}
		}

		return *this;
	}
};

