#include<iostream>


#include "System.h"
using namespace std;


int main(){

	System s;
    int gameConfigured = s.configureGame();
	//s.displayGraph();



    if(gameConfigured)
        s.beginTurns();

	return 1;
}
