#pragma once
#include "Polynomial.h"


class Parser 
{

public:

// vers by 4elodoy-Molovek
   /* РџСЂРµРѕР±СЂР°Р·СѓРµС‚ СЃС‚СЂРѕРєРѕРІСѓСЋ РЅРѕС‚Р°С†РёСЋ РїРѕР»РёРЅРѕРјР° РІ РµРіРѕ РїСЂРѕРіСЂР°РјРЅРѕРµ РїСЂРµРґСЃС‚Р°РІР»РµРЅРёРµ
	* РџСЂРё РѕР±РЅР°СЂСѓР¶РµРЅРёРё РѕС€РёР±РєРё РєРёРґР°РµС‚ РёСЃРєР»СЋС‡РµРЅРёРµ
  */
// vers by main
	Parser() {}
	virtual ~Parser() {}

   /* Преобразует строковую нотацию полинома в его програмное представление
	* При обнаружении ошибки кидает исключение
	*/
	virtual Polynomial convertStringToPolynomial(const std::string poly_string) = 0;

	// Преобразует полином в строковую нотацию
	virtual std::string convertPolynomialToString(const Polynomial& poly) = 0;

};