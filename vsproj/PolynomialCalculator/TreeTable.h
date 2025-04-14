#pragma once
#include <Polynomial.h>
#include <Table.h>
#include <stack>

template<typename K, typename T>
class TreeTable : public Table<K, T>
{
protected:

	template<typename K, typename T>
	struct TreeNode
	{
		K key;
		T data;

		TreeNode<K, T>* left = nullptr;
		TreeNode<K, T>* right = nullptr;

		size_t height = 1;

		TreeNode() : left(nullptr), right(nullptr), height(1) {}
		TreeNode(const K& inKey, const T& inData) : key(inKey), data(inData), left(nullptr), right(nullptr), height(1) {}

		static size_t getHeight(TreeNode<K, T>* node) 
		{
			if (!node) return 0;
			return node->height;
		}
	};


	TreeNode<K, T>* root;
	size_t size;


	// Удаляет поддерево, начинающееся с узла root, используется в деструкторе
	void deleteSubtree(TreeNode<K, T>* subtreeRoot)
	{
		if (!subtreeRoot) return;

		deleteSubtree(subtreeRoot->left);
		deleteSubtree(subtreeRoot->right);

		delete subtreeRoot;
	}


	// Повороты для ребалансировки

	// Левый поворот
	TreeNode<K, T>* rotateLeft(TreeNode<K, T>* node)
	{
		// Правый наследник становится корнем
		TreeNode<K, T>* newParent = node->right;

		// Левый наследник нового корня становится правым наследником node
		node->right = newParent->left;

		// node становится левым наследником нового корня
		newParent->left = node;

		// Обновляем высоты
		node->height = 1 + std::max(TreeNode<K, T>::getHeight(node->left), TreeNode<K, T>::getHeight(node->right));
		newParent->height = 1 + std::max(TreeNode<K, T>::getHeight(newParent->left), TreeNode<K, T>::getHeight(newParent->right));

		return newParent;
	}

	// Правый поворот
	TreeNode<K, T>* rotateRight(TreeNode<K, T>* node)
	{
		// Левый наследник становится корнем
		TreeNode<K, T>* newParent = node->left;

		// Правый наследник нового корня становится левым наследником node
		node->left = newParent->right;

		// node становится правым наследником нового корня
		newParent->right = node;

		// Обновляем высоты
		node->height = 1 + std::max(TreeNode<K, T>::getHeight(node->left), TreeNode<K, T>::getHeight(node->right));
		newParent->height = 1 + std::max(TreeNode<K, T>::getHeight(newParent->left), TreeNode<K, T>::getHeight(newParent->right));

		return newParent;
	}

	// Рекурсивное добавление элемента
	TreeNode<K, T>* addElementReq(TreeNode<K, T>* currentNode, const K& key, const T& pol)
	{
		if (!currentNode)
		{
			TreeNode<K, T>* newNode = new TreeNode<K, T>(key, pol);
			return newNode;
		}

		if (key < currentNode->key) currentNode->left = addElementReq(currentNode->left, key, pol);
		else if (key > currentNode->key) currentNode->right = addElementReq(currentNode->right, key, pol);
		else throw(std::runtime_error("ERROR: TreeTable: trying to insert an element with already existing key!"));

		currentNode->height = 1 + std::max(TreeNode<K, T>::getHeight(currentNode->left), TreeNode<K, T>::getHeight(currentNode->right));
		int balance = TreeNode<K, T>::getHeight(currentNode->left) - TreeNode<K, T>::getHeight(currentNode->right);

		if (balance > 1)
		{
			// left-right
			if (key > currentNode->left->key)
			{
				currentNode->left = rotateLeft(currentNode->left);
				return rotateRight(currentNode);
			}

			// left-left
			else return rotateRight(currentNode);
		}

		else if (balance < -1)
		{
			// right-left
			if (key < currentNode->right->key)
			{
				currentNode->right = rotateRight(currentNode->right);
				return rotateLeft(currentNode);
			}

			// right-right
			else return rotateLeft(currentNode);
		}

		return currentNode;
	}

