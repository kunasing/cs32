#ifndef ACTOR_H_
#define ACTOR_H_

#include "GraphObject.h"

class StudentWorld;
// Students:  Add code to this file, Actor.cpp, StudentWorld.h, and StudentWorld.cpp


const int PIXEL_SIZE = 16;

class Actor: public GraphObject{
private:
    bool alive = true;
    StudentWorld* m_world = nullptr;
    
public:
    Actor(int imageID, int startX, int startY, int dir, int depth, StudentWorld* world);
    virtual void doSomething() = 0;
    
    // Student world will deallocate actor if dead
    bool isDead() const {return !alive;}
    void setDead() {alive = false;}
    
    // Returns a pointer to the world that an actor resides in. Allows access to world member functions.
    StudentWorld* world() const {return m_world;};
    
    // Actor movement considerations.
    bool canMove(int dir) const;
    bool forksAvailable() const;
    
    void teleport();
    
    // Necessary to know for all actors.
    virtual bool canBeKilled() = 0;
    virtual bool vortexHittable() = 0;

};


// PLAYER AVATAR

class playerAvatar: public Actor{
private:
    int playerNum;
    int coins = 0;
    int stars = 0;
    bool vortexes = false;
    
    int m_walkDirection = right;
    bool m_walking = false;
    int m_ticksToMove = 0;
    
    // allows for swapping, called only by swapspots
    void getSwapped(int& walkDir, bool& isWalking, int& ticksLeft, int& x, int& y);
        
public:
    playerAvatar(int imageID, int startX, int startY, StudentWorld* world, int playerNum);
    virtual void doSomething();
    
    void walk();
    virtual bool solveFork();
    virtual void stand();
    
    int getPlayer() const{return playerNum;}

    // accessors and modifiers of player coins, stars, vortexes
    void giveCoins(int coinsToAdd);
    void giveStars(int starsToAdd);
    void giveVortex()   {vortexes = true;}
    
    void setCoins(int newcoins){coins = newcoins;}
    void setStars(int newstars){stars = newstars;}
    
    int getStars() const {return stars;}
    int getCoins() const {return coins;}
    bool hasVortex()      {return vortexes == true;}   //nti
    
    int getRoll() const {return (m_ticksToMove + 7)/ 8;}
    
    // swaps player of self with given player
    void swapSpots(playerAvatar*& player);
    
    // accessors and modifiers of movement info
    int walkDirection() {return m_walkDirection;}
    bool walking() {return m_walking;}
    int ticksToMove() {return m_ticksToMove;}
    
    void setWalkDirection (int dir) {m_walkDirection = dir;}
    void setWalking (bool walking) {m_walking = walking;}
    void setTicksToMove (int ticks) {m_ticksToMove = ticks;}
    
    // players cannot be killed nor hit by vortexes
    bool canBeKilled()  {return false;}
    virtual bool vortexHittable()  {return false;}
    
};


// BOWSER AND BOO

class Baddie: public playerAvatar{
private:
    int pauseCounter = 180;
    bool activatedThisStop[2] = {false, false};
    
public:
    Baddie(int imageID, int startX, int startY, StudentWorld* world);
    
    //overriding of stand action and fork solving from player, do not necessitate player input
    virtual void stand();
    virtual bool solveFork();
    
    // different for every baddie
    virtual void attack(int p) = 0;
    virtual void startOfStand() = 0;
    virtual int maxRoll() = 0;
    
    // baddies can be hit by vortexes
    bool vortexHittable()  {return true;}
    
};

class Bowser: public Baddie{
public:
    Bowser(int startX, int startY, StudentWorld* world);
    void attack(int p);
    void startOfStand();
    int maxRoll()  {return 10;}

};

class Boo: public Baddie{
public:
    Boo(int startX, int startY, StudentWorld* world);
    void attack(int p);
    void startOfStand();
    int maxRoll()  {return 3;}
};

//Squares

class Square: public Actor{
private:
    bool m_playerWasHere[2] = {false, false};         // player was here last tick
    bool m_playerWasWasHere[2] = {false, false};      // player was here 2 ticks ago
    
public:
    Square(int imageID, int startX, int startY, int dir, StudentWorld* world);
    virtual void doSomething();
    virtual void playerLandsAction(int p) = 0;
    virtual void playerPassAction(int p) = 0;
    
    // returns if player was at a square last tick or the tick before
    bool playerWasWasHere(int p) const {return m_playerWasWasHere[p];}
    bool playerWasHere(int p) const {return m_playerWasHere[p];}
    
    // sets that a player is here this tick, updates previous two ticks
    void playerIsHere(int p, bool trueOrNot) {      m_playerWasWasHere[p] = m_playerWasHere[p];  m_playerWasHere[p] = trueOrNot;}
    
    // makes sure the square does not activate on the given player
    void noActivate(int p){m_playerWasWasHere[p] = true; m_playerWasHere[p] = true;}
    
    // squares can be killed but not hit by vortexes
    bool canBeKilled() {return true;}
    bool vortexHittable()  {return false;}
    
};

class coinSquare: public Square{
private:
    int coinsToGive;
    
public:
    coinSquare(bool evil, int imageID, int startX, int startY, StudentWorld* world);
    virtual void playerLandsAction(int p);
    virtual void playerPassAction(int p)    {};    // DOES NOTHING
};

class starSquare: public Square{
public:
    starSquare(int startX, int startY, StudentWorld* world);
    virtual void playerLandsAction(int p);          // BOTH ARE SAME
    virtual void playerPassAction(int p)        {playerLandsAction(p);};
};

class directionSquare: public Square{
private:
    int direction = 0;
public:
    directionSquare(int dir, int startX, int startY, StudentWorld* world);
    virtual void playerLandsAction(int p);          // BOTH ARE SAME
    virtual void playerPassAction(int p)        {playerLandsAction(p);};
};

class bankSquare: public Square{
public:
    bankSquare(int startX, int startY, StudentWorld* world);
    virtual void playerLandsAction(int p);
    virtual void playerPassAction(int p);
};

class eventSquare: public Square{
public:
    eventSquare(int startX, int startY, StudentWorld* world);
    virtual void playerLandsAction(int p);
    virtual void playerPassAction(int p)    {}; //DOES NOTHING
};

class droppingSquare: public Square{
public:
    droppingSquare(int startX, int startY, StudentWorld* world);
    virtual void playerLandsAction(int p);
    virtual void playerPassAction(int p)    {}; //DOES NOTHING
};



class Vortex: public Actor{
private:
    int dir;
public:
    Vortex(int startX, int startY, int dir, StudentWorld* world);
    void doSomething();
    
    // vortexes cannot be killed by bowser nor can be hit by other vortexes
    bool canBeKilled()  {return false;}
    bool vortexHittable()  {return false;}
};



#endif // ACTOR_H_
