#pragma once
#include "Polynomial.h"
#include "Parser.h"

class Parser_v1 : public Parser
{

public:

	Parser_v1 () {}
	virtual ~Parser_v1 () {}

	/* Ïðåîáðàçóåò ñòðîêîâóþ íîòàöèþ ïîëèíîìà â åãî ïðîãðàìíîå ïðåäñòàâëåíèå
	 * Ïðè îáíàðóæåíèè îøèáêè êèäàåò èñêëþ÷åíèå
	 */
	virtual Polynomial convertStringToPolynomial(const std::string poly_string) override;

	// Ïðåîáðàçóåò ïîëèíîì â ñòðîêîâóþ íîòàöèþ
	virtual std::string convertPolynomialToString(const Polynomial& poly) override;

};