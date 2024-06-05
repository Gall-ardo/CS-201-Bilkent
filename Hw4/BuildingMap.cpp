//
// Halil Arda Ozongun
// ID: 22202709
// Cs201 - Hw4
// 11/05/2024
//

#include "BuildingMap.h"
#include <fstream>
#include "Stack.h"

BuildingMap::BuildingMap(const string buildingMapFile) {
    ifstream inFile(buildingMapFile);

    if (!inFile) {
        cout << "Cannot open file: " << buildingMapFile << endl;
        exit(1);
    }

    inFile >> rowNum >> colNum;
    map = new Node*[rowNum];
    for (int i = 0; i < rowNum; ++i) {
        map[i] = new Node[colNum];
        for (int j = 0; j < colNum; ++j) {
            map[i][j].row = i;
            map[i][j].col = j;
            map[i][j].left = nullptr;
            map[i][j].right = nullptr;
            map[i][j].up = nullptr;
            map[i][j].down = nullptr;
            map[i][j].visited = false;
        }
    }
    cout << rowNum << " rows and " << colNum << " columns have been read." << endl;

    for (int i = 0; i < rowNum; ++i) {
        for (int j = 0; j < colNum; ++j) {
            char c;
            inFile >> c;

            //if (c == '3') { }// has both left and bottom wall

            if (c == '2') { // has only bottom wall
                if (j != 0) {
                    map[i][j].left = &map[i][j - 1];
                    map[i][j - 1].right = &map[i][j];
                }
            }
            if (c == '1') { // has only left wall
                if (i != rowNum - 1){
                    map[i][j].down = &map[i + 1][j];
                    map[i + 1][j].up = &map[i][j];
                }
            }
            if (c == '0') { // has neither left nor bottom
                if (j != 0) {
                    map[i][j].left = &map[i][j - 1];
                    map[i][j - 1].right = &map[i][j];
                }
                if (i != rowNum - 1) {
                    map[i][j].down = &map[i + 1][j];
                    map[i + 1][j].up = &map[i][j];
                }
            }
        }
    }
    inFile.close();
}

BuildingMap::~BuildingMap() {
    for (int i = 0; i < rowNum; ++i) {
        delete[] map[i];
    }
    delete[] map;

}

void BuildingMap::displayAllCubicles() const {
    cout << "The cubicles in the building are:" << endl;
    for (int i = 0; i < rowNum; ++i) {
        for (int j = 0; j < colNum; ++j) {
            cout << "(" << i << "," << j << ")";
            if (j != colNum - 1) {
                cout << ",";
            }
        }
        cout << endl;
    }
}

void BuildingMap::displayAdjacentCubicles(const int row, const int col) const {
    bool thereIsAEarlier = false;
    if (row >= 0 && row < rowNum && col >= 0 && col < colNum){
        cout << "The cubicles adjacent to (" << row << "," << col << ") are:" << endl;
        cout << "(" << row << "," << col << ") -> ";

        if (map[row][col].up != nullptr) {
            thereIsAEarlier = true;
            cout << "(" << row - 1 << "," << col << ")";
        }
        if (map[row][col].left != nullptr) {
            if (thereIsAEarlier) {
                cout << ",";
            }
            thereIsAEarlier = true;
            cout << "(" << row << "," << col - 1 << ")";
        }
        if (map[row][col].right != nullptr) {
            if (thereIsAEarlier) {
                cout << ",";
            }
            thereIsAEarlier = true;
            cout << "(" << row << "," << col + 1 << ")";
        }
        if (map[row][col].down != nullptr) {
            if (thereIsAEarlier) {
                cout << ",";
            }
            cout << "(" << row  + 1 << "," << col << ")";
        }

        cout << endl;
    }
    else {
        cout << "Invalid row or column number" << endl;
    }
}

void BuildingMap::displayBuildingMap() const {
    cout << "The building map is as follows:" << endl;
    for (int i = 0; i < rowNum; ++i) {
        for (int j = 0; j < colNum; ++j) {
            bool thereIsAEarlier = false;
            cout << "(" << i << "," << j << ") -> ";
            if (map[i][j].up != nullptr) {
                cout << "(" << i  - 1 << "," << j << ")";
                thereIsAEarlier = true;
            }
            if (map[i][j].left != nullptr) {
                if (thereIsAEarlier) {
                    cout << ",";
                }
                thereIsAEarlier = true;
                cout << "(" << i << "," << j - 1 << ")";
            }
            if (map[i][j].right != nullptr) {
                if (thereIsAEarlier) {
                    cout << ",";
                }
                thereIsAEarlier = true;
                cout << "(" << i << "," << j + 1 << ")";
            }
            if (map[i][j].down != nullptr) {
                if (thereIsAEarlier) {
                    cout << ",";
                }
                cout << "(" << i + 1 << "," << j << ")";
            }
            cout << endl;
        }
    }

}

bool BuildingMap::isInDirections(const List<Direction>& directions, const int startRow, const int startCol, const int endRow, const int endCol ) {
    for (int i = 0; i < directions.getSize(); ++i) {
        if (directions[i].startRow == startRow && directions[i].startCol == startCol && directions[i].endRow == endRow && directions[i].endCol == endCol) {
            return true;
        }
    }
    return false;

}

