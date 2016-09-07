#ifndef _ARRAYSTACK_CPP
#define _ARRAYSTACK_CPP

//ArrayStack.cpp

#include "ArrayStack.hpp"
//#include <cstdlib> //for NULL
#include <cassert>
#include <iostream>
//using namespace std;

/**
 * Constructor: initialize member variables and do any other initialization needed (if any)
 */
ArrayStack::ArrayStack() : top(0) {
    array = new MazeState *[INIT_SIZE];
    capacity = INIT_SIZE;
}

/**
 * Adds an element to the Array Stack (push)
 * @param elem a pointer to the MazeState element to be added to the stack.
 */
void ArrayStack::add(MazeState *elem) {
    //make sure enough space in the array
    ensure_capacity(top + 1);
    //LIFO
    array[top] = elem;
    top++;
}

/**
 * Removes the top elemenet of the stack (pop) if not empty
 * @returns the top element that was removed
 */
MazeState *ArrayStack::remove() {
    assert(!is_empty());
    top--;
    return array[top];
}

/**
 * Checks whether the array stack is empty or not
 * @returns true if empty and false if not
 */
bool ArrayStack::is_empty() {
    return top == 0;
}

/**
* ensure the array stack is big enough to contain all elements, if not it will grow the array
* @param n the number of elements the array needs to be able to contain
*/
void ArrayStack::ensure_capacity(int n) {
    if (capacity < n) {
        // Make plenty of room.
        int target_capacity = (n > 2 * capacity + 1) ? n : (2 * capacity + 1);

        // Set the current array aside and make room for the new one.
        MazeState **oldarray = array;
        array = new MazeState *[target_capacity];

        // Copy each element of the old array over.
        for (int i = 0; i < top; i++) {
            array[i] = oldarray[i];
        }

        capacity = target_capacity;
        delete[] oldarray;
    }
}

/**
* Deconstructor
*/
ArrayStack::~ArrayStack() {
    delete[] array;
}

#endif
