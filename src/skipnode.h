/*
 * CS 106B/X Patient Queue
 * This file declares the SkipNode structure.
 * Each SkipNode structure represents a single node in a linked list for a
 * priority queue, storing a string of data, an int of priority, and
 * a vector of pointers to next nodes at various levels (where each pointer
 * in the vector might be nullptr if there is no next node at that level).
 *
 * Nodes can be printed to the console using the << operator.
 * This is not the same as printing a pointer to a node, which would just
 * print the node's memory address as a hexadecimal integer.
 *
 * Please do not modify this provided file. Your turned-in files should work
 * with an unmodified version of all provided code files.
 *
 * @author Marty Stepp
 * @version 2017/10/31
 */

#ifndef _skipnode_h
#define _skipnode_h

#include <iostream>
#include <string>
#include "vector.h"

struct SkipNode {
public:
    std::string name;
    int priority;
    Vector<SkipNode*> nexts;   // vector of pointers to next nodes at each level; each is nullptr if absent

    /*
     * Constructs a new node storing the given name, priority, and level.
     * The node's vector of next pointers will be initialized with 'level'
     * copies of nullptr.
     */
    SkipNode(std::string name = "", int priority = 0, int level = 1);

    /*
     * Makes sure that this node's next vector contains at least 'level'
     * elements in it.
     * If it does not, adds nullptr until it reaches the proper size.
     * If it already contains more than this many children, does nothing.
     */
    void ensureLevel(int level);

    /*
     * Returns the level of this node, which is the same as
     * the size of its vector of next pointers.
     */
    int level() const;

    /*
     * Returns the element of the 'next' vector at the given index.
     * This is just for convenience; you can just access the vector directly if you prefer.
     * Most common usage is to pass no index at all and get the 0'th element,
     * which is a bit like saying ->next on a normal linked list node.
     * Note that the next value could be nullptr.
     * Throws an error if you pass an index that is out of bounds.
     */
    SkipNode* next(int index = 0) const;
};

/*
 * Overloaded operator to print a node to an output stream for debugging.
 */
std::ostream& operator <<(std::ostream& out, const SkipNode& node);

/*
 * Helper functions to print debugging information about a skip list.
 * It can be passed by pointer or reference.
 */
void printSkipNode(const SkipNode& node);
void printSkipNode(const SkipNode* const node);

#endif
