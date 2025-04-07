#include "Parser_v1.h"
#include "Polynomial.h"
#include <regex>
#include <sstream>
#include <cctype>
#include <string>
#include <iostream>

Polynomial Parser_v1::convertStringToPolynomial(const std::string poly_string)
{
    Polynomial result;

    std::regex term_regex(R"(([+-]?\s*\d*)([xyz](\^\d+)?)*?)", std::regex_constants::icase);
    std::sregex_iterator iter(poly_string.begin(), poly_string.end(), term_regex);
    std::sregex_iterator end;

    for (; iter != end; ++iter)
    {
        std::string full_match = iter->str();
        if (full_match.empty() || std::all_of(full_match.begin(), full_match.end(), isspace)) continue;

        // Коэффициент
        std::smatch match;
        std::regex term_parse(R"(([+-]?\s*\d*)([xyz](\^\d+)?)*?)");
        if (!std::regex_match(full_match, match, term_parse)) continue;

        std::string coeff_str = match[1].str();
        coeff_str.erase(remove_if(coeff_str.begin(), coeff_str.end(), ::isspace), coeff_str.end());

        int coeff = 1;
        if (!coeff_str.empty() && coeff_str != "+" && coeff_str != "-")
        {
            coeff = std::stoi(coeff_str);
        }
        else if (coeff_str == "-")
        {
            coeff = -1;
        }
        else if (coeff_str == "+")
        {
            coeff = 1;
        }

        // Переменные
        int x = 0, y = 0, z = 0;
        std::regex var_regex(R"(([xyz])(\^(\d+))?)", std::regex_constants::icase);
        std::sregex_iterator var_iter(full_match.begin(), full_match.end(), var_regex);
        std::sregex_iterator var_end;

        for (; var_iter != var_end; ++var_iter)
        {
            char var = tolower((*var_iter)[1].str()[0]);
            int power = 1;
            if ((*var_iter)[3].matched)
                power = std::stoi((*var_iter)[3].str());

            switch (var)
            {
            case 'x': x = power; break;
            case 'y': y = power; break;
            case 'z': z = power; break;
            }
        }

        unsigned grades = x * 100 + y * 10 + z;
        result.insertMonom(coeff, grades);
    }

    return result;
}

std::string Parser_v1::convertPolynomialToString(const Polynomial& poly)
{
    std::ostringstream oss;
    bool first = true;

    // Доступ к pFirst напрямую (Parser_v1 — friend Polynomial)
    //ListNode<Polynomial::polynomialData>* node = poly.monoms[0];
    size_t i = 0;

    while (i < poly.monoms.size())
    {
        int coeff = poly.monoms[i].c;
        if (coeff == 0) {
            i++;
            continue;
        }

        unsigned grades = poly.monoms[i].grades;
        int x = grades / 100;
        int y = (grades / 10) % 10;
        int z = grades % 10;

        // Знак
        if (!first) {
            oss << (coeff > 0 ? "+" : "");
        }

        // Коэффициент
        if (coeff == -1 && (x || y || z))
            oss << "-";
        else if (coeff != 1 || (x == 0 && y == 0 && z == 0))
            oss << coeff;

        // Переменные
        if (x > 0) oss << "x" << (x > 1 ? ("^" + std::to_string(x)) : "");
        if (y > 0) oss << "y" << (y > 1 ? ("^" + std::to_string(y)) : "");
        if (z > 0) oss << "z" << (z > 1 ? ("^" + std::to_string(z)) : "");

        first = false;
        i++;
    }

    std::string result = oss.str();
    if (result.empty()) return "0";
    return result;
}