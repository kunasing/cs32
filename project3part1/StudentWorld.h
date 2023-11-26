#ifndef STUDENTWORLD_H_
#define STUDENTWORLD_H_

#include "GameWorld.h"
#include "Board.h"
#include <string>
#include "Actor.h"
#include <list>

// Students:  Add code to this file, StudentWorld.cpp, Actor.h, and Actor.cpp

class StudentWorld : public GameWorld
{
public:
    StudentWorld(std::string assetPath);
    ~StudentWorld();
    virtual int init();
    virtual int move();
    virtual void cleanUp();
    
    bool bdPositionExists(int x, int y);

private:
    void setupBoard();

    Actor* yoshi = nullptr;
    Actor* peach = nullptr;
    std::list<Actor*> actors;
    Board bd;
};

#endif // STUDENTWORLD_H_
