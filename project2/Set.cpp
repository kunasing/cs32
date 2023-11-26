//
//  Set.cpp
//  project2
//
//  Created by Kunal Singhal on 1/25/23.
//

#include "Set.h"

// Housekeeping Functions


Set::Set(){
    m_size = 0;
    m_head.m_next = nullptr;
    m_head.m_prev = nullptr;
    m_head.m_value = false;
}

Set::Set(const Set& src){
    m_size = 0;
    m_head.m_next = nullptr;
    m_head.m_prev = nullptr;
    m_head.m_value = false;
    
    for (int i = 0; i < src.size(); i++){
        ItemType toInsert;
        src.get(i, toInsert);
        insert(toInsert);
    }
}

Set::~Set(){
    if (!empty()){
        Node* current = &m_head;
        current = current->m_next;
        while (current->m_next != nullptr){
            current = current->m_next;
            delete current->m_prev;
        }
        delete current;
    }

    
//    while(!empty()){
//        ItemType toDelete;
//        get(0, toDelete);
//        erase(toDelete);
//    }
    
}

Set& Set::operator=(const Set& src){
    Set copy = src;
    swap(copy);
    return *this;
    
}


// Public Functions

bool Set::empty() const{
    return m_size == 0;
}

int Set::size() const{
    return m_size;
}

bool Set::insert(const ItemType& value){
    if (contains(value))
        return false;
    Node* current = &m_head;
    while (current->m_next != nullptr && current->m_next->m_value < value)
        current = current->m_next;
    addNext(current, value);
    m_size++;
    return true;
}

bool Set::erase(const ItemType& value){
    
    if (!contains(value))
        return false;
    Node* current = &m_head;
    while (current->m_next != nullptr && current->m_next->m_value != value)
        current = current->m_next;
    Node* toDelete = current->m_next;
    current->m_next = toDelete->m_next;
    delete toDelete;
    if (current ->m_next != nullptr)
        current->m_next->m_prev = current;
    m_size--;
    return true;
    
    
    
}

bool Set::contains(const ItemType& value) const{
    if (empty())
        return false;
    const Node* current = &m_head;
    while (current->m_next != nullptr){
        current = current->m_next;
        if (current->m_value == value)
            return true;
    }
    return false;
}
 
bool Set::get(int i, ItemType& value) const{
    if (i < 0 || i >= m_size)
        return false;
    const Node* current = &m_head;
    current = current->m_next;
    for (; i > 0; i--)
        current = current->m_next;
    value = current->m_value;
    return true;
}

void Set::swap(Set& other){
    Node newHead = other.m_head;
    other.m_head = m_head;
    m_head = newHead;
    
    int newSize = other.m_size;
    other.m_size = m_size;
    m_size = newSize;
}

void Set::dump() const{
    const Node* current = &m_head;
    while (current->m_next != nullptr){
        current = current->m_next;
        std::cerr << "                 "<< current->m_value << std::endl;
        std:: cerr << "prev location:    " << current->m_prev << "\ncurr location:    " << current << "\nnext location:    " << current->m_next << std::endl;
        }
    std::cerr << "set size is " << m_size << std::endl;
}

// Private Functions

void Set::addNext(Node* current, const ItemType& value){
    if (current == nullptr)
        exit(1);
    Node* newNode = new Node;
    newNode->m_next = current->m_next;
    newNode->m_prev = current;
    newNode->m_value = value;
    
    if(current->m_next != nullptr)
        newNode->m_next->m_prev = newNode;
    current->m_next = newNode;
}

// External Functions


void unite(const Set& s1, const Set& s2, Set& result){
    
    if (&s2 == &result){
        
        for (int i = 0; i < s1.size(); i++){
            ItemType copy;
            s1.get(i, copy);
            result.insert(copy);
        }
    }
    else{
        result = s1;
        
        for (int i = 0; i < s2.size(); i++){
            ItemType copy;
            s2.get(i, copy);
            result.insert(copy);
        }
    }
    
}


void butNot(const Set& s1, const Set& s2, Set& result){
    if(&s1 == &s2){
        Set empty;
        result = empty;
    }
    else if (&s2 == &result){
        Set dataToRemove = s2;
        result = s1;
        for (int i = 0; i < dataToRemove.size(); i++){
            ItemType toDelete;
            dataToRemove.get(i, toDelete);
            result.erase(toDelete);
        }
    }
    else{
        result = s1;
        for (int i = 0; i < s2.size(); i++){
            ItemType toDelete;
            s2.get(i, toDelete);
            result.erase(toDelete);
        }
    }
    
    
}
