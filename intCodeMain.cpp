/******************************************************************************
 * Created by Joshua Jones on 12/5/2019.
 * Copyright (c) 2019 
 * All rights reserved.
 ******************************************************************************/
#include <fstream>
#include "IntCodeComputer.hpp"

using std::ifstream;

int main(){
    ifstream inReader("input.txt");
    string data;
    inReader>>data;
    IntCodeComputer computer(data);
    computer.run();
    return 0;
}