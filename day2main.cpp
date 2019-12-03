#include <iostream>
#include <fstream>
#include <vector>

using namespace std;

int sum(vector<int> &vec, int a, int b){
    return vec[a]+vec[b];
}

int mul(vector<int> &vec, int a, int b){
    return vec[a]*vec[b];
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
    int dest = 0, op1, op2;

    for(int k = 0; k<arr.size(); k++){
        array.push_back(arr[k]);
    }

    cout<< array[0];
    for(int i = 0; i<100 && array[0] != 19690720; i++){
        for(int j = 0; j<100 && array[0] != 19690720; j++){

            arr[1] = i;
            arr[2] = j;
            while(array[curIndex]!=99){
                op1 = array[curIndex + 1];
                op2 = array[curIndex + 2];
                dest = array[curIndex + 3];
                switch (array[curIndex]){
                    case 1: array[dest] = sum(array, op1, op2);
                        cout<<array[dest]<<" = "<<array[op1]<< " + "<<array[op2]<<endl;
                        break;
                    case 2: array[dest] = mul(array, op1, op2);
                        cout<<array[dest]<<" = "<<array[op1]<< " * "<<array[op2]<<endl;
                        break;
                    default:
                        cout<<"Something went wrong!!!"<<endl;
                }

                curIndex+=4;

                cout<<array[curIndex] << " "<<curIndex<<endl;
            }
            cout<<"|"<<arr[1]<<" "<<arr[2]<<" "<<array[0]<<"|"<<endl;
            if(array[0] == 19690720){
                break;
            }
            array.clear();
            for(int k = 0; k<arr.size(); k++){
                array.push_back(arr[k]);
            }
            curIndex = 0;
        }
    }



    return 0;
}