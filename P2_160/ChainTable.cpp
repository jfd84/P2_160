//
//  ChainTable.cpp
//  P2_160
//
//  Created by Joe D'Agostino on 9/20/22.
//

#include <stdio.h>
#include "ChainTable.h"


ChainTable::ChainTable(unsigned int dictSize)
{
    size = dictSize;
    arr = new Bucket[size];
}

unsigned int ChainTable::getKey(const string &word)
{
    unsigned int key = 0;
    short wordLen = word.length();
    
    //for (char i = word.begin(); i != )
    
    for(short i = 0; i < wordLen; ++i)
    {
        key = 37 * key + short(word[i]);
    }
    return key % size;
}



//Uses an instance of fstream to read file data and fill the array
long ChainTable::loadTable(string fileName)
{
    ifstream inFile;
    inFile.open(fileName.c_str());
    string tempWord;
    unsigned int key = 0;
    
    //auto start = chrono::high_resolution_clock::now();  //START
    chrono::high_resolution_clock::time_point t1 = chrono::high_resolution_clock::now();
    while (inFile >> tempWord)
    {
        key = getKey(tempWord);
        arr[key].add(tempWord);
    }
    chrono::high_resolution_clock::time_point t2 = chrono::high_resolution_clock::now();
    
    //auto end = chrono::high_resolution_clock::now();  //END
    //chrono::duration<double> time_span = chrono::duration_cast<chrono::duration<double>>(t2 - t1);
    
    long time = chrono::duration_cast<chrono::nanoseconds>(t2 - t1).count();

    //long time = chrono::duration_cast<chrono::nanoseconds>(end - start).count();
    
    //Closes stream
    inFile.close();
    return time;
}

//Iterates through array, prints each element
void ChainTable::print()
{
    for (unsigned int i = 0; i < size; ++i)
    {
        cout << "#" << i << ": " << arr[i].size << "  ****  ";
        arr[i].print();
        cout << endl;
    }
    cout << endl << endl;
}

//Iterates through array, prints the number of empty buckets (for analysis of hash function)
void ChainTable::numEmpty()
{
    unsigned int numEmpty = 0;
    for (unsigned int i = 0; i < size; ++i)
    {
        if (arr[i].size == 0)
        {
            ++numEmpty;
        }
    }
    cout << "Number of Empty Buckets: " << numEmpty << " out of " << size << endl << endl;
}


unsigned int ChainTable::readInput(string fileName)
{
    unsigned int numIncorrect = 0;
    bool found;
    fstream inFile;
    inFile.open(fileName.c_str());
    
    string thisWord;
    unsigned int thisKey;
    Node *thisNode = new Node();
    //Parses through each word in the file
    auto start = chrono::steady_clock::now();
    while (inFile >> thisWord)
    {
        //If the word is spelled correctly, the key should reveal the index of the hashTable
        thisKey = getKey(thisWord);
        thisNode = arr[thisKey].header;
        found = false;
        for(unsigned int i = 0; i < arr[thisKey].size; ++i)
        {
            if (thisWord == thisNode->word)
            {
                found = true;
                break;
            }
            thisNode = thisNode->next;
        }
        if (found == false) { numIncorrect+=1; }
    }
    auto end = chrono::steady_clock::now();
    long time = chrono::duration_cast<chrono::nanoseconds>(end - start).count();
    cout << "TIME TO CHECK INPUT: " << time << " nanoseconds" << endl; //REMOVE
    return numIncorrect;
}
