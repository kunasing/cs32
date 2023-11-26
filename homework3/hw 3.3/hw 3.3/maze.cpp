#include <iostream>
#include <string>
using namespace std;




bool pathExists(string maze[], int nRows, int nCols, int sr, int sc, int er, int ec);


void printMaze(string maze[], int nRows){
    for (int i = 0; i < nRows; i++)
        cerr << maze[i] << endl;
    cerr << endl;
}


int main(){
    
    
    
    string maze[10] = {
                    "XXXXXXXXXX",
                    "X..X...X.X",
                    "X.XXXX.X.X",
                    "X.X.X..X.X",
                    "X...X.XX.X",
                    "XXX......X",
                    "X.X.XXXX.X",
                    "X.XXX....X",
                    "X...X..X.X",
                    "XXXXXXXXXX"
                };

    printMaze(maze, 10);
                if (pathExists(maze, 10,10, 5,3, 1,3))
                    cout << "Solvable!" << endl;
                else
                    cout << "Out of luck!" << endl;
    printMaze(maze, 10);


}





bool pathExists(string maze[], int nRows, int nCols, int sr, int sc, int er, int ec){
        
    if (sr == er && sc == ec)
        return true;
    
    maze[sr][sc] = '!';
    bool pass = false;
    
    
    
    if (maze[sr - 1][sc] == '.')
        pass = pathExists(maze, nRows, nCols, sr - 1, sc, er, ec);
    
    if(pass == true)
        return true;
    
    
    
    if (maze[sr + 1][sc] == '.')
        pass = pathExists(maze, nRows, nCols, sr + 1, sc, er, ec);
    if(pass == true)
        return true;
    
    
    
    if (maze[sr][sc + 1] == '.')
        pass = pathExists(maze, nRows, nCols, sr, sc + 1, er, ec);
    
    if(pass == true)
        return true;
    
    
    
    if (maze[sr][sc - 1] == '.')
        pass = pathExists(maze, nRows, nCols, sr, sc - 1, er, ec);
    
    if(pass == true)
        return true;
    
    

    
    
    return false;
    
    
}
