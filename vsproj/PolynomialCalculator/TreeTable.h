#pragma once
#include <Polynomial.h>
#include <Table.h>
#include <stack>

#define NODE_BLACK false
#define NODE_RED true

template<typename K, typename T>
class TreeTable : public Table<K, T>
{
protected:

	template<typename K, typename T>
	struct TreeNode
	{
		K key;
		T data;
		// 0 - ������, 1 - �������
		bool color;

		TreeNode<K, T>* parent;
		TreeNode<K, T>* left;
		TreeNode<K, T>* right;

		// �������� �� ���� ������?
		bool isLeaf() { return !left; }

		TreeNode() : color(NODE_BLACK), parent(nullptr), left(nullptr), right(nullptr) {}
		TreeNode(const K& inKey, const T& inData, bool inColor) : key(inKey), data(inData), color(inColor), parent(nullptr), left(nullptr), right(nullptr) {}
	};


	TreeNode<K, T>* root;


	// ������� ���������, ������������ � ���� root, ������������ � �����������
	void deleteSubtree(TreeNode<K, T>* subtreeRoot)
	{
		if (!subtreeRoot) return;

		deleteSubtree(subtreeRoot->left);
		deleteSubtree(subtreeRoot->right);

		delete subtreeRoot;
	}


	// �������� ��� ��������������

	// ����� �������
	void rotateLeft(TreeNode<K, T>* node)
	{
		// ������ ��������� ���������� ������
		TreeNode<K, T>* newParent = node->right;
		newParent->parent = node->parent;

		// ���������� �����, ��� ��� ��������
		if (!newParent->parent)
			root = newParent;

		// ����� ��������� ������ ����� ���������� ������ ����������� node
		node->right = newParent->left;
		node->right->parent = node;

		// node ���������� ����� ����������� ������ �����
		node->parent = newParent;
		newParent->left = node;
	}

	// ������ �������
	void rotateRight(TreeNode<K, T>* node)
	{
		// ����� ��������� ���������� ������
		TreeNode<K, T>* newParent = node->left;
		newParent->parent = node->parent;

		// ���������� �����, ��� ��� ��������
		if (!newParent->parent)
			root = newParent;

		// ������ ��������� ������ ����� ���������� ����� ����������� node
		node->left = newParent->right;
		node->left->parent = node;

		// node ���������� ������ ����������� ������ �����
		node->parent = newParent;
		newParent->right = node;
	}

	// ����������� ��� ������ ������ �� �������
	void inorderTraversal(TreeNode<K, T>* node, std::vector<std::pair<const K&, const T&>>& outElements)
	{
		if (!node) return;

		if (node->left) inorderTraversal(node->left, outElements);

		outElements.push_back(std::pair<const K&, const T&>(node->key, node->data));

		if (node->right) inorderTraversal(node->right, outElements);
	}

public:
	TreeTable() {}
	~TreeTable() override { deleteSubtree(root); }

	// ��������� � ������� ������� � ������ key
	virtual void addElement(const K& key, const T& pol) override
	{
		if (!root)
		{
			TreeNode<K, T>* newNode = new TreeNode<K, T>(key, pol, NODE_BLACK);
			root = newNode;

			root->right = new TreeNode<K, T>();
			root->left = new TreeNode<K, T>();

			return;
		}

		TreeNode<K, T>* node = root;
		while (!node->isLeaf()) // ��������� �������� ��
		{
			if (key > node->key)
				node = node->right;
			else if (key < node->key)
				node = node->left;
			else
				throw(std::exception("ERROR: Red-Black Tree (TreeTable): trying to insert an element with already existing key!"));
		}

		TreeNode<K, T>* newNode = new TreeNode<K, T>(key, pol, NODE_RED);
		newNode->parent = node->parent;

		// �������� ����� ������
		node->parent = newNode;
		newNode->left = node;
		newNode->right = new TreeNode<K, T>();
		newNode->right->parent = newNode;

		size++;

		// ��������������
		node = newNode;

		while (node->parent->color == NODE_RED)
		{
			TreeNode<K, T>* parent = node->parent;
			TreeNode<K, T>* grandParent = parent->parent;

			if (parent == grandParent->left)
			{
				if (grandParent->right->color == NODE_RED)
				{
					grandParent->right->color = NODE_BLACK;
					grandParent->left->color = NODE_BLACK;
					grandParent->color = NODE_RED;

					node = grandParent;
					continue;
				}

				else
				{
					if (node == parent->right)
					{
						node = parent;
						rotateLeft(node);
					}

					parent->color = NODE_BLACK;
					grandParent->color = NODE_RED;
					rotateRight(grandParent);
				}
			}

			else
			{
				if (granParent->left->color == NODE_RED)
				{
					grandParent->right->color == NODE_BLACK;
					grandParent->left->color == NODE_BLACK;
					grandParent->color == NODE_RED;

					node = grandParent;
					continue;
				}

				else
				{
					if (node == parent->left)
					{
						node = parent;
						rotateRight(node);
					}

					parent->color = NODE_BLACK;
					grandParent->color = NODE_RED;
					rotateLeft(grandParent);
				}
			}
		}
	}

