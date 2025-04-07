#pragma once
#include "Table.h"

class HashTableTwo : public Table
{
protected:
	struct Node
	{
		Polynomial data;
		bool deleted;
	};
	int size; // ñêîëüêî ýëåìåíòîâ ó íàñ ñåé÷àñ â ìàññèâå (áåç ó÷åòà deleted)
	int bufferSize; // ðàçìåð ñàìîãî ìàññèâà, ñêîëüêî ïàìÿòè âûäåëåíî ïîä õðàíåíèå íàøåé òàáëèöû
	int sizeAllNonNullptr; // ñêîëüêî ýëåìåíòîâ ó íàñ ñåé÷àñ â ìàññèâå (ñ ó÷åòîì deleted)

public:
	HashTableTwo(size_t sz = defaultSize);
	~HashTableTwo() override;

	// Äîáàâëÿåò ïîëèíîì pol â òàáëèöó ñ êëþ÷åì(èìåíåì) name
	virtual void addElement(const std::string& name, const Polynomial& pol) override;

	// Óäàëÿåò èç ïîëèíîì ñ èìåíåì name èç òàáëèöû
	virtual void deleteElement(const std::string& name) override;

	// Èùåò è âîçâðàùàåò ññûëêó íà ýëåìåíò ñ êëþ÷åì K, â ïðîòèâíîì ñëó÷àå áðîñàåò èñêëþ÷åíèå
	virtual T* findElement(const K& key) override;
};