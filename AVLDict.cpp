#ifndef _AVLDICT_CPP
#define _AVLDICT_CPP

//AVLDict.cpp
#include "AVLDict.hpp"
#include <cassert>
#include <cstdlib>//for NULL
#include <iostream>
#include <functional>

// An implementation of a dictionary ADT as an AVL tree
//
AVLDict::AVLDict() {
    root = NULL;
    count = 0;

    // Initialize array of counters for depth statistics
    depth_stats = new int[MAX_STATS]();
}

/**
* Deletes every node in the tree recursivelu
*/
void AVLDict::destructor_helper(node *x) {
    if (x == NULL) return; // Nothing to destroy.
    destructor_helper(x->left);
    destructor_helper(x->right);
    delete x->key;
    delete x;
}

/**
* Deconstructor
*/
AVLDict::~AVLDict() {
    // Clean up the tree.
    // This is most easily done recursively.
    destructor_helper(root);

    // It's not good style to put this into a destructor,
    // but it's convenient for this assignment...
    cout << "Depth Statistics for find():\n";
    for (int i = 0; i < MAX_STATS - 1; i++)
        cout << i << ": " << depth_stats[i] << endl;
    cout << "More: " << depth_stats[MAX_STATS - 1] << endl;
    delete[] depth_stats;
}

// 221 Students:  DO NOT CHANGE THIS FUNCTION
// You need to call this function from your find (or from a helper function).
// Pass in the depth in the tree that the find stopped at.
// E.g., you'd call record_stats(0) if the entire dictionary were
// a NULL tree and you did a find on it.
// You'd call record_stats(1) if the entire dictionary were a single
// node, and you did a find on that dictionary, successful or not.
// (Another way to understand this is the number of nodes on the chain
// from the root to the node where the find succeeded,
// or to a leaf if the find didn't succeed.)
void AVLDict::record_stats(int depth) {
    if (depth > MAX_STATS - 1) depth = MAX_STATS - 1;
    depth_stats[depth]++;
}

/**
* Find a specific key in the tree
 * @param key, a pointer to the element needed to be found
 * @param pred the data of the found element
 * @returns true if key was found in tree (and pred, the value corresponding to it), false if not
*/
bool AVLDict::find(MazeState *key, MazeState *&pred) {

    return find_helper(key, pred, root, 0);
}

/**
* Helper method to find a key in the tree
 * @param key, a poiinter to the element needed to be found
 * @param pred the data of the found element
 * @param temp the node to check values against
 * @param depth the depth of the node temp
 * @returns true if key was found in tree (and pred, the valur corresponding to it), false if not
*/
bool AVLDict::find_helper(MazeState *key, MazeState *&pred, node *temp, int depth) {
    if (temp == NULL) {
        record_stats(depth);
        return false;
    }

    //bst, so compare to the given node's key
    //if the key is less than the current node's key - go left
    if (key->getUniqId() < temp->key->getUniqId()) {
        depth++;
        return find_helper(key, pred, temp->left, depth);
    }
    //if the key is greater than the current node's key - go right
    else if (key->getUniqId() > temp->key->getUniqId()) {
        depth++;
        return find_helper(key, pred, temp->right, depth);
    }
    //else, they are equal - found it!
    else {
        //save the nodes value
        pred = temp->data;
        record_stats(depth + 1);
        return true;
    }
}

/**
* updates the height of a tree
 * @param x, the node to update its height
 * @returns true if height was updated, false if not
*/
bool AVLDict::update_height(node *x) {
    // TODO:  Write this function!
    if (x == NULL)
        return false;
    int childHeight = std::max(height(x->right), height(x->left)) + 1;
    // if the height of x is not the same as the height of the children + 1, update it
    if (height(x) != childHeight) {
        x->height = childHeight;
        return true;
    }
    return false;


}

/**
* rotates the subtree rooted at x to the left (RR case)
 * @param a, the root of the subtree
*/
void AVLDict::rotate_left(node *&a) {
    // "rotates" the subtree rooted at a to the left (counter-clockwise)

// 221 Students:  DO NOT CHANGE OR DELETE THE NEXT FEW LINES!!!
// We will use this code when marking to be able to watch what
// your program is doing, so if you change things, we'll mark it wrong.
#ifdef MARKING_TRACE
    std::cout << "Rotate Left: " << a->getUniqId() << std::endl;
#endif
// End of "DO NOT CHANGE" Block
// TODO:  Write this function!
    node *temp = a->right;
    a->right = temp->left;
    temp->left = a;
    update_height(a);
    update_height(temp);
    a = temp;


}

/**
* rotates the subtree rooted at x to the right (LL case)
 * @param  b, the root of the subtree
*/
void AVLDict::rotate_right(node *&b) {
    // "rotates" the subtree rooted at b to the right (clockwise)


// 221 Students:  DO NOT CHANGE OR DELETE THE NEXT FEW LINES!!!
// We will use this code when marking to be able to watch what
// your program is doing, so if you change things, we'll mark it wrong.
#ifdef MARKING_TRACE
    cout << "Rotate Right: " << b->getUniqId() << endl;
#endif
// End of "DO NOT CHANGE" Block

    // TODO:  Write this function!
    node *temp = b->left;
    b->left = temp->right;
    temp->right = b;
    update_height(b);
    update_height(temp);
    b = temp;
}

/**
* Balances the tree
 * @param a, the root of the subtree
*/
void AVLDict::balance(node *&x) {
    int heightRight = height(x->right);
    int heightLeft = height(x->left);
    int maxHeight = std::max(heightRight, heightLeft);
    int minHeight = std::min(heightRight, heightLeft);
    //if not balanced (difference is more than 1)
    if ((maxHeight - minHeight) > 1) {
        if (heightLeft > heightRight) {
            //LL case
            if (height(x->left->left) > height(x->left->right))
                rotate_right(x);
            else {
                //double rotate right
                rotate_left(x->left);
                rotate_right(x);
            }
        } else {
            //RR case
            if (height(x->right->left) < height(x->right->right))
                rotate_left(x);
            else {
                //double rotate left
                rotate_right(x->right);
                rotate_left(x);
            }
        }
    }
}

/**
* Inserts a new node into the AVL tree
 * @param temp, the node to be inserted
 * @param parent, the parent of the node to be inserted
*/
void AVLDict::insert(node *temp, node *&parent) {
    if (parent == NULL) {
        parent = temp;
        return;
    }
    //go left if less
    if (temp->key->getUniqId() < parent->key->getUniqId())
        insert(temp, parent->left);
    //go right if more
    else if (temp->key->getUniqId() > parent->key->getUniqId())
        insert(temp, parent->right);
    if (update_height(parent))
        balance(parent);
}

// You may assume that no duplicate MazeState is ever added.
/**
* addds/creates a new node in the tree
 * @param key, the key of the element to be added to the tree
 * @param pred, the data of the element to be added
*/
void AVLDict::add(MazeState *key, MazeState *pred) {

    // TODO:  Write this function!
    node *temp = new node;
    temp->key = key;
    temp->data = pred;
    temp->height = 0;
    temp->right = NULL;
    temp->left = NULL;

    insert(temp, root);


}

#endif 
