#pragma once
#include "Table.h"

template<typename K, typename T>
class SortedArrayTable : public Table<K, T>
{
protected:
	std::vector<T> data;
	size_t size;
	size_t bufferSize;

public:
	SortedArrayTable(size_t sz = defaultSize);
	~SortedArrayTable() override;

	// ��������� � ������� ������� � ������ key
	virtual void addElement(const K& key, const T& pol) override;

	// ������� �� ������� ������� � ������ key
	virtual void deleteElement(const K& key) override;

	// ���� � ���������� ������ �� ������� � ������ K, � ��������� ������ ������� ����������
	virtual T& findElement(const K& key) override;
};