//
//  History.cpp
//  proj1
//
//  Created by Kunal Singhal on 1/13/23.
//

#include "History.h"
#include <iostream>
using namespace std;

void clearScreen();

History::History(int nRows, int nCols){
    rows = nRows;
    cols = nCols;
    for (int r = 1; r <= rows; r++)
        for (int c = 1; c <= cols; c++)
            grid[r-1][c-1] = 0;
}

bool History::record(int r, int c){
    if (r-1 > rows || c-1 > cols)
        return false;
    
    grid[r-1][c-1]++;
    return true;
}

void History::display() const{
    
    
    char displayGrid[MAXROWS][MAXCOLS];
    int r, c;
    
      // Fill displayGrid with dots (empty) and letter corresponding to number of poisoned carrots placed
    for (r = 1; r <= rows; r++)
        for (c = 1; c <= cols; c++){
            int currentSquareRecord = grid[r-1][c-1];
            char& currentDisplay = displayGrid[r-1][c-1];
            switch (currentSquareRecord) {
                case 0:
                    currentDisplay = '.';
                    break;
                default:
                    currentDisplay = 'A' - 1 + currentSquareRecord;
                    break;
            }
            if (currentDisplay != '.' && !isupper(currentDisplay))
                currentDisplay = 'Z';
        }
    
    

    // Draw the grid
    clearScreen();
    for (r = 1; r <= rows; r++)
    {
        for (c = 1; c <= cols; c++)
            cout << displayGrid[r-1][c-1];
        cout << endl;
    }
    cout << endl;
    
}
