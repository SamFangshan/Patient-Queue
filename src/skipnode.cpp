/*
 * CS 106B/X Patient Queue
 * This file implements the members of the SkipNode structure.
 * See patientnode.h for declaration and documentation of each member.
 *
 * Please do not modify this provided file. Your turned-in files should work
 * with an unmodified version of all provided code files.
 *
 * @author Marty Stepp
 * @version 2017/10/31
 */

#include "skipnode.h"
#include <iostream>
#include <sstream>
#include "error.h"
#include "hashcode.h"

SkipNode::SkipNode(std::string name, int priority, int level) {
    if (level < 1) {
        error("level must be 1 or greater");
    }
    this->name = name;
    this->priority = priority;
    ensureLevel(level);
}

void SkipNode::ensureLevel(int level) {
    while (nexts.size() < level) {
        nexts.add(nullptr);
    }
}

int SkipNode::level() const {
    return nexts.size();
}

SkipNode* SkipNode::next(int index) const {
    return nexts[index];
}

std::ostream& operator <<(std::ostream& out, const SkipNode& node) {
    return out << node.priority << ":" << node.name;
}

void printSkipNode(const SkipNode& node) {
    printSkipNode(&node);
}

void printSkipNode(const SkipNode* const node) {
    // debug print each level of the skip list
    // (Note: If this function is crashing for you, it probably means that
    // your linked list levels are corrupted, point to freed memory, or other
    // such things.)
    if (!node) {
        std::cout << "nullptr" << std::endl;
    } else {
        for (int i = node->nexts.size() - 1; i >= 0; i--) {
            std::cout << " " << i << ": ";
            const SkipNode* curr = node;
            while (curr && curr->nexts[i]) {
                std::cout << " --> " << curr->nexts[i]->priority << ":" << curr->nexts[i]->name;
                curr = curr->nexts[i];
            }
            std::cout << " /" << std::endl;
        }
    }
}
