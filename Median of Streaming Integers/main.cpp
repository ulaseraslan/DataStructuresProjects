//
//  main.cpp
//  ulaseraslan_Eraslan_Ulas_hw4
//
//  Created by Ulaş Eraslan on 30.04.2020.
//  Copyright © 2020 Ulaş Eraslan. All rights reserved.

// CS 300 HW4 Sabanci University

#include <iostream>
#include "Binary_Heap.h"
#include <string>
#include <fstream>

using namespace std;

void balance ();
double give_median ();
void file_read (string filename);


BinaryHeap<int> minheap;
max_heap<int> maxheap;


int main() {
    
    string filename;
    
    //File operations
    cout << "Please enter the next filename that contains integer stream: " ;
    while (cin>>filename) { // If ctrl-d (for linux) is pushed it stops (ctr-z for windows)
        file_read(filename);
        cout << "Please enter the next filename that contains integer stream: " ;
    }
    return 0;
}

void file_read (string filename) {
    string line;
    fstream input;
    
    input.open(filename);
    
    while (input.fail()) {
        cout << "Wrong file name!"<<endl;
        cout << "Please enter the next filename that contains integer stream: " ;
        cin >> filename;
        input.open(filename);
    }
    
    while (!input.eof()) {
        
        getline(input,line);        // File reading operations.
        
        int value = stoi(line);
        
        if (value <= give_median()) {       // If read value is smaller than median, put it to max heap.
            maxheap.insert(value);
        }
        
        else if (value >= give_median()) {  // If read value is greater than median put it to min heap.
            minheap.insert(value);
        }
        
    }
    input.close();
    
    
    cout << "Current median: " << give_median() << endl;
}


double give_median () {
    
    float max = 0;
    
    balance();
    
    if (maxheap.get_size() == minheap.get_size()) { // If heaps have same size, median is the average of the top elements of min and max heaps.
        max = ( maxheap.findTop() + minheap.findTop() ) / 2.0;
    }
    else {
        
        if (maxheap.get_size()>minheap.get_size()) {        // If max heap's size is greater than min heap's size median is the top element of max.
            max = maxheap.findTop();
        }
        
        else {                                              // If min heap's size is greater than max's size median is the top element of the min.
            
            max = minheap.findTop();
        }
    }
    
    return max;
}

void balance () {   // check sizes of heaps if difference is more than 1 re-balance it
    
    int top=0;
    
    if (minheap.get_size() - maxheap.get_size() > 1) {
        top = minheap.findTop();
        minheap.deleteMin();
        maxheap.insert(top);
    }
    
    else if (maxheap.get_size() - minheap.get_size() > 1) {
        top = maxheap.findTop();
        maxheap.deleteMax();
        minheap.insert(top);
    }
}
