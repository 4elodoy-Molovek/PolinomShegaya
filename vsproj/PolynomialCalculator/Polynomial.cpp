#include "Polynomial.h"
#include <cmath>
#include <stdexcept>
#include <iostream>
#include <vector>
#include <algorithm>

Polynomial::Polynomial()
{
}

Polynomial::Polynomial(const Polynomial& pl)
{
	monoms = pl.monoms;
}

Polynomial::Polynomial(int constant)
{
	if (constant != 0)
	{
		polynomialData monom;
		monom.c = constant;
		monom.grades = 0;
		monoms.insertLast(monom);
	}
}

Polynomial::~Polynomial()
{
}

Polynomial& Polynomial::operator=(const Polynomial& poly)
{
	if (this != &poly)
	{
		monoms = poly.monoms;
	}
	return *this;
}

bool Polynomial::operator==(const Polynomial& pl) const
{
	if (monoms.size() != pl.monoms.size())
	{
		return false;
	}

	std::vector<polynomialData> thisSorted, otherSorted;

	for (int i = 0; i < monoms.size(); ++i)
		thisSorted.push_back(monoms[i]);

	for (int i = 0; i < pl.monoms.size(); ++i)
		otherSorted.push_back(pl.monoms[i]);

	auto comparator = [](const polynomialData& a, const polynomialData& b) {
		return a.grades < b.grades;
		};

	std::sort(thisSorted.begin(), thisSorted.end(), comparator);
	std::sort(otherSorted.begin(), otherSorted.end(), comparator);

	for (size_t i = 0; i < thisSorted.size(); ++i)
	{
		if (!(thisSorted[i] == otherSorted[i]))
			return false;
	}

	return true;
}

bool Polynomial::operator!=(const Polynomial& pl) const
{
	return !(*this == pl);
}

Polynomial Polynomial::operator+(const Polynomial& rhs)
{
	Polynomial result;

	for (int i = 0; i < monoms.size(); ++i)
	{
		result.insertMonom(monoms[i]);
	}

	for (int i = 0; i < rhs.monoms.size(); ++i)
	{
		result.insertMonom(rhs.monoms[i]);
	}

	return result;
}

Polynomial Polynomial::operator-(const Polynomial& rhs)
{
	Polynomial result;

	for (int i = 0; i < monoms.size(); ++i)
	{
		result.insertMonom(monoms[i]);
	}

	for (int i = 0; i < rhs.monoms.size(); ++i)
	{
		polynomialData neg = rhs.monoms[i];
		neg.c *= -1;
		result.insertMonom(neg);
	}

	return result;
}

Polynomial Polynomial::operator*(const Polynomial& rhs)
{
	Polynomial result;

	for (int i = 0; i < monoms.size(); ++i)
	{
		for (int j = 0; j < rhs.monoms.size(); ++j)
		{
			polynomialData prod;
			prod.c = monoms[i].c * rhs.monoms[j].c;

			unsigned a = monoms[i].grades;
			unsigned b = rhs.monoms[j].grades;

			int x = (a / 100) + (b / 100);
			int y = ((a / 10) % 10) + ((b / 10) % 10);
			int z = (a % 10) + (b % 10);

			prod.grades = x * 100 + y * 10 + z;

			result.insertMonom(prod);
		}
	}

	return result;
}

Polynomial Polynomial::operator*(float scalar) const
{
	Polynomial result;

	for (int i = 0; i < monoms.size(); ++i)
	{
		polynomialData scaled = monoms[i];
		scaled.c *= scalar;
		result.insertMonom(scaled);
	}

	return result;
}

Polynomial Polynomial::derivate(const std::string& var)
{
	Polynomial result;

	int varIndex;
	if (var == "x") varIndex = 0;
	else if (var == "y") varIndex = 1;
	else if (var == "z") varIndex = 2;
	else throw std::invalid_argument("Unknown variable");

	for (int i = 0; i < monoms.size(); ++i)
	{
		polynomialData mon = monoms[i];
		int degrees[3] = { mon.grades / 100, (mon.grades / 10) % 10, mon.grades % 10 };

		if (degrees[varIndex] == 0) continue;

		polynomialData der;
		der.c = mon.c * degrees[varIndex];
		degrees[varIndex] -= 1;
		der.grades = degrees[0] * 100 + degrees[1] * 10 + degrees[2];

		result.insertMonom(der);
	}

	return result;
}

Polynomial Polynomial::integrate(const std::string& var)
{
	Polynomial result;

	int varIndex;
	if (var == "x") varIndex = 0;
	else if (var == "y") varIndex = 1;
	else if (var == "z") varIndex = 2;
	else throw std::invalid_argument("Unknown variable");

	for (int i = 0; i < monoms.size(); ++i)
	{
		polynomialData mon = monoms[i];
		int degrees[3] = { mon.grades / 100, (mon.grades / 10) % 10, mon.grades % 10 };

		degrees[varIndex] += 1;

		polynomialData integ;
		integ.grades = degrees[0] * 100 + degrees[1] * 10 + degrees[2];
		integ.c = mon.c / degrees[varIndex];

		result.insertMonom(integ);
	}

	return result;
}

void Polynomial::insertMonom(int co, unsigned grad)
{
	polynomialData el = { co, grad };
	insertMonom(el);
}

void Polynomial::insertMonom(const polynomialData& el)
{
	for (int i = 0; i < monoms.size(); ++i)
	{
		if (monoms[i].grades == el.grades)
		{
			monoms[i].c += el.c;

			if (monoms[i].c == 0)
			{
				monoms.remove(i);
			}

			return;
		}
	}

	if (el.c != 0)
	{
		monoms.insertLast(el);
	}
}

void Polynomial::insertMonomLast(int co, unsigned grad)
{
	polynomialData el = { co, grad };
	monoms.insertLast(el);
}

void Polynomial::insertMonomLast(const polynomialData& el)
{
	monoms.insertLast(el);
}

long Polynomial::calculate(const int px, const int py, const int pz)
{
	long result = 0;

	for (int i = 0; i < monoms.size(); ++i)
	{
		polynomialData mon = monoms[i];
		int x = mon.grades / 100;
		int y = (mon.grades / 10) % 10;
		int z = mon.grades % 10;

		long term = mon.c * std::pow(px, x) * std::pow(py, y) * std::pow(pz, z);
		result += term;
	}

	return result;
}

std::ostream& operator<<(std::ostream& os, const Polynomial& pl)
{
	if (pl.monoms.size() == 0)
	{
		os << "0";
		return os;
	}

	for (int i = 0; i < pl.monoms.size(); ++i)
	{
		const auto& mon = pl.monoms[i];
		if (mon.c == 0) continue;

		if (i > 0 && mon.c > 0) os << " + ";
		else if (mon.c < 0) os << " - ";

		os << std::abs(mon.c);

		int x = mon.grades / 100;
		int y = (mon.grades / 10) % 10;
		int z = mon.grades % 10;

		if (x > 0) os << "x^" << x;
		if (y > 0) os << "y^" << y;
		if (z > 0) os << "z^" << z;
	}

	return os;
}
