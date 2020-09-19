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
void search_bst ();
void add_contact ();
void delete_contact ();
void draw ();


int main() {
    
    string file_name,line,option;
    vector <person> person_vec;
    
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
        transform(fullname.begin(), fullname.end(),fullname.begin(), ::toupper);
        per.fullname = fullname;
        
        person_vec.push_back(per);
    }
    
   
    // AVL - BST Insertions
   
    bst_create(person_vec); //To create a BST.
    avl_create(person_vec); //To create an AVL.
    
    cout << "Choose which aciton to perform from 1 to 6:" << endl;
    cout << "1 - Search a phonebook contact" << endl;
    cout << "2 - Adding a phonebook contact" << endl;
    cout << "3 - Deleting phonebook contact" << endl;
    cout << "4 - Printing the phonebook contact to a file (inorder)" << endl;
    cout << "    Printing the phonebook contact to a file (inorder)"<< endl;
    cout << "5 - Draw the Phonebook as a Tree to a file" << endl;
    cout << "6 - Press 6 to exit" << endl;
    
    cin>> option;
    
    while (option != "6") {
        
        
        if (option == "1") {
            
            search_bst ();
            
        }
        
        else if (option == "2") {
            add_contact ();
        }
        
        else if (option == "3") {
            delete_contact ();
            
        }
        
        else if (option == "4") {
            
            ofstream file,file2,file3,file4;
            string file_name = "phonebookInOrderBST.txt";
            file.open(file_name);
            bst.printTree(file);
            file.close();
            
            string file_name2 = "phonebookPreOrderBST.txt";
            file2.open(file_name2);
            bst.printTreePre(file2);
            file2.close();
            
            string file_name3 = "phonebookInOrderAVL.txt";
            file3.open(file_name3);
            avl.printTree(file3);
            file3.close();
            
            string file_name4 = "phonebookPreOrderAVL.txt";
            file4.open(file_name4);
            avl.printTreePre(file4);
            file4.close();
    
        }
        
        else if (option == "5") {
            draw ();
           
        }
    
        cout << "Choose which aciton to perform from 1 to 6:" << endl;
        cout << "1 - Search a phonebook contact" << endl;
        cout << "2 - Adding a phonebook contact" << endl;
        cout << "3 - Deleting phonebook contact" << endl;
        cout << "4 - Printing the phonebook contact to a file (inorder)" << endl;
        cout << "    Printing the phonebook contact to a file (pre-order)"<< endl;
        cout << "5 - Draw the Phonebook as a Tree to a file" << endl;
        cout << "6 - Press 6 to exit" << endl;
        
        cin>>option;
        
    }
    
    
    
    return 0;
}



void bst_create (vector<person> p) {        //Creation takes place here.
        
    cout << "Loading into BST"<< endl<< endl;
    
    std::chrono::time_point<std::chrono::system_clock> start, end;
    
    start = std::chrono::system_clock::now();
    for (int i=0; i<p.size(); i++) {
        
        bst.insert(p[i]);       //Each contact is inserted to the BST.
    }
    end = std::chrono::system_clock::now();
    
    std::chrono::duration<double> elapsed_seconds = (end - start)*1000;
    std::cout << "Phonebook creation in BST took " << elapsed_seconds.count() << " milliseconds\n";
    
    check_balanced(bst);    //Program checks if tree is balanced or not.
    
    height_check(bst);      // Program gives the height trees.
    
    cout << endl;
}

void avl_create (vector<person> p) {        //Same operations for the AVL.
    
    cout << "Loading into AVL"<< endl<< endl;
    
    std::chrono::time_point<std::chrono::system_clock> start, end;
    
    start = std::chrono::system_clock::now();
    for (int i=0; i<p.size(); i++) {
        
        avl.insert(p[i]);
    }
    end = std::chrono::system_clock::now();
    
    std::chrono::duration<double> elapsed_seconds = (end - start)*1000;
    std::cout << "Phonebook creation in AVL took " << elapsed_seconds.count() << " milliseconds\n";
    
    check_balanced_avl(avl);
    height_check_avl(avl);
    
}



