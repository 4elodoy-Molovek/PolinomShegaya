#pragma once
#include <string>


template <typename T>
struct ListNode
{
	T data;
	ListNode<T>* pNext;
};


template <typename L>
class List
{
	ListNode<L>* pFirst;
	ListNode<L>* pLast;

	size_t sz;

public:

	// Конструктор по умолчанию
	List() : pFirst(nulltpr), pLast(nullptr), sz(0) {}

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
			ListNode<L>* node = list.pFirst();
			while (node)
			{

			}
		}
	}


	// Деструктор
	~List();

	// Utility функции

	// Возвращает число элементов в списке
	size_t size();
	// Пуст ли список?
	bool empty();


	// Вставка в начало
	void insertFirst(const T& data);
	// Вставка в конец
	void insertLast(const T& data);
	// Вставляет в произвольную позицию списка
	void insert(int index, const T& data);


	// Получение значения первого элемента
	L& getFirst();

	// Получение значения последнего элемента
	L& getLast();

	// Получение произвольного элемента
	L& operator[](int);

	bool operator==(const List<L>& list);
	List& operator=(const List<L>& list);
};

