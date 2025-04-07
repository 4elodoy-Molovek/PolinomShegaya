#pragma once

#include <string>
#include "List.h"

class Polynomial
{
private:

	// Содержит данные об одном мономе
	struct polynomialData
	{
		int c;
		unsigned grades;
	};

	// Лист всех мономов полинома
	List<polynomialData> monoms;

public:

	// Конструктор по умолчанию
	Polynomial();

	// Конструктор копирования
	Polynomial(const Polynomial& pl);

	// Конструктор константы
	Polynomial(int constant);

	// Деструктор
	~Polynomial();

	// Оператор присванивания
	Polynomial* operator= (const Polynomial& poly);

	// Оператор сравнения полиномов
	bool operator==(const Polynomial& pl);

	// Сложение полиномов
	Polynomial operator+ (const Polynomial& rhs);
	// Вычитание полиномов
	Polynomial operator- (const Polynomial& rhs);
	// Умножение полиномов
	Polynomial operator* (const Polynomial& rhs);
	// Умножение полинома на константу
	Polynomial operator* (float scalar) const;

	// Взятие производной полинома
	Polynomial derivate(const std::string& var);
	// Интегрирование полинома
	Polynomial integrate(const std::string& var);

	// Вставка монома в правильную позицию (поддерживает отсортированность полинома)
	void insertMonom(int co, unsigned grad);
	void insertMonom(const polynomialData& el);

	// Вставка монома в конец списка (правильност порядка на совести программиста)
	void insertMonomLast(int co, unsigned grad);
	void insertMonomLast(const polynomialData& el);

	// Вычисляет значение полинома в точке
	long calculate(const int px, const int py, const int pz);

	friend std::ostream& operator<<(std::ostream& os, const Polynomial& pl);

	friend class Parser_v1;
};