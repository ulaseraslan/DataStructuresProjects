//
//  main.cpp
//  ulaseraslan_cs300_hw2
//
//  Created by Ulaş Eraslan on 11.03.2020.
//  Copyright © 2020 Ulaş Eraslan. All rights reserved.
//

#include <iostream>
#include <fstream>
#include <algorithm>
#include <sstream>
#include <vector>
#include "BinarySearchTree.h"
#include "Tree.h"
#include "AvlNode.h"
#include "AvlTree.h"
#include "BinarySearchTree.cpp"
#include "AvlTree.cpp"
#include <chrono>
#include <ctime>
#include <fstream>
#include "SORT.h"

using namespace std;


struct person {
    
    string name;
    string lastname;
    string phoneNumber;
    string city;
    string fullname;
    
    person (string name, string lastname, string phoneNumber , string city,string fullname): name(name), lastname(lastname),phoneNumber(phoneNumber),city(city), fullname(fullname) {}
    
    person (string name, string lastname, string phoneNumber , string city): name(name), lastname(lastname),phoneNumber(phoneNumber),city(city) {}
    person (){}
    
};

person a;

BinarySearchTree<person> bst(a);
AvlTree<person> avl(a);

void check_balanced (BinarySearchTree<person> bst);
void check_balanced (BinarySearchTree<person> bst);
void height_check (BinarySearchTree<person> bst);
void bst_create (vector<person>p);
void avl_create (vector<person> p);

void height_check_avl (AvlTree<person> avl);
void check_balanced_avl (AvlTree<person> avl);
void search_bst (string query,vector<person>&contacts);
void add_contact ();
void delete_contact ();

double result_comparison (double first, double second);

double quick_time,heap_time,insertion_time,merge_time,bst_time,avl_time,binary_time;
int main() {
    
    
    string file_name,line,option,query;
    vector <person> person_vec;
    
    vector<person>quick_sort;           //Each vector for different sorting algorithms.
    vector<person>heap_sort;
    vector<person>insertion_sort;
    vector<person>merge_sort;
    
    cout << "Please enter the contact file name:" << endl;
    cin >> file_name;
    
    ifstream input;
    input.open(file_name);
    
    while (!input.eof() ) {     //Given file is reading.
        getline(input,line);
        stringstream ss (line);
        string fullname;
        
        person per;
        ss>>per.name>>per.lastname>>per.phoneNumber>>per.city;//Each "person" is pushed to the vector.
        
        
        fullname = per.name + " " + per.lastname;
        //transform(fullname.begin(), fullname.end(),fullname.begin(), ::toupper);
        per.fullname = fullname;
        
        person_vec.push_back(per);
        quick_sort.push_back(per);
        heap_sort.push_back(per);
        insertion_sort.push_back(per);
        merge_sort.push_back(per);
    }
    
    // AVL - BST Insertions
    bst_create(person_vec); //To create a BST.
    avl_create(person_vec); //To create an AVL.
    
    cout << "Please enter the word to be queried:"<<endl;
    cin.ignore();
    std::getline(cin,query);
    
    
    //Sorting operations                        // Calculate the each sorting algorithm's time.
    
    cout << endl;
    cout << "Sorting the vector copies"<<endl;
    cout << "======================================"<< endl;
    cout << endl;
    
    auto start = chrono::steady_clock::now();
    quicksort(quick_sort,quick_time);
    auto end = chrono::steady_clock::now();
    quick_time = chrono::duration_cast<chrono::nanoseconds>(end - start).count();
    cout << "Quick Sort Time:" << quick_time << " Nanoseconds" << endl;
    
    auto start1 = chrono::steady_clock::now();
    insertionSort(insertion_sort,insertion_time);
    auto end1 = chrono::steady_clock::now();
    insertion_time= chrono::duration_cast<chrono::nanoseconds>(end1 - start1).count();
    cout << "Insertion Sort Time:" << insertion_time << " Nanoseconds" << endl;
    
    auto start2 = chrono::steady_clock::now();
    in_mergesort(merge_sort,merge_time);
    auto end2 = chrono::steady_clock::now();
    merge_time= chrono::duration_cast<chrono::nanoseconds>(end2 - start2).count();
    cout << "Merge Sort Time:" << merge_time << " Nanoseconds" << endl;
    
    auto start3 = chrono::steady_clock::now();
    heapsort(heap_sort,heap_time);
    auto end3 = chrono::steady_clock::now();
    heap_time = chrono::duration_cast<chrono::nanoseconds>(end3 - start3).count();
    cout << "Heap Sort Time:" << heap_time << " Nanoseconds" << endl;
    
    cout << endl;
    
    //Searching
    
    vector<person>contacts; // Calculate the each search algorithm's time.
    
    cout << "Searching for " << query << endl;
    cout << "======================================"<< endl;
    search_bst(query,contacts);
    
    auto start4 = chrono::steady_clock::now();
    binaarySearhcall(insertion_sort, query,binary_time,contacts);
    auto end4 = chrono::steady_clock::now();
    binary_time = (chrono::duration_cast<chrono::nanoseconds>(end4 - start4).count())/insertion_sort.size();
    cout << "Binary Search Time:" << binary_time << " Nanoseconds" << endl;
    cout << endl;
    
    
    
    // SpeedUps for Search                                  //For given search time calculate SpeedUps (Slower/Faster)
    cout << "SpeedUps in search" <<endl;
    cout << "======================================"<< endl<<endl;
    cout << "(BST / AVL) SpeedUp = " << result_comparison(bst_time, avl_time)<<endl;
    cout <<"(Binary Search / AVL) SpeedUp = " << result_comparison(binary_time, avl_time) <<endl;
    cout << "(Binary Search / BST) SpeedUp  = " << result_comparison(binary_time, bst_time)<<endl;
    cout << endl;
    
    
    //SpeedUps for Sorting
    cout << "SpeedUps between Sorting Algorithms"<< endl;
    cout << "======================================"<< endl<<endl;
    cout << "(Insertion Sort/ Quick Sort) SpeedUp = " << result_comparison(insertion_time, quick_time)<<endl;;
    cout << "(Merge Sort / Quick Sort) SpeedUp = " << result_comparison(merge_time, quick_time)<< endl;
    cout << "(Heap Sort / Quick Sort) SpeedUp = " << result_comparison(heap_time, quick_time)<<endl;
    cout << endl;
    
    
    return 0;
}



