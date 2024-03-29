/******************************************************************************
 * Created by Joshua Jones on 12/2/2019.
 * Copyright (c) 2019 
 * All rights reserved.
 ******************************************************************************/

#include <iostream>
#include <vector>
#include <fstream>
#include <map>
#include <set>

using namespace std;

int main(){
    ifstream inReader("input.txt");
    int count = 0;
    for(int i = 193651; i<649729; i++){
        bool repeat = false;
        bool valid = true;
        string str = to_string(i);
        for(int j = 0; j <str.length()-1 && valid;j++){
            if(str[j] == str[j+1]){
                repeat = true;

            } else if(str[j] > str[j+1]){
                valid = false;
            }
        }
        if(valid && repeat){
            count++;
        }
    }
    cout<<count<<endl;
    return 0;
}