#pragma once

#include"token.h"
#include<vector>

enum State
{
    S0,
    S1,
    S2,
    S3,
    S4,
    S5
};

void tokenize(const std::string &expt, std::vector<Token> &tokens);