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

void setCurrentOp(int rawOp, int &currentOp, int &op1Mode, int &op2Mode, int &op3Mode) {
    string settings = to_string(rawOp);
    int index = settings.length()-1;
    string strOp = "";
    strOp+=settings[index];
    if(settings.length()>2){
        strOp = settings[settings.length()-2] + strOp;
    }

    currentOp = stoi(strOp);

    if(currentOp < 3) {
        op3Mode = settings.length() == 5;
        op2Mode = (settings.length() > 3) && (settings[settings.length()-4] == '1');
        op1Mode = (settings.length() > 2) && (settings[settings.length()-3] == '1');
    } else if(currentOp == 3){
        op3Mode = 1;
        op2Mode = op1Mode = 0;
    } else {
        op3Mode = settings.length() == 3;
        op2Mode = op1Mode = 0;
    }
}

int main() {
    ifstream inReader("input.txt");
    int num, result = 0;
    vector<int> array;
    vector<int> arr;
    while(!inReader.eof()){
        string tempStr;
        getline(inReader, tempStr, ',');
        arr.push_back(stoi(tempStr));
    }

    int curIndex = 0;
    int op[3];

    for(int k = 0; k<arr.size(); k++){
        array.push_back(arr[k]);
    }



    int currentOp;
    int opMode[3];

    setCurrentOp(array[curIndex], currentOp, opMode[0], opMode[1], opMode[2]);

    while(array[curIndex] !=99){
        if(currentOp >=3){
            op[2] = array[curIndex+1];
            if(!opMode[2]){
                op[2] = array[op[2]];
            }
        } else{
            for (int i = 0; i < 2; ++i) {
                op[i] = array[curIndex+i+1];
                if(!opMode[i]){
                    op[i] = array[op[i]];
                }
            }
            op[2] = array[curIndex+2+1];
        }

        string temp;

        switch (currentOp){
            case 1: array[op[2]] = sum(op[0], op[1]);
//                cout<<array[op[2]]<<" = "<<op[0]<< " + "<<op[1]<<endl;
                curIndex+=4;
                break;
            case 2: array[op[2]] = mul(op[0], op[1]);
//                cout<<array[op[2]]<<" = "<<op[0]<< " * "<<op[1]<<endl;
                curIndex+=4;
                break;
            case 3: array[op[2]] = 1;
                curIndex+=2;
                break;
            case 4: cout<<"OUTPUT: "<<op[2]<<endl;
                curIndex+=2;
                break;
            default:
                cout<<"Something went wrong!!!"<<endl;
        }
        cout<<array[curIndex]<<endl;
        setCurrentOp(array[curIndex], currentOp, opMode[0], opMode[1], opMode[2]);
    }




    return 0;
}