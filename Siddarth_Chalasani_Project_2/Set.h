//
//  Set.hpp
//  project_2
//
//  Created by Siddarth Chalasani on 1/28/19.
//  Copyright © 2019 Siddarth Chalasani. All rights reserved.
//

#ifndef Set_h
#define Set_h

#include <string>

using ItemType = std::string;

class Set
{
public:
    Set();
    Set(const Set& other);
    ~Set();
    Set& operator=(const Set& other);
    bool empty() const;
    int size() const;
    bool insert(const ItemType& value);
    bool erase(const ItemType& value);
    bool contains(const ItemType& value) const;
    bool get(int pos, ItemType& value) const;
    void swap(Set& other);
    
private:
    struct Node {
        Node* prev;
        Node* next;
        ItemType item;
    };
    Node* dummy;
    int m_size;
};

void unite(const Set& s1, const Set& s2, Set& result);

void subtract(const Set& s1, const Set& s2, Set& result);

#endif /* Set_hpp */
