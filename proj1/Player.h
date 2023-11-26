//
//  Player.hpp
//  proj1
//
//  Created by Kunal Singhal on 1/13/23.
//

#ifndef Player_hpp
#define Player_hpp

#include <stdio.h>
#include <string>

class Arena;

class Player
{
  public:
      // Constructor
    Player(Arena* ap, int r, int c);

      // Accessors
    int  row() const;
    int  col() const;
    bool isDead() const;

      // Mutators
    std::string dropPoisonedCarrot();
    std::string move(int dir);
    void   setDead();

  private:
    Arena* m_arena;
    int    m_row;
    int    m_col;
    bool   m_dead;
};


#endif /* Player_hpp */
