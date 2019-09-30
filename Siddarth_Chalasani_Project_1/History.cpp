#include "History.h"
#include "globals.h"
#include <iostream>
using namespace std;

History::History(int nRows, int nCols) {
    m_nRows = nRows;
    m_nCols = nCols;
    for (int i = 0; i < m_nRows; i++)   //sets all elements of History array to 0
        for (int j = 0; j < m_nCols; j++)
            m_arr[i][j] = 0;
}

bool History::record(int r, int c) {
    if (r > m_nRows || c > m_nCols || r < 0 || c < 0)   //makes sure parameters are within bounds
        return false;
    m_arr[r-1][c-1]++;
    return true;
}

void History::display() const {
    clearScreen();
    for (int i = 0; i < m_nRows; i++) {
        for (int j = 0; j < m_nCols; j++) {
            if (m_arr[i][j] == 0)   //prints "." if 0 zombies were killed in that location
                cout << ".";
            else if (m_arr[i][j] < 26) {
                char temp = 'A' + m_arr[i][j] - 1;  //converts numbers to letters using ASCII
                cout << temp;
            }
            else
                cout << "Z";
        }
        cout << endl;
    }
    cout << endl;
}
