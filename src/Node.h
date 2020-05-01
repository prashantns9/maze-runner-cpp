#ifndef _NODE_H
#define _NODE_H

#include<iostream>

using namespace std;

class Node{
private:
    string name;
    Node *attachedNodes[4];
    Node *snakeOrLadderNode;
public:
    Node(){
        for(int i=0;i<4;i++)
            attachedNodes[i]=NULL;
        snakeOrLadderNode = NULL;

    }
    Node(string nName){
        name = nName;
    }
    void setNodeName(string nName){
        name = nName;
    }

    void attachNewNodes(Node *n, int dir){
        if((dir>-1)&&(dir<4)){
            attachedNodes[dir] = n;
        }
        else{
            snakeOrLadderNode = n;
        }
    }
    string getNodeName(){
        return name;
    }

    Node *getAttachedNodes(int dir){
        if((dir>-1)&&(dir<4)){
            return attachedNodes[dir];
        }
    }
    Node *getsnakeOrLadderNode(){
        return snakeOrLadderNode;
    }
};


#endif