void bst_create (vector<person> p) {        //Creation takes place here.
    
    //cout << "Loading into BST"<< endl<< endl;
    
    //std::chrono::time_point<std::chrono::system_clock> start, end;
    
    //start = std::chrono::system_clock::now();
    for (int i=0; i<p.size(); i++) {
        
        bst.insert(p[i]);       //Each contact is inserted to the BST.
    }
    //end = std::chrono::system_clock::now();
    
    //std::chrono::duration<double> elapsed_seconds = (end - start)*1000;
    //std::cout << "Phonebook creation in BST took " << elapsed_seconds.count() << " milliseconds\n";
    
    //check_balanced(bst);    //Program checks if tree is balanced or not.
    
    //height_check(bst);      // Program gives the height trees.
    
    //cout << endl;
}

void avl_create (vector<person> p) {        //Same operations for the AVL.
    
    //cout << "Loading into AVL"<< endl<< endl;
    
    //std::chrono::time_point<std::chrono::system_clock> start, end;
    
    //start = std::chrono::system_clock::now();
    
  
    for (int i=0; i<p.size(); i++) {
        avl.insert(p[i]);
    }
    
    
    
    //end = std::chrono::system_clock::now();
    
    //std::chrono::duration<double> elapsed_seconds = (end - start)*1000;
    //std::cout << "Phonebook creation in AVL took " << elapsed_seconds.count() << " milliseconds\n";
    
    //check_balanced_avl(avl);
    //height_check_avl(avl);
    
}



/*void check_balanced (BinarySearchTree<person> bst) {
 
 if  (bst.isHeightBalanced(bst.root) == true ) {
 
 cout << "The tree is balanced"<< endl;
 }
 
 else {
 cout << "The tree is not balanced"<< endl;
 
 }
 
 }
 
 void check_balanced_avl (AvlTree<person> avl) {
 
 if  (avl.isHeightBalanced(avl.root) == true ) {
 
 cout << "The tree is balanced"<< endl;
 }
 
 else {
 cout << "The tree is not balanced"<< endl;
 
 }
 
 }*/

