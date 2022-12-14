//
//  ChainTable.cpp
//  P2_160
//
//  Created by Joe D'Agostino on 9/20/22.
//

#include "ChainTable.h"

ChainTable::ChainTable(unsigned int dSize, unsigned int iSize)
{
    dictSize = dSize;
    inputSize = iSize;
    arr = new Bucket[dSize];
    inputDuration = 0;
}

unsigned int ChainTable::getKey(const string &word) const
{
    unsigned int key = 0;
    for (char i : word) { key = 37 * (key + short(i)); }
    return key % dictSize;
}

//Uses an instance of ifstream to read file data and fill the array
long ChainTable::loadTable(const string& fileName) const
{
    ifstream inFile;
    inFile.open(fileName.c_str());
    string tempWord;
    unsigned int key;
    chrono::high_resolution_clock::time_point start = chrono::high_resolution_clock::now(); //START
    while(inFile >> tempWord)
    {
        key = getKey(tempWord);
        arr[key].add(tempWord);
    }
    chrono::high_resolution_clock::time_point stop = chrono::high_resolution_clock::now(); //STOP
    long time = chrono::duration_cast<chrono::nanoseconds>(stop - start).count();
    //Closes stream
    inFile.close();
    return time;
}

unsigned int ChainTable::readInput(const string& fileName)
{

    ifstream inFile;
    inFile.open(fileName.c_str());
    string tempWord;
    string tempArray[inputSize];

    int splitIndex;
    int doubleIndex;
    string splitWord1;
    string splitWord2;
    int i = 0;

    //Parses through the input file, cleans up issues with strings, and stores each string to a temporary array.
    while (inFile >> tempWord)
    {
        splitIndex = 0;
        doubleIndex = 0;

        if (tempWord.empty()) { continue; }
        while (ispunct(tempWord.back())) { tempWord.pop_back(); if (tempWord.empty()) { break; } }
        if (tempWord.empty()) { continue; }
        while (ispunct(tempWord.front())) {tempWord.erase(0, 1); if (tempWord.empty()) { break; } }
        if (tempWord.empty()) { continue; }
        if (tempWord.back() == 's')
        {
            if (ispunct(tempWord[tempWord.length()-2])) { tempWord.erase(tempWord.length()-2,2); }
        }
        if (tempWord.empty()) { continue; }
        if (tempWord.front() >='A' && tempWord.front() <= 'Z')
        {
            tempWord[0] = char(tempWord[0] + 32);
            if (tempWord[1] >='A' && tempWord[1] <= 'Z')
            {
                for(unsigned int j = 1; j < tempWord.length(); ++j) { tempWord[j] = char(tempWord[j] + 32); }
            }
        }
        splitIndex = int(tempWord.find('-'));
        if (splitIndex != -1)
        {
            doubleIndex = int(tempWord.find("--"));
            splitWord1 = tempWord.substr(0, splitIndex);
            if (doubleIndex != -1) { splitWord2 = tempWord.substr(splitIndex+2, tempWord.length() - splitIndex-1); }
            else { splitWord2 = tempWord.substr(splitIndex+1, tempWord.length() - splitIndex-2); }
            if (splitWord1.empty()) { continue; }
            while (ispunct(splitWord1.back())) { splitWord1.pop_back();  if (splitWord1.empty()) { break; } }
            if (splitWord2.empty()) { continue; }
            while (ispunct(splitWord2.back())) { splitWord2.pop_back();  if (splitWord2.empty()) { break; } }
            if (splitWord1.empty()) { continue; }
            while (ispunct(splitWord1.front())) { splitWord1.erase(0, 1); if(splitWord1.empty()) { break; } }
            if (splitWord2.empty()) { continue; }
            while (ispunct(splitWord2.front())) { splitWord2.erase(0, 1); if(splitWord2.empty()) { break; } }

            if (isdigit(splitWord1.front())) { continue; }
            if (isdigit(splitWord2.front())) { continue; }

            tempArray[i] = splitWord1;
            tempArray[i+1] = splitWord2;
            i += 2;
        }
        else {
            if (tempWord.empty()) { continue; }
            if (isdigit(tempWord.front())) { continue; }
            tempArray[i] = tempWord;
            ++i;
        }
    }
    cout << "ACTUAL SIZE: " << i << endl;
    inFile.close();

    //Creates variables necessary for operations in the proceeding while loop
    string thisWord;
    unsigned int testKey;
    unsigned int bucketSize;
    Node *thisNode;
    unsigned int numIncorrect = 0;
    bool found;
    //Parses through each word in the file, and check if it exists in the hash table
    chrono::high_resolution_clock::time_point start = chrono::high_resolution_clock::now();  //START
    for (unsigned int i = 0; i < inputSize; ++i)
    {
        if (tempArray[i].empty()) { continue; }
        thisWord = tempArray[i];

        //If the word is spelled correctly, the key should reveal the index of the hashTable
        testKey = getKey(thisWord);
        thisNode = arr[testKey].header;
        bucketSize = arr[testKey].size;
        found = false;
        for (unsigned int w = 0; w < bucketSize; ++w)
        {
            if (thisWord == thisNode->word)
            {
                found = true;
                break;
            }
            thisNode = thisNode->next;
        }
        if (!found) { ++numIncorrect; }
    }
    chrono::high_resolution_clock::time_point stop = chrono::high_resolution_clock::now();  //STOP
    long time = chrono::duration_cast<chrono::nanoseconds>(stop - start).count();
    inputDuration = time;

    return numIncorrect;
}

//Iterates through array, prints each element
void ChainTable::print()
{
    for (unsigned int i = 0; i < dictSize; ++i)
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
    for (unsigned int i = 0; i < dictSize; ++i)
    {
        if (arr[i].size == 0)
        {
            ++numEmpty;
        }
    }
    cout << "Number of Empty Buckets: " << numEmpty << " out of " << dictSize << endl << endl;
}
