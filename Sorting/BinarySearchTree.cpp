//
//  BinarySearchTree.cpp
//  ulaseraslan_cs300_hw2
//
//  Created by Ulaş Eraslan on 11.03.2020.
//  Copyright © 2020 Ulaş Eraslan. All rights reserved.
//

#include <stdio.h>
#include "BinarySearchTree.h"
#include "Tree.h"
#include <iostream>
#include <fstream>

using namespace std;

template <class Comparable>

BinarySearchTree<Comparable>:: BinarySearchTree(const Comparable & notFound ) : ITEM_NOT_FOUND( notFound ), root( NULL ){}


template <class Comparable>

BinarySearchTree<Comparable>::~BinarySearchTree( ) {

    makeEmpty( );

}

template <class Comparable>

void BinarySearchTree<Comparable>::makeEmpty( )

{

makeEmpty( root );

}


template <class Comparable>

void BinarySearchTree<Comparable>:: makeEmpty( BinaryNode<Comparable> * & t ) const {

    if( t != NULL ) {

        makeEmpty( t->left );

        makeEmpty( t->right );

        delete t;

        }

    t = NULL;

}


template <class Comparable>

const Comparable & BinarySearchTree<Comparable>:: elementAt( BinaryNode<Comparable> *t ) const {
    return t == NULL ? ITEM_NOT_FOUND : t->element;
}



template <class Comparable>

BinaryNode<Comparable> * BinarySearchTree<Comparable>::find( const Comparable & x, BinaryNode<Comparable> * t ) const {

    if ( t == NULL )

        return NULL;

    else if( x < t->element )

        return find( x, t->left );

    else if( t->element < x )

        return find( x, t->right );

    else

        return t; // Match

}


template <class Comparable>

const Comparable & BinarySearchTree<Comparable>:: find( const Comparable & x ) const {

return elementAt( find( x, root ) );
    
}


template <class Comparable>

BinaryNode<Comparable> * BinarySearchTree<Comparable>::findMin( BinaryNode<Comparable> *t ) const {

    if( t == NULL )

        return NULL;

    if( t->left == NULL )

        return t;

    return findMin( t->left);
                   
}

template <class Comparable>

const Comparable & BinarySearchTree<Comparable>::findMin( ) const {

    return elementAt( findMin( root ) );

}

template <class Comparable>

BinaryNode<Comparable> * BinarySearchTree<Comparable>::findMax( BinaryNode<Comparable> *t ) const {

    if( t != NULL )

    while( t->right != NULL )

    t = t->right;

    return t;
    
}


template <class Comparable>

const Comparable & BinarySearchTree<Comparable>::findMax( ) const {

    return elementAt( findMax( root ));
}



template <class Comparable>

void BinarySearchTree<Comparable>::insert( const Comparable & x ) {
    
    insert( x, root );
    
}

template <class Comparable>

void BinarySearchTree<Comparable>:: insert( const Comparable & x, BinaryNode<Comparable> * & t ) const {

    if( t == NULL ) // create a new node at the right place

        t = new BinaryNode<Comparable>( x, NULL, NULL );

    else if( x.fullname < t->element.fullname )

        insert( x, t->left ); // insert at the left or

    else if( t->element.fullname < x.fullname )

        insert( x, t->right ); // right subtree

    else; // Duplicate; do nothing

}

template <class Comparable>

void BinarySearchTree<Comparable>::remove( std::string & x , bool & check) {

    remove( x, root ,check);
}

template <class Comparable>

void BinarySearchTree<Comparable>::remove( std::string & x, BinaryNode<Comparable> * & t , bool & check) const {

    if( t == NULL ){

        cout << "Not found!"<< endl<< endl;
        return; // Item not found; do nothing
    }

    if( x < t->element.fullname )

        remove( x, t->left ,check);

    else if( t->element.fullname < x )

        remove( x, t->right ,check);

    else if( t->left != NULL && t->right != NULL ) // Two children
    {

        t->element = findMin( t->right )->element;

        remove( t->element.fullname, t->right ,check);

}

    else // one or no children
{

    BinaryNode<Comparable> *oldNode = t;

    t = ( t->left != NULL ) ? t->left : t->right;

    delete oldNode;
    check=true;
    }
    
}

template <class Comparable>

void BinarySearchTree<Comparable>:: printTree( BinaryNode<Comparable> * t , ofstream &file) const {  //InOrder Print
      
    if ( t != NULL )
      {
            printTree( t->left,file );
            file << t->element.fullname << " " <<t->element.phoneNumber << " " << t->element.city<<endl;
            printTree( t->right,file );
      }
}

template <class Comparable>

void BinarySearchTree<Comparable>:: printTreePre( BinaryNode<Comparable> * t ,ofstream &file2) const {  //PreOrder Print
    
      if ( t != NULL )
      {
            file2 << t->element.fullname << " " <<t->element.phoneNumber << " " << t->element.city  <<endl;
            printTreePre( t->left , file2);
            printTreePre( t->right, file2 );
      }
}


template <class Comparable>

void BinarySearchTree<Comparable>::printTree(ofstream &file ) const

{

    if( isEmpty( ))

        cout << "Empty tree" << endl;

    else

        printTree(root,file);
}

template <class Comparable>

void BinarySearchTree<Comparable>::printTreePre(ofstream &file ) const

{

    if( isEmpty( ))

        cout << "Empty tree" << endl;

    else

        printTreePre(root,file);
}

template <class Comparable>

bool BinarySearchTree<Comparable>::isEmpty() const {
    
    if (root !=nullptr) {
        return false;
        
    }
    
    else {
        
        return true;
    }
    
}


