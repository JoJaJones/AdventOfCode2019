/******************************************************************************
 * Created by Joshua Jones on 12/4/2019.
 * Copyright (c) 2019 
 * All rights reserved.
 ******************************************************************************/

#include <iostream>
#include <fstream>
#include <vector>

using namespace std;

int sum(int a, int b){
    return a + b;
}

int mul(int a, int b){
    return a*b;
}

int compare(int a, int b){
    if(a>b){
        return 1;
    } else if( a==b){
        return 0;
    } else {
        return -1;
    }
}

void jump(int &index, int target, int jumpLength, bool jump){
    if(jump){
        index = target;
    } else {
        index+=jumpLength;
    }
}

void setCurrentOp(int rawOp, int &currentOp, int &op1Mode, int &op2Mode, int &op3Mode) {
    string settings = to_string(rawOp);
    int index = settings.length()-1;
    string strOp = "";
    strOp+=settings[index];
    if(settings.length()>2){
        strOp = settings[settings.length()-2] + strOp;
    }

    currentOp = stoi(strOp);

    switch (currentOp){
        case 1:
        case 2:
        case 5:
        case 6:
        case 7:
        case 8:
            op3Mode = settings.length() == 5;
            op2Mode = (settings.length() > 3) && (settings[settings.length()-4] == '1');
            op1Mode = (settings.length() > 2) && (settings[settings.length()-3] == '1');
            break;
        case 3:
            op3Mode = 1;
            op2Mode = op1Mode = 0;
            break;
        case 4:
            op3Mode = settings.length() == 3;
            op2Mode = op1Mode = 0;
            break;
    }
}

void setOps(int curOp, int *opMode, int *ops, vector<int> &array, int curIndex){
    switch (curOp){
        case 1:
        case 2:
        case 7:
        case 8:
            ops[2] = array[curIndex+2+1];
        case 5:
        case 6:
            for (int i = 0; i < 2; ++i) {
                ops[i] = array[curIndex+i+1];
                if(!opMode[i]){
                    ops[i] = array[ops[i]];
                }
            }
            break;
        case 3:
        case 4:
            ops[2] = array[curIndex+1];
            if(!opMode[2]){
                ops[2] = array[ops[2]];
            }
    }
}

int main() {
    ifstream inReader("input.txt");
    vector<int> array;
    while(!inReader.eof()){
        string tempStr;
        getline(inReader, tempStr, ',');
        array.push_back(stoi(tempStr));
    }

    int curIndex = 0;
    int op[3];
    int opMode[3];

    int currentOp;


    setCurrentOp(array[curIndex], currentOp, opMode[0], opMode[1], opMode[2]);

    while(array[curIndex] !=99){
        setOps(currentOp, opMode, op, array, curIndex);

        string temp;

        switch (currentOp){
            //addition
            case 1: array[op[2]] = sum(op[0], op[1]);
                curIndex+=4;
                break;
                //multiplication
            case 2: array[op[2]] = mul(op[0], op[1]);
                curIndex+=4;
                break;
            case 3: array[op[2]] = 5;
                curIndex+=2;
                break;
            case 4: cout<<"OUTPUT: "<<op[2]<<endl;
                curIndex+=2;
                break;
            case 5:
                jump(curIndex, op[1], 3, compare(op[0], 0));//jnz
                break;
            case 6:
                jump(curIndex, op[1], 3, !compare(op[0], 0));//jz
                break;
            case 7:array[op[2]] = compare(op[0], op[1]) == -1;//jl
                curIndex+=4;
                break;
            case 8:array[op[2]] = compare(op[0], op[1]) == 0;//jg
                curIndex+=4;
                break;
            default:
                cout<<"Something went wrong!!!"<<endl;
        }
        cout<<array[curIndex]<<" "<<curIndex<<endl;
        setCurrentOp(array[curIndex], currentOp, opMode[0], opMode[1], opMode[2]);
    }

    return 0;
}