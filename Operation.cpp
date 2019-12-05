/******************************************************************************
 * Created by Joshua Jones on 12/5/2019.
 * Copyright (c) 2019 
 * All rights reserved.
 ******************************************************************************/

#include "Operation.hpp"

int Operation::sum(){
    return params[0]+params[1];
}

int Operation::mul(){
    return params[0]*params[1];
}

int Operation::compare(int a, int b){
    if(a>b){
        return 1;
    } else if(a==b){
        return 0;
    } else {
        return -1;
    }
}

void Operation::jump(bool jump){
    if(jump) {
        *index = params[1];
        numParams = 0;
    }
}

Operation::Operation(vector<int> *memory, int *curIndex) {
    this->memory = memory;
    this->index = curIndex;
}

void Operation::initOperation(int opCode) {
    this->rawOpCode = opCode;
    this->curOpCode = rawOpCode%100;
    setModes();
    setParams();
}

void Operation::setModes() {
    numParams = 1;
    switch(curOpCode){
        case 1:
        case 2:
        case 7:
        case 8:
            modes.push_back(static_cast<ParamMode>(rawOpCode / 10000));
            numParams++;
        case 5:
        case 6:
            numParams+=2;
            rawOpCode/=100;
            for (int i = 0; i < 2; ++i) {
                modes.push_back(static_cast<ParamMode>(rawOpCode % 10));
                rawOpCode/=10;
            }
            break;
        case 3:
            numParams++;
            modes.push_back(IMMEDIATE);
            break;
        case 4:
            numParams++;
            modes.push_back(static_cast<ParamMode>((rawOpCode/100 > 0)));
            break;
    }
}

void Operation::setParams() {
    int shift = 0;
    switch (curOpCode){
        case 1:
        case 2:
        case 7:
        case 8:
            dest = memory[0][*index+3];
            shift++;
        case 5:
        case 6:
            for (int i = 0; i < 2; ++i) {
                params.push_back(memory[0][*index+i+1]);
                if(modes[i+shift] == POSITION){
                    params[i] = memory[0][params[i]];
                }
            }
            break;
        case 3:
        case 4:
            dest = memory[0][*index+1];
            if(modes[0] == POSITION){
                dest = memory[0][dest];
            }
    }
}

void Operation::performOp(int input) {
    switch (curOpCode){
        //addition
        case 1: memory[0][dest] = sum();
            break;
            //multiplication
        case 2: memory[0][dest] = mul();
            break;
        case 3: memory[0][dest] = input;
            break;
        case 4: cout<<"OUTPUT: "<<dest<<endl;
            break;
        case 5:
            jump(compare(params[0], 0));//jnz
            break;
        case 6:
            jump(!compare(params[0], 0));//jz
            break;
        case 7:memory[0][dest] = compare(params[0], params[1]) == -1;//jl
            break;
        case 8:memory[0][dest] = compare(params[0], params[1]) == 0;//jg
            break;
        default:
            cout<<"Something went wrong!!!"<<endl;
    }
    *index+=numParams;
    clearOpData();
}

void Operation::clearOpData() {
    modes.clear();
    params.clear();
}