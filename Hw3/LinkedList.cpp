/*
 * Name: Halil Arda Ozongun
 * Student ID: 22202709
 * Date: 16.04.2024
 */


#include "LinkedList.h"
#include "Pathway.h"

template<typename T>
LinkedList<T>::LinkedList() {
    head = nullptr;
    size = 0;
}

template<typename T>
LinkedList<T>::~LinkedList() {
    Node<T>* temp = head;
    while (temp != nullptr) {
        Node<T>* next = temp->next;
        delete temp;
        temp = next;
    }
    head = nullptr;
    size = 0;
}

template<typename T>
LinkedList<T>::LinkedList(const LinkedList<T> &other) {
    head = nullptr;
    size = 0;
    Node<T>* temp = other.head;
    while (temp != nullptr) {
        this->insert(temp->data);
        temp = temp->next;
    }
    size = other.size;
}

template<typename T>
LinkedList<T>& LinkedList<T>::operator=(const LinkedList<T> &other) {
    if(&other != this) {
        Node<T>* temp = head;
        // delete the current list first
        while (temp != nullptr) {
            Node<T>* next = temp->next;
            delete temp;
            temp = next;
        }
        head = nullptr;
        size = 0;
        temp = other.head; // temp is now iterator of other list
        while (temp != nullptr) {
            this->insert(temp->data);
            // handles the deep copying part in insert, we know it is "new" so not shallow copy
            temp = temp->next;
            size++;
        }
    }
    return *this;
}

template<typename T>
bool LinkedList<T>::insert(T data) {
    // check if the data already exists
    bool check = this->doesExist(data);
    if (check) {
        return false; // if it exists return false
    }

    // find the right place to insert, in ascending order
    Node<T>* newNode = new Node<T>(data);
    if (head == nullptr) { // empty list, add to begining
        head = newNode;
        size++;
        return true;
    }
    Node<T>* temp = head;
    Node<T>* prev = nullptr;
    // find the right place to insert
    while (temp != nullptr && temp->data < data) {
        prev = temp;
        temp = temp->next;
    }
    // if smallest, add to begining
    if (prev == nullptr) {
        newNode->next = head;
        head = newNode;
    } else { // not the first element
        prev->next = newNode;
        newNode->next = temp;
    }
    size++;
    return true;
}

template<typename T>
bool LinkedList<T>::remove(T data) {
    // if the list is empty return false
    if (head == nullptr) {
        return false;
    }
    Node<T>* temp = head;
    Node<T>* prev = nullptr;
    // either goes to the end of the list or finds the data
    while (temp != nullptr && temp->data != data) {
        prev = temp;
        temp = temp->next;
    }
    // if the data does not exist return false
    if (temp == nullptr) {
        return false;
    }
    // here data exists
    // check if data is the first element
    if (prev == nullptr) {
        head = temp->next;
    } else { // means data is not in the first element
        prev->next = temp->next;
    }
    // to avoid memory leak
    delete temp;
    size--;
    return true;
}

template<typename T>
bool LinkedList<T>::doesExist(T data) const {
    Node<T>* temp = head;
    // iterate in list to see if the data exists or not
    while (temp != nullptr) {
        if (temp->data == data) {
            return true;
        }
        temp = temp->next;
    }
    return false;
}

template<typename T>
int LinkedList<T>::getSize() const {
    return size;
}

template class LinkedList<Pathway>;
template class LinkedList<Protein>;
template class LinkedList<Gene>;
