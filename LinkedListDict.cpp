#ifndef _LINKEDLISTDICT_CPP
#define _LINKEDLISTDICT_CPP

//LinkedListDict.cpp
#include "LinkedListDict.hpp"
#include <cassert>
#include <cstdlib>//for NULL
#include <iostream>

// An implementation of a dictionary ADT as an unsorted linked list.
//
/**
 * Constructor: initializing the root node of the linked list
 */
LinkedListDict::LinkedListDict() {
    root = NULL;
}
/**
 * Deconstructor: deleting every node in the linked list
 */
LinkedListDict::~LinkedListDict() {
    // Clean up linked list.
    node *rest = root;
    while (rest != NULL) {
        node *temp = rest;
        rest = rest->next;
        delete temp->key;
        // delete temp->data; // Don't delete this here, to avoid multiple deletes.
        delete temp;
    }
}

/**
 * Find a certain node in the list by key
 * @param key the element to be found
 * @param pred the data of the node found (saved by reference)
 */
bool LinkedListDict::find(MazeState *key, MazeState *&pred) {
    node *temp = root; // A temporary pointer to sequentially walk the list.

    while (temp != NULL) {
        if (key->getUniqId() == temp->key->getUniqId()) {
            pred = temp->data; // Found it!  Put the result in pred to pass to caller.
            return true;
        }
        temp = temp->next; // Else try the next node in the list...
    }

    return false; // Did not find the key.
}

/**
 * Adds an element to the linked list, from the beginning/top (pushes to start of list)
 * @param key the key of the node to be added
 * @param pred the data of the node to be added
 */
void LinkedListDict::add(MazeState *key, MazeState *pred) {
    node *temp = new node();
    temp->key = key;
    temp->data = pred;
    temp->next = root;
    root = temp;
    return;
}

#endif 
