//
//  CardSet.cpp
//  homework1
//
//  Created by Kunal Singhal on 1/21/23.
//

#include "CardSet.hpp"

CardSet::CardSet(){}

bool CardSet::add(unsigned long cardNumber){
    return m_cardSet.insert(cardNumber);
}

int CardSet::size() const{
    return m_cardSet.size();
}

void CardSet::print() const{
    ItemType current;
    int i = 0;
    while(m_cardSet.get(i, current)){
        std::cout << current << std::endl;
        i++;
    }
}
