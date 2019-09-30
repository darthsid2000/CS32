#include <iostream>
#include <queue>
#include <string>
using namespace std;

class Coord
{
public:
    Coord(int rr, int cc) : m_r(rr), m_c(cc) {}
    int r() const { return m_r; }
    int c() const { return m_c; }
private:
    int m_r;
    int m_c;
};

bool pathExists(string maze[], int nRows, int nCols, int sr, int sc, int er, int ec) {
    queue<Coord> coordQueue;
    coordQueue.push(Coord(sr, sc));
    maze[sr][sc] = 'O';
    
    while (!coordQueue.empty()) {
        Coord temp = coordQueue.front();
        coordQueue.pop();
        
        if (temp.r() == er && temp.c() == ec)
            return true;
        
        if (maze[temp.r() + 1][temp.c()] == '.') {
            coordQueue.push(Coord(temp.r() + 1, temp.c()));
            maze[temp.r() + 1][temp.c()] = 'O';
        }
        
        if (maze[temp.r()][temp.c() - 1] == '.') {
            coordQueue.push(Coord(temp.r(), temp.c() - 1));
            maze[temp.r()][temp.c() - 1] = 'O';
        }
        
        if (maze[temp.r() - 1][temp.c()] == '.') {
            coordQueue.push(Coord(temp.r() - 1, temp.c()));
            maze[temp.r() - 1][temp.c()] = 'O';
        }
        
        if (maze[temp.r()][temp.c() + 1] == '.') {
            coordQueue.push(Coord(temp.r(), temp.c() + 1));
            maze[temp.r()][temp.c() + 1] = 'O';
        }
    }
    return false;
}

int main() {
    
}
