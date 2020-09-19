//
//  AvlTree.cpp
//  ulaseraslan_cs300_hw2
//
//  Created by Ulaş Eraslan on 11.03.2020.
//  Copyright © 2020 Ulaş Eraslan. All rights reserved.
//

#include <stdio.h>
#include "AvlTree.h"
#include "AvlNode.h"
#include <iostream>
#include <fstream>

using namespace std;


   template <class Comparable>
   AvlTree<Comparable>::AvlTree( const Comparable & notFound ) :
     ITEM_NOT_FOUND( notFound ), root( NULL )
   {
   }

   /**
    * Copy constructor.
    */
   template <class Comparable>
   AvlTree<Comparable>::AvlTree( const AvlTree<Comparable> & rhs ) :
     ITEM_NOT_FOUND( rhs.ITEM_NOT_FOUND ), root( NULL )
   {
      *this = rhs;
   }

   /**
    * Destructor for the tree.
    */
   template <class Comparable>
   AvlTree<Comparable>::~AvlTree( )
   {
       makeEmpty( );
   }

   /**
    * Insert x into the tree; duplicates are ignored.
    */
   template <class Comparable>
   void AvlTree<Comparable>::insert( const Comparable & x )
   {
       insert( x, root );
   }

   /**
    * Remove x from the tree. Nothing is done if x is not found.
    */
   template <class Comparable>

void AvlTree<Comparable>::remove( std::string & x ) {
    
    remove(x, root);
    
}


/*template <class Comparable>

AvlNode<Comparable> * AvlTree<Comparable> :: remove(std::string & x, AvlNode<Comparable> * & t ) const {
       
       AvlNode<Comparable >* temp;

       // Element not found
       if(t == NULL)
           return nullptr;

       // Searching for element
       else if(x < t->element.fullname)
           t->left = remove(x, t->left);
       else if(x > t->element.fullname)
           t->right = remove(x, t->right);

       // Element found
       // With 2 children
       else if(t->left && t->right)
       {
           temp = findMin(t->right);
           t->element = temp->element;
           t->right = remove(t->element.fullname, t->right);
       }
       // With one or zero child
       else
       {
           temp = t;
           if(t->left == NULL)
               t = t->right;
           else if(t->right == NULL)
               t = t->left;
           delete temp;
       }
       if(t == NULL)
           return t;

       t->height = max(height(t->left), height(t->right))+1;

       // If node is unbalanced
       // If left node is deleted, right case
    
       if(height(t->left) - height(t->right) == 2)
       {
           // right right case
           if(height(t->left->left) - height(t->left->right) == 1)
               return rotateWithLeftChild(t);
           // right left case
           else
               return doubleWithLeftChild(t);
       }
       // If right node is deleted, left case
       else if(height(t->right) - height(t->left) == 2)
       {
           // left left case
           if(height(t->right->right) - height(t->right->left) == 1)
               return rotateWithRightChild(t);
           // left right case
           else
               return doubleWithRightChild(t);
       }
        return t;
   }*/

   /**
    * Find the smallest item in the tree.
    * Return smallest item or ITEM_NOT_FOUND if empty.
    */
   template <class Comparable>
   const Comparable & AvlTree<Comparable>::findMin( ) const
   {
       return elementAt( findMin( root ) );
   }

   /**
    * Find the largest item in the tree.
    * Return the largest item of ITEM_NOT_FOUND if empty.
    */
   template <class Comparable>
   const Comparable & AvlTree<Comparable>::findMax( ) const
   {
       return elementAt( findMax( root ) );
   }

   /**
    * Find item x in the tree.
    * Return the matching item or ITEM_NOT_FOUND if not found.
    */
   template <class Comparable>
   const Comparable & AvlTree<Comparable>::
                            find( const Comparable & x ) const
   {
       return elementAt( find( x, root ) );
   }

   /**
    * Make the tree logically empty.
    */
   template <class Comparable>
   void AvlTree<Comparable>::makeEmpty( )
   {
       makeEmpty( root );
   }

   /**
    * Test if the tree is logically empty.
    * Return true if empty, false otherwise.
    */
   template <class Comparable>
   bool AvlTree<Comparable>::isEmpty( ) const
   {
       return root == NULL;
   }

   /**
    * Print the tree contents in sorted order.
    */
   template <class Comparable>
   void AvlTree<Comparable>::printTreePre(ofstream &file ) const
   {
       if( isEmpty( ) )
           cout << "Empty tree" << endl;
       else
           printTreePre( root,file);
   }



    template <class Comparable>

    void AvlTree<Comparable>:: printTreePre( AvlNode<Comparable> * t ,ofstream &file2) const {  //PreOrder Print
          if ( t != NULL )
          {
                file2 << t->element.fullname << " " <<t->element.phoneNumber << " " << t->element.city  <<endl;
                printTreePre( t->left , file2);
                printTreePre( t->right, file2 );
          }
    }

      template <class Comparable>
      void AvlTree<Comparable>::printTree(ofstream &file ) const
      {
          if( isEmpty( ) )
              cout << "Empty tree" << endl;
          else
              printTree( root,file);
      }

    template <class Comparable>

    void AvlTree<Comparable>::printTree( AvlNode<Comparable> * t , ofstream &file) const {  //InOrder Print
          
        if ( t != NULL )
          {
                printTree( t->left,file );
                file << t->element.fullname << " " <<t->element.phoneNumber << " " << t->element.city<<endl;
                printTree( t->right,file );
          }
    }
   /**
    * Deep copy.
    */
   template <class Comparable>
   const AvlTree<Comparable> &
   AvlTree<Comparable>::
   operator=( const AvlTree<Comparable> & rhs )
   {
       if( this != &rhs )
       {
           makeEmpty( );
           root = clone( rhs.root );
       }
       return *this;
   }

   /**
    * Internal method to get element field in node t.
    * Return the element field or ITEM_NOT_FOUND if t is NULL.
    */
   template <class Comparable>
   const Comparable & AvlTree<Comparable>::elementAt( AvlNode<Comparable> *t ) const
   {
       if( t == NULL )
          return ITEM_NOT_FOUND;
       else
          return t->element;
   }

   /**
    * Internal method to insert into a subtree.
    * x is the item to insert.
    * t is the node that roots the tree.
    */
   template <class Comparable>
