#include "Set.h"
#include <iostream>
#include <string>
#include <cassert>
using namespace std;

int main()
{
    Set s;
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
