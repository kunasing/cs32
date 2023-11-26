//
//  main.cpp
//  homework1
//
//  Created by Kunal Singhal on 1/21/23.
//

#include "CardSet.h"
#include <iostream>
#include <string>
#include <cassert>

int main() {

    CardSet myset;

    assert(myset.size() == 0);
    assert(myset.add(8) && myset.size() == 1);
    assert(!myset.add(8) && myset.size() == 1);
    assert(myset.add(3) && myset.add(1) && myset.add(6) && myset.add(4));

    myset.print();

    std::cout << "All tests passed.\n";

}
