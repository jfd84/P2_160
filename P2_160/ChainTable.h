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
#include <cctype>

#include "Bucket.h"
using namespace std;

class ChainTable {
public:
    //Creates an array with the size specified in the first line of the file
    ChainTable(unsigned int dSize, unsigned int iSize);
    
    unsigned int getKey(const string &word) const;
    
    //Creates an instance of fstream to read file data and fill the table
    long loadTable(const string& fileName) const;
    
    //Iterates through array, prints the number of empty buckets (for analysis of hash function)
    unsigned int readInput(const string& fileName);
    
    void numEmpty();
    
    
    //Iterates through array, prints each element
    void print();
    
    unsigned int dictSize;
    unsigned int inputSize;
    Bucket *arr;
    long inputDuration;
    
}; //END ChainTable Declaration


#endif /* ChainTable_h */
