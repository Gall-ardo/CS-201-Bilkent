//
// Created by Msi on 03/05/2024.
// @Author Halil Arda Ozongun
//

#include "DVD.h"

// 0: is available, 1: is rented
DVD::DVD() {
    this->isRented = false;
    this->serialNo = "";
    this->title = "";
    this->director = "";
}

DVD::DVD(const string serialNo, const string title, const string director) {
    this->serialNo = serialNo;
    this->title = title;
    this->director = director;
    this->isRented = false;
}

string DVD::getSerialNo() const {
    return serialNo;
}

string DVD::getTitle() const {
    return title;
}

string DVD::getDirector() const {
    return director;
}

bool DVD::getIsRented() const {
    return isRented;
}

void DVD::setSerialNo(const string serialNo) {
    this->serialNo = serialNo;
}

void DVD::setTitle(const string title) {
    this->title = title;
}

void DVD::setDirector(const string director) {
    this->director = director;
}

void DVD::setIsRented(const bool isRented) {
    this->isRented = isRented;
}
