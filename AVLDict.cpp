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

void AVLDict::destructor_helper(node *x) {
    if (x == NULL) return; // Nothing to destroy.
    destructor_helper(x->left);
    destructor_helper(x->right);
    delete x->key;
    delete x;
}

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


/*
bool AVLDict::find(MazeState *key, MazeState *&pred) {
  // TODO:  Write this function!
  
  node* temp = root;
  if(root == NULL){
    record_stats(count);
    return false;
  }
  
  count++;

  if(key->getUniqId() > temp->key->getUniqId()){
    temp = temp->right;
  }
  else if(key->getUniqId() < temp->key->getUniqId()){
    temp = temp->left;
  }
  else{
    record_stats(count);
    pred = temp->data;
    return true;
  }
  find(key, pred);
  return false;

}
*/



bool AVLDict::find(MazeState *key, MazeState *&pred) {

    return find_helper(key, pred, root, 0);

}

bool AVLDict::find_helper(MazeState *key, MazeState *&pred, node *temp, int depth) {
    if (temp == NULL) {
        record_stats(depth);
        return false;
    }

    if (key->getUniqId() < temp->key->getUniqId()) {
        depth++;
        return find_helper(key, pred, temp->left, depth);
    } else if (key->getUniqId() > temp->key->getUniqId()) {
        depth++;
        return find_helper(key, pred, temp->right, depth);
    } else {
        pred = temp->data;
        record_stats(depth + 1);
        return true;
    }
}

bool AVLDict::update_height(node *x) {
    // TODO:  Write this function!
    if (x == NULL)
        return false;
    int childHeight = std::max(height(x->right), height(x->left)) + 1;
    if (height(x) != childHeight) {
        x->height = childHeight;
        return true;
    }
    return false;


}

void AVLDict::rotate_left(node *&a) {
    // "rotates" the subtree rooted at a to the left (counter-clockwise)

// 221 Students:  DO NOT CHANGE OR DELETE THE NEXT FEW LINES!!!
// We will use this code when marking to be able to watch what
// your program is doing, so if you change things, we'll mark it wrong.
#ifdef MARKING_TRACE
    std::cout << "Rotate Left: " << a->getUniqId() << std::endl;
#endif
// End of "DO NOT CHANGE" Block

    node *temp = a->right;
    a->right = temp->left;
    temp->left = a;
    update_height(a);
    update_height(temp);
    a = temp;
    // TODO:  Write this function!

}

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

void AVLDict::balance(node *&x) {
    int heightRight = height(x->right);
    int heightLeft = height(x->left);
    int maxHeight = std::max(heightRight, heightLeft);
    int minHeight = std::min(heightRight, heightLeft);
    //if not balanced
    if ((maxHeight - minHeight) > 1) {
        if (heightLeft > heightRight) {
            if (height(x->left->left) > height(x->left->right))
                rotate_right(x);
            else {
                //double rotate right
                rotate_left(x->left);
                rotate_right(x);
            }
        } else {
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


void AVLDict::insert(node *temp, node *&parent) {
    if (parent == NULL) {
        parent = temp;
        return;
    }
    if (temp->key->getUniqId() < parent->key->getUniqId())
        insert(temp, parent->left);
    else if (temp->key->getUniqId() > parent->key->getUniqId())
        insert(temp, parent->right);
    if (update_height(parent))
        balance(parent);
}

// You may assume that no duplicate MazeState is ever added.
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
