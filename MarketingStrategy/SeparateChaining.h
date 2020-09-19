//
//  SeparateChaining.h
//  ulaseraslan_hw3
//
//  Created by Ulaş Eraslan on 13.04.2020.
//  Copyright © 2020 Ulaş Eraslan. All rights reserved.
//

#ifndef SeparateChaining_h
#define SeparateChaining_h

#include <vector>
#include <string>
#include "LinkedList.h"

// SeparateChaining Hash table class
//
// CONSTRUCTION: an initialization for ITEM_NOT_FOUND
//               and an approximate initial size or default of 101
//
// ******************PUBLIC OPERATIONS*********************
// void insert( x )       --> Insert x
// void remove( x )       --> Remove x
// Hashable find( x )     --> Return item that matches x
// void makeEmpty( )      --> Remove all items
// int hash( string str, int tableSize )
//                        --> Global method to hash strings

template <class HashedObj>

class HashTable
{
  public:
    explicit HashTable( const HashedObj & notFound, int size = 101 );
    HashTable( const HashTable & rhs )
      : ITEM_NOT_FOUND( rhs.ITEM_NOT_FOUND ), theLists( rhs.theLists ) { }

    const HashedObj & find( const HashedObj & x ) const;

    void makeEmpty( );
    void insert( const HashedObj & x );
    void remove( const HashedObj & x );
    
    void increase_amount( const HashedObj & x ) const;
    double  get_amount ( const HashedObj & x );
    double  get_support ( const HashedObj & x );
    void set_support ( const HashedObj & x , double val) const;
    
    //vector<HashedObj> perm_count();

    const HashTable & operator=( const HashTable & rhs );
  private:
    std::vector<List<HashedObj> > theLists;   // The array of Lists
    const HashedObj ITEM_NOT_FOUND;
};

int hashed( const std::string & key, int tableSize );
int hashed( int key, int tableSize );


/**
 * Internal method to test if a positive number is prime.
 * Not an efficient algorithm.
 */
bool isPrime( int n )
{
    if( n == 2 || n == 3 )
        return true;

    if( n == 1 || n % 2 == 0 )
        return false;

    for( int i = 3; i * i <= n; i += 2 )
        if( n % i == 0 )
            return false;

    return true;
}

/**
 * Internal method to return a prime number at least as large as n.
 * Assumes n > 0.
 */
int nextPrime( int n )
{
    if( n % 2 == 0 )
        n++;

    for( ; !isPrime( n ); n += 2 )
        ;

    return n;
}

/**
 * Construct the hash table.
 */
template <class HashedObj>
HashTable<HashedObj>::HashTable( const HashedObj & notFound, int size )
  : ITEM_NOT_FOUND( notFound ), theLists( nextPrime( size ) )
{
}

/**
 * Insert item x into the hash table. If the item is
 * already present, then do nothing.
 */
template <class HashedObj>
void HashTable<HashedObj>::insert( const HashedObj & x )
{
    List<HashedObj> & whichList = theLists[ hashed( x, theLists.size( ) ) ];
    ListItr<HashedObj> itr = whichList.find( x );

    if( itr.isPastEnd( ) )
        whichList.insert( x, whichList.zeroth( ) );
}

/**
 * Remove item x from the hash table.
 */
template <class HashedObj>
void HashTable<HashedObj>::remove( const HashedObj & x )
{
   theLists[ hashed( x, theLists.size( ) ) ].remove( x );
}

/**
 * Find item x in the hash table.
 * Return the matching item or ITEM_NOT_FOUND if not found
 */
template <class HashedObj>
const HashedObj & HashTable<HashedObj>::find( const HashedObj & x ) const
{
    ListItr<HashedObj> itr;
    itr = theLists[ hashed( x, theLists.size( ) ) ].find( x );
    if( itr.isPastEnd( ) )
        return ITEM_NOT_FOUND;
    else
        return itr.retrieve( );
}

template <class HashedObj>
void HashTable<HashedObj>::increase_amount( const HashedObj & x ) const
{
    ListItr<HashedObj> itr;
    itr = theLists[ hashed( x, theLists.size( ) ) ].find( x );
    if( !itr.isPastEnd( ) )
        itr.increase_amount();
        
}
template <class HashedObj>
double HashTable<HashedObj> :: get_amount ( const HashedObj & x ) {
    ListItr<HashedObj> itr;
       itr = theLists[ hashed( x, theLists.size( ) ) ].find( x );
    if( !itr.isPastEnd( )){
        return itr.get_amount();
    }
    else {
        return 0;
    }
}

template <class HashedObj>
double HashTable<HashedObj> :: get_support ( const HashedObj & x ) {
    ListItr<HashedObj> itr;
       itr = theLists[ hashed( x, theLists.size( ) ) ].find( x );
    if( !itr.isPastEnd( )){
        return itr.get_support();
    }
    else {
        return 0;
    }
}

template <class HashedObj>
void HashTable<HashedObj>::set_support ( const HashedObj & x , double val) const {
    
    ListItr<HashedObj> itr;
    itr = theLists[ hashed( x, theLists.size( ) ) ].find( x );
    if( !itr.isPastEnd( ) )
       itr.set_support(val);
}


/**
 * Make the hash table logically empty.
 */
template <class HashedObj>
void HashTable<HashedObj>::makeEmpty( )
{
    for( int i = 0; i < theLists.size( ); i++ )
        theLists[ i ].makeEmpty( );
}

/**
 * Deep copy.
 */
template <class HashedObj>
const HashTable<HashedObj> &
HashTable<HashedObj>::operator=( const HashTable<HashedObj> & rhs )
{
    if( this != &rhs )
        theLists = rhs.theLists;
    return *this;
}


/**
 * A hash routine for string objects.
 */
int hashed( const std::string & key, int tableSize )
{
    int hashVal = 0;

    for( int i = 0; i < key.length( ); i++ )
        hashVal = 37 * hashVal + key[ i ];

    hashVal %= tableSize;
    if( hashVal < 0 )
        hashVal += tableSize;

    return hashVal;
}


/**
 * A hash routine for ints.
 */
int hashed( int key, int tableSize )
{
    if( key < 0 ) key = -key;
    return key % tableSize;
}

/*template <class HashedObj>
vector<HashedObj> HashTable<HashedObj> :: perm_count() {
    
    string word1="",word2="";
    vector<HashedObj> perms;
    
    ListItr<HashedObj> itr1;
    ListItr<HashedObj> itr2;
    
    for (int i =0; i<theLists.size(); i++) {
        
        bool check = false;
        if (theLists[i].first().check_current()) {
        word1 = theLists[i].first().retrieve();
            
            string sub1="",sub2="";
            if (word1.find(" ") != string::npos) {
                sub1= word1.substr(0,word1.find(" "));
                sub2 = word1.substr(word1.find(" ")+1);
                check= true;
            }
        
        for (int k=0; k<theLists.size(); k++) {
            
            if (theLists[k].first().check_current()) {
            word2 = theLists[k].first().retrieve();
    
                if (!check) {
                    if (word2.find(word1) == string::npos && word1.find(word2) == string::npos) {
                        
                        string word = word1 + "," + word2;
                        
                        perms.push_back(word);
                        
                        }
                    }
                
                else {
                    if (word2.find(sub1) == string::npos && word2.find(sub2) == string::npos) {
                            string word = word1 + "," + word2;
                            perms.push_back(word);
                        }
                    }
                }
            }
        }
    }
    return perms;
}*/


#endif
