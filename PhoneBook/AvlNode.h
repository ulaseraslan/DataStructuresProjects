//
//  AvlNode.h
//  ulaseraslan_cs300_hw2
//
//  Created by Ulaş Eraslan on 11.03.2020.
//  Copyright © 2020 Ulaş Eraslan. All rights reserved.
//

#ifndef AvlNode_h
#define AvlNode_h


template <class Comparable>
class AvlTree;

template <class Comparable>
class AvlNode
{
       Comparable element;
       AvlNode           *left;
       AvlNode           *right;
       int                height;

    AvlNode( const Comparable & theElement, AvlNode *lt, AvlNode *rt, int h = 0 ) : element( theElement ), left( lt ), right( rt ), height( h ) { }

    friend class AvlTree<Comparable>;
};

#endif /* AvlNode_h */
