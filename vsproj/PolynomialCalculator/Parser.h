#pragma once
#include "Polynomial.h"


class Parser 
{

public:

	Parser() {}
	virtual ~Parser() {}

   /* Преобразует строковую нотацию полинома в его програмное представление
	* При обнаружении ошибки кидает исключение
	*/
	virtual Polynomial convertStringToPolynomial(const std::string poly_string) = 0;

	// Преобразует полином в строковую нотацию
	virtual std::string convertPolynomialToString(const Polynomial& poly) = 0;

};