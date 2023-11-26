//
//  Game.hpp
//  proj1
//
//  Created by Kunal Singhal on 1/13/23.
//

#ifndef Game_hpp
#define Game_hpp

#include <stdio.h>
#include <string>

class Arena;


class Game
{
  public:
      // Constructor/destructor
    Game(int rows, int cols, int nRabbits);
    ~Game();

      // Mutators
    void play();

  private:
    Arena* m_arena;

      // Helper functions
    std::string takePlayerTurn();
};

#endif /* Game_hpp */
