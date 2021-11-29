#ifndef ICL_H
#define ICL_H

#include <vector>
#include <queue>
#include <stack>
#include <iostream>
#include <cstdlib>
#include <ctime>
#include "node.h"
using namespace std;



class ImageComponent {//this class will create and solve image component of a maze using both BFS and DFS
public:
    ImageComponent() = default; // a default constructor; we do not need to define it explicitly
    void getMaze();//Get maze dimensions and density and print the maze
    void labelMazeDFS();//Label the maze image components
    void labelBlockDFS(int i, int j);//Label specific blocks of image components using DFS
    void labelMazeBFS();//label maze image components
    void labelBlockBFS(int i, int j);//label maze image components using BFS
    void printMaze();
    ~ImageComponent(){//deconstructor to prevent memory leak
    	delete []myvec;
}
private:
    int size;
    int testInt;
    int iNum = 2;
    double density, rnd;
    vector<int> *myvec;//Pointer to dynamically allocated vector array to hold maze image
    int num[30][30];//Array that holds order of ivars set by dfs or bfs
};

void ImageComponent::getMaze() {//Prompt user for size and density of maze

	cout << "Enter size of maze: " << endl;
	cin >> size;
	cout << "Enter maze density: " << endl;
	cin >> density;
	for(int i = 0; i <= size+1; i++) {
		for(int j = 0; j <= size+1; j++){
			num[i][j] = 0;
		}
	}
	myvec = new vector<int>[size+2];//This is an array of vectors where our pixel values will be stored
	for(int i = 0; i <= size + 1; i++){
		for(int j = 0; j <= size + 1; j++){//Double for loop loops through vector array twice
			rnd = rand() % 100 + 1;//generate number between 1 and 100
			if(i == 0 || j == 0 || i == size + 1 || j == size + 1)
				myvec[i].push_back(0);
			else if(rnd >= density*100)//create 0's and 1's in vector proportial to density
				myvec[i].push_back(0);
			else
				myvec[i].push_back(1);
		}
    }
}

void ImageComponent::printMaze(){
	for(int i = 0; i <= size+1; i++){//Print the created maze
		for(int j = 0; j <= size+1; j++)
			cout << "(" <<myvec[i][j] << "," << num[i][j] << ") ";
		cout << endl;
	}
	cout << endl;
}

void ImageComponent::labelMazeDFS() {	
	for(int i = 1; i <= size; i++) {
		for(int j = 1; j <= size; j++){
			if(myvec[i][j] == 1){//if we encounter a non labeled foregroud pixel
				labelBlockDFS(i,j);
			}
		}
	}
}
void ImageComponent::labelMazeBFS() {	
	for(int i = 1; i <= size; i++) {
		for(int j = 1; j <= size; j++){
			if(myvec[i][j] == 1){//if we encounter a non labeled foregroud pixel
				labelBlockBFS(i,j);
			}
		}
	}
}

void ImageComponent::labelBlockDFS(int k, int l){//Depth first search
	stack<node> mystack;//create stack of nodes
	int found = 1;
	node temp(k,l);//new node to put in stack
	mystack.push(temp);
	myvec[k][l] = iNum;//Starting location of block set to Image Block Component Numberx
	num[k][l] = found;
	found++;	
	while(true){//While loop exits when stack is empty
		if(myvec[k][l+1] == 1){//check right
			myvec[k][l+1] = iNum;//Set Image
			num[k][l+1] = found;//Label order
			found++;
			l++;//Move to new location
			node temp1(k,l);
			mystack.push(temp1);//push new location onto stack
		}else if(myvec[k + 1][l] == 1){//check down
			myvec[k+1][l] = iNum;//Set Image
			num[k+1][l] = found;//Label order
			found++;
			k++;//Move
			node temp1(k,l);
			mystack.push(temp1);//push new location onto stack
		}else if(myvec[k][l-1] == 1){//check left
			myvec[k][l-1] = iNum;//Set image
			num[k][l-1] = found;//Label order
			found++;
			l--;//Move
			node temp1(k,l);//push new location onto stack
			mystack.push(temp1);
		}else if(myvec[k - 1][l] == 1){//check up
			myvec[k-1][l] = iNum;//Set image
			num[k-1][l] = found;//Label order
			found++;
			k--;//Move
			node temp1(k,l);
			mystack.push(temp1);//push new location onto stack
		}else{
			mystack.pop();//backtrack to previous location
			if(mystack.empty() == 1)//Loop break condition
				break;
			k = mystack.top().x;//reset coordinates
			l = mystack.top().y;
		}
	}
	iNum++;//Increment Image number for next Image Block 
}
void ImageComponent::labelBlockBFS(int k, int l){//Breadth first search
	queue<node> myqueue;//create queue of nodes
	int found = 1;//Keeps track of image labling order
	int distance = 0;//distance from start point
	node temp(k,l,distance);//new node to put in queue
	myqueue.push(temp);//push starting position into queue
	myvec[k][l] = iNum;//Starting location of block set to Image Block Component Number
	num[k][l] = found;
	found++;	
	while(true){//While loop exits when stack is empty
		if(myvec[k][l+1] == 1){//check right
			myvec[k][l+1] = iNum;//Set Image
			num[k][l+1] = found;//Label order
			found++;
			node temp1(k,l+1,distance);
			myqueue.push(temp1);//push new location onto queue
		}else if(myvec[k + 1][l] == 1){//check down
			myvec[k+1][l] = iNum;//Set Image
			num[k+1][l] = found;//Label order
			found++;
			node temp1(k+1,l,distance);
			myqueue.push(temp1);//push new location onto queue
		}else if(myvec[k][l-1] == 1){//check left
			myvec[k][l-1] = iNum;//Set image
			num[k][l-1] = found;//Label order
			found++;
			node temp1(k,l-1,distance);//push new location onto queue
			myqueue.push(temp1);
		}else if(myvec[k - 1][l] == 1){//check up
			myvec[k-1][l] = iNum;//Set image
			num[k-1][l] = found;//Label order
			found++;
			node temp1(k-1,l,distance);
			myqueue.push(temp1);//push new location onto queue
		}else{
			myqueue.pop();//go to next point in queue
			if(myqueue.empty() == 1)//Loop break condition
				break;
			k = myqueue.front().x;//reset coordinates
			l = myqueue.front().y;
			distance++;
		}
	}
	iNum++;//Increment Image number for next Image Block 
}
#endif
