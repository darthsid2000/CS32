#include "SSNSet.h"
#include <iostream>
using namespace std;

SSNSet::SSNSet() {
}

bool SSNSet::add(unsigned long ssn) {
    return m_Set.insert(ssn);
}

int SSNSet::size() const {
    return m_Set.size();
}

void SSNSet::print() const {
    unsigned long temp;
    for (int i = 0; i < m_Set.size(); i++) {
        m_Set.get(i, temp);
        cout << temp << endl;
    }
}
