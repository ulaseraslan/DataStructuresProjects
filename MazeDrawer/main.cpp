//  Created by Ulaş Eraslan on 22.02.2020.
//  CS300 HW1- 2020 Sabanci University
//  Copyright © 2020 Ulaş Eraslan. All rights reserved.

#include <iostream>
//#include <stdlib.h>
#include <fstream>
#include <vector>
#include "DynamicIntStack.h"
#include "DynamicIntStack.cpp"
using namespace std;

enum directions {r,l,u,d};
void vecCreate (vector <vector<CellStackNode>> &matrix,int row , int column);
void StackOperation(int row, int column,int maze_number);
void false_setter (bool &r_visit, bool &l_visit, bool &u_visit, bool &d_visit);
void maze_file (int i,vector<vector<CellStackNode>> maze, int row, int column);
void path_finder ( DynamicIntStack<CellStackNode>&stack ,int entry_x , int entry_y, int exit_x , int exit_y, int maze_no);
void path_print (DynamicIntStack<CellStackNode> stack,int exit_x, int exit_y , int enter_x , int enter_y, int maze_num);

vector<vector<vector<CellStackNode>>>path_matrix;

int main() {
        
    int maze_num,row,column;
    srand((unsigned) time(NULL)); //To seed the random time of the machine is used.
    
    cout << "Enter the number of mazes: ";
    cin >> maze_num;
    
    cout << "Enter the number of rows and columns (M and N): ";
    cin >> row >> column;
    
    StackOperation(row,column,maze_num);         //Maze genetaring operations
    
    cout << "All mazes are generated." << endl;
    
    // Path Operations
    
        int maze_id=0;
        int entry_x, entry_y, exit_x, exit_y;
    
    while (maze_id != -1) {
   
        cout << "Enter a maze ID between 1 to "<< maze_num << " inclusive to find a path (Press -1 to exit): " ;
        cin>> maze_id;
        
        if (maze_id == -1) {
            break;
        }
    
        cout << "Enter x and y coordinates of the entry points (x,y) or (column,row): " ;
        cin >> entry_x>> entry_y;
    
        cout << "Enter x and y coordinates of the exit points (x,y) or (column,row): " ;
        cin >> exit_x>> exit_y;
    
        DynamicIntStack<CellStackNode> path_stack;
    
        path_matrix[maze_id-1][entry_y][entry_x].path_visit=true;
        path_stack.push(path_matrix[maze_id-1][entry_y][entry_x]);
        path_finder(path_stack, entry_x, entry_y, exit_x, exit_y, maze_id-1);
        path_print (path_stack,exit_x,exit_y ,entry_x ,entry_y, maze_id);
    }
    return 0;
}

void vecCreate (vector<vector<CellStackNode>> &maze, int row , int column) {
    
    for (int i =0 ; i<row; i++) {
        for (int j=0; j< column ; j++) {
            
             CellStackNode cell(i,j);
            maze[i][j]=cell;
        }
    }
}

