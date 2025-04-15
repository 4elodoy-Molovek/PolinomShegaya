#pragma once

#include <string>
#include <cmath>
#include "List.h"

class Polynomial
{
private:

	struct polynomialData
	{
		double c;
		unsigned grades;

		bool operator==(const polynomialData& rhs) const
		{
			constexpr double EPS = 1e-9;
			return std::fabs(c - rhs.c) < EPS && grades == rhs.grades;
		}

		bool operator!=(const polynomialData& rhs) const
		{
			return !(*this == rhs);
		}

	};

	List<polynomialData> monoms;

public:

	Polynomial();
	Polynomial(const Polynomial& pl);
	explicit Polynomial(double constant);
	~Polynomial();

	Polynomial& operator=(const Polynomial& poly);

	bool operator==(const Polynomial& pl) const;
	bool operator!=(const Polynomial& pl) const;

	Polynomial operator+(const Polynomial& rhs);
	Polynomial operator-(const Polynomial& rhs);
	Polynomial operator*(const Polynomial& rhs);
	Polynomial operator*(double scalar) const;

	Polynomial derivate(const std::string& var);
	Polynomial integrate(const std::string& var);

	void insertMonom(double co, unsigned grad);
	void insertMonom(const polynomialData& el);

	void insertMonomLast(double co, unsigned grad);
	void insertMonomLast(const polynomialData& el);

	double calculate(double px, double py, double pz);

	friend std::ostream& operator<<(std::ostream& os, const Polynomial& pl);
	friend class Parser_v1;
};
