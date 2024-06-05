/*
 * Name: Halil Arda Ozongun
 * Student ID: 22202709
 * Date: 16.04.2024
 */

#include "BiologicalPathway.h"

BiologicalPathway::BiologicalPathway() {
    this->pathways = LinkedList<Pathway>();
}

BiologicalPathway::~BiologicalPathway() {
    // nothing to do here, LinkedList destructor will handle memory deallocation
}

void BiologicalPathway::addPathway(const int pathwayId, const string pathwayName) {
    // check if the pathway exists
    bool exists = pathways.doesExist(Pathway(pathwayId, pathwayName));
    if (exists) {
        cout << "Cannot add pathway. There is already a pathway with ID " << pathwayId << "." << endl;
        return;
    }
    // add the pathway
    Pathway pathway(pathwayId, pathwayName);
    if(pathways.insert(pathway)){
        cout << "Added pathway " << pathwayId << "." << endl;
        return;
    }
}

void BiologicalPathway::removePathway(const int pathwayId) {
    // check if the pathway exists
    bool exists = pathways.doesExist(Pathway(pathwayId, ""));
    if (!exists) {
        cout << "Cannot remove pathway. There is no pathway with ID " << pathwayId << "." << endl;
        return;
    }
    // remove the pathway
    if(pathways.remove(Pathway(pathwayId, ""))){
        cout << "Removed pathway " << pathwayId << "." << endl;
        return;
    }
}

void BiologicalPathway::printPathways() const {
    // check num of pathways
    if(this->pathways.getSize() == 0){
        cout << "There are no pathways to show." << endl;
        return;
    }
    // print pathways, proteins and genes
    cout << "Pathways in the system:" << endl;
    for (auto it = pathways.begin(); it != pathways.end(); ++it) {
        cout << "Pathway " << (*it).getPathwayId() << " : " << (*it).getPathwayName()
        << " (" << (*it).getProteins().getSize() << " Proteins) (";
        int geneCount = 0; // to find all genes in the proteins, iterate over all proteins in "the" pathway
        for (auto proteinIt = (*it).getProteins().begin(); proteinIt != (*it).getProteins().end(); ++proteinIt) {
            geneCount += (*proteinIt).getGenes().getSize();
        }
        cout << geneCount << " Genes)" << endl;
    }
}

void BiologicalPathway::addProtein(const int proteinId, const int pathwayId) {
    // first check if the pathway exists
    bool isPathwayExists = pathways.doesExist(Pathway(pathwayId, ""));
    if(!isPathwayExists){
        cout << "Cannot add protein. There is no pathway with ID " << pathwayId << "." << endl;
        return;
    }
    // if pathway exists, check for protein exists in whole biologicalPathway object
    for (auto it = pathways.begin(); it != pathways.end(); ++it) {
        if((*it).getProteins().doesExist(Protein(proteinId))){
            cout << "Cannot add protein. There is a pathway having a protein with ID " << proteinId << "." << endl;
            return;
        }
    }
    // everything is ok, add the protein to the pathway
    Protein protein(proteinId);
    for (auto it = pathways.begin(); it != pathways.end(); ++it) { // iterate over all pathways
        if ((*it).getPathwayId() == pathwayId) { // find the right pathway
            (*it).getProteins().insert(protein);
            cout << "Added protein " << proteinId << " to pathway " << pathwayId << "." << endl;
            return;
        }
    }
}

void BiologicalPathway::removeProtein(const int proteinId, const int pathwayId) {
    // first check if the pathway exists
    bool isPathwayExists = pathways.doesExist(Pathway(pathwayId, ""));
    if(!isPathwayExists){
        cout << "Cannot remove protein. There is no pathway with ID " << pathwayId << "." << endl;
        return;
    }
    // get the pathway and hold it in currentPathway
    auto currentPathway = pathways.begin();
    while (currentPathway != pathways.end()){
        if((*currentPathway).getPathwayId() == pathwayId){
            break;
        }
        ++currentPathway; // means iterator goes to next object
    }
    // check if protein exists in the pathway
    if(!(*currentPathway).getProteins().doesExist(Protein(proteinId))){
        cout << "Cannot remove protein. Pathway " << pathwayId << " does not have a protein with ID " << proteinId << "." << endl;
        return;
    }
    // protein exists in the right pathway, remove
    if((*currentPathway).getProteins().remove(Protein(proteinId))){
        cout << "Removed protein " << proteinId << " from pathway " << pathwayId << "." << endl;
        return;
    }
}

void BiologicalPathway::printProteinsInPathway(const int pathwayId) const {
    // check if the pathway exists
    if(!pathways.doesExist(Pathway(pathwayId, ""))){
        cout << "Cannot print proteins. There is no pathway with ID " << pathwayId << "." << endl;
        return;
    }
    // get the pathway
    auto currentPathway = pathways.begin();
    while (currentPathway != pathways.end()){
        if((*currentPathway).getPathwayId() == pathwayId){
            break;
        }
        ++currentPathway;
    }
    // print the proteins
    if((*currentPathway).getProteins().getSize() == 0){
        cout << "There are no proteins to show in pathway " << pathwayId << "." << endl;
        return;
    }
    cout << "Proteins in pathway " << pathwayId << ":" << endl;

    for (auto it = (*currentPathway).getProteins().begin(); it != (*currentPathway).getProteins().end(); ++it) {
        cout << "Protein ID : " << (*it).getProteinId() << ", Gene IDs : ";
        /*if((*it).getGenes().getSize() == 0){
            cout << "None" << endl;
        } else {
            cout << "[";
            auto geneIt = (*it).getGenes().begin();
            auto endIt = (*it).getGenes().end();
            if (geneIt != endIt) { // Check to ensure that there is at least one gene to print, dont risking size may be miscalculated
                while (true) {
                    cout << (*geneIt).getGeneID();
                    ++geneIt;
                    if (geneIt != endIt) { // means there are more genes to print, add a comma
                        cout << ", ";
                    } else {
                        break;// means there are no more genes to print, dont add a comma, break the loop
                    }
                }
            }
            cout << "]" << endl;
        }*/
        auto geneIt = (*it).getGenes().begin();
        auto endIt = (*it).getGenes().end();
        if (geneIt != endIt) { // if there is at least one gene
            cout << "[";
            while (geneIt != endIt) {
                cout << (*geneIt).getGeneID();
                ++geneIt;
                if (geneIt != endIt) {
                    cout << ", ";
                }
            }
            cout << "]" << endl;
        } else { // no gene
            cout << "None" << endl;

        }
    }
}

