//LinkedListStack.cpp
#ifndef _LINKEDLISTSTACK_CPP
#define _LINKEDLISTSTACK_CPP

// We suggest at least these includes:
#include "LinkedListStack.hpp"
#include <cstdlib>
#include <cassert>
#include <iostream>


/**
 * Constructor: initialize member variables and do any other initialization needed (if any)
 */
LinkedListStack::LinkedListStack() {
    top = NULL;
}

/**
 * Adds an element to the linked list Stack from the head/top
 * @param elem a pointer to the MazeState element to be added to the stack.
 */
void LinkedListStack::add(MazeState *elem) {
    node *temp = new node;
    temp->data = elem;
    temp->next = top;
    top = temp;
}

/**
 * Removes the top/head elemenet of the stack (pop) if not empty
 * @returns the data of the head element that was removed
 */
MazeState *LinkedListStack::remove() {
    assert(top != NULL);
    MazeState *ret = top->data;
    node *temp = top->next;
    delete top;
    top = temp;
    return ret;
}

/**
 * Checks whether the linked list stack is empty or not
 * @returns true if empty and false if not
 */
bool LinkedListStack::is_empty() {
    return top == NULL;
}

/**
 * Deconstructor: removes all nodes from list
 */
LinkedListStack::~LinkedListStack() {
    while (top != NULL)
        remove();
}

#endif
