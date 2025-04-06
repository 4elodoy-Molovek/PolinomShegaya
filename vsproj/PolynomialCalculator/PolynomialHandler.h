#pragma once
#include "Table.h"
#include "ExpressionAnalyzer.h"
#include "Parser.h"
#include "Parser_v1.h"

#include "LinearArrayTable.h"
#include "LinearListTable.h"
#include "HashTableOne.h"
#include "HashTableTwo.h"
#include "TreeTable.h"
#include "SortedArrayTable.h"
#include "Polynomial.h"


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
		//analyzer = new ...
		parser = new Parser_v1();

		tableList[0] = new LinearArrayTable<std::string, Polynomial>();
		//tableList[1] = new LinearListTable<std::string, Polynomial>();
		//tableList[2] = new HashTableOne<std::string, Polynomial>();
		//tableList[3] = new HashTableTwo<std::string, Polynomial>();
		tableList[4] = new TreeTable<std::string, Polynomial>();
		//tableList[5] = new SortedArrayTable<std::string, Polynomial>();

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