void BuildingMap::findPaths(const int startRow, const int startCol, const int endRow, const int endCol) {
    // clear the map
    for (int i = 0; i < rowNum; ++i) {
        for (int j = 0; j < colNum; ++j) {
            map[i][j].visited = false;
        }
    }
    bool found = false; // a flag to check if we found a path, if not print None
    cout << "Paths from (" << startRow << "," << startCol << ") to (" << endRow << "," << endCol << ") are:" << endl;

    Stack path; // a stack to keep the path
    List<Direction> directionsList; // a list to keep the directions of the path
    // this list helps us to avoid going back to the same node from same previous path
    path.push(&map[startRow][startCol]);
    map[startRow][startCol].visited = true;

    while (!path.isEmpty()) {
        Node* current = path.top();
        int row = current->row;
        int col = current->col;

        // means we found a path, print it
        if (row == endRow && col == endCol) {
            found = true;
            // print the path

            // stack if filo, so we need to reverse the path
            Stack tempStack;
            int countOfNodes = 0;
            string result = "";
            while (!path.isEmpty()) {
                tempStack.push(path.top());
                countOfNodes++;
                path.pop();
            }

            while (!tempStack.isEmpty()) {
                Node* current = tempStack.top();
                path.push(current);
                result += "(" + to_string(current->row) + "," + to_string(current->col) + ")";
                if (countOfNodes != 1) {
                    result += " -> ";
                }
                countOfNodes--;
                tempStack.pop();
            }

            cout << result << endl;
            path.pop();
            // make this node not visited
            current->visited = false;

        }
        else {
            if (current->up != nullptr && !current->up->visited && !isInDirections(directionsList, row, col, row - 1, col)) {
                path.push(current->up);
                current->up->visited = true;
                directionsList.insert(Direction(row, col, row - 1, col),directionsList.getSize());

            }
            else if (current->left != nullptr && !current->left->visited && !isInDirections(directionsList, row, col, row, col - 1)) {
                path.push(current->left);
                current->left->visited = true;
                directionsList.insert(Direction(row, col, row, col - 1),directionsList.getSize());
            }
            else if (current->right != nullptr && !current->right->visited && !isInDirections(directionsList, row, col, row, col + 1)) {
                path.push(current->right);
                current->right->visited = true;
                directionsList.insert(Direction(row, col, row, col + 1),directionsList.getSize());
            }
            else if (current->down != nullptr && !current->down->visited && !isInDirections(directionsList, row, col, row + 1, col)) {
                path.push(current->down);
                current->down->visited = true;
                directionsList.insert(Direction(row, col, row + 1, col),directionsList.getSize());
            }
            else {
                path.pop();
                // remove the directions with the current node as the first node of the path

                for (int i = 0; i < directionsList.getSize(); ++i) {
                    if (directionsList[i].startRow == current->row && directionsList[i].startCol == current->col) {
                        directionsList.removeAt(i);
                        i--;
                    }
                }
                current->visited = false;
            }
        }
    }


    if (!found){
        cout << "None" << endl;
    }

}

// same logic with the previous function, but this time we avoid a specific node, so we are making it visited
void BuildingMap::findPaths(const int startRow, const int startCol, const int endRow, const int endCol, const int avoidRow, const int avoidCol) {
    // clear the map
    for (int i = 0; i < rowNum; ++i) {
        for (int j = 0; j < colNum; ++j) {
            map[i][j].visited = false;
        }
    }
    // make the avoid node visited
    map[avoidRow][avoidCol].visited = true;
    bool found = false;
    cout << "Paths from (" << startRow << "," << startCol << ") to (" << endRow << "," << endCol << ") avoiding (" << avoidRow << "," << avoidCol << ") are:" << endl;

    Stack path;
    List<Direction> directionsList;
    path.push(&map[startRow][startCol]);
    map[startRow][startCol].visited = true;

    while (!path.isEmpty()) {
        Node* current = path.top();
        int row = current->row;
        int col = current->col;

        // means we found a path, print it
        if (row == endRow && col == endCol) {
            found = true;
            // print the path
            Stack tempStack;
            int countOfNodes = 0;
            string result = "";
            while (!path.isEmpty()) {
                tempStack.push(path.top());
                countOfNodes++;
                path.pop();
            }

            while (!tempStack.isEmpty()) {
                Node* current = tempStack.top();
                path.push(current);
                result += "(" + to_string(current->row) + "," + to_string(current->col) + ")";
                if (countOfNodes != 1) {
                    result += " -> ";
                }
                countOfNodes--;
                tempStack.pop();
            }

            cout << result << endl;
            path.pop();
            // make this node not visited
            current->visited = false;
        }
        else {
            if (current->up != nullptr && !current->up->visited && !isInDirections(directionsList, row, col, row - 1, col)) {
                path.push(current->up);
                current->up->visited = true;
                directionsList.insert(Direction(row, col, row - 1, col),directionsList.getSize());

            }
            else if (current->left != nullptr && !current->left->visited && !isInDirections(directionsList, row, col, row, col - 1)) {
                path.push(current->left);
                current->left->visited = true;
                directionsList.insert(Direction(row, col, row, col - 1),directionsList.getSize());
            }
            else if (current->right != nullptr && !current->right->visited && !isInDirections(directionsList, row, col, row, col + 1)) {
                path.push(current->right);
                current->right->visited = true;
                directionsList.insert(Direction(row, col, row, col + 1),directionsList.getSize());
            }
            else if (current->down != nullptr && !current->down->visited && !isInDirections(directionsList, row, col, row + 1, col)) {
                path.push(current->down);
                current->down->visited = true;
                directionsList.insert(Direction(row, col, row + 1, col),directionsList.getSize());
            }
            else {
                path.pop();
                // remove the directions with the current node as the first node of the path

                for (int i = 0; i < directionsList.getSize(); ++i) {
                    if (directionsList[i].startRow == current->row && directionsList[i].startCol == current->col) {
                        directionsList.removeAt(i);
                        i--;
                    }
                }
                current->visited = false;
            }
        }
    }

    if (!found){
        cout << "None" << endl;
    }
}