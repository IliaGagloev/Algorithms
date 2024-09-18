#include"token.h"

Token::Token(std::string token, Type type, OperatorAssos asc):type(type){
    opAsc = asc;
    str = token;
}

int Token::getPrecendance() const{
    static std::map<std::string, int> op_leftassociative = {
        {"+", 2},
        {"-", 2},
        {"/", 3},
        {"*", 3},
        {"^", 5}
    };
    static std::map<std::string, int> op_rightassociative = {
        {"-", 4}
    };
    switch(opAsc){
        case LEFT:
            if(op_leftassociative.find(str) != op_leftassociative.end()) return op_leftassociative[str];
            break;
        case RIGHT:
            if(op_rightassociative.find(str) != op_rightassociative.end()) return op_rightassociative[str];
            break;
        case NONE:
            std::cout << "GO AWAY";
            break;
    }
    return 0;
}

