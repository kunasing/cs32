#include <iostream>
#include <string>
#include <stack>
using namespace std;

class Coord{
 public:
     Coord(int r, int c) : m_row(r), m_col(c) {}
     int r() const { return m_row; }
     int c() const { return m_col; }
 private:
     int m_row;
     int m_col;
 };

void printMaze(string maze[], int nRows){
    for (int i =0; i < nRows; i++)
        cerr << maze[i] << endl;
    cerr << endl;
}



bool pathExists(string maze[], int nRows, int nCols, int sr, int sc, int er, int ec){
    
    stack<Coord> solver;
    
    solver.push(Coord(sr, sc));
    maze[sr][sc] = '!';
    printMaze(maze, nRows);
    while (solver.empty() == false) {
        Coord loc = solver.top();       // current location var
        cout << loc.r() << "," << loc.c() << "\n";
        
        if (loc.r() == er && loc.c() == ec)
            return true;
        solver.pop();
        if (maze[loc.r()][loc.c() + 1] == '.'){
            solver.push(Coord(loc.r(), loc.c() + 1));
            maze[loc.r()][loc.c() + 1] = '!';
        }
        if (maze[loc.r() - 1][loc.c()] == '.'){
            solver.push(Coord(loc.r() - 1, loc.c()));
            maze[loc.r() - 1][loc.c()] = '!';
        }
        if (maze[loc.r()][loc.c() - 1] == '.'){
            solver.push(Coord(loc.r(), loc.c() - 1));
            maze[loc.r()][loc.c() - 1] = '!';
        }
        if (maze[loc.r() + 1][loc.c()] == '.'){
            solver.push(Coord(loc.r() + 1, loc.c()));
            maze[loc.r() + 1][loc.c()] = '!';
        }

        
    }
    
    return false;
    
}


//int main(int argc, const char * argv[]) {
//
//
//
//    string maze[10] = {
//                    "XXXXXXXXXX",
//                    "X..X...X.X",
//                    "X.XXXX.X.X",
//                    "X.X.X..X.X",
//                    "X...X.XX.X",
//                    "XXX......X",
//                    "X.X.XXXX.X",
//                    "X.XXX....X",
//                    "X...X..X.X",
//                    "XXXXXXXXXX"
//                };
//
//                if (pathExists(maze, 10,10, 5,3, 8,5))
//                    cout << "Solvable!" << endl;
//                else
//                    cout << "Out of luck!" << endl;
//
//}
