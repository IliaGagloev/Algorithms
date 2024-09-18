#include"sort_station.h"
#include<stack>

void shuntingYard(const std::vector<Token> &expr, std::vector<Token> &outQueue){
    std::stack<Token> stack;
    auto fromStackToQueue = [&]() {outQueue.push_back(stack.top()); stack.pop();};

    for(const auto& token : expr){
        Token::Type type = token.getType();
        switch(token.getType()){
            case Token::INT_LITERAL:
            case Token::FLOAT_LITERAL:
                outQueue.push_back(token);
                break;
            case Token::L_PARANTHESIS:
            case Token::FUNCTION:
                stack.push(token);
                break;
            case Token::OPERATOR:
                if(!stack.empty()){
                    while(stack.top().getType() == Token::OPERATOR && ((stack.top().getPrecendance() > token.getPrecendance()) 
                    || (stack.top().getPrecendance()  == token.getPrecendance() && stack.top().getPrecendance() == Token::LEFT))){
                        fromStackToQueue();
                        if(stack.empty())
                            break;
                    }
                }
                stack.push(token);
                break;
            case Token::R_PARANTHESIS:
                if(stack.empty())
                    throw "MAAAAAN";
                while(stack.top().getType() != Token::L_PARANTHESIS){
                    fromStackToQueue();
                    if(stack.empty())
                        throw "Non balanced paranthesis";
                }
                stack.pop();
                
                if(!stack.empty() && stack.top().getType() == Token::FUNCTION)
                    fromStackToQueue();
                break;
            case Token::SEPARATOR:
                if(stack.empty())
                    throw "BROOOOO ITS NOT GOOD. INDIAN PEOPLE DO NOT LIKE THIS";

                while(stack.top().getType() != Token::L_PARANTHESIS)
                {
                    fromStackToQueue();

                    if(stack.empty())
                        throw "BROOOOO ITS NOT GOOD. INDIAN PEOPLE DO NOT LIKE THIS";
                }
                break;
        }
    }
    while(!stack.empty()){
        if(stack.top().getType() == Token::L_PARANTHESIS){
            throw "BROOOOO ITS NOT GOOD. INDIAN PEOPLE DO NOT LIKE THIS";
        }
        else
            fromStackToQueue();
    }
}
