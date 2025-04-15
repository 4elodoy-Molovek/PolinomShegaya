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

    std::string cleaned = poly_string;
    cleaned.erase(remove_if(cleaned.begin(), cleaned.end(), ::isspace), cleaned.end());

    std::regex monom_regex(R"(([+-]?[^+-]+))");
    std::sregex_iterator iter(cleaned.begin(), cleaned.end(), monom_regex);
    std::sregex_iterator end;

    for (; iter != end; ++iter)
    {
        std::string monom_str = iter->str();

        int coeff = 1;
        int sign = 1;

        if (monom_str[0] == '-') {
            sign = -1;
            monom_str = monom_str.substr(1);
        }
        else if (monom_str[0] == '+') {
            monom_str = monom_str.substr(1);
        }

        std::regex coeff_regex(R"(^\d+)");
        std::smatch coeff_match;
        if (std::regex_search(monom_str, coeff_match, coeff_regex))
        {
            coeff = std::stoi(coeff_match.str());
            monom_str = monom_str.substr(coeff_match.length());
        }

        coeff *= sign;

        int x = 0, y = 0, z = 0;
        std::regex var_regex(R"(([xyz])(\^(\d+))?)");
        std::sregex_iterator var_iter(monom_str.begin(), monom_str.end(), var_regex);
        std::sregex_iterator var_end;

        for (; var_iter != var_end; ++var_iter)
        {
            char var = tolower((*var_iter)[1].str()[0]);
            int power = 1;
            if ((*var_iter)[3].matched)
                power = std::stoi((*var_iter)[3].str());

            if (power > 99)
                throw(std::out_of_range("The power of variable " + std::string(1, var) + " is more than 99"));

            switch (var)
            {
            case 'x': x = power; break;
            case 'y': y = power; break;
            case 'z': z = power; break;
            }
        }

        // Преобразуем (x, y, z) в длинный hash-ключ
        // Например, x=10, y=20, z=30 -> 0010 0020 0030 -> long ключ
        // Используем 3 цифры на каждую переменную:
        unsigned grades = x * 10000 + y * 100 + z;

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
        int x = grades / 10000;
        int y = (grades / 100) % 100;
        int z = grades % 100;

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