#include "Set.h"

Set::Set() {
    numItems = 0;
}

bool Set::empty() const {
    return !numItems;
}

int Set::size() const {
    return numItems;
}

bool Set::insert(const ItemType& value) {
    if (numItems == DEFAULT_MAX_ITEMS) // checking if set is already at max capacity
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
    ItemType temp;
    for (int i = 0; i < this->numItems || i < other.numItems; i++) {
        temp = this->a[i];
        this->a[i] = other.a[i];
        other.a[i] = temp;
    }
    
    int tempNumItems = this->numItems;
    this->numItems = other.numItems;
    other.numItems = tempNumItems;
}
