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

	// Äîáàâëÿåò â òàáëèöó ýëåìåíò ñ êëþ÷åì key
	virtual void addElement(const K& key, const T& pol) override;

	// Óäàëÿåò èç òàáëèöû ýëåìåíò ñ êëþ÷åì key
	virtual void deleteElement(const K& key) override;

	// Èùåò è âîçâðàùàåò ññûëêó íà ýëåìåíò ñ êëþ÷åì K, â ïðîòèâíîì ñëó÷àå áðîñàåò èñêëþ÷åíèå
	virtual T& findElement(const K& key) override;
};