void check_balanced (BinarySearchTree<person> bst) {
    
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
    
}

void height_check (BinarySearchTree<person> bst) {
    
    bst.heightCheck(bst.root);
        
}

void height_check_avl (AvlTree<person> avl) {
    
    avl.height_check(avl.root);
        
}


void search_bst () { //Search for both avl and bst.
    
    string contact;
    bool check = false;
    cout << "Search for a contact: ";
    cin.ignore();
    getline(cin,contact);
    
    std::chrono::time_point<std::chrono::system_clock> start, end,start_avl,end_avl;    //To calculate the time of the operation.
    
    start = std::chrono::system_clock::now();
    cout << "Phonebook seraching for: (" << contact << ")" << endl;
    cout << "========================================="<< endl<<endl;
    
    bst.Search(bst.root, contact,check);
    
    end = std::chrono::system_clock::now();
    
    std::chrono::duration<double> elapsed_seconds = (end - start)*1000;
    
    
    
    start_avl = std::chrono::system_clock::now();           //For AVL Tree, it starts here.
    cout << endl;
    cout << "Searching an item in the phonebook (AVL)" << endl;
    cout << "Phonebook: Section (" << contact << ")" << endl;
    cout << "========================================="<< endl<<endl;
    
    avl.Search(avl.root,contact,check);
    
    end_avl = std::chrono::system_clock::now();
    
    std::chrono::duration<double> elapsed_seconds_avl = (end_avl - start_avl)*1000;
    
    if (check==true) {  //If contact is found in the tree time info is printed.
    cout << endl;
    std::cout << "The search BST took " << elapsed_seconds.count() << " milliseconds\n";
    std::cout << "The search AVL took " << elapsed_seconds_avl.count() << " milliseconds\n"<<endl;
    }
}


void add_contact () {       //This method adds a contact to the trees.
    
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
        
    }
    
}


void delete_contact () {
    
    string contact;
    bool bts_check=false;
    cout << " Deleting an item from phonebook " << endl;
    cout << "========================================="<< endl<<endl;
    
    cout << "Enter the fullname of the contact to be deleted: "<< endl;
    cin.ignore();
    getline(cin,contact);
    
    std::chrono::time_point<std::chrono::system_clock> start, end,start_avl,end_avl;    //To calculate the time of the operation.
    start = std::chrono::system_clock::now();
    bst.remove(contact,bts_check);
    end = std::chrono::system_clock::now();
    std::chrono::duration<double> elapsed_seconds = (end - start)*1000;
    
    start_avl= std::chrono::system_clock::now();
    avl.remove(contact);
    end_avl = std::chrono::system_clock::now();
    std::chrono::duration<double> elapsed_seconds_avl = (end - start)*1000;
    
    if (bts_check==true) {
        cout << endl;
        cout << "Deleted sucessfully!" << endl;
        std::cout << "Deleting a contact to the BST took " << elapsed_seconds.count() << " milliseconds\n";
        std::cout << "Deleting a contact to the AVL took " << elapsed_seconds_avl.count() << " milliseconds\n"<<endl;
    }
}


void draw () {      //This method draws the AVL and BST.
    
    /*cout << " Printing out the phonebook (BST) " << endl;
    cout << "=================================="<< endl<<endl;*/
    
    string shape = "|__ ";
    int width=0;
    ofstream file1,file2;
    
    string file_name = "phonebookTreeBST.txt";
    file1.open(file_name);
    bst.draw(bst.root,shape,width,file1);
    file1.close();
    
    string file_name2 = "phonebookTreeAVL.txt";
    file2.open(file_name2);
    avl.draw(avl.root, shape, width,file2);
    file2.close();    
}

