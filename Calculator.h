//
// Created by bekor on 9/25/17.
//

#ifndef CPP_NOT_SO_SIMPLE_CALCULATOR_KAPPA_CPLUSPLUS_CALCULATOR_H
#define CPP_NOT_SO_SIMPLE_CALCULATOR_KAPPA_CPLUSPLUS_CALCULATOR_H

#include <iostream>
#include <vector>
#include <stack>

class Calculator {

public:
    double evaluate(std::string math_problem);

private:
    std::string LIST_OF_VALID_OPERATORS[6];
    std::vector<std::string> list_of_oprs;
    std::vector<double> numbers;
    std::string  get_next_operator(std::string part);
    bool are_operators_valid;
    void solve(std::string op);
    bool checkOperators();

};


#endif //CPP_NOT_SO_SIMPLE_CALCULATOR_KAPPA_CPLUSPLUS_CALCULATOR_H
