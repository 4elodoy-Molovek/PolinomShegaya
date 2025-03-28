#pragma once
#include "Table.h"

template<typename K, typename T>
class LinearListTable : public Table<K, T>
{
protected:

	template<typename K, typename T>
	struct ListTableString {
		K key;
		T value;
	};

	List<ListTableString> data;

public:
	LinearListTable(size_t sz = defaultSize);
	~LinearListTable() override;

	// ��������� � ������� ������� � ������ key
	virtual void addElement(const K& key, const T& pol) override;

	// ������� �� ������� ������� � ������ key
	virtual void deleteElement(const K& key) override;

	// ���� � ���������� ������ �� ������� � ������ K, � ��������� ������ ������� ����������
	virtual T& findElement(const K& key) override;
};