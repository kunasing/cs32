//
//  Set.h
//  project2
//
//  Created by Kunal Singhal on 1/25/23.
//

#ifndef Set_h
#define Set_h

#include <string>
#include <iostream>

using ItemType = std::string;

class Set
{
private:
    struct Node{
        ItemType m_value;
        Node* m_next;
        Node* m_prev;
    };
    
public:
    Set();               // Create an empty set (i.e., one whose size() is 0).
    
    // Housekeeping Functions
    Set(const Set& src);
    ~Set();
    Set& operator=(const Set& src);
    
    
    bool empty() const;  // Return true if the set is empty, otherwise false.
    
    int size() const;    // Return the number of items in the set.

    bool insert(const ItemType& value);
      // Insert value into the set if it is not already present.  Return
      // true if the value is actually inserted.  Leave the set unchanged
      // and return false if value is not inserted (perhaps because it
      // was already in the set or because the set has a fixed capacity and
      // is full).

    bool erase(const ItemType& value);
      // Remove the value from the set if it is present.  Return true if the
      // value was removed; otherwise, leave the set unchanged and
      // return false.

    bool contains(const ItemType& value) const;
      // Return true if the value is in the set, otherwise false.
     
    bool get(int i, ItemType& value) const;
      // If 0 <= i < size(), copy into value the item in the set that is
      // strictly greater than exactly i items in the set and return true.
      // Otherwise, leave value unchanged and return false.

    void swap(Set& other);
      // Exchange the contents of this set with the other one.
    
    void dump() const;

private:
    
    Node    m_head;                     // start of linked list, dummy node
    int     m_size;                     // number of items in the set

      // At any time, the elements of m_data indexed from 0 to m_size-1
      // are in use and are stored in increasing order.
    
    //private functions
    void addNext(Node* current, const ItemType& value);
      // adds Node containing "value" immeadiately after the node pointed to by current, and adds connections to within the nodes to each other
    
};

void unite(const Set& s1, const Set& s2, Set& result);

void butNot(const Set& s1, const Set& s2, Set& result);


#endif /* Set_hpp */
