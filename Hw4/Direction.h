//
// Halil Arda Ozongun
// ID: 22202709
// Cs201 - Hw4
// 11/05/2024
//

#ifndef HW4_DIRECTION_H
#define HW4_DIRECTION_H

class Direction {
public:
    int startRow;
    int startCol;
    int endRow;
    int endCol;
    Direction(int startRow, int startCol, int endRow, int endCol) : startRow(startRow), startCol(startCol), endRow(endRow), endCol(endCol) {}
    Direction(const Direction& other) : startRow(other.startRow), startCol(other.startCol), endRow(other.endRow), endCol(other.endCol) {}

    // Overloading == operator
    bool operator==(const Direction& other) const {
        return startRow == other.startRow && startCol == other.startCol && endRow == other.endRow && endCol == other.endCol;
    }
    bool operator!=(const Direction& other) const {
        return startRow != other.startRow || startCol != other.startCol || endRow != other.endRow || endCol != other.endCol;
    }
};

#endif //HW4_DIRECTION_H