/*void height_check (BinarySearchTree<person> bst) {
 
 bst.heightCheck(bst.root);
 
 }
 
 void height_check_avl (AvlTree<person> avl) {
 
 avl.height_check(avl.root);
 
 }*/


void search_bst (string contact,vector<person>&contacts) { //Search for both avl and bst.
    
    /*string contact;
     cout << "Search for a contact: ";
     cin.ignore();
     getline(cin,contact);*/
    
    bool check = false;
    
    //std::chrono::time_point<std::chrono::system_clock> start, end,start_avl,end_avl;    //To calculate the time of the operation.
    
    auto start5 = chrono::steady_clock::now();
    //cout << "Phonebook seraching for: (" << contact << ")" << endl;
    //cout << "========================================="<< endl<<endl;
    
    bst.Search(bst.root, contact,check,contacts);
    auto end5 = chrono::steady_clock::now();
    bst_time = chrono::duration_cast<chrono::nanoseconds>(end5 - start5).count();
    cout << "Binary Search Time:" << bst_time << " Nanoseconds" << endl;
    
    auto start6 = chrono::steady_clock::now();         //For AVL Tree, it starts here.
    //cout << endl;
    //cout << "Searching an item in the phonebook (AVL)" << endl;
    //cout << "Phonebook: Section (" << contact << ")" << endl;
    //cout << "========================================="<< endl<<endl;
    
    avl.Search(avl.root,contact,check);
    
    auto end6 = chrono::steady_clock::now();
    avl_time = chrono::duration_cast<chrono::nanoseconds>(end6 - start6).count();
    cout << "The search in AVL took " << avl_time<< " Nanoseconds" << endl;
    // if (check==true) {  //If contact is found in the tree time info is printed.
    //   cout << endl;

}

double result_comparison (double first, double second) {
    
    double result=0;
    
    if (first>second) {
        result = first/second;
    }
    else {
        result = second/first;
    }
    
    return result;
}


/*void add_contact () {       //This method adds a contact to the trees.
 
 string name,lastname,fullname,city,phone;
 cout << " Adding an item to the phonebook (BST)" << endl;
 cout << "========================================="<< endl<<endl;
 
 cout << "Enter the information of the contatc to be added:" << endl;
 cout << "Name: " ;
 cin.ignore();
 getline(cin,fullname);
 
 bool check=false;
 
 bst.Search_for_adding(bst.root, fullname, check);
 
 if (check!= true) {
 
 cout << "Please enter Tel and City Information.."<< endl;
 cout << "Tel: " ;
 cin>>phone;
 
 cout << "City: " ;
 cin>> city;
 
 name = fullname.substr(0,fullname.find(" "));
 lastname = fullname.substr(name.length());
 
 
 person contact (name,lastname,phone,city,fullname);
 
 std::chrono::time_point<std::chrono::system_clock> start, end,start_avl,end_avl;    //To calculate the time of the operation.
 start = std::chrono::system_clock::now();
 bst.insert(contact);                        //Add to BST.
 end = std::chrono::system_clock::now();
 std::chrono::duration<double> elapsed_seconds = (end - start)*1000;
 
 cout << endl;
 cout << "Contact has been added successfully to the BST "<< endl;
 
 cout << " Adding an item to the phonebook (AVL)" << endl;
 cout << "========================================="<< endl<<endl;
 
 start_avl = std::chrono::system_clock::now();
 avl.insert(contact);            //Add to AVL.
 end_avl = std::chrono::system_clock::now();
 std::chrono::duration<double> elapsed_seconds_avl = (end_avl - start_avl)*1000;
 
 cout << "Contact has been added successfully to the AVL "<< endl;
 
 std::cout << "Adding a contact to the BST took " << elapsed_seconds.count() << " milliseconds\n";
 std::cout << "Adding a contact to the AVL took " << elapsed_seconds_avl.count() << " milliseconds\n"<<endl;
 
 }*/
