#ifndef _DOUBLEHASHDICT_CPP
#define _DOUBLEHASHDICT_CPP

//DoubleHashDict.cpp
#include "DoubleHashDict.hpp"
#include <cassert>
#include <cstdlib>//for NULL
#include <iostream>

// An implementation of a dictionary ADT as hash table with double hashing
//

const int DoubleHashDict::primes[] = {53, 97, 193, 389, 769, 1543, 3079,
                                      6151, 12289, 24593, 49157, 98317, 196613, 393241, 786433, 1572869,
                                      3145739, 6291469, 12582917, 25165843, 50331653, 100663319,
                                      201326611, 402653189, 805306457, 1610612741, -1};
// List of good primes for hash table sizes from
// http://planetmath.org/goodhashtableprimes
// The -1 at the end is to guarantee an immediate crash if we run off
// the end of the array.
const int DoubleHashDict::notprimes[] = {100, 300, 1000, 3000, 10000,
                                         30000, 100000, 300000, 1000000, 3000000, 10000000, 30000000,
                                         100000000, 300000000, 1000000000, -1};
// List of bad sizes for the hash table and this hash function...


/**
 * Constructor: initialize member variables and do any other initialization needed (if any)
 */
DoubleHashDict::DoubleHashDict() {
    size_index = 0;
    size = primes[size_index];
    table = new bucket[size](); // Parentheses force initialization to 0
    number = 0;
    // Initialize the array of counters for probe statistics
    probes_stats = new int[MAX_STATS]();
}

/**
* Deconstructor - delete all table entries
*/
DoubleHashDict::~DoubleHashDict() {
    // Delete all table entries...
    for (int i = 0; i < size; i++) {
        if (table[i].key != NULL) {
            delete table[i].key;
            // Don't delete data here, to avoid double deletions.
        }
    }
    // Delete the table itself
    delete[] table;
    // It's not good style to put this into a destructor,
    // but it's convenient for this assignment...
    cout << "Probe Statistics for find():\n";
    for (int i = 0; i < MAX_STATS - 1; i++)
        cout << i << ": " << probes_stats[i] << endl;
    cout << "More: " << probes_stats[MAX_STATS - 1] << endl;
    delete[] probes_stats;
}

// 221 Students:  DO NOT CHANGE THIS FUNCTION
// You need to call this function from your find (or from a helper function).
// Pass in the number of probes that you needed for that call to find.
// The number of probes should be the total number of buckets that you
// look at:  e.g., on an unsuccessful call to find, you should include
// the empty bucket at the end.
void DoubleHashDict::record_stats(int probes) {
    if (probes > MAX_STATS - 1) probes = MAX_STATS - 1;
    probes_stats[probes]++;
}

/**
* 1st hash function: Hashes a string to a certain index in the table
 * @param keyID the string to be hashed
 * @returns number that corresponds to a table index
*/
int DoubleHashDict::hash1(string keyID) {
    int h = 0;
    for (int i = keyID.length() - 1; i >= 0; i--) {
        h = (keyID[i] + 31 * h) % size;
    }
// 221 Students:  DO NOT CHANGE OR DELETE THE NEXT FEW LINES!!!
// We will use this code when marking to be able to watch what
// your program is doing, so if you change things, we'll mark it wrong.
#ifdef MARKING_TRACE
    std::cout << "Hash 1:  " << keyID << " to " << h << std::endl;
#endif
// End of "DO NOT CHANGE" Block
    return h;
}

/**
* 2nd hash function: Hashes a string to a certain index in the table
 * @param keyID the string to be hashed
 * @returns number that corresponds to a table index
*/
int DoubleHashDict::hash2(string keyID) {
    int h = 0;
    for (int i = keyID.length() - 1; i >= 0; i--) {
        h = (keyID[i] + 29 * h) % size;
    }
    // Make sure second hash is never 0 or size
    h = h / 2 + 1;

// 221 Students:  DO NOT CHANGE OR DELETE THE NEXT FEW LINES!!!
// We will use this code when marking to be able to watch what
// your program is doing, so if you change things, we'll mark it wrong.
#ifdef MARKING_TRACE
    std::cout << "Hash 2:  " << keyID << " to " << h << std::endl;
#endif
// End of "DO NOT CHANGE" Block
    return h;
}