void StackOperation(int row, int column,int maze_number) {
    
    int mazeCount=0;
    int row_new = row-1;
    int column_new = column-1;
    
while (mazeCount!=maze_number) {
        
    vector <vector<CellStackNode>> maze(row,vector<CellStackNode>(column));   //Matrix for maze generating
    vecCreate(maze, row, column);   // At this point a matrix is created which consists cells.

    DynamicIntStack<CellStackNode> pathStack;       //Struct is created to do maze operations.
    
    int xVal,yVal;
    bool r_visit=false,l_visit=false,u_visit=false,d_visit=false;
    
    maze[0][0].visited=true;            //First cell (0,0) is pushed to the stack.
    pathStack.push(maze[0][0]);
        
    while (!pathStack.isEmpty()) {      //While there is a cell in the stack operations will continue.
        
        int a;
        
        xVal = pathStack.top->cell.xVal;
        yVal = pathStack.top->cell.yVal;
        
        a = (rand() % 4); //Random number generator.
        
        if (a==r) { // right (x,y+1)
            
            if ((0<=xVal && xVal<=row_new) && (0<= yVal+1 && yVal+1 <= column_new)) {       //First checkpoint -Boundary check.
                
                if (!maze[xVal][yVal+1].visited) {      //Second checkpoint -Visited or Not
                    maze[xVal][yVal].right=0;               //If all checkpoints are passed then do the related operations.
                    maze[xVal][yVal+1].left=0;
                    pathStack.top->cell.visit_count++;      //Visit cound -> to check whether 4 directions are visited or not.
                    maze[xVal][yVal+1].visited=true;
                    pathStack.push(maze[xVal][yVal+1]);
                    false_setter(r_visit,l_visit,u_visit,d_visit);    //False setter set all directions (r_visit,l_visit,etc.) false.
                    
                }
                else {
                    if (r_visit == false) {
                        pathStack.top->cell.visit_count++;
                        r_visit=true;
                    }
                    
                }
            }
            
            else {
                if (r_visit == false) {
                    pathStack.top->cell.visit_count++;
                    r_visit=true;
                }
                
            }
        }
    
        else if (a==l) { // left (x,y-1)
            
            if ((0<=xVal && xVal<=row_new) && (0<= yVal-1 && yVal-1 <= column_new)) {       //Same operations as like "right".
                
                if (!maze[xVal][yVal-1].visited) {
                    maze[xVal][yVal].left=0;
                    maze[xVal][yVal-1].right=0;
                    pathStack.top->cell.visit_count++;
                    maze[xVal][yVal-1].visited=true;
                    pathStack.push(maze[xVal][yVal-1]);
                    false_setter(r_visit,l_visit,u_visit,d_visit);
                    
                    }
                else {
                    if (l_visit == false) {
                        pathStack.top->cell.visit_count++;
                        l_visit=true;
                        }
                    }
                }
            
            else {
                if (l_visit == false) {
                    pathStack.top->cell.visit_count++;
                    l_visit=true;
                    
                    }
                }
            }
        
        else if (a==u) {    // up (x+1,y)       //Same operations as like "right".
            
            if ((0<=xVal+1 && xVal+1 <=row_new) && (0<= yVal && yVal <= column_new)) {
                
                if (!maze[xVal+1][yVal].visited) {
                    maze[xVal][yVal].up=0;
                    maze[xVal+1][yVal].down=0;
                    pathStack.top->cell.visit_count++;
                    maze[xVal+1][yVal].visited=true;
                    pathStack.push(maze[xVal+1][yVal]);
                    false_setter(r_visit,l_visit,u_visit,d_visit);
    
                }
                else {
                    
                    if (u_visit == false) {
                        pathStack.top->cell.visit_count++;
                        u_visit=true;
                    }
                    
                }
            }
            
            else {
                if (u_visit == false) {
                    pathStack.top->cell.visit_count++;
                    u_visit=true;
                    }
            }
            
        }
        
        else if (a==d) { // down (x-1,y)        //Same operations as like "right".
            
            if ((0<=xVal-1 && xVal-1 <=row_new) && (0<= yVal && yVal <= column_new)) {
                
                if (!maze[xVal-1][yVal].visited) {
                    maze[xVal][yVal].down=0;
                    maze[xVal-1][yVal].up=0;
                    pathStack.top->cell.visit_count++;
                    maze[xVal-1][yVal].visited=true;
                    pathStack.push(maze[xVal-1][yVal]);
                    false_setter(r_visit,l_visit,u_visit,d_visit);
                    
                }
                else {
                    if (d_visit == false) {
                        pathStack.top->cell.visit_count++;
                        d_visit=true;
                    }
                }
            }
            else {
                if (d_visit == false) {
                    pathStack.top->cell.visit_count++;
                    d_visit=true;
                }
            }
        }
        
        if (pathStack.top->cell.visit_count==4) {
            pathStack.pop();
            false_setter(r_visit,l_visit,u_visit,d_visit);
            if (pathStack.top !=NULL) {
            pathStack.top->cell.visit_count=0;
                }
            }
        }
    
    maze_file(mazeCount, maze, row, column);        //At this point created maze is sent to file writing process.
    path_matrix.push_back(maze);        //To find the path created maze is pushed to the vector.
    mazeCount++;
    pathStack.clear();
    maze.clear();
    }
}

