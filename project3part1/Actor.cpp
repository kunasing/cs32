#include "Actor.h"
#include "StudentWorld.h"

// Students:  Add code to this file, Actor.h, StudentWorld.h, and StudentWorld.cpp

//\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\
//\\\\\\\             ACTOR              \\\\\\
//\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\

Actor::Actor(int imageID, int startX, int startY, int dir, int depth):GraphObject(imageID, startX, startY, dir, depth, 1.0){}

//\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\
//\\\\\\\             AVATAR             \\\\\\
//\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\

playerAvatar::playerAvatar(int imageID, int startX, int startY, StudentWorld* world, int playerNum):Actor(imageID, startX * SPRITE_WIDTH, startY * SPRITE_HEIGHT, 0, 0), world(world), playerNum(playerNum) {}

void playerAvatar::doSomething(){
    int action = world->getAction(playerNum);
    
    if (walking == false){
        switch (action) {
            case ACTION_ROLL:
                walking = true;
                ticksToMove = randInt(1, 10) * 8;
                break;
            case ACTION_FIRE:
                // NEED TO DO
                break;
            default:
                return;
        }
    }
    
    if (walking){
        // if getx or gety one more in the direction we are walking does not exist then you must change things
                        
        if (canMoveForward() == false){
            if (walkDirection == right || walkDirection == left){
                walkDirection = up;
                if (canMoveForward() == false)
                    walkDirection = down;
            }
            else if (walkDirection == up || walkDirection == down){
                walkDirection = right;
                if (canMoveForward() == false)
                    walkDirection = left;
            }
        }
        
        if (canMoveForward()){
            moveAtAngle(walkDirection, 2);
            ticksToMove--;
        }
        if (ticksToMove == 0)
            walking = false;
    }
    
}


bool playerAvatar::canMoveForward(){
    
    switch (walkDirection) {
        case up:
            return world->bdPositionExists(getX()/ SPRITE_WIDTH, (getY() + SPRITE_HEIGHT)/ SPRITE_HEIGHT);
        case down:
            return world->bdPositionExists(getX()/ SPRITE_WIDTH, (getY() - SPRITE_HEIGHT)/ SPRITE_HEIGHT);
        case left:
            return world->bdPositionExists((getX() - SPRITE_WIDTH)/ SPRITE_WIDTH, getY()/ SPRITE_HEIGHT);
        case right:
            return world->bdPositionExists((getX() + SPRITE_WIDTH)/ SPRITE_WIDTH, getY()/ SPRITE_HEIGHT);
        default:
            exit(-1);
    }
    
}


//\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\
//\\\\\\\             SQUARE             \\\\\\
//\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\

Square::Square(int imageID, int startX, int startY, int dir): Actor(imageID, startX * PIXEL_SIZE, startY * PIXEL_SIZE, dir, 1){}


coinSquare::coinSquare(bool evil, int imageID, int startX, int startY): Square(imageID, startX, startY, 0){
    if (evil)
        coinsToGive = -3;
    else
        coinsToGive = 3;
}

void coinSquare::doSomething(){
    if (isDead())
        return;
    
//    std::cout << "i am coin square af" << std::endl;
}



starSquare::starSquare(int startX, int startY):Square(IID_STAR_SQUARE, startX, startY, 0){}
directionSquare::directionSquare(int dir, int startX, int startY):Square(IID_DIR_SQUARE, startX, startY, dir * 90), direction(dir){}
bankSquare::bankSquare(int startX, int startY):Square(IID_BANK_SQUARE, startX, startY , 0){}
eventSquare::eventSquare(int startX, int startY):Square(IID_EVENT_SQUARE, startX, startY, 0){}
droppingSquare::droppingSquare(int startX, int startY):Square(IID_DROPPING_SQUARE, startX, startY, 0){}
