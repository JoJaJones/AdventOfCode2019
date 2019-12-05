/******************************************************************************
 * Created by Joshua Jones on 12/5/2019.
 * Copyright (c) 2019 
 * All rights reserved.
 ******************************************************************************/


#include "IntCodeComputer.hpp"
IntCodeComputer::IntCodeComputer(string data) : curOp(&memory, &curAddress) {
    stringstream ss(data);
    string temp;
    curAddress = 0;
    while(!ss.eof()){
        getline(ss, temp, ',');
        memory.push_back(stoi(temp));
    }
}

int IntCodeComputer::run() {
    input = getInput("Enter the input value: ");
    while(memory[curAddress] != 99) {
        setOperation();
        curOp.performOp(input);
    }
}

int IntCodeComputer::getInput(string prompt) {
    string result;
    cout<<prompt;
    getline(cin, result);
    return stoi(result);
}

int IntCodeComputer::setOperation() {
    curOp.initOperation(memory[curAddress]);
}