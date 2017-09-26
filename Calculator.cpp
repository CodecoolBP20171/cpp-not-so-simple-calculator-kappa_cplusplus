//
// Created by bekor on 9/25/17.
//

#include "Calculator.h"
#include <cstring>
#include <algorithm>
#include <cmath>

std::vector<std::string> list_of_oprs;
std::vector<double> numbers;

double Calculator::evaluate(std::string math_problem) {
    math_problem.erase(std::remove_if(begin(math_problem), end(math_problem), isspace), math_problem.end());

    while (0 != math_problem.length()){
        std::string::size_type p;
        double next_nr = stod(math_problem, &p);
        math_problem = math_problem.substr(p);
        numbers.push_back(next_nr);

        math_problem = get_next_operator(math_problem);
    }

    for(const auto& e: list_of_oprs){
        std::cout << "operator(s): " << e << std::endl;
    }
    for(const auto& e: numbers){
        std::cout << "numbers: " << e << std::endl;
    }
    solve("root");
    solve("^");
    solve("/");
    std::cout << "Solving / " << std::endl;
    for(const auto& e: list_of_oprs){
        std::cout << "operator(s): " << e << std::endl;
    }
    for(const auto& e: numbers){
        std::cout << "numbers: " << e << std::endl;
    }
    solve("*");
    std::cout << "Solving * " << std::endl;
    for(const auto& e: list_of_oprs){
        std::cout << "operator(s): " << e << std::endl;
    }
    for(const auto& e: numbers){
        std::cout << "numbers: " << e << std::endl;
    }
    solve("-");
    solve("+");
    std::cout << "Solving + " << std::endl;
    for(const auto& e: list_of_oprs){
        std::cout << "operator(s): " << e << std::endl;
    }
    for(const auto& e: numbers){
        std::cout << "numbers: " << e << std::endl;
    }
    std::cout << "Solving - " << std::endl;
    for(const auto& e: list_of_oprs){
        std::cout << "operator(s): " << e << std::endl;
    }
    for(const auto& e: numbers){
        std::cout << "numbers: " << e << std::endl;
    }

    return numbers[0];
}


std::string Calculator::get_next_operator(std::string part){
    std::string next_opr = "";
    for (int i = 0; i < part.length(); ++i) {
        if(!isdigit(part[i])){
            if(next_opr != "" && std::string(1,part[i]) == "-"){
                list_of_oprs.push_back(next_opr);
                return part.substr(next_opr.length());
            }
            next_opr += part[i];
        } else if(isdigit(part[i])){
            list_of_oprs.push_back(next_opr);
            return part.substr(next_opr.length());
        }
    }
}

void Calculator::solve(std::string op) {

    while(std::find(list_of_oprs.begin(), list_of_oprs.end(), op) != list_of_oprs.end()){
        for (int i = 0; i < list_of_oprs.size(); ++i) {
            if (list_of_oprs[i] == op) {
                if (op == "/") {
                    numbers[i] = numbers[i] / numbers[i+1];
                } else if (op == "*") {
                    numbers[i] = numbers[i] * numbers[i+1];
                } else if (op == "+") {
                    numbers[i] = numbers[i] + numbers[i+1];
                } else if (op == "-") {
                    numbers[i] = numbers[i] - numbers[i+1];
                } else if (op == "^") {
                    numbers[i] = pow(numbers[i], numbers[i+1]);
                } else if (op == "root") {
                    numbers[i] = pow(numbers[i+1], 1.0/numbers[i]);
                }
                numbers.erase(numbers.begin() + (i+1));
                list_of_oprs.erase(list_of_oprs.begin() + i);
                break;
            }
        }
    }
}
