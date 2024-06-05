/*
 * Name: Halil Arda Ozongun
 * Student ID: 22202709
 * Date: 16.04.2024
 */


#ifndef HW3TEMPLATE_BIOLOGICALPATHWAY_H
#define HW3TEMPLATE_BIOLOGICALPATHWAY_H

#include <iostream>
#include "Pathway.h"
using namespace std;


class BiologicalPathway {
public:
    BiologicalPathway();
    ~BiologicalPathway();

    // pathway methods
    void addPathway( const int pathwayId, const string pathwayName );
    void removePathway( const int pathwayId );
    void printPathways() const;

    // protein methods
    void addProtein( const int proteinId, const int pathwayId );
    void removeProtein( const int proteinId, const int pathwayId );
    void printProteinsInPathway( const int pathwayId ) const;

    // gene methods
    void addGene( const int geneID, const string geneName, const int proteinId );
    void removeGene( const int geneID, const int proteinId );
    void printGenesOfProtein( const int proteinId ) const;

private:
    LinkedList<Pathway> pathways;
};

#endif //HW3TEMPLATE_BIOLOGICALPATHWAY_H
