/*
 * Name: Halil Arda Ozongun
 * Student ID: 22202709
 * Date: 16.04.2024
 */


#include "Gene.h"

Gene::Gene() {
    this->geneID = 0;
    this->geneName = "";
}

Gene::Gene(const int geneID, const string geneName) {
    this->geneID = geneID;
    this->geneName = geneName;
}

int Gene::getGeneID() const {
    return geneID;
}

string Gene::getGeneName() const {
    return geneName;
}

bool Gene::operator==(const Gene &other) const {
    return other.geneID == this->geneID;
}

bool Gene::operator!=(const Gene &other) const {
    return other.geneID != this->geneID;
}

bool Gene::operator<(const Gene &other) const {
    return this->geneID < other.geneID;
}

bool Gene::operator>(const Gene &other) const {
    return this->geneID > other.geneID;
}
