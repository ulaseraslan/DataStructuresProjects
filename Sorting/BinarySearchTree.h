//
//  BinarySearchTree.h
//  ulaseraslan_cs300_hw2
//
//  Created by Ulaş Eraslan on 11.03.2020.
//  Copyright © 2020 Ulaş Eraslan. All rights reserved.
//

#ifndef BinarySearchTree_h
#define BinarySearchTree_h

#include "Tree.h"
#include <iostream>
#include <string>
template <class Comparable>

class BinarySearchTree {

public:

    BinaryNode<Comparable> *root;
    
    explicit BinarySearchTree( const Comparable & notFound );

    BinarySearchTree( const BinarySearchTree & rhs );

    ~BinarySearchTree( );

    const Comparable & findMin( ) const;

    const Comparable & findMax( ) const;

    const Comparable & find( const Comparable & x ) const;

    bool isEmpty( ) const;

    void printTree( std::ofstream &file) const;
    
    void printTreePre(std::ofstream &file ) const;

    void makeEmpty( );

    void insert( const Comparable & x );

    void remove( std::string & x , bool &check);
    
    bool isHeightBalanced(BinaryNode<Comparable> * root) const;
    
    void heightCheck (BinaryNode<Comparable> * root) const;

    BinarySearchTree<Comparable>&operator=(const BinarySearchTree<Comparable>& that);
    
    void Search(BinaryNode<Comparable> *root, std::string fullname,bool &check,std::vector<Comparable>&contacts);
    void Search_for_adding(BinaryNode<Comparable> *root, std::string input,bool &check);
    
    int height(BinaryNode<Comparable> * root) const;
    
    int height_left(BinaryNode<Comparable> * root) const;
    int height_right(BinaryNode<Comparable> * root) const;
    
    void draw (BinaryNode<Comparable> * root, std::string shape, int &width,std::ofstream &file);
    
    BinaryNode<Comparable> * left ();
    BinaryNode<Comparable> * right();

    void count_node (BinaryNode<Comparable> * root,int &count);
    
private:

    const Comparable ITEM_NOT_FOUND;

    const Comparable & elementAt( BinaryNode<Comparable> *t ) const;

    void insert( const Comparable & x, BinaryNode<Comparable> * & t ) const;

    void remove( std::string & x, BinaryNode<Comparable> * & t , bool &check) const;

    BinaryNode<Comparable> * findMin( BinaryNode<Comparable> *t ) const;

    BinaryNode<Comparable> * findMax( BinaryNode<Comparable> *t ) const;

    BinaryNode<Comparable> * find( const Comparable & x, BinaryNode<Comparable> *t ) const;

    void makeEmpty( BinaryNode<Comparable> * & t ) const;

    void printTree( BinaryNode<Comparable> *t ,std::ofstream &file) const;
    
    void printTreePre( BinaryNode<Comparable> *t ,std::ofstream &file) const;
    
    

    BinaryNode<Comparable> * clone( BinaryNode<Comparable> * t ) const;
    
    
    
    
    
    
};
#endif /* BinarySearchTree_h */
