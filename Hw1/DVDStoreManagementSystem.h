//
// Created by Msi on 03/05/2024.
// @Author Halil Arda Ozongun
//

#ifndef DVDSTOREMANAGEMENTSYSTEM_H
#define DVDSTOREMANAGEMENTSYSTEM_H

#include <iostream>
#include "Transaction.h"
#include "DVD.h"
#include "Customer.h"
using namespace std;

class DVDStoreManagementSystem {

    public:
        DVDStoreManagementSystem();
        ~DVDStoreManagementSystem();
        void addDVD( const string serialNo, const string title, const string director );
        void removeDVD( const string serialNo );
        void addCustomer( const int customerID, const string name );
        void removeCustomer( const int customerID );
        void rentDVD( const int customerID, const string serialNo );
        void returnDVD( const int customerID, const string serialNo );
        void showAllDVDs() const;
        void showAllCustomers() const;
        void showDVD( const string serialNo ) const;
        void showCustomer( const int customerID ) const;
        void showTransactionHistory() const;

    private:
        DVD* dvdInventory;
        Customer* customerList;
        Transaction* transactionHistory;
        int dvdCount;
        int customerCount;
        int transactionCount;

};

#endif //DVDSTOREMANAGEMENTSYSTEM_H