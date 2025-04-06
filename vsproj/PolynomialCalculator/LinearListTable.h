ï»¿#pragma once
#include "Table.h"
#include <stdexcept>

template<typename K, typename T>
class LinearListTable : public Table<K, T>
{
protected:


	template<typename K, typename T>
	struct ListTableString {
		K key;
		T value;
	};

	List<ListTableString<K, T>> data;

public:
	LinearListTable(size_t sz = defaultSize);
	~LinearListTable() override;

	// Äîáàâëÿåò â òàáëèöó ýëåìåíò ñ êëþ÷åì key
	virtual void addElement(const K& key, const T& pol) override;

	// Óäàëÿåò èç òàáëèöû ýëåìåíò ñ êëþ÷åì key
	virtual void deleteElement(const K& key) override;
  
	// Èùåò è âîçâðàùàåò ññûëêó íà ýëåìåíò ñ êëþ÷åì K, â ïðîòèâíîì ñëó÷àå áðîñàåò èñêëþ÷åíèå
	virtual T& findElement(const K& key) override;
};