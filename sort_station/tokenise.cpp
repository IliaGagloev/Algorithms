#include "tokenise.h"
#include<iostream>
#include<map>
#include<string>


void tokenize(const std::string &expr, std::vector<Token> &tokens){
    State state = State::S0;
    std::string validOperators = "+-*^/";
    bool isDigit, isLetter, isOp, isParanth, isPoint, isSep, isLParanth, isRParanth;

    std::string buffer;
    Token::Type bufferTokenType = Token::INT_LITERAL;

    for(auto& s: expr){
        isDigit = std::isdigit(s);
        isLetter = std::isalpha(s);
        isLParanth = s == '(';
        isRParanth = s == ')';
        isParanth = isLParanth || isRParanth;
        isPoint = s == '.';
        isSep = s == '.';
        isOp = validOperators.find(s) != validOperators.npos;
        if(!(isDigit || isLetter || isParanth || isPoint || isSep || isOp))
            throw "Unknown symbol";
        
        switch(state){
            case State::S0:
                if(isOp || isParanth)
                    state = State::S1;
                else if(isDigit)
                    state = State::S2;
                else if(isLetter)
                    state = State::S4;
                else if(isPoint || isSep)
                    throw "Unexpected symbol";
                break;
            case State::S1:
                if(isDigit)
                    state = State::S2;
                else if(isLetter)
                    state = State::S4;
                else if(isPoint || isSep)
                    throw "Unexpected symbol";
                break;
            case State::S2:
                bufferTokenType = Token::INT_LITERAL;
                if(isPoint)
                    state = State::S3;
                else if(isParanth || isOp || isSep)
                    state = State::S5;
                else if(isLetter)
                    throw "Unexpected symbol";
                break;
            case State::S3:
                bufferTokenType = Token::FLOAT_LITERAL;
                if(isParanth || isOp || isSep)
                    state = State::S5;
                if(isPoint)
                    throw "Unexpected symbol";
                break;
            case State::S4:
                bufferTokenType = Token::FUNCTION;
                if(isLParanth)
                    state = State::S5;
                else if(isOp || isParanth || isSep)
                    throw "Unexpected symbol";
                break;
            case State::S5:
                if(isParanth || isOp)
                    state = State::S1;
                else if(isDigit)
                    state = State::S2;
                else if(isLetter)
                    state = State::S4;
                else if(isPoint || isSep)
                    throw "Unexpected symbol";
                break;
            default:
                break;
        }
        auto tokenize_Op_Paranth_Sep = [&]()
        {
            if(isOp){
                if(tokens.size() == 0 || tokens[tokens.size() - 1].getType() == Token::L_PARANTHESIS)
                    tokens.push_back({std::string{s}, Token::OPERATOR, Token::RIGHT});
                else    
                    tokens.push_back({std::string{s}, Token::OPERATOR, Token::LEFT});
            }else if(isParanth){
                tokens.push_back({std::string{s}, isRParanth ?  Token::R_PARANTHESIS : Token::L_PARANTHESIS});
            }else if(isSep){
                tokens.push_back({std::string{s},Token::SEPARATOR});
            }
        };
        switch(state){
            case S1:
                tokenize_Op_Paranth_Sep();
                break;
            case S2: case S3: case S4:
                buffer.push_back(s);
                break;
            case S5:
                
                tokens.push_back({buffer, bufferTokenType});
                buffer.clear();
                tokenize_Op_Paranth_Sep();
                break;
            default:
                break;
        }
    }
    if(!buffer.empty())
        tokens.push_back({buffer, bufferTokenType});
}