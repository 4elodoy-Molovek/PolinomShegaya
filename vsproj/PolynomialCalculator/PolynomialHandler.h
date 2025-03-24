#pragma once
#include "Table.h"
#include "ExpressionAnalyzer.h"
#include "Parser.h"

class PolynomialHandler 
{

private:

	// Массив указателей на все типы таблиц
	Table* tableList[6];

	// Индекс активной таблицы
	int activeTableID;

	/* Указатель на Объект класса ExpressionAnalyzer, 
	 * отвечающий за обработку математических выражений с полиномами.
	 */
	ExpressionAnalyzer* analyzer;
	
	/* Указатель на Объект класса Parser, 
	 * отвечающий за перевод строковой нотации полинома в его программное представление в виде объекта класса Polynomial
	 */
	Parser* parser;

public:

	PolynomialHandler()
	{
		// Инициализация (Создание) Таблиц, ExpressionAnalyzer и Parser
	}

	void addPolynomial()
	{

	}
	void deletePolynomial();
	void findPolynomial();

	void calculatePolynomialExpression(const std::string expression);
};