void BiologicalPathway::addGene(const int geneID, const string geneName, const int proteinId) {
    bool isProteinExists = false;
    // check protein exists
    for (auto it = pathways.begin(); it != pathways.end(); ++it) {
        if((*it).getProteins().doesExist(Protein(proteinId))){
            isProteinExists = true;
            break;
        }
    }
    if(!isProteinExists){
        cout << "Cannot add gene. There is no protein with ID " << proteinId << "." << endl;
        return;
    }
    // protein exists, now check gene exists in system
    // 3 loop means , for each pathway for each protein look for each gene to check
    for (auto it = pathways.begin(); it != pathways.end(); ++it) {
        for (auto proteinIt = (*it).getProteins().begin(); proteinIt != (*it).getProteins().end(); ++proteinIt) {
            auto geneIt = (*proteinIt).getGenes().begin();
            while (geneIt != (*proteinIt).getGenes().end()){
                if((*geneIt).getGeneID() == geneID){ // gene exists, get out of method
                    cout << "Cannot add gene. Gene " << geneID << " is already in use." << endl;
                    return;
                }
                ++geneIt;
            }

        }
    }
    // gene does not exist and protein exists
    // add the gene to the protein without trouble

    // first find the protein
    Protein protein(proteinId);
    for (auto it = pathways.begin(); it != pathways.end(); ++it) {
        if ((*it).getProteins().doesExist(protein)) {
            auto currentProtein = (*it).getProteins().begin();
            while (currentProtein != (*it).getProteins().end()){
                if((*currentProtein).getProteinId() == proteinId){// found the protein
                    //now add the gene
                    Gene gene(geneID, geneName);// in stack
                    (*currentProtein).getGenes().insert(gene);// insert handles dynamic memory allocation
                    cout << "Added gene " << geneID << " to protein " << proteinId << "." << endl;
                    return;
                }
            ++currentProtein;// go to next protein
            }
        }
    }


}

void BiologicalPathway::removeGene(const int geneID, const int proteinId) {
    bool isProteinExists = false;
    for (auto it = pathways.begin(); it != pathways.end(); ++it) {
        if((*it).getProteins().doesExist(Protein(proteinId))){
            isProteinExists = true;
            break;
        }
    }
    if(!isProteinExists){
        cout << "Cannot remove gene. There is no protein with ID " << proteinId << "." << endl;
        return;
    }
    // find protein, then find gene in protein
    Protein protein(proteinId);
    for (auto it = pathways.begin(); it != pathways.end(); ++it) {
        auto currentProtein = (*it).getProteins().begin();
        while (currentProtein != (*it).getProteins().end()){
            if((*currentProtein).getProteinId() == proteinId){ // found the protein
                //now remove the gene
                if((*currentProtein).getGenes().doesExist(Gene(geneID, ""))){ // gene exists in "the" protein
                    (*currentProtein).getGenes().remove(Gene(geneID, ""));
                    cout << "Removed gene " << geneID << " from protein " << proteinId << "." << endl;
                } else { // gene does not exist in "the" protein
                    cout << "Cannot remove gene. There is no gene " << geneID << " encoding protein " << proteinId << "." << endl;
                }
                return;
            }
            ++currentProtein;
        }
    }
    //  if gene exists, but not in the protein, still printing:"Cannot remove gene. There is no gene * encoding protein *."
}

void BiologicalPathway::printGenesOfProtein(const int proteinId) const {
    bool isProteinExists = false;
    // check protein exists
    for (auto it = pathways.begin(); it != pathways.end(); ++it) {
        if((*it).getProteins().doesExist(Protein(proteinId))){
            isProteinExists = true;
            break;
        }
    }
    if(!isProteinExists){
        cout << "Cannot print genes. There is no protein with ID " << proteinId << "." << endl;
        return;
    }

    // first find the protein
    Protein protein(proteinId);
    for (auto it = pathways.begin(); it != pathways.end(); ++it) {
        if ((*it).getProteins().doesExist(protein)) { // found the pathway which has "the" protein
            auto currentProtein = (*it).getProteins().begin();
            while (currentProtein != (*it).getProteins().end()){
                if((*currentProtein).getProteinId() == proteinId){ // now also found right protein
                    //now print the genes
                    if ((*currentProtein).getGenes().begin() != (*currentProtein).getGenes().end()) { // there are genes in the protein
                        cout << "Genes in protein " << proteinId << ":" << endl;
                        for (auto it2 = (*currentProtein).getGenes().begin(); it2 != (*currentProtein).getGenes().end(); ++it2) {
                            cout << "GENE " << (*it2).getGeneID() << " : " << (*it2).getGeneName() << endl;
                        }
                        return;
                    }
                    // there are no genes in the protein print warnging
                    cout << "There are no genes to show in protein " << proteinId << "." << endl;
                    return;
                }
                ++currentProtein;
            }
        }
    }
}