/**
* 3rd hash function: Hashes a string to a certain index in the table
 * @param keyID the string to be hashed
 * @returns number that corresponds to a table index
*/
int DoubleHashDict::hash3(string keyID) {
    int h = 0;
    for (int i = keyID.length() - 1; i >= 0; i--) {
        h = (keyID[i] + 29 * h) % size;
    }
    // Make sure second hash is never 0 or size
    h = h / 2 + 1;

    while ((h % 2 == 0) || (h % 3 == 0) || (h % 5 == 0)) h++;

// 221 Students:  DO NOT CHANGE OR DELETE THE NEXT FEW LINES!!!
// We will use this code when marking to be able to watch what
// your program is doing, so if you change things, we'll mark it wrong.
#ifdef MARKING_TRACE
    std::cout << "Hash 3:  " << keyID << " to " << h << std::endl;
#endif
// End of "DO NOT CHANGE" Block
    return h;
}

/**
* creates a bigger table, and rehashes all elements of old table to the new one
*/
void DoubleHashDict::rehash() {
// 221 Students:  DO NOT CHANGE OR DELETE THE NEXT FEW LINES!!!
// And leave this at the beginning of the rehash() function.
// We will use this code when marking to be able to watch what
// your program is doing, so if you change things, we'll mark it wrong.
#ifdef MARKING_TRACE
    std::cout << "*** REHASHING " << size;
#endif
// End of "DO NOT CHANGE" Block
    // TODO:  Your code goes here...

    int oldSize = size;
    size_index++;
    size = primes[size_index];
    bucket *oldTable = table;
    table = new bucket[size]();

    for (int i = 0; i < oldSize; i++) {
        //dont rehash non existent items
        if (oldTable[i].key == NULL)
            continue;
        else {
            //rehashing
            string id = oldTable[i].key->getUniqId();
            int hashIndex = hash1(id);
            int hashIndex2 = hash2(id);
            while (table[hashIndex].key != NULL) {
                //double hashing
                hashIndex = hashIndex + hashIndex2;
                hashIndex %= size;
            }
            table[hashIndex] = oldTable[i];
        }
    }

    delete[] oldTable;
    // Keep a pointer to the old table.

    // Get a bigger table

    // Rehash all the data over

    // No need to delete the data, as all copied into new table.


// 221 Students:  DO NOT CHANGE OR DELETE THE NEXT FEW LINES!!!
// And leave this at the end of the rehash() function.
// We will use this code when marking to be able to watch what
// your program is doing, so if you change things, we'll mark it wrong.
#ifdef MARKING_TRACE
    std::cout << " to " << size << " ***\n";
#endif
// End of "DO NOT CHANGE" Block
}

/**
* Find a specific key in the table
 * @param key, a pointer to the element needed to be found
 * @param pred the data of the found element
 * @returns true if key was found in table (and pred, the valur corresponding to it), false if not
*/
bool DoubleHashDict::find(MazeState *key, MazeState *&pred) {
    // TODO:  Your code goes here...
    int probes = 1;
    string id = key->getUniqId();
    int hashIndex = hash1(id);
    int hashIndex2 = hash2(id);
    while (table[hashIndex].key != NULL) {
        if (table[hashIndex].key->getUniqId() == key->getUniqId()) {
            pred = table[hashIndex].data;
            record_stats(probes);
            return true;
        }
        hashIndex = hashIndex + hashIndex2;
        hashIndex %= size;
        probes++;
        if (probes > size) {
            break;
        }
    }
    record_stats(probes);
    return false;


}

// You may assume that no duplicate MazeState is ever added.
/**
* Adds a new element to the table
 * @param key a pointer to the key of the element to be added
 * @param pred a pointer to the data of the element to be added
*/
void DoubleHashDict::add(MazeState *key, MazeState *pred) {

    // Rehash if adding one more element pushes load factor over 3/4
    if (4 * (number + 1) > 3 * size)
        rehash();
    int probes = 1;
    string id = key->getUniqId();
    int hashIndex = hash1(id);
    int hashIndex2 = hash2(id);
    bool isValid = true;

    while (table[hashIndex].key != NULL) {
        //double hashing, use another hash function
        hashIndex = hashIndex + hashIndex2;
        hashIndex %= size;
        probes++;
        //tried the whole array, should abort
        if (probes > size) {
            return;
        }
    }
        //if we're here, table[hashIndex] is null
        table[hashIndex].key = key;
        table[hashIndex].data = pred;
        number++;



}

#endif 
