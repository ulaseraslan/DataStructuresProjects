//
//  SORT.h
//  ulaseraslan_Eraslan_Ulas_hw5
//
//  Created by Ulaş Eraslan on 19.05.2020.
//  Copyright © 2020 Ulaş Eraslan. All rights reserved.
//

#ifndef SORT_h
#define SORT_h

//#define merge Merge
#define swap Swap
/**
 * Several sorting routines.
 * Arrays are rearranged with smallest item first.
 */

#include <vector>

/**
 * Simple insertion sort.
 */
template <class Comparable>
void insertionSort( vector<Comparable> & a ,double &insertion_time)
{
    //auto start = chrono::steady_clock::now();
    
    /* 1*/      for( int p = 1; p < a.size( ); p++ )
    {
        /* 2*/          Comparable tmp = a[ p ];
        
        int j;
        /* 3*/          for( j = p; j > 0 && tmp.fullname < a[ j - 1 ].fullname; j-- )
        /* 4*/              a[ j ] = a[ j - 1 ];
        /* 5*/          a[ j ] = tmp;
    }
    //auto end = chrono::steady_clock::now();
    
    //insertion_time =chrono::duration_cast<chrono::nanoseconds>(end - start).count();
    //cout << "Insertion Sort Time:" << insertion_time << " Nanoseconds" << endl;
}

/**
 * Shellsort, using Shell's (poor) increments.
 */
template <class Comparable>
void shellsort( vector<Comparable> & a )
{
    for( int gap = a.size( ) / 2; gap > 0; gap /= 2 )
        for( int i = gap; i < a.size( ); i++ )
        {
            Comparable tmp = a[ i ];
            int j = i;
            
            for( ; j >= gap && tmp < a[ j - gap ]; j -= gap )
                a[ j ] = a[ j - gap ];
            a[ j ] = tmp;
        }
}

/**
 * Standard heapsort.
 */
template <class Comparable>
void heapsort( vector<Comparable> & a , double & heap_time)
{
    
    //auto start = chrono::steady_clock::now();
    
    /* 1*/      for( int i = a.size( ) / 2; i >= 0; i-- )  /* buildHeap */
    /* 2*/          percDown( a, i, a.size( ) );
    /* 3*/      for( int j = a.size( ) - 1; j > 0; j-- )
    {
        /* 4*/          swap( a[ 0 ], a[ j ] );                  /* deleteMax */
        /* 5*/          percDown( a, 0, j );
    }
    
    //auto end = chrono::steady_clock::now();
    //heap_time = chrono::duration_cast<chrono::nanoseconds>(end - start).count();
    //cout << "Heap Sort Time:" << heap_time<< " Nanoseconds" << endl;
}

/**
 * Internal method for heapsort.
 * i is the index of an item in the heap.
 * Returns the index of the left child.
 */
inline int leftChild( int i )
{
    return 2 * i + 1;
}

/**
 * Internal method for heapsort that is used in
 * deleteMax and buildHeap.
 * i is the position from which to percolate down.
 * n is the logical size of the binary heap.
 */
template <class Comparable>
void percDown( vector<Comparable> & a, int i, int n )
{
    int child;
    Comparable tmp;
    
    /* 1*/      for( tmp = a[ i ]; leftChild( i ) < n; i = child )
    {
        /* 2*/          child = leftChild( i );
        /* 3*/          if( child != n - 1 && a[ child ].fullname < a[ child + 1 ].fullname )
        /* 4*/              child++;
        /* 5*/          if( tmp.fullname < a[ child ].fullname )
        /* 6*/              a[ i ] = a[ child ];
        else
        /* 7*/              break;
    }
    /* 8*/      a[ i ] = tmp;
}


template <class Comparable>
void merge_f(vector<Comparable> & arr, int start, int mid, int end)
{
    int start2 = mid + 1;
    
    // If the direct merge is already sorted
    if (arr[mid].fullname <= arr[start2].fullname) {
        return;
    }
    
    // Two pointers to maintain start
    // of both arrays to merge
    while (start <= mid && start2 <= end) {
        
        // If element 1 is in right place
        if (arr[start].fullname <= arr[start2].fullname) {
            start++;
        }
        else {
            Comparable value = arr[start2];
            int index = start2;
            
            // Shift all the elements between element 1
            // element 2, right by 1.
            while (index != start) {
                arr[index] = arr[index - 1];
                index--;
            }
            arr[start] = value;
            
            // Update all the pointers
            start++;
            mid++;
            start2++;
        }
    }
}

