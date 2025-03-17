#pragma once
#include <string>
#include "List.h"


struct polynomialData {
	int c;
	unsigned grades;
};


template <typename T>
class Polynomial 
{
private:
	List<polynomialData> monoms;

	void insertMonom(polynomialData& el);
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

