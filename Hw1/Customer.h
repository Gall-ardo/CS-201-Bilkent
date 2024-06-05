//
// Created by Msi on 03/05/2024.
// @Author Halil Arda Ozongun
//

#ifndef CUSTOMER_H
#define CUSTOMER_H

#include <iostream>
#include "DVD.h"
using namespace std;

class Customer {

public:
    // functions
    Customer();
    ~Customer();
    Customer(const int customerID, const string name);
    Customer& operator=(const Customer& customer);

    // getters
    int getCustomerID() const;
    string getName() const;
    int getNumberOfRentedDVDs() const;
    DVD* getRentedDVDs() const;

    // setters
    void setCustomerID(const int customerID);
    void setName(const string name);
    void setNumberOfRentedDVDs(const int numberOfRentedDVDs);
    void setRentedDVDs(DVD* rentedDVDs);

private:
    int customerID;
    string name;
    int numberOfRentedDVDs;
    DVD* rentedDVDs;

};
#endif //CUSTOMER_H