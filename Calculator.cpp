//
// Created by bekor on 9/25/17.
//

#include "Calculator.h"

Calculator::Calculator(){
    number_of_operators = sizeof(VALID_OPERATORS)/sizeof(VALID_OPERATORS[0]);
    are_operators_valid = true;
    parenthesis_are_valid = true;
}

double Calculator::evaluate(std::string formula) {
    formula.erase(std::remove_if(begin(formula), end(formula), isspace), formula.end());

    check_parenthesis(formula); // make it return bool and assign here.
    if(!parenthesis_are_valid){
        std::cout << "Invalid parenthesis" << std::endl;
        return 0;
    }

    formula = handle_parentheses(formula);

    return calculate(formula);

    // TODO make a calculate function to avoid pointless re-checking.
    /*
    for(const auto& e: list_of_oprs){
        std::cout << "operator(s): " << e << std::endl;
    }
    for(const auto& e: numbers){
        std::cout << "numbers: " << e << std::endl;
    }
    */
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
                    numbers[i] = pow(numbers[i+1], 1/numbers[i]);
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

void Calculator::check_parenthesis(std::string mp) {
    int pare_counter = 0;
    for (int i = 0; i < mp.length(); i++) {
        if (mp[i] == '(') {
            pare_counter++;
        } else if (mp[i] == ')') {
            pare_counter--;
            if(pare_counter < 0) parenthesis_are_valid = false;
        }
    }
    if(pare_counter == 0) parenthesis_are_valid = true;
    else parenthesis_are_valid = false;
}

std::string Calculator::handle_parentheses(std::string formula) {
    bool exist_parent = true;
    while(exist_parent) {
        int open_par = -1;
        int par_length = 0;
        for (int i = 0; i < formula.length(); i++) {
            if (formula[i] == '(') {
                open_par = i;
            } else if (formula[i] == ')') {
                par_length = i-open_par;
                double parenth_value = calculate(formula.substr(open_par+1, par_length-1));
                formula.replace(open_par, par_length+1, std::to_string(parenth_value));
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
        double next_nr = stod(formula, &p);
        formula = formula.substr(p);
        numbers.push_back(next_nr);

        formula = get_next_operator(formula);
    }

}

double Calculator::calculate(std::string formula) {
    parse_math_problem(formula);

    if(are_operators_valid){
        for (int i = 0; i < number_of_operators; ++i) {
            solve(VALID_OPERATORS[i]);
        }
        return numbers[0];
    } else {
        std::cout << "The problem contained one or more invalid operators." << std::endl;
        return 0;
    }
}
