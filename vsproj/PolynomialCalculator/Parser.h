#pragma once
#include "Polynomial.h"


class Parser 
{

public:

   /* Преобразует строковую нотацию полинома в его програмное представление
	* При обнаружении ошибки кидает исключение
	*/
	Polynomial convertStringToPolynomial(const std::string poly_string);

	// Преобразует полином в строковую нотацию
	std::string convertPolynomialToString(const Polynomial& poly);

};