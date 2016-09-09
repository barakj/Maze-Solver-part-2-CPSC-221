//HeapPriorityQueue.cpp - COMMENT THIS
#ifndef _HEAPPRIORITYQUEUE_CPP
#define _HEAPPRIORITYQUEUE_CPP

#include "HeapPriorityQueue.hpp"
#include <algorithm> // C++ std:: heap operations
#include <cassert>
#include <cstdlib>//for NULL
#include <iostream>

// Quick-and-dirty kludge to allow using STL heap operators...
bool compareBadness(MazeState *a, MazeState *b) {
    // This is backwards because C++ std heap is a max heap.
    return a->getBadness() > b->getBadness();
}

HeapPriorityQueue::HeapPriorityQueue() {
    // Empty... nothing needs to be done.
}

HeapPriorityQueue::~HeapPriorityQueue() {
    // no clean-up to do, since the heap is not dynamically allocated
}

/**
 * Adds an element to the vector heap
 * @param elem a pointer to the MazeState element to be added to the heap priority queue.
 */
void HeapPriorityQueue::add(MazeState *elem) {
    heap.push_back(elem);
    std::push_heap(heap.begin(), heap.end(), compareBadness);
}

/**
 * Removes the minimum element in the heap - the root, but still keeping heap property (swapping down)
 * @returns the removed element
 */
MazeState *HeapPriorityQueue::remove() {
    assert(!is_empty());

    // Grab the element to return and move the last element to the top.
    std::pop_heap(heap.begin(), heap.end(), compareBadness);
    MazeState *result = heap.back();
    heap.pop_back();

    return result;
}

/**
 * Checks whether the heap priority queue is empty or not
 * @returns true if empty and false if not
 */
bool HeapPriorityQueue::is_empty() {
    return (heap.size() == 0);
}

#endif
