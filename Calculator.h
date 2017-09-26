//
// Created by bekor on 9/25/17.
//

#ifndef CPP_NOT_SO_SIMPLE_CALCULATOR_KAPPA_CPLUSPLUS_CALCULATOR_H
#define CPP_NOT_SO_SIMPLE_CALCULATOR_KAPPA_CPLUSPLUS_CALCULATOR_H

#include <iostream>
#include <vector>

class Calculator {

public:
    double evaluate(const char * string);

private:
    std::vector<std::string> list_of_oprs;
    std::vector<std::int> numbers;
    std::string  get_next_operator(char *part);
};


#endif //CPP_NOT_SO_SIMPLE_CALCULATOR_KAPPA_CPLUSPLUS_CALCULATOR_H
