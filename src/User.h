#ifndef _USER_H
#define _USER_H

#include<iostream>

#include "Node.h"
using namespace std;

class User{
private:
    int id, pathSize;
    string name;
    Node *userLocation, *path[50];
public:
    User(){
        pathSize = 0;
    }
    void createUser(int i){
        id=i+1;
        cout<<"\nEnter name of the Player #"<<id<<": ";
        cin>>name;
    }
    string getUserName(){
        return name;
    }
    void moveUser(Node *n){
        userLocation = n;
        path[pathSize] = n;
        pathSize++;
    }
    Node *getUserLocation(){
        return userLocation;
    }
    void showpath(){
        cout<<"\nYou took "<<pathSize-1<<" steps.";
        cout<<"\nThe node you path are ";

        for(int i=0;i<pathSize;i++){
            cout<<" "<<path[i]->getNodeName();
        }
    }
};


#endif
