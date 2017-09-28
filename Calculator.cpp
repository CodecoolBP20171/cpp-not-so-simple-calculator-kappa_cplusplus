//
// Created by bekor on 9/25/17.
//

#include "Calculator.h"

Calculator::Calculator(){
    number_of_operators = sizeof(VALID_OPERATORS)/sizeof(VALID_OPERATORS[0]);
    are_operators_valid = true;
    exists_div_by_zero = false;
    result_is_complex_nr = false;
}

double Calculator::evaluate(std::string formula) {
    if(formula.empty()) return 0;

    formula.erase(std::remove_if(begin(formula), end(formula), isspace), formula.end());

    if(!check_parenthesis(formula)){
        std::cout << "Invalid parenthesis" << std::endl;
        return 0;
    }

    formula = handle_parentheses(formula);

    return calculate(formula);
}


std::string Calculator::get_next_operator(std::string part){
    std::string next_opr = "";
    for (int i = 0; i < part.length(); ++i) {
        if(!isdigit(part[i])){
            if(next_opr != "" && std::string(1,part[i]) == "-"){
                list_of_oprs.push_back(next_opr);
                are_operators_valid = is_operator_valid(next_opr);
                return part.substr(next_opr.length());
            }
            next_opr += part[i];
        } else if(isdigit(part[i])){
            list_of_oprs.push_back(next_opr);
            are_operators_valid = is_operator_valid(next_opr);
            return part.substr(next_opr.length());
        }
    }
    return "";
}

void Calculator::solve(std::string op) {
    while(std::find(list_of_oprs.begin(), list_of_oprs.end(), op) != list_of_oprs.end()){
        for (int i = 0; i < list_of_oprs.size(); ++i) {
            if (list_of_oprs[i] == op) {
                if (op == "/") {
                    if(numbers[i+1] == 0){
                        exists_div_by_zero = true;
                    } else {
                        numbers[i] = numbers[i] / numbers[i+1];
                    }
                } else if (op == "*") {
                    numbers[i] = numbers[i] * numbers[i+1];
                } else if (op == "+") {
                    numbers[i] = numbers[i] + numbers[i+1];
                } else if (op == "-") {
                    numbers[i] = numbers[i] - numbers[i+1];
                } else if (op == "^") {
                    numbers[i] = pow(numbers[i], numbers[i+1]);
                } else if (op == "root") {
                    if(numbers[i+1] < 0) {
                        result_is_complex_nr = true;
                    } else {
                        numbers[i] = pow(numbers[i+1], 1/numbers[i]);
                    }
                }
                numbers.erase(numbers.begin() + (i+1));
                list_of_oprs.erase(list_of_oprs.begin() + i);
                break;
            }
        }
    }
}

bool Calculator::is_operator_valid(std::string op){
    for (int i = 0; i < number_of_operators ; ++i) {
        if(op == VALID_OPERATORS[i]){
            return true;
        }
    }
    return false;
}

bool Calculator::check_parenthesis(std::string mp) {
    int pare_counter = 0;
    for (int i = 0; i < mp.length(); i++) {
        if (mp[i] == '(') {
            pare_counter++;
        } else if (mp[i] == ')') {
            pare_counter--;
            if(pare_counter < 0){
                return false;
            }
        }
    }
    return pare_counter == 0;
}

std::string Calculator::handle_parentheses(std::string formula) {
    if(formula.empty()) return 0;
    bool exist_parent = true;
    while(exist_parent) {
        int open_par = -1;
        int par_length = 0;
        for (int i = 0; i < formula.length(); i++) {
            if (formula[i] == '(') {
                open_par = i;
            } else if (formula[i] == ')') {
                par_length = i-open_par;
                if(par_length == 1){
                    formula.replace(open_par, par_length+1, std::to_string(0));
                } else {
                    double parenth_value = calculate(formula.substr(open_par+1, par_length-1));
                    formula.replace(open_par, par_length+1, std::to_string(parenth_value));
                }
                numbers.clear();
                break;
            }
        }
        if(open_par == -1 && par_length == 0){
            exist_parent = false;
        }
    }
    return formula;
}

void Calculator::parse_math_problem(std::string formula) {
    while (0 != formula.length() && are_operators_valid){
        std::string::size_type p;
        double next_nr;
        try {
            next_nr = stod(formula, &p);
            formula = formula.substr(p);
        } catch(const std::invalid_argument){
            std::cout << "Formula has to start with a number!" << std::endl;
            next_nr = 0;
        }
        numbers.push_back(next_nr);

        formula = get_next_operator(formula);
    }

}

double Calculator::calculate(std::string formula) {
    parse_math_problem(formula);

    if(are_operators_valid){
        for (int i = 0; i < number_of_operators; ++i) {
            if(exists_div_by_zero){
                std::cout << "Formula contained division by zero." << std::endl;
                return 0;
            } else if(result_is_complex_nr){
                std::cout << "Result is complex number" << std::endl;
                return 0;
            }
            solve(VALID_OPERATORS[i]);
        }
        return numbers[0];
    } else {
        std::cout << "The problem contained one or more invalid operators." << std::endl;
        return 0;
    }
}
