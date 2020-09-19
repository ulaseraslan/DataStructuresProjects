
#ifndef DYNAMICINTSTACK_H
#define DYNAMICINTSTACK_H

struct CellStackNode  //Cell Struct.
{
    int xVal;         
    int yVal;
    int left;
    int right;
    int up;
    int down;
    int visit_count;
    bool visited=false;
    bool path_visit=false;
    
    CellStackNode() {
        xVal=1;
        yVal=1;
        left=1;
        right=1;
        up=1;
        down=1;
        visit_count=1;
        path_visit=false;
        visited = false;
    }
    
    CellStackNode(int x,int y):xVal(x),yVal(y),left(1),right(1),up(1),down(1),visit_count(1),visited(false),path_visit(false) {}
    
};

struct IntStackNode
{
    CellStackNode cell;
    IntStackNode *next;
    
};

template <class T>

class DynamicIntStack
{
	
	public:
    
        IntStackNode *top;
		DynamicIntStack(void);
		void push(T);
		void pop();
		bool isEmpty(void);
		T* GetTopPointer();
		void clear();

};


#endif