void AvlTree<Comparable>::insert( const Comparable & x, AvlNode<Comparable> * & t ) const
   {
       if( t == NULL )
           t = new AvlNode<Comparable>( x, NULL, NULL );
       else if( x.fullname < t->element.fullname )
       {
           insert( x, t->left );
           if( height( t->left ) - height( t->right ) == 2 )
               if( x.fullname < t->left->element.fullname )
                   rotateWithLeftChild(t);
               else
                   doubleWithLeftChild( t );
       }
       else if( t->element.fullname < x.fullname )
       {
           insert( x, t->right );
           if( height( t->right ) - height( t->left ) == 2 )
               if( t->right->element.fullname < x.fullname )
                   rotateWithRightChild( t );
               else
                   doubleWithRightChild( t );
       }
       else
           ;  // Duplicate; do nothing
       t->height = max( height( t->left ), height( t->right ) ) + 1;
   }

   /**
    * Internal method to find the smallest item in a subtree t.
    * Return node containing the smallest item.
    */
   template <class Comparable>
   AvlNode<Comparable> *
   AvlTree<Comparable>::findMin( AvlNode<Comparable> *t ) const
   {
       if( t == NULL)
           return t;

       while( t->left != NULL )
           t = t->left;
       return t;
   }

   /**
    * Internal method to find the largest item in a subtree t.
    * Return node containing the largest item.
    */
   template <class Comparable>
   AvlNode<Comparable> *
   AvlTree<Comparable>::findMax( AvlNode<Comparable> *t ) const
   {
       if( t == NULL )
           return t;

       while( t->right != NULL )
           t = t->right;
       return t;
   }

   /**
    * Internal method to find an item in a subtree.
    * x is item to search for.
    * t is the node that roots the tree.
    * Return node containing the matched item.
    */
   template <class Comparable>
   AvlNode<Comparable> *
   AvlTree<Comparable>::find( const Comparable & x, AvlNode<Comparable> *t ) const
   {
       while( t != NULL )
           if( x < t->element )
               t = t->left;
           else if( t->element < x )
               t = t->right;
           else
               return t;    // Match

       return NULL;   // No match
   }

   /**
    * Internal method to make subtree empty.
    */
   template <class Comparable>
   void AvlTree<Comparable>::makeEmpty( AvlNode<Comparable> * & t ) const
   {
       if( t != NULL )
       {
           makeEmpty( t->left );
           makeEmpty( t->right );
           delete t;
       }
       t = NULL;
   }

   /**
    * Internal method to clone subtree.
    */
   template <class Comparable>
   AvlNode<Comparable> *
   AvlTree<Comparable>::clone( AvlNode<Comparable> * t ) const
   {
       if( t == NULL )
           return NULL;
       else
           return new AvlNode<Comparable>( t->element, clone( t->left ),
                                         clone( t->right ), t->height );
   }

   /**
    * Return the height of node t or -1 if NULL.
    */
   template <class Comparable>
   int AvlTree<Comparable>::height( AvlNode<Comparable> *t ) const
   {
       return t == NULL ? -1 : t->height;
   }


    template <class Comparable>

    void AvlTree<Comparable>:: height_check (AvlNode<Comparable> *t ) const {
    
        int left=0,right=0;
    
        left = height(t->left);
        right = height(t->right);
    
        cout << "The heights of AVL are for left: " << left+1 << " for right: " << right+1 << endl<<endl;
}


