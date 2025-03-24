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
	List(); 
	// Конструктор из указателя на первую Node (должен искать pLast в цепочке, начинающейся с fst)
	List(ListNode<L>* fst);
	// Конструктор копирования
	List(const List<L>& list);


	// Деструктор
	~List();

	// Utility функции

	// Возвращает число элементов в списке
	size_t size();
	// Пуст ли список?
	bool empty();


	// Вставка в начало
	void InsertFirst(const T& data);
	// Вставка в конец
	void InsertLast(const T& data);


	// Операторы

	bool operator==(const List<L>& list);
	List& operator=(const List<L>& list);

	
};

