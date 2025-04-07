#include <string>
#include "Polynomial.h"
#include "Parser.h"

class Parser_v1 : public Parser
{
public:
    Parser_v1() = default;
    virtual ~Parser_v1() = default;

    virtual Polynomial convertStringToPolynomial(const std::string poly_string) override;

    virtual std::string convertPolynomialToString(const Polynomial& poly) override;
};