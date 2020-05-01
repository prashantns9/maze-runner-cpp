#ifndef _SYSTEM_H
#define _SYSTEM_H

#include<iostream>
#include<fstream>
#include<time.h>
#include<string>
#include<sstream>
#include<stdlib.h>
#include "Node.h"
#include "User.h"
using namespace std;


class System{
    
    private:
        User users[10];
        Node *graph[50], *startNode, *endNode;
        int UserCount, graphSize, gameOver;

    public:
        System(){
            UserCount=0;
        }

		void displayGraph(){
			cout<<"\nNodes ";
			for(int i=0;i<(graphSize-1);i++){	
				
				cout<<"\n\n";
				cout<<"\nNode: "<<graph[i]->getNodeName();

				if(graph[i]->getAttachedNodes(0)!=NULL)
					cout<<"\nNorth: "<<graph[i]->getAttachedNodes(0)->getNodeName();
				if(graph[i]->getAttachedNodes(1)!=NULL)
					cout<<"\nEast: "<<graph[i]->getAttachedNodes(1)->getNodeName();
				if(graph[i]->getAttachedNodes(2)!=NULL)
					cout<<"\nSouth: "<<graph[i]->getAttachedNodes(2)->getNodeName();
				if(graph[i]->getAttachedNodes(3)!=NULL)			
					cout<<"\nWest: "<<graph[i]->getAttachedNodes(3)->getNodeName();
				if(graph[i]->getsnakeOrLadderNode()!=NULL)
					cout<<"\nSn:  "<<graph[i]->getsnakeOrLadderNode()->getNodeName();
			}
		}
        
        int createGraph(){
            fstream fileStream;
            int left,right;
            string startName, endName;
            
            fileStream.open("../examples/maze0/CONFIG.TXT");
            if(!fileStream.is_open()){
                cout<<"\nConfiguration File not found";
                return 0;
            }
            string fileText((istreambuf_iterator<char>(fileStream) ),(istreambuf_iterator<char>()));;
            fileStream.close();
            string count;
            int line = fileText.find('\n',0);
            count = fileText.substr(0,line);
            stringstream ss(count);
            ss>>graphSize;
         
         	left = line + 1;
         	right = fileText.find('\n', left);
         	
         	startName = fileText.substr(left, right-left);
         	//startName = startName.substr(0,startName.size()-1);//comment this line for no line offset
         
         	left = right + 1;
         	right = fileText.find('\n',left);
         	
         	endName = fileText.substr(left, right - left);
         	//endName = endName.substr(0, endName.size()-1); //comment this line for no line offset
         	
         	
         	line = right;
            line++;
            left = line;
            string nodename, north,east,south,west,snakeLadder;
            for(int i=0;i<graphSize;i++){

                graph[i] = new Node();					
                right = fileText.find(" ",left);

                nodename = fileText.substr(left, right-left);
                graph[i]->setNodeName(nodename);
                
                if(graph[i]->getNodeName() == startName){
                	startNode = graph[i];
                }
                if(graph[i]->getNodeName() == endName){
                	endNode = graph[i];
                }

                left = fileText.find("\n", left) + 1;


            }
            left = fileText.find(" ",line);
            left++;
            for(int i=0;i<(graphSize-1);i++){
                right = fileText.find(" ",left);
                north = fileText.substr(left, right-left);
                if(north!="*"){

                    for(int j=0;j<graphSize;j++){
                        if(graph[j]->getNodeName()==north){
                            graph[i]->attachNewNodes(graph[j],0);
                            break;
                        }
                    }
                }
                left = right + 1;
                right = fileText.find(" ",left);
                east = fileText.substr(left,right-left);
                if(east!="*"){

                    for(int j=0;j<graphSize;j++){
                        if(graph[j]->getNodeName()==east){
                            graph[i]->attachNewNodes(graph[j],1);
                            break;
                        }
                    }
                }
                left = right + 1;
                right = fileText.find(" ",left);
                south = fileText.substr(left,right-left);
                if(south!="*"){
                    for(int j=0;j<graphSize;j++){
                        if(graph[j]->getNodeName()==south){
                            graph[i]->attachNewNodes(graph[j],2);
                            break;
                        }
                    }
                }
                left = right + 1;
                right = fileText.find(" ",left);
                west = fileText.substr(left,right-left);
                if(west!="*"){

                    for(int j=0;j<graphSize;j++){
                        if(graph[j]->getNodeName()==west){
                            graph[i]->attachNewNodes(graph[j],3);
                            break;
                        }
                    }
                }
                left = right + 1;
                right = fileText.find('\n',left);
                snakeLadder = fileText.substr(left,right-left);
                //snakeLadder = snakeLadder.substr(0, snakeLadder.size()-1); // comment this line for no line offset
                

                if(snakeLadder!="*"){

                    for(int j=0;j<graphSize;j++){
                        if(graph[j]->getNodeName()==snakeLadder){

                            graph[i]->attachNewNodes(graph[j],4);
                            break;
                        }
                    }
                }

                left = fileText.find(" ",right) + 1;
                
            }
            return 1;
        }

