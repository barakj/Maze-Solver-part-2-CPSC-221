#ifndef _UNSORTEDPRIORITYQUEUE_CPP
#define _UNSORTEDPRIORITYQUEUE_CPP

//UnsortedPriorityQueue.cpp
#include "UnsortedPriorityQueue.hpp"
#include <cassert>
#include <cstdlib>//for NULL
#include <iostream>

// A naive implementation of a priority queue, using
// a vector and searching for the max for each remove operation.
//
// Priority is based on the each MazeState's getBadness() method.

UnsortedPriorityQueue::UnsortedPriorityQueue() {
    // empty, nothing to do
}

UnsortedPriorityQueue::~UnsortedPriorityQueue() {
    // no clean-up to do, since list is not dynamically allocated
}

/**
 * Adds an element to the unsorted priority queue
 * @param elem a pointer to the MazeState element to be added to the heap priority queue
 */
void UnsortedPriorityQueue::add(MazeState *elem) {
    list.push_back(elem);
}

/**
 * Finds and Removes the minimum element in the heap(unsorted)
 * @returns the removed element (minimum)
 */
MazeState *UnsortedPriorityQueue::remove() {
    if (list.size() < 1)
        return (MazeState *) NULL;

    int min_index = 0;
    for (int i = 0; i < (int) list.size(); i++) {
        if (list[i]->getBadness() < list[min_index]->getBadness())
            min_index = i;
    }

    MazeState *ret = list[min_index];
    list.erase(list.begin() + min_index); // remove list[min_index]
    return ret;
}

/**
 * Checks whether the unsorted priority queue is empty or not
 * @returns true if empty and false if not
 */
bool UnsortedPriorityQueue::is_empty() {
    return (list.size() == 0);
}

#endif 