template <class Comparable>

bool AvlTree<Comparable>:: isHeightBalanced(AvlNode<Comparable> * root) const {
    
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


   /**
    * Return maximum of lhs and rhs.
    */
   template <class Comparable>
   int AvlTree<Comparable>::max( int lhs, int rhs ) const
   {
       return lhs > rhs ? lhs : rhs;
   }

   /**
    * Rotate binary tree node with left child.
    * For AVL trees, this is a single rotation for case 1.
    * Update heights, then set new root.
    */
   template <class Comparable>
   void AvlTree<Comparable>::rotateWithLeftChild( AvlNode<Comparable> * & k2 ) const
   {
       AvlNode<Comparable> *k1 = k2->left;
       k2->left = k1->right;
       k1->right = k2;
       k2->height = max( height( k2->left ), height( k2->right ) ) + 1;
       k1->height = max( height( k1->left ), k2->height ) + 1;
       k2 = k1;
   }

   /**
    * Rotate binary tree node with right child.
    * For AVL trees, this is a single rotation for case 4.
    * Update heights, then set new root.
    */
   template <class Comparable>
   void AvlTree<Comparable>::rotateWithRightChild( AvlNode<Comparable> * & k1 ) const
   {
       AvlNode<Comparable> *k2 = k1->right;
       k1->right = k2->left;
       k2->left = k1;
       k1->height = max( height( k1->left ), height( k1->right ) ) + 1;
       k2->height = max( height( k2->right ), k1->height ) + 1;
       k1 = k2;
   }

   /**
    * Double rotate binary tree node: first left child.
    * with its right child; then node k3 with new left child.
    * For AVL trees, this is a double rotation for case 2.
    * Update heights, then set new root.
    */
   template <class Comparable>
   void AvlTree<Comparable>::doubleWithLeftChild( AvlNode<Comparable> * & k3 ) const
   {
       rotateWithRightChild( k3->left );
       rotateWithLeftChild( k3 );
   }

   /**
    * Double rotate binary tree node: first right child.
    * with its left child; then node k1 with new right child.
    * For AVL trees, this is a double rotation for case 3.
    * Update heights, then set new root.
    */
   template <class Comparable>
   void AvlTree<Comparable>::doubleWithRightChild( AvlNode<Comparable> * & k1 ) const
   {
       rotateWithLeftChild( k1->right );
       rotateWithRightChild( k1 );
   }

   /**
    * Internal method to print a subtree in sorted order.
    * t points to the node that roots the tree.
    */
   template <class Comparable>
   void AvlTree<Comparable>::printTree( AvlNode<Comparable> *t ) const
   {
       if( t != NULL )
       {
           printTree( t->left );
           cout << t->element << endl;
           printTree( t->right );
       }
   }


template <class Comparable>

void  AvlTree<Comparable>:: Search(AvlNode<Comparable> *root, string input,bool &check) {
    int lenght = input.size();
    //bool check=false;
    Comparable temp_p;
    AvlNode<Comparable> *temp = new AvlNode<Comparable>(temp_p,nullptr,nullptr);
    
    temp = root;
    while(temp != NULL) {
      if(temp->element.fullname.substr(0,lenght) == input) {
          cout<<temp->element.fullname << " " << temp->element.phoneNumber << " " << temp->element.city << endl;
          check = true;
          Search(temp->left, input,check);
          Search(temp->right, input,check);
          return;
          
      } else if(temp->element.fullname.substr(0,lenght) > input)
         temp = temp->left;
         else
            temp = temp->right;
   }
    
    if (check==false) {
        cout<<"\n Contact not found"<<endl<<endl;
    }
   return;
}

    
template <class Comparable>

AvlNode<Comparable>* AvlTree<Comparable>:: singleRightRotate(AvlNode<Comparable> * &t)
{
    AvlNode<Comparable>* u = t->left;
    t->left = u->right;
    u->right = t;
    t->height = max(height(t->left), height(t->right))+1;
    u->height = max(height(u->left), t->height)+1;
    return u;
}

template <class Comparable>

AvlNode<Comparable> * AvlTree<Comparable>::singleLeftRotate(AvlNode<Comparable> * &t)
{
    AvlNode<Comparable> * u = t->right;
    t->right = u->left;
    u->left = t;
    t->height = max(height(t->left), height(t->right))+1;
    u->height = max(height(t->right), t->height)+1 ;
    return u;
}

template <class Comparable>

AvlNode<Comparable> * AvlTree<Comparable>:: doubleLeftRotate(AvlNode<Comparable>* &t)
{
    t->right = singleRightRotate(t->right);
    return singleLeftRotate(t);
}

template <class Comparable>

AvlNode<Comparable> * AvlTree<Comparable>:: doubleRightRotate(AvlNode<Comparable> * &t)
{
    t->left = singleLeftRotate(t->left);
    return singleRightRotate(t);
}
    
template <class Comparable>

AvlNode<Comparable> * AvlTree<Comparable>::remove(string x, AvlNode<Comparable>* t)
{
    AvlNode<Comparable>* temp;

    // Element not found
    if(t == NULL)
        return NULL;

    // Searching for element
    else if(x < t->element.fullname)
        t->left = remove(x, t->left);
    else if(x > t->element.fullname)
        t->right = remove(x, t->right);

    // Element found
    // With 2 children
    else if(t->left && t->right)
    {
        temp = findMin(t->right);
        t->element = temp->element;
        t->right = remove(t->element.fullname, t->right);
    }
    // With one or zero child
    else
    {
        temp = t;
        if(t->left == NULL)
            t = t->right;
        else if(t->right == NULL)
            t = t->left;
        delete temp;
    }
    if(t == NULL)
        return t;

    t->height = max(height(t->left), height(t->right))+1;

    // If node is unbalanced
    // If left node is deleted, right case
    if(height(t->left) - height(t->right) == 2)
    {
        // right right case
        if(height(t->left->left) - height(t->left->right) == 1)
            return singleLeftRotate(t);
        // right left case
        else
            return doubleLeftRotate(t);
    }
    // If right node is deleted, left case
    else if(height(t->right) - height(t->left) == 2)
    {
        // left left case
        if(height(t->right->right) - height(t->right->left) == 1)
            return singleRightRotate(t);
        // left right case
        else
            return doubleRightRotate(t);
    }
    return t;
}

template <class Comparable>

void  AvlTree<Comparable>:: draw (AvlNode<Comparable> * root, string shape, int &width,ofstream &file) {
    
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
