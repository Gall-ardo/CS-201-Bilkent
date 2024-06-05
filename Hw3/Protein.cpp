/*
 * Name: Halil Arda Ozongun
 * Student ID: 22202709
 * Date: 16.04.2024
 */

#include "Protein.h"

Protein::Protein() {
    proteinID = 0;
    genes = LinkedList<Gene>();
}

Protein::Protein(const int proteinID) {
    this->proteinID = proteinID;
    genes = LinkedList<Gene>();
}

LinkedList<Gene> &Protein::getGenes() {
    return genes;
}

int Protein::getProteinId() const {
    return proteinID;
}

bool Protein::operator==(const Protein &other) const {
    return this->proteinID == other.proteinID;
}

bool Protein::operator!=(const Protein &other) const {
    return this->proteinID != other.proteinID;
}

bool Protein::operator<(const Protein &other) const {
    return this->proteinID < other.proteinID;
}

bool Protein::operator>(const Protein &other) const {
    return this->proteinID > other.proteinID;
}
