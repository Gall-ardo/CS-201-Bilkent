//
// Created by Msi on 03/05/2024.
// @Author Halil Arda Ozongun
//

#include "Transaction.h"

Transaction::Transaction() {

}

Transaction::Transaction(const string serialNo, const int customerID, const bool transactionType) {
    this->serialNo = serialNo;
    this->customerID = customerID;
    this->transactionType = transactionType;
}

string Transaction::getSerialNo() const {
    return serialNo;
}

int Transaction::getCustomerID() const {
    return customerID;
}

bool Transaction::getTransactionType() const {
    return transactionType;
}

void Transaction::setSerialNo(const string serialNo) {
    this->serialNo = serialNo;
}

void Transaction::setCustomerID(const int customerID) {
    this->customerID = customerID;
}

void Transaction::setTransactionType(const bool transactionType) {
    this->transactionType = transactionType;
}