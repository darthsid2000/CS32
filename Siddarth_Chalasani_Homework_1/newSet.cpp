#include "newSet.h"

Set::Set() {
    numItems = 0;
    m_maxItems = DEFAULT_MAX_ITEMS;
    a = new ItemType[m_maxItems];
}

Set::Set(int maxItems) {
    numItems = 0;
    if (maxItems >= 0)
        m_maxItems = maxItems;
    else
        m_maxItems = DEFAULT_MAX_ITEMS;
    a = new ItemType[m_maxItems];
}

Set::Set(const Set& aSet) {
    numItems = aSet.numItems;
    m_maxItems = aSet.m_maxItems;
    a = new ItemType[m_maxItems];
    for (int i = 0; i < m_maxItems; i++)
        this->a[i] = aSet.a[i];
}

Set::~Set() {
    delete [] a;
}

Set& Set::operator=(const Set& aSet) {
    if (this != &aSet) {
        numItems = aSet.numItems;
        m_maxItems = aSet.m_maxItems;
        a = new ItemType[m_maxItems];
        for (int i = 0; i < m_maxItems; i++)
            this->a[i] = aSet.a[i];
    }
    return *this;
}

bool Set::empty() const {
    return !numItems;
}

int Set::size() const {
    return numItems;
}

bool Set::insert(const ItemType& value) {
    if (numItems == m_maxItems) // checking if set is already at max capacity
        return false;
    for (int i = 0; i < numItems; i++) // chacking if value is already present in set
        if (value == a[i])
            return false;
    a[numItems] = value;
    numItems++;
    return true;
}

bool Set::erase(const ItemType& value) {
    for (int i = 0; i < numItems; i++)
        if (a[i] == value) {
            a[i] = a[numItems-1];
            numItems--;
            return true;
        }
    return false;
}

bool Set::contains(const ItemType& value) const {
    for (int i = 0; i < numItems; i++)
        if (a[i] == value)
            return true;
    return false;
}

bool Set::get(int i, ItemType& value) const {
    if (i < 0 || i >= numItems)
        return false;
    int count;
    for (int j = 0; j < numItems; j++) {
        count = 0;
        for (int k = 0; k < numItems; k++) {
            if (k == j)
                continue;
            if (a[j] > a[k])
                count++;
        }
        if (count == i) {
            value = a[j];
            return true;
        }
    }
    return false;
}

void Set::swap(Set& other) {
    ItemType* temp = a;
    this->a = other.a;
    other.a = temp;
    
    int tempNumItems = this->numItems;
    this->numItems = other.numItems;
    other.numItems = tempNumItems;
    
    int tempMaxItems = this->m_maxItems;
    this->m_maxItems = other.m_maxItems;
    other.m_maxItems = tempMaxItems;
}
