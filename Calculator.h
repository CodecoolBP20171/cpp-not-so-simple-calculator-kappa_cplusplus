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
    std::vector<std::string> list_of_oprs;
    std::vector<double> numbers;
    std::string  get_next_operator(std::string part);
    void solve(std::string op);

};


#endif //CPP_NOT_SO_SIMPLE_CALCULATOR_KAPPA_CPLUSPLUS_CALCULATOR_H
