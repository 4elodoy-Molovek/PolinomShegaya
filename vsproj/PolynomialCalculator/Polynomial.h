#pragma once
#include <string>
using ui = unsigned;

struct Node 
{
	int c;
	ui grades;
	Node* pNext;
};

class List 
{
	friend class Polynomial;
	Node* pFirst;
	Node* pLast;

public:
	List();
	List(Node*& fst);
	List(const List& lis);
	~List();

	void InsertFirst(Node*& n);
	void InsertLast(Node*& n);

	bool operator==(const List& l);
	List& operator=(const List& lis);
};

class Polynomial 
{
	List monoms;

	void Insert(Node*& el);
	void Unite();
	bool check(const std::string& s);
	std::string despace(const std::string& str);
public:
	Polynomial();
	Polynomial(const std::string& poly);
	Polynomial(const Polynomial& pl);
	~Polynomial();

	Polynomial* operator= (const Polynomial& poly);
	bool operator==(const Polynomial& pl);
	Polynomial operator+ (const Polynomial& rhs);
	Polynomial operator- (const Polynomial& rhs);
	Polynomial operator* (const Polynomial& rhs);
	Polynomial derivate(const std::string& var);
	Polynomial integrate(const std::string& var);

	std::string getStrVers();
	long calculate(const int px, const int py, const int pz);
	friend std::ostream& operator<<(std::ostream& os, const Polynomial& pl);

};

