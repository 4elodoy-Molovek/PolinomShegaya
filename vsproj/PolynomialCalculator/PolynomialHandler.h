#pragma once
#include "Table.h"
#include "ExpressionAnalyzer.h"
#include "Parser.h"

class PolynomialHandler 
{

private:

	// Массив указателей на таблицы, хранящие полиномы
	Table<std::string, Polynomial>* tableList[6];

	// Индекс активной таблицы
	size_t activeTableID;

	/* Указатель на объект класса ExpressionAnalyzer, 
	 * Отвечает за обработку математических выражений с полиномами.
	 */
	ExpressionAnalyzer* analyzer;
	
	/* Указатель на объект класса Parser, 
	 * Преобразует строковую нотацию полинома в объект класса Polynomial и обратно
	 */
	Parser* parser;

public:

	PolynomialHandler()
	{
		// Инициализация (Создание) Таблиц, ExpressionAnalyzer и Parser

	}

	void addPolynomial(const std::string& name, const std::string& notation)
	{

	}

	void deletePolynomial(const std::string& name);

	Polynomial calculatePolynomialExpression(const std::string expression);

	const Polynomial& findPolynomial(const std::string& name);

	void setActiveTable(size_t newActiveTable);
	size_t GetActiveTable();
};

