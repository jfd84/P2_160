//
//  Bucket.cpp
//  P2_160
//
//  Created by Joe D'Agostino on 9/19/22.
//

#include <stdio.h>
#include "Bucket.h"

//BEGIN implementation of Node class
Node::Node()
{
    word = "";
    next = NULL;
}

//END implementation of Node class

//********************************************************************

//BEGIN Bucket class implementation
Bucket::Bucket()
{
    size = 0;
    header = new Node();
    current = header;
}

Bucket::~Bucket()
{
    unsigned int currentI = 0;
    Node *thisNode = header;
    //loops through the bucket, deleting each node
    while (currentI < size)
    {
        Node *next = thisNode->next;
        delete thisNode;
        thisNode = next;
        ++currentI;
        
    }
    size = 0;
}

void Bucket::add(string word)
{
    if (size == 0){
        header->word = word;
        ++size;
        return;
    }
    Node *newNode = new Node();
    newNode->word = word;
    
    current->next = newNode;
    current = newNode;
    
    ++size;
}

void Bucket::print() const
{
    Node *tmp = new Node;
    tmp = header;
    if (size == 0)
    {
        return;
    }
    for (unsigned int i = 0; i < size; i++)
    {
        cout << tmp->word << ", ";
        tmp = tmp->next;
    }
}
//END Bucket class implementation