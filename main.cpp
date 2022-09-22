//
//  main.cpp
//  P2_160
//
//  Created by Joe D'Agostino on 9/19/22.
//

#include <cstdio>
#include <iostream>
#include <fstream>
#include <cmath>
#include <chrono>
#include "ChainTable.h"

using namespace std;

//int main(int argc, const char * argv[])
int main() {

    //Ensures that an argument (path for dictionary) was passed. If not, requests run time input
    string dictName = "hello";
    //string dictName = argv[1];
    
    //Opens stream of file
    ifstream inFile;
    unsigned int dictSize = 0;
    inFile.open(dictName.c_str());
    //Quickly loops through file to determine total size
    string tempWord;
    while(inFile)
    {
        getline(inFile, tempWord);
        ++dictSize;
    }
    //Closes stream
    inFile.close();
    
    
    //Multiplies dictSize by 1.33 and rounds up, to ensure that the load is not < 0.75
    dictSize = ceil(dictSize * 1.33);
    //Makes sure that dictSize is not an even number
    if (dictSize % 2 != 0) { ++dictSize; }
    
    //Creates "chain" an instance of the ChainTable class
    ChainTable chain(dictSize);
    //Calls the loadTable() function of the ChainTable class, which returns time taken to construct
    
    long time = chain.loadTable(dictName);
    
    //chain.print(); //REMOVE
    cout << "TIME TO LOAD: " << time << " nanoseconds" << endl; //REMOVE
    chain.numEmpty(); //REMOVE

    //Creates a string to store the second argument passed
    string inputName = "ehhlo";
    //string inputName = argv[2];
    unsigned int numIncorrect = chain.readInput(inputName);
    cout << "# Misspelled: " << numIncorrect << endl;

    return 0;
}
