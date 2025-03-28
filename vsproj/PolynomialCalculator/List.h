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
	List() : pFirst(nulltpr), pLast(nullptr), sz(0) {}

	// ����������� �� ��������� �� ������ Node
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

	// ����������� �����������
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


	// ����������
	~List();

	// Utility �������

	// ���������� ����� ��������� � ������
	size_t size();
	// ���� �� ������?
	bool empty();


	// ������� � ������
	void insertFirst(const T& data);
	// ������� � �����
	void insertLast(const T& data);
	// ��������� � ������������ ������� ������
	void insert(int index, const T& data);


	// ��������� �������� ������� ��������
	L& getFirst();

	// ��������� �������� ���������� ��������
	L& getLast();

	// ��������� ������������� ��������
	L& operator[](int);

	bool operator==(const List<L>& list);
	List& operator=(const List<L>& list);
};

