//
//  Set.cpp
//  homework1
//
//  Created by Kunal Singhal on 1/19/23.
//

#include "Set.h"
#include <iostream>



Set::Set(){
    m_size = 0;
}

bool Set::empty() const{
    return size() == 0;
}

int Set::size() const{
    return m_size;
}

bool Set::insert(const ItemType& value){
    if (m_size == DEFAULT_MAX_ITEMS || contains(value))
        return false;

    int insertLocation;
    for (insertLocation = 0; insertLocation < m_size; insertLocation++)
        if (value < m_set[insertLocation])
            break;

    for (int i = m_size; i > insertLocation; i--)
        m_set[i] = m_set[i-1];
    
    m_set[insertLocation] = value;
    m_size++;

    return true;
}

bool Set::erase(const ItemType& value){
    int erasePosition;
    for (erasePosition = 0; erasePosition < m_size; erasePosition++)
        if (m_set[erasePosition] == value)
            break;
    
    if (erasePosition == m_size)
        return false;
    
    for (int i = erasePosition; i + 1 < m_size; i++)
        m_set[i] = m_set[i+1];

    m_size--;
    return true;
}

bool Set::contains(const ItemType& value) const{
    for (int i = 0; i < m_size; i++)
        if (m_set[i] == value)
            return true;
    return false;
}

bool Set::get(int i, ItemType& value) const{
    if (i < 0 || i >= m_size)
        return false;
    
    value = m_set[i];
    
    return true;
}

void Set::swap(Set& other){
    Set temp;
    temp = *this;
    *this = other;
    other = temp;
}

void Set::dump() const{
    for (int i = 0; i < m_size; i++)
        std::cerr << "item " << i << ": " << m_set[i] << "\n";
    std::cerr << "set size is " << m_size << "\n";
}
