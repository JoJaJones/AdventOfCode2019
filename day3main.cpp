/******************************************************************************
 * Created by Joshua Jones on 12/2/2019.
 * Copyright (c) 2019 
 * All rights reserved.
 ******************************************************************************/

#include <iostream>
#include <vector>
#include <fstream>
#include <cstdlib>
#include <map>

using namespace std;

bool inrange(int one, int two, int test){
    int minVal = min(one, two);
    int maxVal = max(one, two);

    return !(test < minVal || test > maxVal);

}

tuple<int, int, int> findOverlap(tuple<int,int,int> oneA, tuple<int,int,int> twoA, tuple<int,int,int> oneB, tuple<int,int,int> twoB){
    if(get<0>(oneA) == get<0>(twoA)){
        if(inrange(get<1>(oneA), get<1>(twoA), get<1>(oneB)) && inrange(get<0>(oneB), get<0>(twoB), get<0>(oneA))) {
            int steps = get<2>(oneA);
            steps+= (get<0>(oneA) - min(get<0>(oneB), get<0>(twoB)));
            steps+= get<2>(oneB) + (get<1>(oneB) - min(get<1>(oneA), get<1>(twoA)));
            return make_tuple(get<0>(oneA), get<1>(twoA), steps);
        } else {
            return make_tuple(-1,-1, -1);
        }
    } else if (get<1>(oneA) == get<1>(twoA)){\
        if(inrange(get<0>(oneA), get<0>(twoA), get<0>(oneB)) && inrange(get<1>(oneB), get<1>(twoB), get<1>(oneA))){
            int steps = get<2>(oneA);
            steps+= (get<1>(oneA) - min(get<1>(oneB), get<1>(twoB)));
            steps+= get<2>(oneB) + (get<0>(oneB) - min(get<0>(oneA), get<0>(twoA)));
            return make_tuple(get<1>(oneA), get<0>(oneB), steps);
        } else {
            return make_tuple(-1,-1, -1);
        }
    }
}

int getNum(int &curIndex, string &wire){
    int num = 0;
    while(curIndex <= wire.length() && wire[curIndex]!= ','){
        num*=10;
        num+= wire[curIndex]-'0';
        curIndex++;
    }

    return num;
}

int main(){
    ifstream inReader("input.txt");
    string wireOne, wireTwo;
    getline(inReader, wireOne);
    getline(inReader, wireTwo);


    vector<tuple <int, int,int>> schemOne;
    vector<tuple <int, int,int>> schemTwo;

    int minDistance = 400000;

    int index = 0;
    int x, y;
    string wire;
    vector<tuple<int,int, int>> *schem;

    for (int i = 0; i < 2; ++i) {
        if(i==0){
            wire = wireOne;
            schem = &schemOne;
        } else {
            wire = wireTwo;
            schem = &schemTwo;
        }
        index = 0;
        x = 0;
        y = 0;
        int numSteps = 0;
        while(index < wire.length()){
            int temp;
            switch(wire[index]){
                case 'U':temp = getNum(++index, wire);
                    y+=temp;
                    numSteps += temp;
                    break;
                case 'R': temp = getNum(++index, wire);
                    x+= temp;
                    numSteps += temp;
                    break;
                case 'D': temp = getNum(++index, wire);
                    y-=temp;
                    numSteps += temp;
                    break;
                case 'L': temp = getNum(++index, wire);
                    x-= temp;
                    numSteps += temp;
                    break;
            }

            schem->push_back(make_tuple(x, y, numSteps));

            cout<<index<<" "<<wire[index]<<endl;
            if(index < wire.length() && wire[index] == ','){
                index++;
            }
        }

    }


    for(int i = 0; i< schemOne.size()-1; i++){
        for (int j = 0; j < schemTwo.size()-1; ++j) {
            tuple<int, int, int> intersect = findOverlap(schemOne[i], schemOne[i+1], schemTwo[j], schemTwo[j+1]);
            if(get<0>(intersect) != -1){
                if(get<2>(intersect) < minDistance){
                    minDistance = get<2>(intersect);
                }
            }
        }
    }

    cout<<minDistance<<endl;

    return 0;
}