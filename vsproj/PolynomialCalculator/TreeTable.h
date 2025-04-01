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

	// Удаляет поддерево, начинающееся с узла root, используется в деструкторе
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

	// Добавляет в таблицу элемент с ключем key
	virtual void addElement(const K& key, const T& pol) override;

	// Удаляет из таблицы элемент с ключем key
	virtual void deleteElement(const K& key) override;

	// Ищет и возвращает ссылку на элемент с ключем K, в противном случае бросает исключение
	virtual T* findElement(const K& key) override
	{
		if (size == 0) return nullptr;
		if (size == 1 && root->key != key) return nullptr;
		
		if (size == 1 && root->key == key) return &key->data;

		// Размер >= 2
		TreeNode* node = root;
		while (node && node->key != key)
		{
			if (node->key > key) node = node->right;
			else node = node->left;
		}

		if (!node) return nullptr;
		return &node->data;
	}

	// В outElements помещает все элементы таблицы в некотором порядке
	virtual void getAllElements(std::vector<std::pair<const K&, const T&>>& outElements) override {}
};