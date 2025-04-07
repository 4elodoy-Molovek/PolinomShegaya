#pragma once
#include <string>
#include <vector>
#include <map>
#include <stack>
#include <set>
#include "Polynomial.h"


/*
 * Отвечает за обработку математических выражений с полиномами
 */

class ExpressionAnalyzer 
{
protected: 
	// Постфиксная форма последнего проанализированного выражения
	std::vector<std::string> cachedPostfix;

public:

	ExpressionAnalyzer() {}
	virtual ~ExpressionAnalyzer() {}

	/* 
	 * Анализирует выражение строя его постфиксную форму и записывая её в cachedPostfix
	 * В outRequestedPolynomials метод положит имена полиномов, которые необходимо получить из таблиц
	 * 
	 * Подробности:
	 *		1) Поддержка операций '+', '-', '* на полином', '* на константу';
	 *		2) Поддержка скобок '(' и ')';
	 *		3) Лексемы состоящие исключительно из цифр и точек воспринимаются как константы;
	 *		4) Любые другие лексемы воспринимаются как имена полиномов;
	 *		5) Умножение ТОЛЬКО через знак '*';
	 *		6) При обнаружении ошибки бросает исключение
	 */
	virtual void analyzeExpression(const std::string& expression, std::set<std::string>& outRequestedPolynomials) = 0;

	/*
	 * Вычисляет результат последнего проанализированного выражения
	 * В polynomials подаются полиномы, запрошенные в outRequestedPolynomials, полученном от analyzeExpression
	 */
	virtual Polynomial calculateSummaryPolynomial(const std::map<std::string, const Polynomial&> polynomials) = 0;

protected:

	// Строит постфиксную форму выражения
	virtual std::vector<std::string> getPostfix(const std::string& expression, std::set<std::string>& outRequestedPolynomials) = 0;
};