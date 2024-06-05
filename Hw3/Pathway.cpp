/*
 * Name: Halil Arda Ozongun
 * Student ID: 22202709
 * Date: 16.04.2024
 */

#include "Pathway.h"

Pathway::Pathway() {
    this->pathwayID = 0;
    this->pathwayName = "";
    this->proteins = LinkedList<Protein>();
}

Pathway::Pathway(const int pathwayID, const string pathwayName) {
    this->pathwayID = pathwayID;
    this->pathwayName = pathwayName;
    this->proteins = LinkedList<Protein>();

}

int Pathway::getPathwayId() const {
    return pathwayID;
}

const string &Pathway::getPathwayName() const {
    return pathwayName;
}

LinkedList<Protein> &Pathway::getProteins(){
    return proteins;
}

bool Pathway::operator==(const Pathway &other) const {
    return this->pathwayID == other.pathwayID;
}

bool Pathway::operator!=(const Pathway &other) const {
    return this->pathwayID != other.pathwayID;
}

bool Pathway::operator<(const Pathway &other) const {
    return this->pathwayID < other.pathwayID;
}

bool Pathway::operator>(const Pathway &other) const {
    return this->pathwayID > other.pathwayID;
}
