#pragma once
#include <string>

template <typename T>
struct ListNode
{
	T data;
	ListNode<T>* pNext;

	ListNode() {}
	ListNode(const T& value) : data(value) {}
};


template <typename L>
class List
{
	ListNode<L>* pFirst;
	ListNode<L>* pLast;

	size_t sz;

public:
	// Êîíñòðóêòîð ïî óìîë÷àíèþ
	List() : pFirst(nulltpr), pLast(nullptr), sz(0) {}

	// Êîíñòðóêòîð èç óêàçàòåëÿ íà ïåðâóþ Node

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


	// Êîíñòðóêòîð êîïèðîâàíèÿ
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


	// ÐÐµÑÑÑÑÐºÑÐ¾Ñ
	~List()
	{
		ListNode<L>* node = pFirst;
		while (pFirst)
		{
			pFirst = node->pNext;
			delete node;
		}
	}

	// Utility ÑÑÐ½ÐºÑÐ¸Ð¸

	// ÐÐ¾Ð·Ð²ÑÐ°ÑÐ°ÐµÑ ÑÐ¸ÑÐ»Ð¾ ÑÐ»ÐµÐ¼ÐµÐ½ÑÐ¾Ð² Ð² ÑÐ¿Ð¸ÑÐºÐµ
	size_t size() const { return sz; }
	// ÐÑÑÑ Ð»Ð¸ ÑÐ¿Ð¸ÑÐ¾Ðº?
	bool empty() const { return sz == 0; }


	// ÐÑÑÐ°Ð²ÐºÐ° Ð² Ð½Ð°ÑÐ°Ð»Ð¾
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

	// ÐÑÑÐ°Ð²ÐºÐ° Ð² ÐºÐ¾Ð½ÐµÑ
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

	// ÐÑÑÐ°Ð²Ð»ÑÐµÑ Ð² Ð¿ÑÐ¾Ð¸Ð·Ð²Ð¾Ð»ÑÐ½ÑÑ Ð¿Ð¾Ð·Ð¸ÑÐ¸Ñ ÑÐ¿Ð¸ÑÐºÐ°
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
				node = pFirst->pNext;
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


	// ÐÐ¾Ð»ÑÑÐµÐ½Ð¸Ðµ Ð·Ð½Ð°ÑÐµÐ½Ð¸Ñ Ð¿ÐµÑÐ²Ð¾Ð³Ð¾ ÑÐ»ÐµÐ¼ÐµÐ½ÑÐ°
	L& getFirst()
	{
		if (pFirst)
			return pFirst->data;

		throw(std::exception("LIST: getFirst in an empty list!"));
	}

	// ÐÐ¾Ð»ÑÑÐµÐ½Ð¸Ðµ Ð·Ð½Ð°ÑÐµÐ½Ð¸Ñ Ð¿Ð¾ÑÐ»ÐµÐ´Ð½ÐµÐ³Ð¾ ÑÐ»ÐµÐ¼ÐµÐ½ÑÐ°
	L& getLast()
	{
		if (pLast)
			return pLast->data;

		throw(std::exception("LIST: getLast in an empty list!"));
	}

	// ÐÐ¾Ð»ÑÑÐµÐ½Ð¸Ðµ Ð¿ÑÐ¾Ð¸Ð·Ð²Ð¾Ð»ÑÐ½Ð¾Ð³Ð¾ ÑÐ»ÐµÐ¼ÐµÐ½ÑÐ°
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

	bool operator==(const List<L>& list)
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

		// Ð£Ð´Ð°Ð»ÐµÐ½Ð¸Ðµ ÑÐµÐºÑÑÐµÐ³Ð¾ ÑÐ¿Ð¸ÑÐºÐ°
		while (pFirst)
		{
			pFirst = node->pNext;
			delete node;
		}

		// ÐÐ¾Ð¿Ð¸ÑÐ¾Ð²Ð°Ð½Ð¸Ðµ
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

