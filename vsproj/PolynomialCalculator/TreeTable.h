#pragma once
#include <Polynomial.h>
#include <Table.h>

template<typename K, typename T>
class TreeTable : public Table<K, T>
{
protected:
	struct TreeNode
	{
		K Value;
		T data;
		int color;

		TreeNode* parent;
		TreeNode* left;
		TreeNode* right;
	};

public:
	TreeTable(size_t sz = defaultSize);
	~TreeTable() override;

	// ��������� � ������� ������� � ������ key
	virtual void addElement(const K& key, const T& pol) override;

	// ������� �� ������� ������� � ������ key
	virtual void deleteElement(const K& key) override;

	// ���� � ���������� ������ �� ������� � ������ K, � ��������� ������ ������� ����������
	virtual T& findElement(const K& key) override;
};