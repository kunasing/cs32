//
//  main.cpp
//  homework1
//
//  Created by Kunal Singhal on 1/21/23.
//

#include "newSet.h"
#include <iostream>
#include <string>
#include <cassert>
using namespace std;

int main() {

    Set set1(13);
    Set set2(26);
    
    for (char i = 'a'; i <= 'm'; i++){
        std::string a = "";
        a.push_back(i);
        assert(set1.insert(a));
    }
    
    for (char i = 'A'; i <= 'Z'; i++){
        std::string a = "";
        a.push_back(i);
        assert(set2.insert(a));
    }
    
    assert(set1.size() == 13 && set2.size() == 26);
    assert(!set1.insert("past max") && set1.size() == 13);
    assert(!set2.insert("past max") && set2.size() == 26);
    
    
    Set setA(set1);
    Set setB(100);
    setB = set2;
    
    assert(setA.contains("a") && setA.size() == 13);
    assert(setB.contains("A") && setB.size() == 26);
    
    
    for (int i =0 ; i < 10; i++)  //allocate multiple new sets to test for memory leak
        Set x(4000);
    
    
    //old tests to test other
    Set s(5);
    assert(s.empty());
    ItemType x = "unchanged";
    assert( !s.get(3, x)  &&  x == "unchanged");
    s.insert("a");
    s.insert("b");
    assert(s.contains("a"));
    assert(s.size() == 2);
    s.insert("c");
    s.insert("d");
    assert(s.get(3,x) && x == "d");
    assert(s.erase("b") && s.size() == 3 && s.contains("b") == false);
    assert(!s.insert("a") && s.size() == 3);
    s.insert("e");
    assert(s.size() == 4 && !s.get(4, x));
    
    
    
    cout << "Passed all tests" << endl;
}
    
    
    

