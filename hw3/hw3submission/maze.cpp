

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
