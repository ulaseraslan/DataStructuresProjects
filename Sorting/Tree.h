//
//  Tree.h
//  ulaseraslan_cs300_hw2
//
//  Created by Ulaş Eraslan on 11.03.2020.
//  Copyright © 2020 Ulaş Eraslan. All rights reserved.
//

#ifndef Tree_h
#define Tree_h

template <class Comparable>

class BinarySearchTree;

template <class Comparable>

class BinaryNode {

    Comparable element;

    BinaryNode *left;

    BinaryNode *right;

    BinaryNode( const Comparable & theElement, BinaryNode *lt, BinaryNode *rt ) : element( theElement ), left( lt ), right( rt ) {}

    friend class BinarySearchTree<Comparable>;
    
};


#endif /* Tree_h */
