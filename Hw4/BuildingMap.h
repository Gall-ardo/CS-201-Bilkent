//
// Halil Arda Ozongun
// ID: 22202709
// Cs201 - Hw4
// 11/05/2024
//

#ifndef HW4_BUILDINGMAP_H
#define HW4_BUILDINGMAP_H

#include <iostream>
#include "List.h"
#include "Direction.h"
using namespace std;

class Node {
    public:
        int row;
        int col;
        Node* left;
        Node* right;
        Node* up;
        Node* down;
        bool visited;
        Node() : row(0), col(0), left(nullptr), right(nullptr), up(nullptr), down(nullptr), visited(false){}
};

class BuildingMap {
    public:
        BuildingMap(const string buildingMapFile);
        ~BuildingMap();
        void displayAllCubicles() const;
        void displayAdjacentCubicles(const int row, const int col) const;
        void displayBuildingMap() const;
        void findPaths(const int startRow, const int startCol, const int endRow, const int endCol);
        void findPaths(const int startRow, const int startCol, const int endRow, const int endCol, const int avoidRow, const int avoidCol);

    private:
        int rowNum;
        int colNum;
        Node** map;
        static bool isInDirections (const List<Direction>& directions, const int startRow, const int startCol, const int endRow, const int endCol);
};

#endif //HW4_BUILDINGMAP_H