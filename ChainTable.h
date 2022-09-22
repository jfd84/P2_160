//
//  ChainTable.h
//  P2_160
//
//  Created by Joe D'Agostino on 9/20/22.
//

#ifndef ChainTable_h
#define ChainTable_h

#include <cstdio>
#include <iostream>
#include <fstream>
#include <chrono>

#include "Bucket.h"
using namespace std;

class ChainTable {
public:
    //Creates an array with the size specified in the first line of the file
    ChainTable(unsigned int dictSize);
    
    unsigned int getKey(const string &word);
    
    //Creates an instance of fstream to read file data and fill the table
    long loadTable(string fileName);
    
    //Iterates through array, prints the number of empty buckets (for analysis of hash function)
    unsigned int readInput(string fileName);
    
    void numEmpty();
    
    
    //Iterates through array, prints each element
    void print();
    
    unsigned int size;
    Bucket *arr;
    
}; //END ChainTable Declaration


#endif /* ChainTable_h */
