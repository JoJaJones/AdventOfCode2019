/******************************************************************************
 * Created by Joshua Jones on 12/5/2019.
 * Copyright (c) 2019 
 * All rights reserved.
 ******************************************************************************/

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
#include <queue>
#include <stack>

using namespace std;

struct Node {
    vector<Node*> nodes;
    Node *parent;
    int depth;
    string value;
};

struct Tree {
    int size;
    Node* root;
    int depth;
};

Node* addNode(Tree &t, string str, Node *cur){
    t.size++;
    Node *newNode = new Node;
    cur->nodes.push_back(newNode);
    newNode->value = str;
    newNode->depth = cur->depth+1;
    newNode->parent = cur;
    return newNode;
}

int main(){
    ifstream inReader("input.txt");
    string one, two, temp;
    map<string, set<string>> orbits;

    int num = 0;
    while(inReader>>temp){
        num++;
        one = "";
        two = "";
        for (int i = 0; i < 3 ; ++i) {
            one+= temp[i];
        }

        for (int j = 4; j < 7; ++j) {
            two+=temp[j];
        }
        if(orbits.count(one)){
            orbits[one].insert(two);
        } else {
            orbits[one] = set<string>();
            orbits[one].insert(two);
        }
    }

    Tree tree;
    tree.size = 0;
    tree.depth = 0;

    Node* cur = new Node;
    cur->depth = 0;
    cur->value = "COM";
    tree.root = cur;
    queue<Node*> orbitQue;
    orbitQue.push(cur);
    set<string> visitedSet;

    Node *san, *you;


    int count = 0;

    while(!orbitQue.empty()){
        cur = orbitQue.front();
        orbitQue.pop();
        cout<<cur->value<<endl;
        count+=cur->depth;
        if(orbits.count(cur->value)) {
            auto it = orbits[cur->value].begin();
            while (it != orbits[cur->value].end()) {
                Node *temp = addNode(tree, *it, cur);
                if(temp->value == "SAN"){
                    san = temp;
                } else if(temp->value == "YOU"){
                    you = temp;
                }
                orbitQue.push(temp);
                it++;
            }
        }
    }

    stack<Node*> youStack, sanStack;
    you = you->parent;
    while(you){
        youStack.push(you);
        you = you->parent;
    }

    san = san->parent;
    while(san){
        sanStack.push(san);
        san = san->parent;
    }

    while(sanStack.top() == youStack.top()){
        sanStack.pop();
        youStack.pop();
    }

    cout<<sanStack.size() + youStack.size()<<endl;
    return 0;
}