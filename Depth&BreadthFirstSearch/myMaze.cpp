#include <vector>
#include <stack>
#include <iostream>
#include <cstdlib>
#include <ctime>
#include "ICL.h"

using namespace std;

int size = 15;

double density = .33;



double rnd = 0;


int main(){
	//Test DFS Image Component Labling//
	srand(time(0));
	ImageComponent myImage,myImage2;//Declare Class
	myImage.getMaze();//Prompt user for maze density and size, and create the requested maze 
	cout << "Unlabled maze:" << endl << endl;
	myImage.printMaze();//Print created maze
	myImage.labelMazeDFS();//Lable the Image Components using DFS
	cout << "Labled maze:" << endl << endl;
	myImage.printMaze();//Print the newly labled maze
	//Test BFS ImageComponent Labling//
	myImage2.getMaze();//Prompt user for maze density and size, and create the requested maze 
	myImage2.printMaze();//Print the created maze
	cout << "Unlabled maze:" << endl << endl;
	myImage2.labelMazeBFS();//Lable the Image Components using BFS
	cout << "Labled maze:" << endl << endl;
	myImage2.printMaze();//Print newly labled maze
	
	return 0;	
}
