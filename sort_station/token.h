#pragma once


#include<string>
#include<iostream>
#include<map>

class Token{
public:
    enum Type
    {
        OPERATOR = 1,
        L_PARANTHESIS = 2, 
        R_PARANTHESIS = 3, 
        INT_LITERAL = 4, 
        FLOAT_LITERAL = 5, 
        FUNCTION = 6, 
        SEPARATOR = 7, 
    };
    //Assotiation
    enum OperatorAssos
    {
        NONE, // token is not an operator
        RIGHT, //right assotiation
        LEFT //left assotiation
    };

    Token(std::string token, Type type, OperatorAssos asc = NONE);

    int getPrecendance() const;

    //getFunctions
    const Type& getType() const{return type;}
    const OperatorAssos& getAsc() const{return opAsc;}
    const std::string& getStr() const{return str;}
private:
    Type type;
    OperatorAssos opAsc;
    std::string str;
};
