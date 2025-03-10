#pragma once
#include <string>


template <typename T>
struct Node
{
	T data;
	Node<T>* pNext;
};


template <typename L>
class List
{
	Node<L>* pFirst;
	Node<L>* pLast;

public:
	List();
	List(Node<L>*& fst);
	List(const List<L>& lis);
	~List();

	void InsertFirst(Node<L>*& n);
	void InsertLast(Node< L>*& n);

	bool operator==(const List<L>& l);
	List& operator=(const List<L>& lis);
};

