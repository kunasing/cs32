// Project 2 Testing Page

#include <iostream>
#include "Set.h"
using namespace std;

int main() {
    
    
//    // test functions!
    
    // using Item Type = std::string
    Set s1;

    // checks that freshly initialized set is empty
    assert(s1.size() == 0 && s1.empty());
    
    ItemType a = "unchanged";

    
    // check that cannot remove random values and nothing to get
    assert(s1.erase("h") == false && s1.get(0, a) == false && a == "unchanged");
    
    // checking insert and size functions
    assert(s1.insert("a") && s1.size() == 1 && s1.empty() == false);
    // cannot insert previously inserted values
    assert(s1.insert("a") == false);
    
    // adding new values
    assert(s1.insert("b") && s1.insert("c") && s1.insert("d"));
    assert(s1.size() == 4);
    
    // testing get works properly
    assert(s1.get(2, a) && s1.contains(a) && a == "c");
    
    Set s2 = s1;
    Set s3;
    s3 = s1;
    
    // copy constructor and assignment operators work properly
    assert(s2.contains("d") && s2.size() == 4);
    assert(s3.contains("c") && s3.size() == 4);
    
    Set s4;
    s4.insert("z");
    s4.insert("y");
        
    // testing swap
    s4.swap(s1);
    
    assert(s1.contains("z") && s1.contains("a") == false && s1.size() == 2);
    
    assert(s4.contains("b") && s4.contains("y") == false && s4.size() == 4);
    
    // test erase function, from both front, middle, and back of sorted set
    assert(s4.erase("a") && s4.erase("c"));
    assert(s4.get(2, a) == false && s4.get(0, a));
    
    assert(a == "b");
    
    assert(s4.erase("d") && s4.erase("b"));

    // s1 now empty
    Set empty1;
    s1.swap(empty1);
    
    s1.insert("a");
    s1.insert("b");
    s1.insert("c");
    
    s2 = s1;
    
    s2.insert("d");
    s2.insert("e");
    s2.insert("f");
    
    // test of butnot
    
    butNot(s2, s1, s3);
    
    assert(s3.contains("a") == false && s3.contains("d") && s3.size() == 3);
    
    // s3 now contains d, e, f
    
    
    // test of unite
    unite(s1, s3, s4);
    
    assert(s4.contains("a") && s4.contains("b") && s4.contains("c") && s4.contains("d") && s4.contains("e") && s4.contains("f") && s4.contains("z") == false && s4.size() == 6);
    
    
    
    
}
