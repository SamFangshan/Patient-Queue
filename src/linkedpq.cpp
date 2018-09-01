//Author: https://github.com/SamFangshan
#include "linkedpq.h"

/* creat an empty LinkedPQ pointing to null
 */
LinkedPQ::LinkedPQ() {
    QLinkedNodes = nullptr;
}

/* free up all memory occupied by all nodes of LinkedPQ
 */
LinkedPQ::~LinkedPQ() {
    PNode* node = QLinkedNodes;
    while (node != nullptr) {
        PNode* temp = node->next;
        delete node;
        node = temp;
    }
}

/* free up all memory occupied by all nodes of LinkedPQ and set the front pointing to null
 */
void LinkedPQ::clear() {
    PNode* node = QLinkedNodes;
    while (node != nullptr) {
        PNode* temp = node->next;
        delete node;
        node = temp;
    }
    QLinkedNodes = nullptr;
}

/* get the first patient's name
 */
string LinkedPQ::frontName() const {
    if (QLinkedNodes == nullptr) {
        throw "NO PATIENTS IN THE QUEUE!";
    } else {
        return QLinkedNodes->name;
    }
    return "";
}

/* get the first patient's priority
 */
int LinkedPQ::frontPriority() const {
    if (QLinkedNodes == nullptr) {
        throw "NO PATIENTS IN THE QUEUE!";
    } else {
        return QLinkedNodes->priority;
    }
    return 0;
}

/* return true if the LinkedPQ is empty, otherwise return false
 */
bool LinkedPQ::isEmpty() {
    return QLinkedNodes == nullptr;
}

/* create a new patient with specified name and priority, and put it in a proper place of the queue
 */
void LinkedPQ::newPatient(string name, int priority) {
    //there is/are already patient(s)
    if (QLinkedNodes != nullptr) {
        //deal with the case when the patient should be placed at the very front of the queue
        bool done = false;  //variable to determine whether a new patient has already been placed at the front
        if (QLinkedNodes->priority > priority) {
            PNode* temp = new PNode(name, priority, QLinkedNodes);
            QLinkedNodes = temp;
            done = true;
        }
        //deals with the case when the patient should be placed at a place other than the very front
        if (!done) {
            PNode* node = QLinkedNodes;
            while (node->next != nullptr && node->next->priority <= priority) {
                node = node->next;
            }
            PNode* temp = node->next;
            node->next = new PNode(name, priority, temp);
        }
    //there is no patient
    } else {
        QLinkedNodes = new PNode(name, priority, nullptr);
    }
}

/* remove the first patient and then return the name of patient
 */
string LinkedPQ::processPatient() {
    if (QLinkedNodes == nullptr) {
        throw "NO PATIENTS IN THE QUEUE!";
    } else {
        PNode* node = QLinkedNodes;
        QLinkedNodes = QLinkedNodes->next;
        string name = node->name;
        delete node;
        return name;
    }
    return "";
}

/* find the specified patient in the queue, remove it, and then add it to a new place
 */
void LinkedPQ::upgradePatient(string name, int oldPriority, int newPriority) {
    //to ensure that the new priority is a valid input
    if (oldPriority <= newPriority) {
        throw "PATIENT NO MORE URGENT THAN BEFORE!";
    }

    //finding the patient
    bool isFirst = false;
    PNode* justBeforeObjectPatient = LinkedPQ::findPatient(name, oldPriority, isFirst);  //see detailed comments below
    /* this is the patient just before the object patient that needs to be displaced for most cases.
     * but when the first patient in the queue is the object patient, this variable refers to the object patient
     */

    //deleting and placing
    if (isFirst) {
        delete justBeforeObjectPatient;
        LinkedPQ::newPatient(name, newPriority);
    } else {
        PNode* objectPatient = justBeforeObjectPatient->next;
        justBeforeObjectPatient->next = objectPatient->next;
        delete objectPatient;
        LinkedPQ::newPatient(name, newPriority);
    }
}

/* find the specified patient in the queue
 */
PNode* LinkedPQ::findPatient(string name, int priority, bool& isFirst) const {
    PNode* node = QLinkedNodes;
    if (node == nullptr) {  //empty
        throw "PATIENT NOT PRESENT IN THE QUEUE!";
    } else {
        //the first patient is the object
        if (node->name == name && node->priority == priority) {
            isFirst = true;
            return node;
        }
        //some patient other than the first one is the object
        while (node->next != nullptr) {
            if (node->next->name == name && node->next->priority == priority) {
                return node;
            } else {
                node = node->next;
            }
        }
    }

    //after all those operations, we still haven't found the object patient. then the patient does not exist in the queue
    throw "PATIENT NOT PRESENT IN THE QUEUE!";
    return nullptr;
}

void LinkedPQ::debug() {
    // optional member function
}

PNode* LinkedPQ::getLinkedPQ() const {
    return QLinkedNodes;
}

ostream& operator <<(ostream& out, const LinkedPQ& queue) {
    out << "{";
    PNode* node = queue.getLinkedPQ();
    if (node != nullptr && node->next == nullptr) {
        out << node->priority << ":" << node->name;
    } else if (node != nullptr) {
        while (node != nullptr) {
            out << node->priority << ":" << node->name;
            if (node->next != nullptr) {
                 out << ", ";
            }
            node = node->next;
        }
    }
    out << "}";
    return out;
}