        void setUserCount(){
            cout<<"\nEnter the number of Players? ";
            cin>>UserCount;
            if(UserCount<2){
                cout<<"\nTwo players are required for this game. Try again.";
                setUserCount();
            }

        }

        void setUsers(){
            for(int i=0;i<UserCount;i++){
                users[i].createUser(i);
            }
        }
        int configureGame(){
            if(!createGraph()){
                return 0;
            }
            setUserCount();
            setUsers();
            return 1;
        }
        int hasUserWon(User p){
            if(p.getUserLocation() == endNode){

                cout<<"\nCongratulations! "<<p.getUserName()<<" is the winner. You have reached the destination point.\n";
                p.showpath();
                cout<<"\n";           
                gameOver = 1;
                return 1;
            }
            else{
                return 0;
            }
        }
        void beginTurns(){
            gameOver = 0;
            
            for(int i=0;i<UserCount;i++){
                users[i].moveUser(startNode);
            }
            while(gameOver == 0){
                for(int j=0;j<UserCount&&gameOver==0;j++){

                    int diceValue, avail = 0;
                    srand (time(NULL));
                    string uName = users[j].getUserName();
                    char option;
                    Node *t, *currLoc;
                    cout<<"\n\t======================================";
                    cout<<"\n\t\t"<<users[j].getUserName()<<"'s turn.\t\t";
                    cout<<"\n\t======================================";
                    cout<<"\n"<<users[j].getUserName()<<"'s turn to throw the dice. Just hit enter.";
                    cin.ignore();
                    cin.get();
                    diceValue = rand() % 6 + 1;
                    cout<<"\n"<<users[j].getUserName()<<"'s dice throw is "<<diceValue;
                    cout<<"\n"<<users[j].getUserName()<<" can move "<<diceValue<<" nodes.";
        
                    for(int i=0;i<diceValue;i++){
                        currLoc = users[j].getUserLocation();
                        cout<<"\n"<<uName<<" is currently at node "<<currLoc->getNodeName()<<" of the maze game";
                        while(currLoc->getsnakeOrLadderNode() != NULL){
                            t = currLoc->getsnakeOrLadderNode();
        
                            if(t!=NULL){
                                currLoc = t;
                                users[j].moveUser(currLoc);
        
                                cout<<", and you have been taken to "<<currLoc->getNodeName()<<". Now ";
                            }
                        }
        
                        cout<<"\nYou can go";
                        avail=0;
                        if(currLoc->getAttachedNodes(0)!=NULL){
                            cout<<" North ";
                            avail=1;
                        }
                        if(currLoc->getAttachedNodes(1)!=NULL){
                            if(avail == 1)
                                cout<<" or";
                            cout<<" East";
                            avail = 1;
                        }
                        if(currLoc->getAttachedNodes(2)!=NULL){
                            if(avail == 1)
                                cout<<" or";
                            cout<<" South ";
                            avail = 1;
                        }
                        if(currLoc->getAttachedNodes(3)!=NULL){
                            if(avail == 1)
                                cout<<" or";
                            cout<<" West.";
                            avail = 1;
                        }
        
                        cout<<"\nWhat is your choice? ";
                        cin>>option;
                        switch(option){
                            case 'N':
        
                                if(currLoc->getAttachedNodes(0)==NULL){
                                    cout<<"\nInvalid Option";
                                    i--;
                                    break;
                                }
                                t = currLoc->getAttachedNodes(0);
                                users[j].moveUser(t);
        
                                if(hasUserWon(users[j]))
                                    return;
                                break;
        
                            case 'E':
        
                                if(currLoc->getAttachedNodes(1)==NULL){
                                    cout<<"\nInvalid Option";
                                    i--;
                                    break;
                                }
                                t = currLoc->getAttachedNodes(1);
                                users[j].moveUser(t);
                                if(hasUserWon(users[j]))
                                    return;
                                break;
        
                            case 'S':
                                if(currLoc->getAttachedNodes(2)==NULL){
                                    cout<<"\nInvalid Option";
                                    i--;
                                    break;
                                }
                                t = currLoc->getAttachedNodes(2);
                                users[j].moveUser(t);
                                if(hasUserWon(users[j]))
                                    return;
                                break;
        
                            case 'W':
                                if(currLoc->getAttachedNodes(3)==NULL){
                                    cout<<"\nInvalid Option";
                                    i--;
                                    break;
                                }
                                t = currLoc->getAttachedNodes(3);
                                users[j].moveUser(t);
                                if(hasUserWon(users[j]))
                                    return;
                                break;
        
                            default:
                                cout<<"\nInvalid Option.";
                                i--;
                                break;
                        }
                    }

                }
            }
        }



        
    };
    

#endif
