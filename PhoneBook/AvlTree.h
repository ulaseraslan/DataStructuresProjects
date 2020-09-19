//
//  AvlTree.h
//  ulaseraslan_cs300_hw2
//
//  Created by Ulaş Eraslan on 11.03.2020.
//  Copyright © 2020 Ulaş Eraslan. All rights reserved.
//

#ifndef AvlTree_h
#define AvlTree_h
#include "AvlNode.h"
#include <string>

template <class Comparable>
class AvlTree
{
     public:
         explicit AvlTree( const Comparable & notFound );
         AvlTree( const AvlTree & rhs );
        ~AvlTree( );

        const Comparable & findMin( ) const;
        const Comparable & findMax( ) const;
        const Comparable & find( const Comparable & x ) const;
        bool isEmpty( ) const;
        void printTree(std::ofstream &file ) const;
        void printTree( AvlNode<Comparable> * t ,std::ofstream &file2) const;
        void printTreePre(std::ofstream &file ) const;
        void printTreePre( AvlNode<Comparable> * t ,std::ofstream &file2) const;

        void makeEmpty( );
        void insert( const Comparable & x );
        void remove( std::string & x );

        const AvlTree & operator=( const AvlTree & rhs );
    
        AvlNode<Comparable> *root;
    
        const Comparable ITEM_NOT_FOUND;

        const Comparable & elementAt( AvlNode<Comparable> *t ) const;

        void insert( const Comparable & x, AvlNode<Comparable> * & t ) const;
        //AvlNode<Comparable> * remove(std::string & x, AvlNode<Comparable> * & t ) const;

        AvlNode<Comparable> * findMin( AvlNode<Comparable> *t ) const;
        AvlNode<Comparable> * findMax( AvlNode<Comparable> *t ) const;
        AvlNode<Comparable> * find( const Comparable & x, AvlNode<Comparable> *t ) const;
        void makeEmpty( AvlNode<Comparable> * & t ) const;
        void printTree( AvlNode<Comparable> *t ) const;
        AvlNode<Comparable> * clone( AvlNode<Comparable> *t ) const;

        // Avl manipulations
        int height( AvlNode<Comparable> *t ) const;
        int max( int lhs, int rhs ) const;
        void rotateWithLeftChild( AvlNode<Comparable> * & k2 ) const;
        void rotateWithRightChild( AvlNode<Comparable> * & k1 ) const;
        void doubleWithLeftChild( AvlNode<Comparable> * & k3 ) const;
        void doubleWithRightChild( AvlNode<Comparable> * & k1 ) const;
    
        void height_check (AvlNode<Comparable> *t ) const;
        bool isHeightBalanced(AvlNode<Comparable> * root) const;
        
        void Search(AvlNode<Comparable> *root, std::string input,bool &check);
    
        void draw (AvlNode<Comparable> * root, std::string shape, int &width, std::ofstream &file);
    
    
    
        AvlNode<Comparable> * singleRightRotate(AvlNode<Comparable> * &t);
        AvlNode<Comparable> * singleLeftRotate(AvlNode<Comparable> * &t);
        AvlNode<Comparable> * doubleLeftRotate(AvlNode<Comparable>* &t);
        AvlNode<Comparable> * doubleRightRotate(AvlNode<Comparable> * &t);
        AvlNode<Comparable> * remove(std::string x, AvlNode<Comparable>* t);
    };

#endif /* AvlTree_h */
