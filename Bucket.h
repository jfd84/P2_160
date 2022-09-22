//
//  Bucket.h
//  P2_160
//
//  Created by Joe D'Agostino on 9/19/22.
//

#ifndef Bucket_h
#define Bucket_h

#include <stdio.h>
#include "Node.h"
#include <iostream>

using namespace std;

class Bucket {
public:
    Bucket();
    virtual ~Bucket();
    
    void add(string &str);
    
    void print() const;
    
    Node* header;
    Node* current;
    unsigned int size;
}; //END Bucket Declaration

#endif /* Bucket_h */
