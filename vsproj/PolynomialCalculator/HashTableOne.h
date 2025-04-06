#pragma once
#include "Table.h"

template<typename K, typename T>
class HashTableOne : public Table<K, T>
{
protected:
	struct Node
	{
		T data;
		bool deleted;
	};
	int size; // ÑÐºÐ¾Ð»ÑÐºÐ¾ ÑÐ»ÐµÐ¼ÐµÐ½ÑÐ¾Ð² Ñ Ð½Ð°Ñ ÑÐµÐ¹ÑÐ°Ñ Ð² Ð¼Ð°ÑÑÐ¸Ð²Ðµ (Ð±ÐµÐ· ÑÑÐµÑÐ° deleted)
	int bufferSize; // ÑÐ°Ð·Ð¼ÐµÑ ÑÐ°Ð¼Ð¾Ð³Ð¾ Ð¼Ð°ÑÑÐ¸Ð²Ð°, ÑÐºÐ¾Ð»ÑÐºÐ¾ Ð¿Ð°Ð¼ÑÑÐ¸ Ð²ÑÐ´ÐµÐ»ÐµÐ½Ð¾ Ð¿Ð¾Ð´ ÑÑÐ°Ð½ÐµÐ½Ð¸Ðµ Ð½Ð°ÑÐµÐ¹ ÑÐ°Ð±Ð»Ð¸ÑÑ
	int sizeAllNonNullptr; // ÑÐºÐ¾Ð»ÑÐºÐ¾ ÑÐ»ÐµÐ¼ÐµÐ½ÑÐ¾Ð² Ñ Ð½Ð°Ñ ÑÐµÐ¹ÑÐ°Ñ Ð² Ð¼Ð°ÑÑÐ¸Ð²Ðµ (Ñ ÑÑÐµÑÐ¾Ð¼ deleted)

public:
	HashTableOne(size_t sz = defaultSize);
	~HashTableOne() override;

	// Äîáàâëÿåò â òàáëèöó ýëåìåíò ñ êëþ÷åì key
	virtual void addElement(const K& key, const T& pol) override;

	// Óäàëÿåò èç òàáëèöû ýëåìåíò ñ êëþ÷åì key
	virtual void deleteElement(const K& key) override;

	// Èùåò è âîçâðàùàåò ññûëêó íà ýëåìåíò ñ êëþ÷åì K, â ïðîòèâíîì ñëó÷àå áðîñàåò èñêëþ÷åíèå
	virtual T& findElement(const K& key) override;
};