void maze_file (int i,vector<vector<CellStackNode>> maze, int row, int column) {        //At this point created maze is written to a file.
    
    string number = to_string(i+1);
    string file_name = "maze_"+number+".txt";
    ofstream file;
    file.open(file_name);
    
    file<<row<<" "<< column<<endl;
    
    for (int i=0; i<row ; i++) {
        for (int j=0; j<column ; j++) {
            file << "x=" << maze[i][j].yVal <<" "<<"y=" << maze[i][j].xVal <<" "<<"l=" << maze[i][j].left <<" " <<"r=" << maze[i][j].right<< " "<<"u=" << maze[i][j].up << " "<<"d=" << maze[i][j].down<<endl;
        }
    }
    file.close();
}

void false_setter (bool &r_visit, bool &l_visit, bool &u_visit, bool &d_visit) {
    
    r_visit=false;
    l_visit=false;
    u_visit=false;
    d_visit=false;
    
}

void path_finder (DynamicIntStack<CellStackNode>&stack ,int entry_x , int entry_y, int exit_x , int exit_y, int maze_no) {      //Recursive function to find the path.

    if (path_matrix[maze_no][stack.top->cell.xVal][stack.top->cell.yVal].xVal == exit_y && path_matrix[maze_no][stack.top->cell.xVal][stack.top->cell.yVal].yVal == exit_x) {
        return;         //If the given exit is at the top the finish
    }
    
    else {
    
    if (path_matrix[maze_no][entry_y][entry_x].right==0  && path_matrix[maze_no][entry_y][entry_x+1].path_visit==false) {    //Check no wall and not visited cell
        
        path_matrix[maze_no][entry_y][entry_x].path_visit=true;
        stack.push(path_matrix[maze_no][entry_y][entry_x+1]);
        path_finder(stack,  entry_x+1,  entry_y,  exit_x,  exit_y,  maze_no);
        
        }
    
    else if (path_matrix[maze_no][entry_y][entry_x].left==0  && path_matrix[maze_no][entry_y][entry_x-1].path_visit==false) {  //Check no wall and not visited cell
        
        path_matrix[maze_no][entry_y][entry_x].path_visit=true;
        stack.push(path_matrix[maze_no][entry_y][entry_x-1]);
        path_finder(stack,  entry_x-1,  entry_y,  exit_x,  exit_y,  maze_no);
        
    }
    
   else if (path_matrix[maze_no][entry_y][entry_x].up==0 && path_matrix[maze_no][entry_y+1][entry_x].path_visit==false) {  //Check no wall and not visited cell
        
       path_matrix[maze_no][entry_y][entry_x].path_visit=true;
       stack.push(path_matrix[maze_no][entry_y+1][entry_x]);
       path_finder(stack,  entry_x,  entry_y+1,  exit_x,  exit_y,  maze_no);
    }
    
   else if (path_matrix[maze_no][entry_y][entry_x].down==0 && path_matrix[maze_no][entry_y-1][entry_x].path_visit==false) {  //Check no wall and not visited cell
        
       path_matrix[maze_no][entry_y][entry_x].path_visit=true;
       stack.push(path_matrix[maze_no][entry_y-1][entry_x]);
       path_finder(stack,  entry_x,  entry_y-1,  exit_x,  exit_y,  maze_no);
    }
   else {
       path_matrix[maze_no][stack.top->cell.xVal][stack.top->cell.yVal].path_visit=true;
       stack.pop();
       path_finder(stack, stack.top->cell.yVal, stack.top->cell.xVal, exit_x, exit_y, maze_no);
        }
    }
}

void path_print (DynamicIntStack<CellStackNode> stack,int exit_x, int exit_y , int enter_x , int enter_y, int maze_num) {   //At this point found path is written to a file.
    
    DynamicIntStack<CellStackNode> path_stack_print;
    
    while (stack.top!= NULL) {
        
        path_stack_print.push(stack.top->cell);
        stack.pop();
    }
    
    string number = to_string(maze_num);
    string enterx = to_string(enter_x);
    string entery = to_string(enter_y);
    string exitx = to_string(exit_x);
    string exity = to_string(exit_y);
    
    string file_name = "maze_"+number+"_path_"+enterx+"_"+entery+"_"+exitx+"_"+exity+".txt";
    ofstream file;
    file.open(file_name);
    
    while (path_stack_print.top != NULL) {
        
        file << path_stack_print.top->cell.yVal << " " << path_stack_print.top->cell.xVal << endl;
        path_stack_print.pop();
    }
    file.close();
}
