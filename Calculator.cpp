//
// Created by bekor on 9/25/17.
//

#include "Calculator.h"
#include <cstring>

std::vector<std::string> list_of_oprs;
std::vector<double> numbers;

double Calculator::evaluate(const char * received_problem) {
    char *math_problem = received_problem;
    char *p;
    std::cout << std::strtod(math_problem, &p) << std::endl;

    std::string my_char = get_next_operator(p);
    std::cout << my_char << std::endl;
 
    for(const auto& e: list_of_oprs){
        std::cout << e << std::endl;
    }

    while (0 != strlen(math_problem)){
        char *p;
        int next_nr = strtod(math_problem, &p);
        math_problem = &p;
        numbers.push_back(next_nr);


    }
//    if(my_char.length() != 0){
//        return evaluate(my_char);
//    }
//    return 0;
}

std::string Calculator::get_next_operator(char *part){std::string next_opr = ""; for (int i = 0; i < sizeof(part) -1 ; ++i) {if(!isspace(part[i]) && !isdigit(part[i])){
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
