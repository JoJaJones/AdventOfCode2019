/******************************************************************************
 * Created by Joshua Jones on 12/5/2019.
 * Copyright (c) 2019 
 * All rights reserved.
 ******************************************************************************/

#ifndef ADVENTOFCODE_INTCODECOMPUTER_HPP
#define ADVENTOFCODE_INTCODECOMPUTER_HPP

#include <vector>
#include <string>
#include <sstream>
#include "Operation.hpp"


using std::vector;
using std::string;
using std::stringstream;
using std::cin;

class IntCodeComputer {
private:
    vector<int> memory;
    int curAddress;
    int input;
    Operation curOp;

public:
    IntCodeComputer(string data);
    int run();
    int setOperation();
};


#endif //ADVENTOFCODE_INTCODECOMPUTER_HPP
