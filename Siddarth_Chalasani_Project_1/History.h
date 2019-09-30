#ifndef History_h
#define History_h
#include "globals.h"

class History
{
public:
    History(int nRows, int nCols);
    bool record(int r, int c);
    void display() const;
private:
    int m_nRows;
    int m_nCols;
    int m_arr[MAXROWS][MAXCOLS];
};

#endif
