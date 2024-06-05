//
// Created by Msi on 03/05/2024.
// @Author Halil Arda Ozongun
//

#include "Customer.h"

Customer::Customer() {
    numberOfRentedDVDs = 0;
    rentedDVDs = nullptr;
}

Customer::Customer(const int customerID, const string name) {
    this->customerID = customerID;
    this->name = name;
    this->numberOfRentedDVDs = 0;
    this->rentedDVDs = nullptr;
}

Customer::~Customer() {
    if(numberOfRentedDVDs > 0) {
        delete[] rentedDVDs;
    }
}

Customer & Customer::operator=(const Customer &customer) {
    this->customerID = customer.getCustomerID();
    this->name = customer.getName();
    if(&customer != this) {
       if(this->numberOfRentedDVDs != customer.getNumberOfRentedDVDs()) {
           if(this->numberOfRentedDVDs > 0) {
               delete[] this->rentedDVDs;
           }
           this->numberOfRentedDVDs = customer.getNumberOfRentedDVDs();
           if(this->numberOfRentedDVDs > 0) {
               this->rentedDVDs = new DVD[this->numberOfRentedDVDs];
           } else {
               this->rentedDVDs = nullptr;
           }
       }
        for (int i = 0; i < this->numberOfRentedDVDs; i++) {
            this->rentedDVDs[i] = customer.getRentedDVDs()[i];
        }
    }

    return *this;
}


int Customer::getCustomerID() const {
    return customerID;
}

string Customer::getName() const {
    return name;
}

int Customer::getNumberOfRentedDVDs() const {
    return numberOfRentedDVDs;
}

DVD* Customer::getRentedDVDs() const {
    return rentedDVDs;
}

void Customer::setCustomerID(const int customerID) {
    this->customerID = customerID;
}

void Customer::setName(const string name) {
    this->name = name;
}

void Customer::setNumberOfRentedDVDs(const int numberOfRentedDVDs) {
    this->numberOfRentedDVDs = numberOfRentedDVDs;
}

void Customer::setRentedDVDs(DVD *rentedDVDs) {
    this->rentedDVDs = rentedDVDs;
}
