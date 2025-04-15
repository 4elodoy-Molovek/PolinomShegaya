#include "Polynomial.h"
#include <cmath>
#include <stdexcept>
#include <iostream>
#include <iomanip>
#include <algorithm>
#include <vector>

constexpr double EPS = 1e-9;

Polynomial::Polynomial() {}

Polynomial::Polynomial(const Polynomial& pl)
{
	monoms = pl.monoms;
}

Polynomial::Polynomial(double constant)
{
	if (std::fabs(constant) > EPS)
	{
		insertMonom(constant, 0);
	}
}

Polynomial::~Polynomial() {}

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
		return false;

	std::vector<polynomialData> a, b;
	for (int i = 0; i < monoms.size(); ++i)
	{
		a.push_back(monoms[i]);
		b.push_back(pl.monoms[i]);
	}

	auto cmp = [](const polynomialData& lhs, const polynomialData& rhs) 
		{
		if (lhs.grades != rhs.grades)
			return lhs.grades < rhs.grades;
		return std::fabs(lhs.c - rhs.c) > 1e-9 ? lhs.c < rhs.c : false;
	};

	std::sort(a.begin(), a.end(), cmp);
	std::sort(b.begin(), b.end(), cmp);

	for (size_t i = 0; i < a.size(); ++i)
	{
		if (a[i].grades != b[i].grades || std::fabs(a[i].c - b[i].c) > 1e-9)
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
	Polynomial result = *this;

	for (int i = 0; i < rhs.monoms.size(); ++i)
	{
		result.insertMonom(rhs.monoms[i]);
	}

	return result;
}

Polynomial Polynomial::operator-(const Polynomial& rhs)
{
	Polynomial result = *this;

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

			int x = (a / 10000) + (b / 10000);
			int y = ((a / 100) % 100) + ((b / 100) % 100);
			int z = (a % 100) + (b % 100);

			if (x > 99 || y > 99 || z > 99)
				throw std::overflow_error("Exponent too large during multiplication");

			prod.grades = x * 10000 + y * 100 + z;

			result.insertMonom(prod);
		}
	}

	return result;
}

Polynomial Polynomial::operator*(double scalar) const
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
		int degrees[3] = {
			mon.grades / 10000,
			(mon.grades / 100) % 100,
			mon.grades % 100
		};

		if (degrees[varIndex] == 0) continue;

		polynomialData der;
		der.c = mon.c * degrees[varIndex];
		degrees[varIndex] -= 1;
		der.grades = degrees[0] * 10000 + degrees[1] * 100 + degrees[2];

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
		int degrees[3] = {
			mon.grades / 10000,
			(mon.grades / 100) % 100,
			mon.grades % 100
		};

		degrees[varIndex] += 1;
		int deg = degrees[varIndex];

		if (degrees[0] > 99 || degrees[1] > 99 || degrees[2] > 99)
			throw std::overflow_error("Exponent too large during integration");

		polynomialData integ;
		integ.grades = degrees[0] * 10000 + degrees[1] * 100 + degrees[2];
		integ.c = mon.c / deg;

		result.insertMonom(integ);
	}

	return result;
}

void Polynomial::insertMonom(double co, unsigned grad)
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

			if (std::fabs(monoms[i].c) < EPS)
			{
				monoms.remove(i);
			}
			return;
		}
	}

	if (std::fabs(el.c) > EPS)
	{
		monoms.insertLast(el);
	}
}

void Polynomial::insertMonomLast(double co, unsigned grad)
{
	insertMonomLast({ co, grad });
}

void Polynomial::insertMonomLast(const polynomialData& el)
{
	monoms.insertLast(el);
}

double Polynomial::calculate(double px, double py, double pz)
{
	double result = 0;

	for (int i = 0; i < monoms.size(); ++i)
	{
		polynomialData mon = monoms[i];
		int x = mon.grades / 10000;
		int y = (mon.grades / 100) % 100;
		int z = mon.grades % 100;

		double term = mon.c * std::pow(px, x) * std::pow(py, y) * std::pow(pz, z);
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
		if (std::abs(mon.c) < EPS) continue;

		if (i > 0 && mon.c > 0) os << "+";
		else if (mon.c < 0) os << "-";

		double absCoeff = std::abs(mon.c);
		int x = mon.grades / 10000;
		int y = (mon.grades / 100) % 100;
		int z = mon.grades % 100;

		bool hasVars = (x || y || z);

		if (!hasVars || std::fabs(absCoeff - 1.0) > EPS)
			os << std::fixed << std::setprecision(3) << absCoeff;

		if (x > 0) os << "x" << (x > 1 ? ("^" + std::to_string(x)) : "");
		if (y > 0) os << "y" << (y > 1 ? ("^" + std::to_string(y)) : "");
		if (z > 0) os << "z" << (z > 1 ? ("^" + std::to_string(z)) : "");
	}

	return os;
}