/* l is for left index and r is right index of the
 sub-array of arr to be sorted */
template <class Comparable>
void inmergeSort(vector<Comparable> & arr, int l, int r)
{
    
    if (l < r) {
        
        // Same as (l + r) / 2, but avoids overflow
        // for large l and r
        int m = l + (r - l) / 2;
        
        // Sort first and second halves
        inmergeSort(arr, l, m);
        inmergeSort(arr, m + 1, r);
        
        merge_f(arr, l, m, r);
    }
}

template <class Comparable>

void in_mergesort (vector<Comparable> &arr, double & merge_time) {
    
    //auto start = chrono::steady_clock::now();
    inmergeSort(arr, 0, (arr.size()-1));
    //auto end = chrono::steady_clock::now();
    //merge_time=chrono::duration_cast<chrono::nanoseconds>(end - start).count();
    //cout << "Merge Sort Time:" << merge_time << " Nanoseconds" << endl;
}

/**
 * Quicksort algorithm (driver).
 */
template <class Comparable>
void quicksort( vector<Comparable> & a ,double &quick_time)
{
    //auto start = chrono::steady_clock::now();
    quicksort( a, 0, a.size( ) - 1 );
    //auto end = chrono::steady_clock::now();
    //quick_time = chrono::duration_cast<chrono::nanoseconds>(end - start).count();
    
    //cout << "Quick Sort Time:" << quick_time<< " Nanoseconds" << endl;
    
    
}

/**
 * Standard swap
 */
template <class Comparable>
inline void swap( Comparable & obj1, Comparable & obj2 )
{
    Comparable tmp = obj1;
    obj1 = obj2;
    obj2 = tmp;
}

template <class Comparable>
void quicksort( vector<Comparable> & a, int left, int right )
{
    /* 1*/      if( left + 10 <= right )
    {
        /* 2*/          Comparable pivot = a[(left+right)/2];
        
        // Begin partitioning
        /* 3*/          int i = left, j = right - 1;
        /* 4*/          for( ; ; )
        {
            /* 5*/              while( a[ ++i ].fullname < pivot.fullname ) { }
            /* 6*/              while( pivot.fullname < a[ --j ].fullname ) { }
            /* 7*/              if( i < j )
            /* 8*/                  swap( a[ i ], a[ j ] );
            else
            /* 9*/                  break;
        }
        
        /*10*/          swap( a[ i ], a[ right - 1 ] );  // Restore pivot
        
        /*11*/          quicksort( a, left, i - 1 );     // Sort small elements
        /*12*/          quicksort( a, i + 1, right );    // Sort large elements
    }
    else  // Do an insertion sort on the subarray
    /*13*/          insertionSort( a, left, right );
}

/**
 * Internal insertion sort routine for subarrays
 * that is used by quicksort.
 * a is an array of Comparable items.
 * left is the left-most index of the subarray.
 * right is the right-most index of the subarray.
 */
template <class Comparable>
void insertionSort( vector<Comparable> & a, int left, int right )
{
    for( int p = left + 1; p <= right; p++ )
    {
        Comparable tmp = a[ p ];
        int j;
        
        for( j = p; j > left && tmp.fullname < a[ j - 1 ].fullname; j-- )
            a[ j ] = a[ j - 1 ];
        a[ j ] = tmp;
    }
}

template <class Comparable>
void binaarySearhcall (vector<Comparable>arr,string query,double & binarytime, vector<Comparable>contacts) {
    
    //auto start = chrono::steady_clock::now();
    for (int i =0; i< contacts.size();i++) {
        query= contacts[i].fullname;
        binarySearch(arr,0,arr.size(), query);
    }
    //auto end = chrono::steady_clock::now();
    //binarytime = chrono::duration_cast<chrono::nanoseconds>(end - start).count();
    //cout << "Binary Search Time:" << binarytime/contacts.size() << " Nanoseconds" << endl;
    
}

template <class Comparable>
int binarySearch(vector<Comparable>arr, int l, int r, string x)
{
    while (l <= r) {
          int m = l + (r - l) / 2;
    
          // Check if x is present at mid
          if (arr[m].fullname == x)
              return m;
    
          // If x greater, ignore left half
          if (arr[m].fullname < x)
              l = m + 1;
    
          // If x is smaller, ignore right half
          else
              r = m - 1;
      }
    
      // if we reach here, then element was
      // not present
      return -1;
}

#endif /* SORT_h */
