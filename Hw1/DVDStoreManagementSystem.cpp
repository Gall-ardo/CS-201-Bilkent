//
// Created by Msi on 03/05/2024.
// @Author Halil Arda Ozongun
//

#include "DVDStoreManagementSystem.h"

DVDStoreManagementSystem::DVDStoreManagementSystem() {
    dvdCount = 0;
    customerCount = 0;
    transactionCount = 0;
    dvdInventory = nullptr;
    customerList = nullptr;
    transactionHistory = nullptr;
}

DVDStoreManagementSystem::~DVDStoreManagementSystem() {
    if(dvdCount > 0) {
        delete[] dvdInventory;
    }
    if(customerCount > 0) {
        delete[] customerList;
    }
    if(transactionCount > 0) {
        delete[] transactionHistory;
    }
}

void DVDStoreManagementSystem::addDVD(const string serialNo, const string title, const string director) {

    // check if the dvd already exists
    for (int i = 0; i < dvdCount; i++) {
        if (dvdInventory[i].getSerialNo() == serialNo) {
            cout << "Cannot add DVD. DVD with serial number " << serialNo << " already exists." << endl;
            return;
        }
    }
    // if the dvd does not exist
    DVD* temp = new DVD[dvdCount + 1];
    for ( int i = 0; i < dvdCount; i++) {
        temp[i] = dvdInventory[i];
    }
    temp[dvdCount].setSerialNo(serialNo);
    temp[dvdCount].setTitle(title);
    temp[dvdCount].setDirector(director);
    dvdCount++;
    if(dvdInventory != nullptr) {
        delete[] dvdInventory;
    }
    dvdInventory = temp;
    cout << "DVD with serial number " << serialNo << " successfully added." << endl;
}

void DVDStoreManagementSystem::removeDVD(const string serialNo) {
    // find the index of the dvd
    int index = -1;
    for (int i = 0; i < dvdCount; i++) {
        if (dvdInventory[i].getSerialNo() == serialNo) {
            index = i;
            break;
        }
    }
    // if the dvd dont exist
    if (index == -1) {
        cout << "Cannot remove DVD. DVD with serial number " << serialNo << " not found." << endl;
        return;
    }
    // check if the dvd is rented
    if (dvdInventory[index].getIsRented()) {
        cout << "Cannot remove DVD. DVD with serial number " << serialNo << " is currently rented by a customer." << endl;
        return;
    }
    // if the dvd exists and not rented, then remove
    DVD* temp = new DVD[dvdCount - 1];
    for (int i = 0; i < index; i++) {
        temp[i] = dvdInventory[i];
    }
    for (int i = index + 1; i < dvdCount; i++) {
        temp[i - 1] = dvdInventory[i];
    }
    dvdCount--;
    delete[] dvdInventory;
    dvdInventory = temp;
    cout << "DVD with serial number " << serialNo << " successfully removed." << endl;

}

void DVDStoreManagementSystem::addCustomer(const int customerID, const string name) {
    // check if the customer already exists
    for (int i = 0; i < customerCount; i++) {
        if (customerList[i].getCustomerID() == customerID) {
            cout << "Cannot add customer. Customer with ID " << customerID << " already exists." << endl;
            return;
        }
    }
    // if the customer does not exist
    Customer* temp = new Customer[customerCount + 1];
    for (int i = 0; i < customerCount; i++) {
        temp[i] = customerList[i]; // should override the equal operator of Customer since it has a pointer
    }
    temp[customerCount].setCustomerID(customerID);
    temp[customerCount].setName(name);
    customerCount++;
    if(customerList != nullptr) {
        delete[] customerList;
    }
    customerList = temp;
    cout << "Customer with ID " << customerID << " successfully added." << endl;
}

void DVDStoreManagementSystem::removeCustomer(const int customerID) {
    // find the index of the customer
    int index = -1;
    for (int i = 0; i < customerCount; i++) {
        if (customerList[i].getCustomerID() == customerID) {
            index = i;
            break;
        }
    }
    // if the customer dont exist
    if (index == -1) {
        cout << "Cannot remove customer. Customer with ID " << customerID << " not found." << endl;
        return;
    }
    // if the customer has rented DVDs
    if (customerList[index].getNumberOfRentedDVDs() > 0) {
        cout << "Cannot remove customer. Customer with ID " << customerID << " has rented DVDs." << endl;
        return;
    }
    // if the customer exists and doesnt rented DVDs, remove
    Customer* temp = new Customer[customerCount - 1];
    for (int i = 0; i < index; i++) {
        temp[i] = customerList[i];
    }
    for (int i = index + 1; i < customerCount; i++) {
        temp[i - 1] = customerList[i];
    }
    customerCount--;
    delete[] customerList;
    customerList = temp;
    cout << "Customer with ID " << customerID << " successfully removed." << endl;
}

