#ifndef ACTOR_H_
#define ACTOR_H_

#include "GraphObject.h"

class StudentWorld;
// Students:  Add code to this file, Actor.cpp, StudentWorld.h, and StudentWorld.cpp

// getX, getY, moveTo
// getDirection, setDirection
// getPositioninthisdireeciotn
// moveAtAngle
const int PIXEL_SIZE = 16;

class Actor: public GraphObject{
private:
    bool alive = true;
    
public:
    Actor(int imageID, int startX, int startY, int dir, int depth);
    virtual void doSomething() = 0;
    bool isDead() {return !alive;}
    void setDead() {alive = false;}
};

class playerAvatar: public Actor{
private:
    StudentWorld* world;
    int playerNum;
    int coins = 0;
    int stars = 0;
    int vortexes = 0;
    
    int walkDirection = right;
    bool walking = false;
    int ticksToMove = 0;
    
    bool canMoveForward();
    
public:
    int getPlayer(){return playerNum;}
    playerAvatar(int imageID, int startX, int startY, StudentWorld* world, int playerNum);
    virtual void doSomething();
};



//4. A Player Avatar object has a starting (x,y) position based on the board data file.
//Your StudentWorld object can pass in that position when constructing this object.
//5. A Player Avatar must keep track of whether it is player 1 (uses left side of
//keyboard) or player 2 (uses right side of keyboard).
//9. A Player Avatar object starts with no Vortex projectile.
//10. A Player Avatar has a ticks_to_move value of 0.
//11. A Player Avatar starts out in the waiting to roll state.


//class Baddie: public Actor{
//
//};
//Baddies





//Squares

class Square: public Actor{
public:
    Square(int imageID, int startX, int startY, int dir);
    virtual void doSomething(){};
};

class coinSquare: public Square{
    int coinsToGive;
    
public:
    coinSquare(bool evil, int imageID, int startX, int startY);
    virtual void doSomething();
};

class starSquare: public Square{
    
public:
    starSquare(int startX, int startY);
    virtual void doSomething(){};
};

class directionSquare: public Square{
    int direction;
public:
    directionSquare(int dir, int startX, int startY);
    virtual void doSomething(){};
};

class bankSquare: public Square{
public:
    bankSquare(int startX, int startY);
    virtual void doSomething(){};
};

class eventSquare: public Square{
public:
    eventSquare(int startX, int startY);
    virtual void doSomething(){};
};

class droppingSquare: public Square{
public:
    droppingSquare(int startX, int startY);
    virtual void doSomething(){};
};


// BOWSER AND BOO
#endif // ACTOR_H_
