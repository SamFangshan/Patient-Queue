//Author: https://github.com/SamFangshan
#ifndef _skiplistpq_h
#define _skiplistpq_h

#include <iostream>
#include <string>
#include "random.h"
#include "skipnode.h"
using namespace std;

class SkipListPQ {
public:
    SkipListPQ();
    ~SkipListPQ();
    void clear();
    string frontName();
    int frontPriority();
    bool isEmpty();
    void newPatient(string name, int priority);
    string processPatient();
    void upgradePatient(string name, int oldPriority, int newPriority);
    void debug();
    friend ostream& operator <<(ostream& out, const SkipListPQ& queue);

private:
    SkipNode* QLinkedSkipNodes;
    void safeInsert(SkipNode*& node, int index, int level, SkipNode*& newP);
    SkipNode* getSkipListPQ() const;

};

ostream& operator <<(ostream& out, const SkipListPQ& queue);

#endif
