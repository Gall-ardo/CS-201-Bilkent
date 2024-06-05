//
// Halil Arda Ozongun
// ID: 22202709
// Cs201 - Hw4
// 11/05/2024
//

#ifndef HW4_STACK_H
#define HW4_STACK_H

#include "BuildingMap.h"

struct StackNode {
    Node* node;
    StackNode* next;
    StackNode(Node* node) : node(node), next(nullptr) {}
};

class Stack {
    private:
        StackNode* topNode;

    public:
    Stack() : topNode(nullptr) {}
    ~Stack() { clear(); }

    void push(Node* node) {
        StackNode* newNode = new StackNode(node);
        newNode->next = topNode;
        topNode = newNode;
    }

    Node* pop() { // pop and peek works together
        if (topNode == nullptr) return nullptr;
        StackNode* poppedNode = topNode;
        Node* node = poppedNode->node;
        topNode = poppedNode->next;
        delete poppedNode;
        return node;
    }

    bool isEmpty() const { return topNode == nullptr; }

    void clear() {
        while (!isEmpty()) {
            pop();
        }
    }

    Node* top() const {
        if (topNode == nullptr) return nullptr;
        return topNode->node;
    }
};

#endif //HW4_STACK_H
