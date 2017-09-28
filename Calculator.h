//
// Created by bekor on 9/25/17.
//

#ifndef CPP_NOT_SO_SIMPLE_CALCULATOR_KAPPA_CPLUSPLUS_CALCULATOR_H
#define CPP_NOT_SO_SIMPLE_CALCULATOR_KAPPA_CPLUSPLUS_CALCULATOR_H

#include <iostream>
#include <vector>
#include <cstring>
#include <algorithm>
#include <cmath>

class Calculator {

public:
    double evaluate(std::string formula);
    Calculator();
    ~Calculator() = default;

private:
    const std::string VALID_OPERATORS[6] = {"root", "^", "/", "*", "-", "+"};
    int number_of_operators;
    bool are_operators_valid;
    bool exists_div_by_zero;
    bool result_is_complex_nr;
    std::vector<std::string> list_of_oprs;
    std::vector<double> numbers;

    std::string handle_parentheses(std::string formula);
    std::string get_next_operator(std::string part);
    double calculate(std::string formula);
    bool is_operator_valid(std::string op);
    void solve(std::string op);
    bool check_parenthesis(std::string formula);
    void parse_math_problem(std::string formula);

};


#endif //CPP_NOT_SO_SIMPLE_CALCULATOR_KAPPA_CPLUSPLUS_CALCULATOR_H