template <class Comparable>

BinarySearchTree<Comparable>:: BinarySearchTree( const BinarySearchTree<Comparable> & rhs ) : root( NULL ), ITEM_NOT_FOUND( rhs.ITEM_NOT_FOUND ) {

    
    this->root = rhs.clone(rhs.root);

}


template <class Comparable>

BinarySearchTree<Comparable>& BinarySearchTree<Comparable>::operator=(const BinarySearchTree<Comparable>& that) {
    
    if(this != &that)
    {
        this->makeEmpty();
        BinaryNode<Comparable> *c = that.root;
        clone(c);
    }
    return *this;
}




template <class Comparable>

BinaryNode<Comparable> * BinarySearchTree<Comparable>:: clone( BinaryNode<Comparable> * t ) const {
    if ( t == NULL )
        return NULL;
    else
        return new BinaryNode<Comparable> ( t->element, clone( t->left ), clone( t->right ) );
    
}

template <class Comparable>

int BinarySearchTree<Comparable>::height(BinaryNode<Comparable> * root) const {
    
    
    if (root == NULL)
        return 0;

    else {
        int leftHt = height(root->left);
        int rightHt = height(root->right);
        int curHt = max(leftHt, rightHt) + 1;
        return curHt;
    }
    
}

template <class Comparable>

int BinarySearchTree<Comparable>::height_left(BinaryNode<Comparable> * root) const {
    
    
    if (root == NULL)
        return 0;

    else {
        int leftHt = height(root->left);
        return leftHt;
    }
    
}

template <class Comparable>

int BinarySearchTree<Comparable>::height_right(BinaryNode<Comparable> * root) const {
    
    
    if (root == NULL)
        return 0;

    else {
        int rightHt = height(root->right);
        return rightHt;
    }
    
}

template <class Comparable>

void  BinarySearchTree<Comparable>:: draw (BinaryNode<Comparable> * root, string shape, int &width,ofstream &file) {
    
    string space="";
    
    if (root!=nullptr) {
            for (int i=0; i <width; i++) {
                space += "\t|";
                
            }
        
        file << space << shape << root->element.fullname << endl;
    
        width ++;
        shape= "-- ";
        draw(root->left,shape,width,file);
        shape="__ ";
        draw(root->right,shape,width,file);
        
        width--;
    }
        
}

template <class Comparable>

bool BinarySearchTree<Comparable>:: isHeightBalanced(BinaryNode<Comparable> * root) const {
    
    if (!root) {
        return true;
    }

    int leftHt = height(root->left);
    int rightHt = height(root->right);

    if (abs(leftHt - rightHt) > 1) {
            return false;
    }
    return isHeightBalanced(root->left) && isHeightBalanced(root->right);
}


template <class Comparable>

void BinarySearchTree<Comparable>::heightCheck (BinaryNode<Comparable> * root) const {
    
    int left = height(root->left);
    int right = height(root->right);
    
    cout << "The heights of BST are for left: " << left << " for right: " << right << endl;
    
}


template <class Comparable>

void BinarySearchTree<Comparable>::Search(BinaryNode<Comparable> *root, string input,bool &check,vector<Comparable>&contacts) {
    int lenght = 0;
    lenght=input.size();
    //bool check=false;
    Comparable temp_p;
    BinaryNode<Comparable> *temp = new BinaryNode<Comparable>(temp_p,nullptr,nullptr);
    
    temp = root;
    while(temp != NULL) {
      if(temp->element.fullname.substr(0,lenght) == input) {
          //cout<<temp->element.fullname << " " << temp->element.phoneNumber << " " << temp->element.city << endl;
          contacts.push_back(temp->element);
          check = true;
          Search(temp->left, input,check,contacts);
          Search(temp->right, input,check,contacts);
          return;
      } else if(temp->element.fullname.substr(0,lenght) > input)
         temp = temp->left;
         else
            temp = temp->right;
   }
    
    if (check == false) {
        cout<<"\n Contact not found"<<endl;
    }
   
   return;
}

template <class Comparable>

void BinarySearchTree<Comparable>::Search_for_adding(BinaryNode<Comparable> *root, string input,bool &check) {
    int lenght = 0;
    lenght=input.size();
    //bool check=false;
    Comparable temp_p;
    BinaryNode<Comparable> *temp = new BinaryNode<Comparable>(temp_p,nullptr,nullptr);
    
    temp = root;
    while(temp != NULL) {
      if(temp->element.fullname.substr(0,lenght) == input) {
          cout<<temp->element.fullname << " " << temp->element.phoneNumber << " " << temp->element.city << endl;
          check = true;
          Search(temp->left, input,check);
          Search(temp->right, input,check);
           cout << endl;
           cout << "The given contact full name already exists in the database."<< endl;
           cout << endl;
          return;
      } else if(temp->element.fullname.substr(0,lenght) > input)
         temp = temp->left;
         else
            temp = temp->right;
   }
    
   return;
}

template <class Comparable>

void BinarySearchTree<Comparable>:: count_node (BinaryNode<Comparable> * root,int &count) {
    
    if (root!=NULL) {
        count ++;
        count_node(root->right,count);
        count_node(root->left,count);

    }
    
    return;
}

template <class Comparable>

BinaryNode<Comparable> * BinarySearchTree<Comparable>:: left () {
    
    return this->root->left;
}
   




template <class Comparable>

BinaryNode<Comparable> * BinarySearchTree<Comparable>:: right () {
    
    return this->root->right;
}
