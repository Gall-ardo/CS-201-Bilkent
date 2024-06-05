//
// Created by Msi on 03/05/2024.
// @Author Halil Arda Ozongun
//

#ifndef TRANSACTION_H
#define TRANSACTION_H

#include <iostream>
using namespace std;

class Transaction {

public:
    // functions
    Transaction();
    Transaction(const string serialNo, const int customerID, const bool transactionType);

    //getters
    string getSerialNo() const;
    int getCustomerID() const;
    bool getTransactionType() const;

    // setters
    void setSerialNo(const string serialNo);
    void setCustomerID(const int customerID);
    void setTransactionType(const bool transactionType);

private:
    string serialNo;
    int customerID;
    bool transactionType; // 1: rent, 0: return

};

#endif //TRANSACTION_H