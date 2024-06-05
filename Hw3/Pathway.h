/*
 * Name: Halil Arda Ozongun
 * Student ID: 22202709
 * Date: 16.04.2024
 */

#ifndef HW3TEMPLATE_PATHWAY_H
#define HW3TEMPLATE_PATHWAY_H


#include <iostream>
#include "Protein.h"
#include "LinkedList.h"
using namespace std;


class Pathway {
public:
    Pathway();
    Pathway( const int pathwayID, const string pathwayName );

    // Getters
    int getPathwayId() const;
    const string &getPathwayName() const;
    LinkedList<Protein> &getProteins();

    // Equality and < > operators need to be overloaded respect to pathwayID
    bool operator==(const Pathway &other) const;
    bool operator!=(const Pathway &other) const;
    bool operator<(const Pathway &other) const;
    bool operator>(const Pathway &other) const;

private:
    int pathwayID;
    string pathwayName;
    LinkedList<Protein> proteins;

};

#endif //HW3TEMPLATE_PATHWAY_H
