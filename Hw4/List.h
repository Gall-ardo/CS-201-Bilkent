//
// Halil Arda Ozongun
// ID: 22202709
// Cs201 - Hw4
// 11/05/2024
//

#ifndef HW4_LIST_H
#define HW4_LIST_H

#include <iostream>
using namespace std;

template <typename T>
class ListNode {
public:
    T data;
    ListNode<T>* next;
    ListNode(T data) : data(data), next(nullptr) {}
};

template <typename T>
class List {
public:
    ListNode<T>* head;
    int size;


    List() {
        head = nullptr;
        size = 0;
    }

    ~List() {
        ListNode<T>* temp = head;
        while (temp != nullptr) {
            ListNode<T>* next = temp->next;
            delete temp;
            temp = next;
        }
    }

    List(const List<T> &other) {
        head = nullptr;
        size = 0;
        ListNode<T>* temp = other.head;
        while (temp != nullptr) {
            this->insert(temp->data, size);
            temp = temp->next;
        }
        size = other.size;
    }

    List<T> operator=(const List<T> &other) {
        if(&other != this) {
            ListNode<T>* temp = head;
            // delete the current list first
            while (temp != nullptr) {
                ListNode<T>* next = temp->next;
                delete temp;
                temp = next;
            }
            head = nullptr;
            size = 0;
            temp = other.head; // temp is now iterator of other list
            while (temp != nullptr) {
                this->insert(temp->data, size);
                // handles the deep copying part in insert, we know it is "new" so not shallow copy
                temp = temp->next;
                size++;
            }
        }
        return *this;
    }

    bool insert(T data, int index) {
        if (index < 0 || index > size) {
            return false;
        }
        ListNode<T>* newNode = new ListNode<T>(data);
        if (index == 0) {
            newNode->next = head;
            head = newNode;
        } else {
            ListNode<T>* prev = getNodeAt(index - 1);
            newNode->next = prev->next;
            prev->next = newNode;
        }
        size++;
        return true;
    }

    bool remove(T data) {
        ListNode<T>* temp = head;
        if (temp->data == data) {
            head = head->next;
            delete temp;
            size--;
            return true;
        }
        while (temp->next != nullptr) {
            if (temp->next->data == data) {
                ListNode<T>* toDelete = temp->next;
                temp->next = toDelete->next;
                delete toDelete;
                size--;
                return true;
            }
            temp = temp->next;
        }
        return false;

    }

    bool removeAt(int index) {
        if (index < 0 || index >= size) {
            return false;
        }
        ListNode<T>* temp = nullptr;
        ListNode<T>* prev = head;
        if (index == 0) {
            temp = head;
            head = head->next;
        } else {
            for (int i = 0; i < index - 1; i++) {
                prev = prev->next;
            }
            temp = prev->next;
            prev->next = temp->next;
        }
        delete temp;
        size--;
        return true;
    }

    bool doesExist(T data) const {
        ListNode<T>* temp = head;
        while (temp != nullptr) {
            if (temp->data == data) {
                return true;
            }
            temp = temp->next;
        }
        return false;
    }

    int getSize() const {
        return size;
    }

    bool isEmpty() const {
        return size == 0;
    }

    ListNode<T>* getNodeAt(int index) const {
        if (index < 0 || index >= size) { // expectation is that index is valid, however still checking to be more safe
            return nullptr;
        }
        ListNode<T>* temp = head;
        for (int i = 0; i < index; i++) {
            temp = temp->next;
        }
        return temp;
    }

    T& operator[](int index) const {
        ListNode<T>* node = getNodeAt(index);
        return node->data;
    }

};

#endif //HW4_LIST_H
