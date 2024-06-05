/*
 * Name: Halil Arda Ozongun
 * Student ID: 22202709
 * Date: 16.04.2024
 */

#ifndef HW3TEMPLATE_LINKEDLIST_H
#define HW3TEMPLATE_LINKEDLIST_H

template <typename T>
// Template node class
class Node {
public:
    T data;
    Node<T>* next;
    Node(T data) : data(data), next(nullptr) {}
};

// Need to add < and > operators for the T classes
template <typename T>
class LinkedList {
public:
    Node<T>* head;
    int size;
    LinkedList();
    ~LinkedList();
    LinkedList(const LinkedList<T>& other);
    LinkedList<T>& operator=(const LinkedList<T>& other);

    // returns bool for checking operation is successful or not
    bool insert(T data);
    bool remove(T data);
    bool doesExist(T data) const;
    int getSize() const;


    // iterator class, to iterate in objects
    class Iterator {
    private:
        Node<T> *currentNode;
    public:
        // constructor
        Iterator(Node<T> *node) : currentNode(node) {}

        // go to the next element
        Iterator& operator++() {
            currentNode = currentNode->next;
            return *this;
        }

        // get the data of the current element
        T& operator*() const {
            return currentNode->data;
        }

        // check if two iterators are equal
        bool operator!=(const Iterator& other) const {
            return currentNode != other.currentNode;
        }
    };

    // gets the first and last element of the list, to iterate
    Iterator begin() const { return Iterator(head); }
    Iterator end() const { return Iterator(nullptr); }
};

#endif //HW3TEMPLATE_LINKEDLIST_H
