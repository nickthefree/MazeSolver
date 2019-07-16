#ifndef chainNode_
#define chainNode_

class node {//This is a simple node class to be utilized within queue or stack
	
public:
	int x, y, dist;
	node(int a, int b){
		x = a;
		y = b;
		dist = 0;
	}
	node(int a, int b, int dst){
		x = a;
		y = b;
		dist = dst;
	}
};

#endif
