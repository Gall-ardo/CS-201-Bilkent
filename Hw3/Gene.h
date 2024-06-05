/*
 * Name: Halil Arda Ozongun
 * Student ID: 22202709
 * Date: 16.04.2024
 */


#ifndef HW3TEMPLATE_GENE_H
#define HW3TEMPLATE_GENE_H

#include <iostream>
using namespace std;


class Gene {

public:
    Gene();
    Gene( const int geneID, const string geneName );

    // Getters
    int getGeneID() const;
    string getGeneName() const;

    // Equality and < > operators need to be overloaded respect to geneID
    bool operator==(const Gene &other) const;
    bool operator!=(const Gene &other) const;
    bool operator<(const Gene &other) const;
    bool operator>(const Gene &other) const;

private:
    int geneID;
    string geneName;
};


#endif //HW3TEMPLATE_GENE_H
