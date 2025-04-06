#pragma once
#include "ExpressionAnalyzer.h"


typedef Polynomial(*Tptr)(Polynomial);


class EA_v1 : public ExpressionAnalyzer 
{
	std::map<std::string, Tptr> function_list; 

public:
	EA_v1();

	~EA_v1() = default;

	void analyzeExpression(const std::string& expression, std::set<std::string>& outRequestedPolynomials);

	Polynomial calculateSummaryPolynomial(std::map<std::string, Polynomial> polynomials);

	private:

	std::vector<std::string> getPostfix(const std::string& expression, std::set<std::string>& outRequestedPolynomials);

	Tptr funcCheck(const std::string&);
};