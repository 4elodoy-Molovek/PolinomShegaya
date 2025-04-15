#pragma once
#include "ExpressionAnalyzer.h"

using namespace std;

typedef Polynomial(*Tptr)(Polynomial&);


class EA_v1 : public ExpressionAnalyzer
{
	std::map<std::string, Tptr> functionList;

public:
	EA_v1();

	~EA_v1() = default;

	std::vector<std::string> getCachedPostfix();

	std::vector<std::string> getCachedPurePostfix();

	void analyzeExpression(const std::string& expression, std::set<std::string>& outRequestedPolynomials);

	Polynomial calculateSummaryPolynomial(const std::map<std::string, const Polynomial&> polynomials);

private:

	std::vector<std::string> getPostfix(const std::string& expression, std::set<std::string>& outRequestedPolynomials);

	Tptr funcCheck(const std::string&);
};