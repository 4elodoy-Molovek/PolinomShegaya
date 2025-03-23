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

	// ����������� �� ���������
	List(); 
	// ����������� �� ��������� �� ������ Node (������ ������ pLast � �������, ������������ � fst)
	List(ListNode<L>* fst);
	// ����������� �����������
	List(const List<L>& list);


	// ����������
	~List();

	// Utility �������

	// ���������� ����� ��������� � ������
	size_t size();
	// ���� �� ������?
	bool empty();


	// ������� � ������
	void InsertFirst(const T& data);
	// ������� � �����
	void InsertLast(const T& data);


	// ���������

	bool operator==(const List<L>& list);
	List& operator=(const List<L>& list);

	
};

