#pragma once

#include"tokenise.h"
#include<string>
#include<iostream>
#include<map>
#include<vector>

void shuntingYard(const std::vector<Token> &expr, std::vector<Token> &outQueue);
