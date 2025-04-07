//﻿
#include "Polynomial.h"
#include <iostream>

// Конструктор по умолчанию
Polynomial::Polynomial() {}

// Конструктор копирования
Polynomial::Polynomial(const Polynomial& pl)
{
	this->monoms = pl.monoms;
}

// Конструктор из константы
Polynomial::Polynomial(int constant)
{
	if (constant != 0)
	{
		polynomialData mono = { constant, 0 };
		insertMonomLast(mono);
	}
}

// Деструктор
Polynomial::~Polynomial() {}

// Присваивание
Polynomial* Polynomial::operator=(const Polynomial& poly)
{
	if (this == &poly)
		return this;


	this->monoms = poly.monoms;
	return this;
}

// Сравнение полиномов
bool Polynomial::operator==(const Polynomial& pl) const
{
	return this->monoms == pl.monoms;
}

// Вставка в правильную позицию (отсортированно по убыванию степени)
void Polynomial::insertMonom(int co, unsigned grad)
{
	polynomialData el{ co, grad };

	if (monoms.empty())
	{
		monoms.insertFirst(el);
		return;
	}

	List<polynomialData> newList;
	bool inserted = false;
	for (size_t i = 0; i < monoms.size(); i++)
	{
		polynomialData curr = monoms[i];
		if (!inserted && curr.grades < el.grades)
		{
			newList.insertLast(el);
			inserted = true;
		}
		newList.insertLast(curr);
	}

	if (!inserted)
		newList.insertLast(el);

	monoms = newList;
}

void Polynomial::insertMonom(const polynomialData& el)
{

	if (monoms.empty())
	{
		monoms.insertFirst(el);
		return;
	}

	List<polynomialData> newList;
	bool inserted = false;
	for (size_t i = 0; i < monoms.size(); i++)
	{
		polynomialData curr = monoms[i];
		if (!inserted && curr.grades < el.grades)
		{
			newList.insertLast(el);
			inserted = true;
		}
		newList.insertLast(curr);
	}

	if (!inserted)
		newList.insertLast(el);

	monoms = newList;
}

// Вставка в конец
void Polynomial::insertMonomLast(int co, unsigned grad)
{
	polynomialData el{ co, grad };
	monoms.insertLast(el);
}

// Вставка в конец
void Polynomial::insertMonomLast(const polynomialData& el)
{
	monoms.insertLast(el);
}

// Сложение
Polynomial Polynomial::operator+(const Polynomial& rhs)
{
	Polynomial result;

	size_t i = 0, j = 0;
	while (i < this->monoms.size() || j < rhs.monoms.size())
	{
		polynomialData newMonom;

		if (j >= rhs.monoms.size() || (i < this->monoms.size() && this->monoms[i].grades > rhs.monoms[j].grades))
		{
			newMonom = this->monoms[i++];
		}
		else if (i >= this->monoms.size() || (j < rhs.monoms.size() && rhs.monoms[j].grades > this->monoms[i].grades))
		{
			newMonom = rhs.monoms[j++];
		}
		else
		{
			newMonom.grades = this->monoms[i].grades;
			newMonom.c = this->monoms[i].c + rhs.monoms[j].c;
			i++;
			j++;
		}

		if (newMonom.c != 0)
			result.insertMonomLast(newMonom);
	}

	return result;
}

// Вычитание
Polynomial Polynomial::operator-(const Polynomial& rhs)
{
	return *this + (rhs * -1.0f);
}

// Умножение на константу
Polynomial Polynomial::operator*(const float scalar) const
{
	Polynomial result;

	for (size_t i = 0; i < monoms.size(); i++)
	{
		polynomialData mono = monoms[i];
		mono.c = static_cast<int>(mono.c * scalar);

		if (mono.c != 0)
			result.insertMonomLast(mono);
	}

	return result;
}

// Умножение полиномов
Polynomial Polynomial::operator*(const Polynomial& rhs)
{
	Polynomial result;

	for (size_t i = 0; i < monoms.size(); i++)
	{
		for (size_t j = 0; j < rhs.monoms.size(); j++)
		{
			polynomialData mono;
			mono.c = monoms[i].c * rhs.monoms[j].c;
			mono.grades = monoms[i].grades + rhs.monoms[j].grades;
			result.insertMonom(mono);
		}
	}

	return result;
}

// Вычисление значения полинома в точке (x, y, z)
long Polynomial::calculate(const int px, const int py, const int pz)
{
	long result = 0;

	for (size_t i = 0; i < monoms.size(); i++)
	{
		int gx = (monoms[i].grades / 100) % 10;
		int gy = (monoms[i].grades / 10) % 10;
		int gz = monoms[i].grades % 10;

		long term = monoms[i].c;
		for (int i = 0; i < gx; i++) term *= px;
		for (int i = 0; i < gy; i++) term *= py;
		for (int i = 0; i < gz; i++) term *= pz;

		result += term;
	}

	return result;
}

// Производная
Polynomial Polynomial::derivate(const std::string& var)
{
	Polynomial result;

	int varIndex;
	if (var == "x") varIndex = 0;
	else if (var == "y") varIndex = 1;
	else if (var == "z") varIndex = 2;
	else return result;

	for (size_t i = 0; i < monoms.size(); i++)
	{
		polynomialData mono = monoms[i];

		int gx = (mono.grades / 100) % 10;
		int gy = (mono.grades / 10) % 10;
		int gz = mono.grades % 10;

		int degrees[3] = { gx, gy, gz };

		if (degrees[varIndex] == 0)
			continue;

		mono.c *= degrees[varIndex];
		degrees[varIndex]--;

		mono.grades = degrees[0] * 100 + degrees[1] * 10 + degrees[2];
		result.insertMonomLast(mono);
	}

	return result;
}

// Интеграл
Polynomial Polynomial::integrate(const std::string& var)
{
	Polynomial result;

	int varIndex;
	if (var == "x") varIndex = 0;
	else if (var == "y") varIndex = 1;
	else if (var == "z") varIndex = 2;
	else return result;

	for (size_t i = 0; i < monoms.size(); i++)
	{
		polynomialData mono = monoms[i];

		int gx = (mono.grades / 100) % 10;
		int gy = (mono.grades / 10) % 10;
		int gz = mono.grades % 10;

		int degrees[3] = { gx, gy, gz };

		degrees[varIndex]++;
		int denom = degrees[varIndex];

		if (mono.c % denom != 0)
			continue;

		mono.c /= denom;
		mono.grades = degrees[0] * 100 + degrees[1] * 10 + degrees[2];
		result.insertMonomLast(mono);
	}

	return result;
}

// Оператор вывода
std::ostream& operator<<(std::ostream& os, const Polynomial& pl)
{
	for (size_t i = 0; i < pl.monoms.size(); i++)
	{
		const auto& mono = pl.monoms[i];
		os << mono.c << "x^" << (mono.grades / 100) % 10
			<< "y^" << (mono.grades / 10) % 10
			<< "z^" << mono.grades % 10 << " ";
	}
	return os;
}