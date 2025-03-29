#pragma once
#include "Polynomial.h"


class Parser_v1 : public Parser
{

public:

	Parser() {}
	virtual ~Parser() {}

	/* Ïðåîáðàçóåò ñòðîêîâóþ íîòàöèþ ïîëèíîìà â åãî ïðîãðàìíîå ïðåäñòàâëåíèå
	 * Ïðè îáíàðóæåíèè îøèáêè êèäàåò èñêëþ÷åíèå
	 */
	virtual Polynomial convertStringToPolynomial(const std::string poly_string) override;

	// Ïðåîáðàçóåò ïîëèíîì â ñòðîêîâóþ íîòàöèþ
	virtual std::string convertPolynomialToString(const Polynomial& poly) override;

};