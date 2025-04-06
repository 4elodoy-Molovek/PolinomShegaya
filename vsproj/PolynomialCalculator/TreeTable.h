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


	// Äîáàâëÿåò â òàáëèöó ýëåìåíò ñ êëþ÷åì key
	virtual void addElement(const K& key, const T& pol) override;

	// Óäàëÿåò èç òàáëèöû ýëåìåíò ñ êëþ÷åì key
	virtual void deleteElement(const K& key) override;

	// Èùåò è âîçâðàùàåò ññûëêó íà ýëåìåíò ñ êëþ÷åì K, â ïðîòèâíîì ñëó÷àå áðîñàåò èñêëþ÷åíèå
	virtual T& findElement(const K& key) override;
};