	// ������� �� ������� ������� � ������ key
	virtual void deleteElement(const K& key) override
	{
		if (size == 0) throw(std::exception("ERROR: Red-Black Tree (TreeTable): trying to delete an element from an empty tree!"));
		if (size == 1 && root->key != key) throw(std::exception("ERROR: Red-Black Tree (TreeTable): trying to delete a non existant element!"));

		// ����� ���� ��� ��������
		TreeNode<K, T>* node = root;

		if (size == 1 && root->key == key) node = root;

		else
		{
			node = root;
			while (node && node->key != key)
			{
				if (node->key > key) node = node->right;
				else node = node->left;
			}
		}

		if (!node) throw(std::exception("ERROR: Red-Black Tree (TreeTable): trying to delete a non existant element!"));

		// ���������� ���������� ��� ��������������
		bool nodeColor = node->color;
		TreeNode<K, T>* rNode = nullptr;

		// �������� ��� � ����� ������ ������

		// �������� ����� � ������ ������
		if (node == root && size == 1)
		{
			delete root->left;
			delete root->right;
			delete root;

			root = nullptr;
		}

		// ������ ����� ����������� ���
		else if (node->left->isLeaf() && node->right->isLeaf())
		{
			if (node->parent->right == node) node->parent->right = node->right;
			else node->parent->left = node->right;

			node->right->parent = node->parent;

			rNode = node->right;

			delete node->left;
			delete node;
		}

		// ������ ����� ��������� ����

		// ������ ���������
		else if (node->left->isLeaf())
		{
			if (node == root)
				root = node->right;

			else
			{
				if (node->parent->right == node) node->parent->right = node->right;
				else node->parent->left = node->right;
			}

			node->right->parent = node->parent;

			rNode = node->right;

			delete node->left;
			delete node;
		}

		// ����� ���������
		else if (node->right->isLeaf())
		{
			if (node == root)
				root = node->left;

			else
			{
				if (node->parent->right == node) node->parent->right = node->left;
				else node->parent->left = node->left;
			}
			node->left->parent = node->parent;

			rNode = node->left;

			delete node->right;
			delete node;
		}

		// ������ ����� ����������� 2
		else
		{
			// ���� ����������� � ����� ��������� node
			TreeNode<K, T>* pred = node->left;

			while (!pred->right->isLeaf()) pred = pred->right;
			
			// ������� pred �� ������ �������
			if (pred->left->isLeaf())
			{
				pred->parent->right = pred->right;
				delete pred->left;
			}

			else
			{
				pred->parent->right = pred->left;
				delete pred->right;
			}

			// ��������� pred �� ����� �������
			pred->parent = node->parent;
			pred->right = node->right;
			pred->left = node->left;

			rNode = pred;

			if (!pred->parent) root = pred;

			delete node;
		}

		size--;


		// ��������������

		if (nodeColor == NODE_RED || size == 0) return;
		
		while (rNode != root && rNode->color == NODE_BLACK)
		{
			if (rNode == rNode->parent->left)
			{
				TreeNode<K, T>* sibling = rNode->parent->right;

				if (sibling->color == NODE_RED)
				{
					sibling->color = NODE_BLACK;
					rNode->parent->color = NODE_RED;
					rotateLeft(rNode->parent);

					sibling = rNode->parent->right;
				}

				if (sibling->left->color == NODE_BLACK && sibling->right->color == NODE_BLACK)
				{
					sibling->color = NODE_RED;
					rNode = rNode->parent;
				}

				else
				{
					if (sibling->right->color == NODE_BLACK)
					{
						sibling->left->color = NODE_BLACK;
						sibling->color = NODE_RED;
						rotateRight(sibling);

						sibling = rNode->parent->right;
					}

					sibling->color = rNode->parent->color;
					rNode->parent->color = NODE_BLACK;
					sibling->right->color = NODE_BLACK;
					rotateLeft(rNode->parent);

					rNode = root;
				}
			}

			else
			{
				TreeNode<K, T>* sibling = rNode->parent->left;

				if (sibling->color == NODE_RED)
				{
					sibling->color = NODE_BLACK;
					rNode->parent->color = NODE_RED;
					rotateRight(rNode->parent);

					sibling = rNode->parent->left;
				}

				if (sibling->left->color == NODE_BLACK && sibling->right->color == NODE_BLACK)
				{
					sibling->color = NODE_RED;
					rNode = rNode->parent;
				}

				else
				{
					if (sibling->left->color == NODE_BLACK)
					{
						sibling->right->color = NODE_BLACK;
						sibling->color = NODE_RED;
						rotateLeft(sibling);

						sibling = rNode->parent->left;
					}

					sibling->color = rNode->parent->color;
					rNode->parent->color = NODE_BLACK;
					sibling->left->color = NODE_BLACK;
					rotateRight(rNode->parent);

					rNode = root;
				}
			}
		}

		rNode->color = NODE_BLACK;
	}

	// ���� � ���������� ������ �� ������� � ������ K, � ��������� ������ ������� ����������
	virtual T* findElement(const K& key) override
	{
		if (size == 0) return nullptr;
		if (size == 1 && root->key != key) return nullptr;
		
		if (size == 1 && root->key == key) return &root->data;

		// ������ >= 2
		TreeNode<K, T>* node = root;
		while (node && node->key != key)
		{
			if (node->key > key) node = node->right;
			else node = node->left;
		}

		if (!node) return nullptr;
		return &node->data;
	}

	// � outElements �������� ��� �������� ������� � ��������� �������
	virtual void getAllElements(std::vector<std::pair<const K&, const T&>>& outElements) override 
	{
		if (!root) return;

		inorderTraversal(root, outElements);
	}
};