#ifndef _linkedpq_h
#define _linkedpq_h

#include <iostream>
#include <string>
#include "pnode.h"
using namespace std;

class LinkedPQ {
public:
    LinkedPQ();
    ~LinkedPQ();
    void clear();
    string frontName() const;
    int frontPriority() const;
    bool isEmpty();
    void newPatient(string name, int priority);
    string processPatient();
    void upgradePatient(string name, int oldPriority, int newPriority);
    void debug();
    friend ostream& operator <<(ostream& out, const LinkedPQ& queue);

private:
    PNode* QLinkedNodes;
    PNode* findPatient(string name, int priority, bool& isFirst) const;
    PNode* getLinkedPQ() const;

};

ostream& operator <<(ostream& out, const LinkedPQ& queue);

#endif