void DVDStoreManagementSystem::rentDVD(const int customerID, const string serialNo) {
    // check if possible to rent the dvd
    int customerIndex = -1, dvdIndex = -1;

    // find the index of the customer
    for (int i = 0; i < customerCount; i++) {
        if (customerList[i].getCustomerID() == customerID) {
            customerIndex = i;
            break;
        }
    }
    // find the index of the dvd
    for (int i = 0; i < dvdCount; i++) {
        if (dvdInventory[i].getSerialNo() == serialNo) {
            dvdIndex = i;
            break;
        }
    }
    if (customerIndex == -1 && dvdIndex == -1) {
        cout << "Cannot rent DVD. Customer with ID " << customerID << " and DVD with serial number " << serialNo << " not found." << endl;
        return;
    }
    if (customerIndex == -1) {
        cout << "Cannot rent DVD. Customer with ID " << customerID << " not found." << endl;
        return;
    }
    if (dvdIndex == -1) {
        cout << "Cannot rent DVD. DVD with serial number " << serialNo << " not found." << endl;
        return;
    }
    if (dvdInventory[dvdIndex].getIsRented()) {
        cout << "Cannot rent DVD. DVD with serial number " << serialNo << " is not available." << endl;
        return;
    }
    // if the customer and the dvd exist and the dvd is not rented, start the rent process
    dvdInventory[dvdIndex].setIsRented(true);
    customerList[customerIndex].setNumberOfRentedDVDs(customerList[customerIndex].getNumberOfRentedDVDs() + 1);
    if (customerList[customerIndex].getNumberOfRentedDVDs() == 1) {
        // new number is 1, so before it was 0, so it was nullptr so do not need to handle it
        customerList[customerIndex].setRentedDVDs(new DVD[1]);
        customerList[customerIndex].getRentedDVDs()[0] = dvdInventory[dvdIndex];
    } else {
        DVD* temp = new DVD[customerList[customerIndex].getNumberOfRentedDVDs()];
        // temp created with the new size
        for (int i = 0; i < customerList[customerIndex].getNumberOfRentedDVDs() - 1; i++) { // -1 since copying until last element
            temp[i] = customerList[customerIndex].getRentedDVDs()[i];
        }
        temp[customerList[customerIndex].getNumberOfRentedDVDs() - 1] = dvdInventory[dvdIndex];
        delete[] customerList[customerIndex].getRentedDVDs();
        customerList[customerIndex].setRentedDVDs(temp);
    }

    // update the transaction history
    Transaction* temp = new Transaction[transactionCount + 1];
    for (int i = 0; i < transactionCount; i++) {
        temp[i] = transactionHistory[i];
    }
    temp[transactionCount] = Transaction(serialNo, customerID, true);
    transactionCount++;
    delete[] transactionHistory;
    transactionHistory = temp;
    cout << "DVD with serial number " << serialNo << " successfully rented by customer with ID " << customerID << "." << endl;
}

void DVDStoreManagementSystem::returnDVD(const int customerID, const string serialNo) {
    //check if possible to return the dvd
    int customerIndex = -1, dvdIndex = -1;

    // find the index of the customer
    for (int i = 0; i < customerCount; i++) {
        if (customerList[i].getCustomerID() == customerID) {
            customerIndex = i;
            break;
        }
    }
    // find the index of the dvd
    for (int i = 0; i < dvdCount; i++) {
        if (dvdInventory[i].getSerialNo() == serialNo) {
            dvdIndex = i;
            break;
        }
    }
    if (customerIndex == -1 && dvdIndex == -1) {
        cout << "Cannot return DVD. Customer with ID " << customerID << " and DVD with serial number " << serialNo << " not found." << endl;
        return;
    }
    if (customerIndex == -1) {
        cout << "Cannot return DVD. Customer with ID " << customerID << " not found." << endl;
        return;
    }
    if (dvdIndex == -1) {
        cout << "Cannot return DVD. DVD with serial number " << serialNo << " not found." << endl;
        return;
    }

    int dvdIndexInThisCustomersRentedDVDs = -1;
    // if the customer and the dvd exist. check it is rented by this customer or not
    for (int i = 0; i < customerList[customerIndex].getNumberOfRentedDVDs(); i++) {
        if (customerList[customerIndex].getRentedDVDs()[i].getSerialNo() == serialNo) {
            dvdIndexInThisCustomersRentedDVDs = i;
            break;
        }
    }
    if (dvdIndexInThisCustomersRentedDVDs == -1) {
        cout << "Cannot return DVD. DVD with serial number " << serialNo << " not rented by customer with ID " << customerID << "." << endl;
        return;
    }

    // if the customer and the dvd exist and the dvd is rented by this customer,
    // everything okey - > handle the return process

    dvdInventory[dvdIndex].setIsRented(false);
    int numRentedDVDs = customerList[customerIndex].getNumberOfRentedDVDs() - 1;

    // Update the customers rented DVDs list.
    if (numRentedDVDs > 0) {
        DVD* temp = new DVD[numRentedDVDs];
        for (int i = 0, j = 0; i < customerList[customerIndex].getNumberOfRentedDVDs(); i++) {
            if (i != dvdIndexInThisCustomersRentedDVDs) {
                temp[j++] = customerList[customerIndex].getRentedDVDs()[i];
            }
        }
        delete[] customerList[customerIndex].getRentedDVDs();
        customerList[customerIndex].setRentedDVDs(temp);
    } else {
        delete[] customerList[customerIndex].getRentedDVDs();
        customerList[customerIndex].setRentedDVDs(nullptr);
    }

    customerList[customerIndex].setNumberOfRentedDVDs(numRentedDVDs);

    // update the transaction history
    Transaction* tempTransaction = new Transaction[transactionCount + 1];
    for (int i = 0; i < transactionCount; i++) {
        tempTransaction[i] = transactionHistory[i];
    }
    tempTransaction[transactionCount] = Transaction(serialNo, customerID, false);
    transactionCount++;
    delete[] transactionHistory;
    transactionHistory = tempTransaction;

    cout << "DVD with serial number " << serialNo << " successfully returned by customer with ID " << customerID << "." << endl;
}

