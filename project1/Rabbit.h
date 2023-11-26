//
//  Rabbit.hpp
//  proj1
//
//  Created by Kunal Singhal on 1/12/23.
//



#ifndef Rabbit_hpp
#define Rabbit_hpp

#include <stdio.h>

class Arena;


class Rabbit
{
  public:
      // Constructor
    Rabbit(Arena* ap, int r, int c);

      // Accessors
    int  row() const;
    int  col() const;
    bool isDead() const;

      // Mutators
    void move();

  private:
    Arena* m_arena;
    int    m_row;
    int    m_col;
    int    m_health;
    int    m_idleTurnsRemaining;
};





#endif /* Rabbit_hpp */
