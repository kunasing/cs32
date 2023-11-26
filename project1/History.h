//
//  History.hpp
//  proj1
//
//  Created by Kunal Singhal on 1/13/23.
//

#ifndef History_hpp
#define History_hpp

#include <stdio.h>
#include "globals.h"

class History
    {
      public:
        History(int nRows, int nCols);
        bool record(int r, int c);
        void display() const;
    private:
        int rows, cols;
        int grid[MAXROWS][MAXCOLS];
    };

#endif /* History_hpp */