void DVDStoreManagementSystem::showAllDVDs() const {
    cout << "DVDs in the system:" << endl;
    // if there are no DVDs
    if (dvdCount == 0) {
        cout << "None" << endl;
    }else {
        for (int i = 0; i < dvdCount; i++) {
            cout << "DVD: " << dvdInventory[i].getSerialNo() << ", Title: " << dvdInventory[i].getTitle() << ", Director: " << dvdInventory[i].getDirector();
            if (dvdInventory[i].getIsRented()) {
                cout << ", Rented" << endl;
            } else {
                cout << ", Available" << endl;
            }
        }
    }
}

void DVDStoreManagementSystem::showAllCustomers() const {
    cout << "Customers in the system:" << endl;
    // if there are no customers
    if (customerCount == 0) {
        cout << "None" << endl;
    } else {
        for (int i = 0; i < customerCount; i++) {
            cout << "Customer: " << customerList[i].getCustomerID() << ", Name: " << customerList[i].getName() << ", DVDs Rented: " << customerList[i].getNumberOfRentedDVDs() << endl;
        }
    }
}

void DVDStoreManagementSystem::showDVD(const string serialNo) const {
   for(int i = 0; i < dvdCount; i++){
       if(dvdInventory[i].getSerialNo() == serialNo){
           cout << "DVD: " << dvdInventory[i].getSerialNo() << ", Title: " << dvdInventory[i].getTitle() << ", Director: " << dvdInventory[i].getDirector();
           if (dvdInventory[i].getIsRented()) {
               cout << ", Rented" << endl;
           } else {
               cout << ", Available" << endl;
           }
           return;
       }
   }
    // if the dvd doesnt exist
    cout << "DVD with serial number " << serialNo << " not found." << endl;
}

void DVDStoreManagementSystem::showCustomer(const int customerID) const {
    for (int i = 0; i < customerCount; i++) {
        if (customerList[i].getCustomerID() == customerID) {
            cout << "Customer: " << customerList[i].getCustomerID() << ", Name: " << customerList[i].getName() << ", DVDs Rented: " << customerList[i].getNumberOfRentedDVDs() << endl;
            return;
        }
    }
    // if the customer doesnt exist
    cout << "Customer with ID " << customerID << " not found." << endl;
}

void DVDStoreManagementSystem::showTransactionHistory() const {
    cout << "Transactions in the system:" << endl;
    // if there are no transactions
    if (transactionCount == 0) {
        cout << "None" << endl;
        return;
    }
    for (int i = 0; i < transactionCount; i++) {
        cout << "Transaction: ";
        if (transactionHistory[i].getTransactionType()) {
            cout << "Rental, ";
        } else {
            cout << "Return, ";
        }
        cout << "Customer: " << transactionHistory[i].getCustomerID() << ", DVD: " << transactionHistory[i].getSerialNo() << endl;
        // with lambda expressions: cout << "Transaction: " << (transactionHistory[i].getTransactionType() ? "Rental" : "Return")
        // << ", Customer: " << transactionHistory[i].getCustomerID() << ", DVD: " << transactionHistory[i].getSerialNo() << endl;
    }
}