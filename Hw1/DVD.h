//
// Created by Msi on 03/05/2024.
// @Author Halil Arda Ozongun
//

#ifndef DVD_H
#define DVD_H

#include <iostream>
using namespace std;

class DVD {

public:
    // functions
    DVD();
    DVD(const string serialNo, const string title, const string director );

    // getters
    string getSerialNo() const;
    string getTitle() const;
    string getDirector() const;
    bool getIsRented() const;

    // setters
    void setSerialNo(const string serialNo);
    void setTitle(const string title);
    void setDirector(const string director);
    void setIsRented(const bool isRented);

private:
    string serialNo;
    string title;
    string director;
    bool isRented; // 0: is available, 1: is rented
};

#endif //DVD_H
