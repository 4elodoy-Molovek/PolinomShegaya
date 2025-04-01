#pragma once
#include <Polynomial.h>
#include <Table.h>

template<typename K, typename T>
class TreeTable : public Table<K, T>
{
protected:
	struct TreeNode
	{
		K key;
		T data;
		char color;

		TreeNode* parent;
		TreeNode* left;
		TreeNode* right;
	};

	TreeNode* root;

	// ������� ���������, ������������ � ���� root, ������������ � �����������
	void deleteSubtree(TreeNode* subtreeRoot)
	{
		if (!subtreeRoot) return;

		deleteSubtree(subtreeRoot->left);
		deleteSubtree(subtreeRoot->root);

		delete subtreeRoot;
	}

public:
	TreeTable() {}
	~TreeTable() override { deleteSubtree(root); }

	// ��������� � ������� ������� � ������ key
	virtual void addElement(const K& key, const T& pol) override;

	// ������� �� ������� ������� � ������ key
	virtual void deleteElement(const K& key) override;

	// ���� � ���������� ������ �� ������� � ������ K, � ��������� ������ ������� ����������
	virtual T* findElement(const K& key) override
	{
		if (size == 0) return nullptr;
		if (size == 1 && root->key != key) return nullptr;
		
		if (size == 1 && root->key == key) return &key->data;

		// ������ >= 2
		TreeNode* node = root;
		while (node && node->key != key)
		{
			if (node->key > key) node = node->right;
			else node = node->left;
		}

		if (!node) return nullptr;
		return &node->data;
	}

	// � outElements �������� ��� �������� ������� � ��������� �������
	virtual void getAllElements(std::vector<std::pair<const K&, const T&>>& outElements) override {}
};