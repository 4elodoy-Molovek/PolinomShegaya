#pragma once
#include "Table.h"

template<typename K, typename T>
class HashTableOne : public Table<K, T>
{
protected:
	struct Node
	{
		T data;
		bool deleted;
	};
	int size; // ������� ��������� � ��� ������ � ������� (��� ����� deleted)
	int bufferSize; // ������ ������ �������, ������� ������ �������� ��� �������� ����� �������
	int sizeAllNonNullptr; // ������� ��������� � ��� ������ � ������� (� ������ deleted)

public:
	HashTableOne(size_t sz = defaultSize);
	~HashTableOne() override;

	// ��������� � ������� ������� � ������ key
	virtual void addElement(const K& key, const T& pol) override;

	// ������� �� ������� ������� � ������ key
	virtual void deleteElement(const K& key) override;

	// ���� � ���������� ������ �� ������� � ������ K, � ��������� ������ ������� ����������
	virtual T* findElement(const K& key) override;
};