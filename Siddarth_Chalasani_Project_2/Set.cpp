//
//  Set.cpp
//  project_2
//
//  Created by Siddarth Chalasani on 1/28/19.
//  Copyright © 2019 Siddarth Chalasani. All rights reserved.
//

#include "Set.h"
#include <string>

Set::Set() {
    dummy = new Node;
    dummy->next = dummy;    // dummy node points to itself
    dummy->prev = dummy;
    m_size = 0;
}

Set::Set(const Set& other) {
    dummy = new Node;
    dummy->next = dummy;
    dummy->prev = dummy;
    m_size = 0;             // creates an empty set
    
    Node* p = other.dummy->next;
    while (p != other.dummy) {
        insert(p->item);    // copies every item from the other set
        p = p->next;
    }
}

Set::~Set() {
    Node* p;
    Node* temp;
    for (p = dummy->next; p != dummy;)  // iterate through all nodes that contain values, stop at dummy head node
    {
        temp = p;           // store current node in temp
        p = p->next;        // change traversal pointer to point to next node before deleting current node
        delete temp;
    }
    delete p;
}

Set& Set::operator=(const Set& other) {
    if (this == &other)
        return *this;
    
    Node* p = dummy->next;
    while (p != dummy) {
        p = p->next;
        delete p->prev;     // deletes all nodes except for the dummy node
    }
    
    dummy->next = dummy;
    dummy->prev = dummy;
    m_size = 0;             // makes it an empty set
    
    p = other.dummy->next;
    while (p != other.dummy) {
        insert(p->item);
        p = p->next;        // copies every item from the other set
    }
    
    return *this;
}

bool Set::empty() const {
    if (m_size == 0)
        return true;
    return false;
}

int Set::size() const {
    return m_size;
}

bool Set::insert(const ItemType& value) {
    Node* p = dummy->next;
    while (p != dummy) {
        if (p->item == value)       // if value is already contained in the set, insert does nothing and returns false
            return false;
        p = p->next;
    }
    Node* newNode = new Node;
    newNode->item = value;
    newNode->next = dummy;
    newNode->prev = dummy->prev;    // updates new node's prev and next pointers
    m_size++;
    
    dummy->prev->next = newNode;    // previously last node's next pointer now points to new node
    dummy->prev = newNode;          // dummy's prev pointer now points to new node
    
    return true;
}

bool Set::erase(const ItemType& value) {
    Node* p = dummy->next;
    while (p != dummy) {
        if (p->item == value)       // pointer points to node containing value
            break;
        p = p->next;
    }
    
    if (p == dummy)                 // if value was not contained in any pointer
        return false;
    
    p->prev->next = p->next;
    p->next->prev = p->prev;        // nodes before and after p now point to each other
    delete p;
    m_size--;
    
    return true;
}

bool Set::contains(const ItemType& value) const {
    Node* p = dummy->next;
    while (p != dummy) {
        if (p->item == value)
            return true;
        p = p->next;
    }
    
    return false;
}

bool Set::get(int pos, ItemType& value) const {
    if (pos < 0 || pos >= m_size)       // if pos is out of bounds
        return false;
    
    Node* p = dummy->next;
    while (p != dummy) {
        int count = 0;
        Node* q = p->next;
        while (q != p) {
            if (q == dummy) {           // skips over dummy node in circular implementation
                q = q->next;
                continue;
            }
            
            if (p->item > q->item)
                count++;                // counts how many items are greater than that contained in p
            q = q->next;
        }
        
        if (count == pos) {             // if item in p is greater than the desired number of items
            value = p->item;
            return true;
        }
        
        p = p->next;
    }
    
    return false;
}

void Set::swap(Set& other) {
    Node* temp = other.dummy;
    other.dummy = dummy;
    dummy = temp;
    
    int tempSize = other.m_size;
    other.m_size = m_size;
    m_size = tempSize;
}

void unite(const Set& s1, const Set& s2, Set& result) {
    Set tempSet;        // temporary set where all the values of s1 and s2 will be stored
    
    for (int i = 0; i < s1.size(); i++) {
        ItemType temp;
        s1.get(i, temp);
        tempSet.insert(temp);
    }
    
    for (int i = 0; i < s2.size(); i++) {
        ItemType temp;
        s2.get(i, temp);
        tempSet.insert(temp);
    }
    
    result = tempSet;
}

void subtract(const Set& s1, const Set& s2, Set& result) {
    Set tempSet;        // temporary set where all the values in s1 and not s2 will be stored
    
    for (int i = 0; i < s1.size(); i++) {
        ItemType temp;
        s1.get(i, temp);
        tempSet.insert(temp);
    }
    
    for (int i = 0; i < s2.size(); i++) {
        ItemType temp;
        s2.get(i, temp);
        tempSet.erase(temp);
    }
    
    result = tempSet;
}
