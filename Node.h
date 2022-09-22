//
//  Node.h
//  P2_160
//
//  Created by Joe D'Agostino on 9/19/22.
//

#ifndef Node_h
#define Node_h

#include <stdio.h>
#include <string>

using namespace std;

class Node {
public:
    Node();
    Node(string &word);
    Node* next;
    string word;
};


#endif /* Node_h */
