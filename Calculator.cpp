//
// Created by bekor on 9/25/17.
//

#include "Calculator.h"

std::vector<std::string> list_of_oprs;

double Calculator::evaluate(const char * math_problem) {
    char *p;
    std::cout << std::strtod(math_problem, &p) << std::endl;


    std::string my_char = get_next_operator(p);
    std::cout << my_char << std::endl;
    std::cout << "boop" << std:: endl;
//    if(my_char.length() != 0){
//        return evaluate(my_char);
//    }
//    return 0;
}

std::string Calculator::get_next_operator(char *part){
    std::string next_opr = "";
    for (int i = 0; i < sizeof(part) -1 ; ++i) {
        if(!isspace(part[i]) && !isdigit(part[i])){
            if(next_opr != "" && std::string(1,part[i]) == "-"){
                list_of_oprs.push_back(next_opr);
                return std::string(part, i, sizeof(part));
            }
            next_opr += part[i];
        } else if(isdigit(part[i])){
            list_of_oprs.push_back(next_opr);
            return std::string(part, i, sizeof(part));
        }
    }
}