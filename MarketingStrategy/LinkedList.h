//
//  LinkedList.h
//  ulaseraslan_hw3
//
//  Created by Ulaş Eraslan on 13.04.2020.
//  Copyright © 2020 Ulaş Eraslan. All rights reserved.
//

#ifndef LinkedList_h
#define LinkedList_h

//#include "dsexceptions.h"
#include <iostream>    // For NULL

// List class
//
// CONSTRUCTION: with no initializer
// Access is via ListItr class
//
// ******************PUBLIC OPERATIONS*********************
// boolean isEmpty( )     --> Return true if empty; else false
// void makeEmpty( )      --> Remove all items
// ListItr zeroth( )      --> Return position to prior to first
// ListItr first( )       --> Return first position
// void insert( x, p )    --> Insert x after current iterator position p
// void remove( x )       --> Remove x
// ListItr find( x )      --> Return position that views x
// ListItr findPrevious( x )
//                        --> Return position prior to x
// ******************ERRORS********************************
// No special errors

using namespace std;

template <class HashedObj>

class List;     // Incomplete declaration.

template <class HashedObj>
class ListItr;     // Incomplete declaration.

template <class HashedObj>
class ListNode
{
    ListNode( const HashedObj & theElement = HashedObj( ), ListNode * n = NULL )
      : element( theElement ), next( n ) { }

    HashedObj   element;
    double amount=0;
    double supportval=0;
    ListNode *next;

    friend class List<HashedObj>;
    friend class ListItr<HashedObj>;
};


template <class HashedObj>
class List
{
  public:
    List( );
    List( const List & rhs );
    ~List( );

    bool isEmpty( ) const;
    void makeEmpty( );
    ListItr<HashedObj> zeroth( ) const;
    ListItr<HashedObj> first( ) const;
    void insert( const HashedObj & x, const ListItr<HashedObj> & p );
    ListItr<HashedObj> find( const HashedObj & x ) const;
    ListItr<HashedObj> findPrevious( const HashedObj & x ) const;
    void remove( const HashedObj & x );

    const List & operator=( const List & rhs );

  private:
    ListNode<HashedObj> *header;
};


// ListItr class; maintains "current position"
//
// CONSTRUCTION: Package friendly only, with a ListNode
//
// ******************PUBLIC OPERATIONS*********************
// bool isPastEnd( )      --> True if past end position in list
// void advance( )        --> Advance (if not already null)
// Object retrieve        --> Return item in current position

template <class HashedObj>
class ListItr
{
  public:
    ListItr( ) : current( NULL ) { }
    bool isPastEnd( ) const
      { return current == NULL; }
    void advance( )
      { if( !isPastEnd( ) ) current = current->next; }
    const HashedObj & retrieve( ) const
      { if( isPastEnd( ) )
          //throw BadIterator( );
          std::cout <<"Bad Iterator";
        return current->element; }
    void increase_amount ()
    {
        current->amount++;
    }
    
    double get_amount( ) const {
        if( !isPastEnd( ) ) {
        //throw BadIterator( );
        return current->amount;
        }
        else {
            return 0;
        }
    }
    
    double get_support( ) const {
        if( !isPastEnd( ) ) {
            
            return current->supportval;
        }
        else {
            return 0;
        }
    }
    
    void set_support (double val)
    {
        current->supportval=val;
    }
    
    bool check_current () {
        if (this->current!= nullptr)
            return true;
        return false;
        
    }
    
    

  private:
    ListNode<HashedObj> *current;    // Current position

    ListItr( ListNode<HashedObj> *theNode )
      : current( theNode ) { }

    friend class List<HashedObj>; // Grant access to constructor
};

/**
 * Construct the list
 */
template <class HashedObj>
List<HashedObj>::List( )
{
    header = new ListNode<HashedObj>;
}

/**
 * Copy constructor
 */
template <class HashedObj>
List<HashedObj>::List( const List<HashedObj> & rhs )
{
    header = new ListNode<HashedObj>;
    *this = rhs;
}

/**
 * Destructor
 */
template <class HashedObj>
List<HashedObj>::~List( )
{
    makeEmpty( );
    delete header;
}

/**
 * Test if the list is logically empty.
 * return true if empty, false otherwise.
 */
template <class HashedObj>
bool List<HashedObj>::isEmpty( ) const
{
    return header->next == NULL;
}

/**
 * Make the list logically empty.
 */
template <class HashedObj>
void List<HashedObj>::makeEmpty( )
{
    while( !isEmpty( ) )
        remove( first( ).retrieve( ) );
}

/**
 * Return an iterator representing the header node.
 */
template <class HashedObj>
ListItr<HashedObj> List<HashedObj>::zeroth( ) const
{
    return ListItr<HashedObj>( header );
}

/**
 * Return an iterator representing the first node in the list.
 * This operation is valid for empty lists.
 */
template <class HashedObj>
ListItr<HashedObj> List<HashedObj>::first( ) const
{
    return ListItr<HashedObj>( header->next );
}

/**
 * Insert item x after p.
 */
template <class HashedObj>
void List<HashedObj>::insert( const HashedObj & x, const ListItr<HashedObj> & p )
{
    if( p.current != NULL )
        p.current->next = new ListNode<HashedObj>( x, p.current->next );
}

/**
 * Return iterator corresponding to the first node containing an item x.
 * Iterator isPastEnd if item is not found.
 */
template <class HashedObj>
ListItr<HashedObj> List<HashedObj>::find( const HashedObj & x ) const
{
    /* 1*/      ListNode<HashedObj> *itr = header->next;
    
    /* 2*/      while( itr != NULL && itr->element != x )
    /* 3*/          itr = itr->next;
    
    /* 4*/      return ListItr<HashedObj>( itr );
}

/**
 * Return iterator prior to the first node containing an item x.
 */
template <class HashedObj>
ListItr<HashedObj> List<HashedObj>::findPrevious( const HashedObj & x ) const
{
    /* 1*/      ListNode<HashedObj> *itr = header;
    
    /* 2*/      while( itr->next != NULL && itr->next->element != x )
    /* 3*/          itr = itr->next;
    
    /* 4*/      return ListItr<HashedObj>( itr );
}

/**
 * Remove the first occurrence of an item x.
 */
template <class HashedObj>
void List<HashedObj>::remove( const HashedObj & x )
{
    ListItr<HashedObj> p = findPrevious( x );
    
    if( p.current->next != NULL )
    {
        ListNode<HashedObj> *oldNode = p.current->next;
        p.current->next = p.current->next->next;  // Bypass deleted node
        delete oldNode;
    }
}

/**
 * Deep copy of linked lists.
 */
template <class HashedObj>
const List<HashedObj> & List<HashedObj>::operator=( const List<HashedObj> & rhs )
{
    ListItr<HashedObj> ritr = rhs.first( );
    ListItr<HashedObj> itr = zeroth( );
    
    if( this != &rhs )
    {
        makeEmpty( );
        for( ; !ritr.isPastEnd( ); ritr.advance( ), itr.advance( ) )
            insert( ritr.retrieve( ), itr );
    }
    return *this;
}

#endif
