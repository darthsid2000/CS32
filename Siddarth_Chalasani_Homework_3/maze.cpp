bool pathExists(string maze[], int nRows, int nCols, int sr, int sc, int er, int ec) {
    if (sr == er && sc == ec)
        return true;
    if (maze[sr][sc] != '.')
        return false;
    maze[sr][sc] = 'O';
    if (pathExists(maze, nRows, nCols, sr+1, sc, er, ec) || pathExists(maze, nRows, nCols, sr, sc-1, er, ec) ||
        pathExists(maze, nRows, nCols, sr-1, sc, er, ec) || pathExists(maze, nRows, nCols, sr, sc+1, er, ec))
        return true;
    return false;
}
