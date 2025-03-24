#pragma once
#include <string>
#include "List.h"


class Polynomial 
{
private:

	// Содержит данные об одном мономе
	struct polynomialData {
		int c;
		unsigned grades;
	};

	// Лист всех мономов полинома
	List<polynomialData> monoms;

	// Вставка монома в правильную позицию (поддерживает отсортированность полинома)
	void insertMonom(polynomialData& el);

	// Вставка монома в конец списка (правильност порядка на совести программиста)
	void insertMonomLast(polynomialData& el);


public:

	// Конструктор по умолчанию
	Polynomial();

	// Конструктор копирования
	Polynomial(const Polynomial& pl);

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
	Polynomial operator* (const float scalar);

	// Взятие производной полинома
	Polynomial derivate(const std::string& var);
	// Интегрирование полинома
	Polynomial integrate(const std::string& var);

	// Вычисляет значение полинома в точке
	long calculate(const int px, const int py, const int pz);

	friend std::ostream& operator<<(std::ostream& os, const Polynomial& pl);
};

