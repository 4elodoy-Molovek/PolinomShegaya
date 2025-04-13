#pragma once
#include "Table.h"
#include "ExpressionAnalyzer.h"
#include "Parser.h"
#include "Parser_v1.h"
#include "EA_v1.h"

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


	// Последний вычисленный результат выражения
	Polynomial cachedExpressionResult;

public:

	PolynomialHandler()
	{
		analyzer = new EA_v1();
		parser = new Parser_v1();

		tableList[0] = new LinearArrayTable<std::string, Polynomial>();
		tableList[1] = new LinearListTable<std::string, Polynomial>();
		tableList[2] = new HashTableOne<std::string, Polynomial>();
		tableList[3] = new HashTableTwo<std::string, Polynomial>();
		tableList[4] = new TreeTable<std::string, Polynomial>();
		tableList[5] = new SortedArrayTable<std::string, Polynomial>();

	}

	void addPolynomial(const std::string& name, const std::string& notation)
	{
		Polynomial pol = parser->convertStringToPolynomial(notation);

		for (int i = 0; i < 6; i++)
			tableList[i]->addElement(name, pol);
	}

	void deletePolynomial(const std::string& name)
	{
		for (int i = 0; i < 6; i++)
			tableList[i]->deleteElement(name);
	}

	Polynomial calculatePolynomialExpression(const std::string expression)
	{
		std::set<std::string> requestedPolynomials;
		analyzer->analyzeExpression(expression, requestedPolynomials);

		std::map<std::string, const Polynomial&> polynomials;
		for (auto& pol : requestedPolynomials)
		{
			Polynomial* polp = tableList[activeTableID]->findElement(pol);

			if (!polp) throw(std::exception(std::string("ERROR: Polynomial '" + pol + "' not found!").data()));
			polynomials.insert({ pol, *polp });
		}

		cachedExpressionResult = analyzer->calculateSummaryPolynomial(polynomials);
		return cachedExpressionResult;
	}

	std::string getCachedExpressionResultNotation()
	{
		return parser->convertPolynomialToString(cachedExpressionResult);
	}

	void getAllPolynomials(std::vector<std::pair<const std::string&, string>>& outPolynomials)
	{
		std::vector<std::pair<const std::string&, const Polynomial&>> polynomialRequest;
		tableList[activeTableID]->getAllElements(polynomialRequest);

		outPolynomials.clear();
		for (auto& pol : polynomialRequest)
		{
			outPolynomials.push_back({ pol.first, parser->convertPolynomialToString(pol.second) });
		}
	}

	void setActiveTable(size_t newActiveTable) { activeTableID = newActiveTable; }
	size_t GetActiveTable() { return activeTableID; }
};

