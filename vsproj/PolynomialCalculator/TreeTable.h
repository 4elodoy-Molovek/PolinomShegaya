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

	// Добавляет в таблицу элемент с ключем key
	virtual void addElement(const K& key, const T& pol) override;

	// Удаляет из таблицы элемент с ключем key
	virtual void deleteElement(const K& key) override;

	// Ищет и возвращает ссылку на элемент с ключем K, в противном случае бросает исключение
	virtual T& findElement(const K& key) override;
};