	// Рекурсивное удаление элемента
	TreeNode<K, T>* removeElementReq(TreeNode<K, T>* currentNode, const K& key)
	{
		currentNode = currentNode;
		if (!currentNode) throw(std::runtime_error("ERROR: TreeTable: trying to delete a non-existant element!"));

		if (key < currentNode->key) currentNode->left = removeElementReq(currentNode->left, key);
		else if (key > currentNode->key) currentNode->right = removeElementReq(currentNode->right, key);
		else
		{
			// Лист
			if (!currentNode->left && !currentNode->right)
			{
				delete currentNode;
				currentNode = nullptr;
			}

			// Только правый наследник
			else if (!currentNode->left)
			{
				TreeNode<K, T>* temp = currentNode;
				currentNode = currentNode->right;

				delete temp;
			}

			// Только левый наследник
			else if (!currentNode->right)
			{
				TreeNode<K, T>* temp = currentNode;
				currentNode = currentNode->left;

				delete temp;
			}

			// Оба наследника
			else
			{
				// Ищем наибольшего в левом поддереве node
				TreeNode<K, T>* max = currentNode->left;
				while (max->right) max = max->right;

				currentNode->key = max->key;
				currentNode->data = max->data;

				currentNode->left = removeElementReq(currentNode->left, max->key);
			}
		}

		if (!currentNode) return nullptr;

		currentNode->height = 1 + std::max(TreeNode<K, T>::getHeight(currentNode->left), TreeNode<K, T>::getHeight(currentNode->right));
		int balance = TreeNode<K, T>::getHeight(currentNode->left) - TreeNode<K, T>::getHeight(currentNode->right);

		if (balance > 1)
		{

			int childBalance = TreeNode<K, T>::getHeight(currentNode->left->left) - TreeNode<K, T>::getHeight(currentNode->left->right);

			// left-left
			if (childBalance >= 0)
				return rotateRight(currentNode);

			// left-right
			else
			{
				currentNode->left = rotateLeft(currentNode->left);
				return rotateRight(currentNode);
			}
		}

		else if (balance < -1)
		{
			int childBalance = TreeNode<K, T>::getHeight(currentNode->right->left) - TreeNode<K, T>::getHeight(currentNode->right->right);

			// right-right
			if (childBalance <= 0)
				return rotateLeft(currentNode);

			// right-left
			else
			{
				currentNode->right = rotateRight(currentNode->right);
				return rotateLeft(currentNode);
			}
		}

		return currentNode;
	}


	// Рекурсивный шаг обхода дерева по порядку
	void inorderTraversal(TreeNode<K, T>* node, std::vector<std::pair<const K&, const T&>>& outElements)
	{
		if (!node) return;

		if (node->left) inorderTraversal(node->left, outElements);

		outElements.push_back({ node->key, node->data });

		if (node->right) inorderTraversal(node->right, outElements);
	}


public:
	TreeTable() : size(0), root(nullptr) {}
	~TreeTable() override { deleteSubtree(root); }

	// Добавляет в таблицу элемент с ключем key
	virtual void addElement(const K& key, const T& pol) override
	{
		root = addElementReq(root, key, pol);

		size++;
	}

	// Удаляет из таблицы элемент с ключем key
	virtual void deleteElement(const K& key) override
	{
		root = root;
		root = removeElementReq(root, key);

		size--;

	}

	// Ищет и возвращает ссылку на элемент с ключем K, в противном случае бросает исключение
	virtual T* findElement(const K& key) override
	{
		if (size == 0) return nullptr;
		if (size == 1 && root->key != key) return nullptr;

		if (size == 1 && root->key == key) return &root->data;

		// Размер >= 2
		TreeNode<K, T>* node = root;
		while (node && node->key != key)
		{
			if (node->key < key) node = node->right;
			else node = node->left;
		}

		if (!node) return nullptr;
		return &node->data;
	}

	// В outElements помещает все элементы таблицы в некотором порядке
	virtual void getAllElements(std::vector<std::pair<const K&, const T&>>& outElements) override
	{
		if (!root) return;

		inorderTraversal(root, outElements);
	}
};