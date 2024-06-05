/*
 * Name: Halil Arda Ozongun
 * Student ID: 22202709
 * Date: 16.04.2024
 */


#ifndef HW3TEMPLATE_PROTEIN_H
#define HW3TEMPLATE_PROTEIN_H

#include <iostream>
#include "Gene.h"
#include "LinkedList.h"

using namespace std;

class Protein {
public:
    Protein();
    Protein( const int proteinID );

    // Getters
    int getProteinId() const;
    LinkedList<Gene> &getGenes(); // not const contrary to ordinary

    // Equality and < > operators need to be overloaded respect to proteinID
    bool operator==(const Protein &other) const;
    bool operator!=(const Protein &other) const;
    bool operator<(const Protein &other) const;
    bool operator>(const Protein &other) const;


private:
    int proteinID;
    LinkedList<Gene> genes;

};


#endif //HW3TEMPLATE_PROTEIN_H
