#ifndef STUDENTWORLD_H_
#define STUDENTWORLD_H_

#include "GameWorld.h"
#include "Board.h"
#include <string>
#include "Actor.h"
#include <list>

// Students:  Add code to this file, StudentWorld.cpp, Actor.h, and Actor.cpp

class StudentWorld : public GameWorld{
private:
    void setupBoard();
    std::vector<playerAvatar*> m_players;
    std::list<Actor*> actors;
    Board bd;
    
    int bank = 0;
    
public:
    // GIVEN FUNCTIONS
    StudentWorld(std::string assetPath);
    ~StudentWorld();
    virtual int init();
    virtual int move();
    virtual void cleanUp();
    
    // BOARD CHECKERS
    bool bdPositionExists(int x, int y);
    bool bdPositionExistsExactly(int graphX, int graphY);
    bool directionSquareHere(int x, int y);
    bool sameLocation(Actor* actor1, Actor* actor2) const;
    
    // BOARD MODIFIERS
    void replaceWithDroppingSquare(int x, int y);
    
    // GET PLAYERS
    playerAvatar* player(int i) const {   return m_players[i];}
    
    //BANKING
    void addToBank(int coins)     {bank += coins;};
    int bankBalance()   {return bank;}
    
    // VORTEXING
    bool checkVortexKill(Actor* vortex);
    void shootVortex(int x, int y, int dir);

};

#endif // STUDENTWORLD_H_
