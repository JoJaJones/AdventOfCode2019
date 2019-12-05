/******************************************************************************
 * Created by Joshua Jones on 12/5/2019.
 * Copyright (c) 2019 
 * All rights reserved.
 ******************************************************************************/

#ifndef ADVENTOFCODE_OPERATION_HPP
#define ADVENTOFCODE_OPERATION_HPP

#include <vector>
#include <iostream>
#include <string>

using std::string;
using std::cout;
using std::endl;
using std::vector;
using std::cin;

enum ParamMode {POSITION, IMMEDIATE};

class Operation {
private:
    vector<int> params;
    vector<ParamMode> modes;
    int rawOpCode, curOpCode;
    int numParams;
    int dest;
    int *index;
    vector<int> *memory;
public:
    Operation(vector<int> *memory, int *curIndex);
    void initOperation(int opCode);
    void setParams();
    void setModes();
    void performOp(int input);
    void clearOpData();
    int getInput(string prompt);
    int mul(int a, int b);
    int sum(int a, int b);
    int compare(int a, int b);
    void jump(bool jump);

};


#endif //ADVENTOFCODE_OPERATION_HPP
