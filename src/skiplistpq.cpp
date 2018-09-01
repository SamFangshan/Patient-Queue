#include "skiplistpq.h"

/* creat an empty SkipListPQ pointing to a front node
 */
SkipListPQ::SkipListPQ() {
    QLinkedSkipNodes = new SkipNode("front");
}

/* free up all memory occupied by all nodes of SkipListPQ
 */
SkipListPQ::~SkipListPQ() {
    SkipNode* node = QLinkedSkipNodes;
    while (node != nullptr) {
        SkipNode* obj = node;
        node = node->nexts[0];
        delete obj;
    }
}

/* free up all memory occupied by all nodes of SkipListPQ other than the front
 */
void SkipListPQ::clear() {
    while (QLinkedSkipNodes->nexts[0] != nullptr) {
        SkipNode* obj = QLinkedSkipNodes->nexts[0];
        QLinkedSkipNodes->nexts[0] = QLinkedSkipNodes->nexts[0]->nexts[0];
        delete obj;
    }
}

/* get the first patient's name
 */
string SkipListPQ::frontName() {
    if (QLinkedSkipNodes->nexts[0] != nullptr) {
        return QLinkedSkipNodes->nexts[0]->name;
    } else {
        throw "NO PATIENTS IN THE QUEUE!";
    }
    return "";
}

/* get the first patient's priority
 */
int SkipListPQ::frontPriority() {
    if (QLinkedSkipNodes->nexts[0] != nullptr) {
        return QLinkedSkipNodes->nexts[0]->priority;
    } else {
        throw "NO PATIENTS IN THE QUEUE!";
    }
    return 0;
}

/* return true if the SkipListPQ only points to the front node, otherwise return false
 */
bool SkipListPQ::isEmpty() {
    if (QLinkedSkipNodes->nexts[0] == nullptr) {
        return true;
    }
    return false;
}

/* create a new patient with specified name and priority, and put it in a proper place of the queue
 */
void SkipListPQ::newPatient(string name, int priority) {
    //first determine a random level incremented from 1
    int level = 1;
    while (randomBool() && level <= 32) {
        level++;
    }
    //ensure the level of the front node is large enough
    QLinkedSkipNodes->ensureLevel(level);

    SkipNode* node = QLinkedSkipNodes;
    SkipNode* newP = new SkipNode(name, priority, level);
    //find the proper place to insert the node
    for (int i = QLinkedSkipNodes->nexts.size() - 1; i >= 0; i--) {
        while (node->nexts[i] != nullptr && node->nexts[i]->priority <= priority) {
            node = node->nexts[i];
        }
        safeInsert(node, i, level, newP);
    }
}

/* insert the node if the level is suited
 */
void SkipListPQ::safeInsert(SkipNode*& node, int index, int level, SkipNode*& newP) {
    if (index + 1 <= level) {  //ensure that the level of the patient node is not too low
        SkipNode* temp = node->nexts[index];
        node->nexts[index] = newP;
        node->nexts[index]->nexts[index] = temp;
    }
}

/* process the first patient and then return the name of the patient
 */
string SkipListPQ::processPatient() {
    SkipNode* objectPatient = QLinkedSkipNodes->nexts[0];
    if (objectPatient != nullptr) {
        for (int i = 0; i < objectPatient->nexts.size(); i++) {
            QLinkedSkipNodes->nexts[i] = QLinkedSkipNodes->nexts[i]->nexts[i];
        }
        string name = objectPatient->name;
        delete objectPatient;
        return name;
    } else {
        throw "NO PATIENTS IN THE QUEUE!";
    }


    return "";
}

/* find the specified patient in the queue, remove it, and then add it to a new place
 */
void SkipListPQ::upgradePatient(string name, int oldPriority, int newPriority) {
    //to ensure that the new priority is a valid input
    if (oldPriority <= newPriority) {
        throw "PATIENT NO MORE URGENT THAN BEFORE!";
    }

    SkipNode* node = QLinkedSkipNodes;
    bool finished = false;  //a variable to determine if the specified patient is ever found in the queue
    //finding the patient
    for (int i = QLinkedSkipNodes->nexts.size() - 1; i >= 0; i--) {
        //skipping to an approapriate place
        while (node->nexts[i] != nullptr && node->nexts[i]->priority < oldPriority) {
            node = node->nexts[i];
        }
        //found
        if (node->nexts[i] != nullptr && node->nexts[i]->priority == oldPriority && node->nexts[i]->name == name) {
            SkipNode* object = node->nexts[i];
            node->nexts[i] = node->nexts[i]->nexts[i];
            if (i == 0) {
                delete object;
            }
            finished = true;
        //if this is not the patient but with same priority, then first keep skipping. if still not found, go back and wait for traversing in a lower level
        } else if (node->nexts[i] != nullptr && node->nexts[i]->priority == oldPriority && node->nexts[i]->name != name) {
            //attempt on skipping to the next
            SkipNode* temp = node;
            while (node->nexts[i] != nullptr && node->nexts[i]->priority == oldPriority && node->nexts[i]->name != name) {
                node = node->nexts[i];
            }
            //found
            if (node->nexts[i] != nullptr && node->nexts[i]->priority == oldPriority && node->nexts[i]->name == name) {
                SkipNode* object = node->nexts[i];
                node->nexts[i] = node->nexts[i]->nexts[i];
                if (i == 0) {
                    delete object;
                }
                finished = true;
            //not found
            } else {
                node = temp;
            }
        }

    }

    if (!finished) {
        throw "PATIENT NOT PRESENT IN THE QUEUE!";
    } else {
        SkipListPQ::newPatient(name, newPriority);
    }

}

void SkipListPQ::debug() {

}

SkipNode* SkipListPQ::getSkipListPQ() const {
    return QLinkedSkipNodes;
}

ostream& operator <<(ostream& out, const SkipListPQ& queue) {
    out << "{";
    SkipNode* node = queue.getSkipListPQ();
    while (node->nexts[0] != nullptr) {
        out << node->nexts[0]->priority << ":" << node->nexts[0]->name;
        if (node->nexts[0]->nexts[0] != nullptr) {
            out << ", ";
        }
        node = node->nexts[0];
    }
    out << "}";
    return out;
}
