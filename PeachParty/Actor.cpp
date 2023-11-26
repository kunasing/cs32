#include "Actor.h"
#include "StudentWorld.h"

// Students:  Add code to this file, Actor.h, StudentWorld.h, and StudentWorld.cpp

//\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\
//\\\\\\\             ACTOR              \\\\\\
//\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\

Actor::Actor(int imageID, int startX, int startY, int dir, int depth, StudentWorld* world):GraphObject(imageID, startX, startY, dir, depth, 1.0), m_world(world){}

// checks if current actor can move 1 square in the given direction
bool Actor::canMove(int dir) const{
    switch (dir) {
        case up:
            return world()->bdPositionExists(getX()/ SPRITE_WIDTH, (getY() + SPRITE_HEIGHT)/ SPRITE_HEIGHT);
        case down:
            if (getY() <= 0)
                return false;
            return world()->bdPositionExists(getX()/ SPRITE_WIDTH, (getY() - 1)/ SPRITE_HEIGHT);
        case left:
            if (getX() <= 0)
                return false;
            return world()->bdPositionExists((getX() - 1)/ SPRITE_WIDTH, getY()/ SPRITE_HEIGHT);
        case right:
            return world()->bdPositionExists((getX() + SPRITE_WIDTH)/ SPRITE_WIDTH, getY()/ SPRITE_HEIGHT);
        default:
            exit(-1);
    }
}

// randomly generates numbers until finding a square that exists, then teleports the player there.
void Actor::teleport(){
    int x;
    int y;
    
    do {
        x = randInt(0, 15);
        y = randInt(0, 15);
    } while (world()->bdPositionExists(x, y) == false);
    
    moveTo(x * SPRITE_WIDTH, y * SPRITE_HEIGHT);
}

// checks if a fork is available; returns true if board positions exist in 3 or more directions.
bool Actor::forksAvailable() const{
    
    int dirsAvailable = 0;
    
    if (world()->bdPositionExistsExactly(getX() + SPRITE_WIDTH, getY()))
        dirsAvailable++;
    if (world()->bdPositionExistsExactly(getX() - SPRITE_WIDTH, getY()))
        dirsAvailable++;
    if (world()->bdPositionExistsExactly(getX(), getY() + SPRITE_HEIGHT))
        dirsAvailable++;
    if (world()->bdPositionExistsExactly(getX(), getY() - SPRITE_HEIGHT))
        dirsAvailable++;
    
    return dirsAvailable >= 3;
}



//\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\
//\\\\\\\             AVATAR             \\\\\\
//\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\


playerAvatar::playerAvatar(int imageID, int startX, int startY, StudentWorld* world, int playerNum):Actor(imageID, startX * SPRITE_WIDTH, startY * SPRITE_HEIGHT, 0, 0, world), playerNum(playerNum){}//Character(imageID, startX * SPRITE_WIDTH, startY * SPRITE_HEIGHT, world), playerNum(playerNum) {}

// while walking, asks player to either walk or stand
void playerAvatar::doSomething(){
    
    if (walking() == false)
        stand();
    
    // WALKING
    else if (walking()){
        walk();
        if (walkDirection() == left)
            setDirection(180);
        else
            setDirection(0);
    }
}


// player stand waits for an action, roll or vortex fire. determines ticks to move based on roll, or fires vortex.
void playerAvatar::stand(){

    switch (world()->getAction(playerNum)) {
        case ACTION_ROLL:
            m_walking = true;
            m_ticksToMove = randInt(1, 10) * 8;
            break;
        case ACTION_FIRE:
            if (hasVortex())
                world()->shootVortex(getX(), getY(), walkDirection());
            vortexes = false;
            break;
        default:
            return;
    }
}

// if there are forks available, asks player to solve fork. otherwise, checks if direction can be moved in, reorienting if no.
// if direction can be moved in, moves forward and decreases move timer.
void playerAvatar::walk(){
    
    if (forksAvailable() && !world()->directionSquareHere(getX() / SPRITE_WIDTH, getY() / SPRITE_HEIGHT)){
        if (solveFork() == false)
            return;
    }

    
    
    else if (canMove(m_walkDirection) == false){
        if (m_walkDirection == right || m_walkDirection == left){
            m_walkDirection = up;
            if (canMove(m_walkDirection) == false)
                m_walkDirection = down;
        }
        else if (m_walkDirection == up || m_walkDirection == down){
            m_walkDirection = right;
            if (canMove(m_walkDirection) == false)
                m_walkDirection = left;
        }
    }
    
    
    
    if (canMove(m_walkDirection)){
        moveAtAngle(m_walkDirection, 2);
        m_ticksToMove--;
    }
    
    if (m_ticksToMove <= 0)
        m_walking = false;
        
}

// waits for player input that has the player choose the direction at a fork.
bool playerAvatar::solveFork(){
    int newDir;
    switch (world()->getAction(playerNum)) {
        case ACTION_UP:
            newDir = up;
            break;
        case ACTION_DOWN:
            newDir = down;
            break;
        case ACTION_LEFT:
            newDir = left;
            break;
        case ACTION_RIGHT:
            newDir = right;
            break;
        default:
            return false;
    }
    if (newDir == ((m_walkDirection + 180) % 360) || canMove(newDir) == false)
        return false;
    else{
        m_walkDirection = newDir;
        return true;
    }
}

void playerAvatar::giveCoins(int coinsToAdd){
    coins += coinsToAdd;
    if (coins < 0)
        coins = 0;
}

void playerAvatar::giveStars(int starsToAdd){
    stars += starsToAdd;
    if (stars < 0)
        stars = 0;
}

// swaps spots with other player
void playerAvatar::swapSpots(playerAvatar*& player){
    
    int x = getX();
    int y = getY();
    player->getSwapped(m_walkDirection, m_walking, m_ticksToMove, x, y);
    moveTo(x, y);
    
}


// stores temporary variables of current walk info and location
// moves to input location and walk information
// sets input values to own initial values
void playerAvatar::getSwapped(int& walkDir, bool& isWalking, int& ticksLeft, int& x, int& y){
    
    int twalkDir = m_walkDirection;
    bool tisWalking = m_walking;
    int tticksLeft = m_ticksToMove;
    int tx = getX();
    int ty = getY();
    
    moveTo(x, y);
    m_walkDirection = walkDir;
    m_ticksToMove = ticksLeft;
    m_walking = isWalking;
    
    walkDir = twalkDir;
    isWalking = tisWalking;
    ticksLeft = tticksLeft;
    x = tx;
    y = ty;
}




//\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\
//\\\\\\\             Baddies            \\\\\\
//\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\

Baddie::Baddie(int imageID, int startX, int startY, StudentWorld* world):playerAvatar(imageID, startX, startY, world, -1){}

// overrides solveFork from player, orients in a random valid direction
bool Baddie::solveFork(){
    int newDir;
    
    do{
        newDir = randInt(0, 3) * 90;
    } while (canMove(newDir) == false);
    
    setWalkDirection(newDir);
    
    return true;
}

// if pause counter is -1, action is taken corresponsing to intially stopping on the square. Equivalent as doing action when tickstomove is 0.
// when a baddies stands, checks if the player is there and attacks if they are. no longer allowed to activate on a given player during this stop.
// otherwise, decrements pause counter. if pause counter falls below 0, starts character walking again, sets pause counter to -1.
void Baddie::stand(){
    
    if (pauseCounter == -1){
        pauseCounter = 180; //resets pause counter
        startOfStand();
    }
        
    for (int i = 0; i < 2; i++){
        if (world()->sameLocation(world()->player(i), this) && activatedThisStop[i] == false){
            activatedThisStop[i] = true;
            attack(i);
            
        }
    }
    
    pauseCounter--;
    if (pauseCounter <= 0){
        setTicksToMove(randInt(1, maxRoll()) * 8);
        solveFork();        // used to orient character, sets character moving in a random direction
        setWalking(true);
        activatedThisStop[0] = false;
        activatedThisStop[1] = false;
        pauseCounter = -1;
    }
}

Bowser::Bowser(int startX, int startY, StudentWorld* world):Baddie(IID_BOWSER, startX, startY, world){}

// Boswer's attack sets coins to 0.
void Bowser::attack(int p){
    if (randInt(0, 1) == 0){
        world()->player(p)->setCoins(0);
        world()->playSound(SOUND_BOWSER_ACTIVATE);
    }
}

// 1 in 4 chance of replacing square with dropping square.
void Bowser::startOfStand(){
    if (randInt(0, 3) == 0){
        world()->replaceWithDroppingSquare(getX(), getY());
        world()->playSound(SOUND_DROPPING_SQUARE_CREATED);
    }
}

Boo::Boo(int startX, int startY, StudentWorld* world):Baddie(IID_BOO, startX, startY, world){}

// Boo attack switches coins with other character.
void Boo::attack(int p){
    if (randInt(0, 1) == 0){
        int pcoins = world()->player(0)->getCoins();
        int ycoins = world()->player(1)->getCoins();
        world()->player(0)->setCoins(ycoins);
        world()->player(1)->setCoins(pcoins);
    }
    else{
        int pstars = world()->player(0)->getStars();
        int ystars = world()->player(1)->getStars();
        world()->player(0)->setStars(ystars);
        world()->player(1)->setStars(pstars);
    }
    
    world()->playSound(SOUND_BOO_ACTIVATE);
}

void Boo::startOfStand(){
    // Boo does nothing special after finishing movement.
}


//\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\
//\\\\\\\             SQUARE             \\\\\\
//\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\

Square::Square(int imageID, int startX, int startY, int dir, StudentWorld* world): Actor(imageID, startX * PIXEL_SIZE, startY * PIXEL_SIZE, dir, 1, world){}

// Checks if a player has just landed or passed a square based on previous ticks and player's current roll. Calls a squares actions based on if player lands or passes, or isn't there. If not there, does nothing.
void Square::doSomething(){
    if (isDead())
        return;
    
    
    for (int i = 0; i < 2; i++){
        if (world()->sameLocation(world()->player(i), this) && playerWasHere(i) == true && playerWasWasHere(i) == false && world()->player(i)->getRoll() == 0){
            playerIsHere(i, true);
            playerLandsAction(i);
        }
        else if (world()->sameLocation(world()->player(i), this) && playerWasHere(i) == false && world()->player(i)->getRoll() != 0){
            playerIsHere(i, true);
            playerPassAction(i);
        }
        else if (world()->sameLocation(world()->player(i), this))
            playerIsHere(i, true);
        else
            playerIsHere(i, false);
    }
    
    
}

// ALL SQUARE ACTIONS ARE AS DESIGNATED BY PROJECT SPECIFICATIONS

// COIN SQUARE & STAR SQUARE
//\\\\\\\\\\\\

coinSquare::coinSquare(bool evil, int imageID, int startX, int startY, StudentWorld* world): Square(imageID, startX, startY, 0, world){
    if (evil)
        coinsToGive = -3;
    else
        coinsToGive = 3;
}

void coinSquare::playerLandsAction(int p){
    
    world()->player(p)->giveCoins(coinsToGive);
    if (coinsToGive >= 0)
        world()->playSound(SOUND_GIVE_COIN);
    else
        world()->playSound(SOUND_TAKE_COIN);
        
}

starSquare::starSquare(int startX, int startY, StudentWorld* world):Square(IID_STAR_SQUARE, startX, startY, 0, world){}

void starSquare::playerLandsAction(int p){
    if (world()->player(p)->getCoins() >= 20){
        world()->player(p)->giveStars(1);
        world()->player(p)->giveCoins(-20);
    }
}


// DIRECTION SQUARE
//\\\\\\\\\\\\

directionSquare::directionSquare(int dir, int startX, int startY, StudentWorld* world):Square(IID_DIR_SQUARE, startX, startY, dir, world), direction(dir){}

void directionSquare::playerLandsAction(int p){
    world()->player(p)->setWalkDirection(direction);
}

// BANK SQUARE
//\\\\\\\\\\\\

bankSquare::bankSquare(int startX, int startY, StudentWorld* world):Square(IID_BANK_SQUARE, startX, startY, 0, world){}

void bankSquare::playerLandsAction(int p){
    int bank = world()->bankBalance();
    world()->addToBank(-bank);
    world()->player(p)->giveCoins(bank);
    world()->playSound(SOUND_WITHDRAW_BANK); 
}

void bankSquare::playerPassAction(int p){
    int playerBalance = world()->player(p)->getCoins();
    if (playerBalance >= 5){
        world()->player(p)->giveCoins(-5);
        world()->addToBank(5);
    }
    else if (playerBalance < 5){
        world()->player(p)->giveCoins(-playerBalance);
        world()->addToBank(playerBalance);
    }
    world()->playSound(SOUND_DEPOSIT_BANK);
}

// EVENT SQUARE
//\\\\\\\\\\\\

eventSquare::eventSquare(int startX, int startY, StudentWorld* world):Square(IID_EVENT_SQUARE, startX, startY, 0, world){}

void eventSquare::playerLandsAction(int p){
    playerAvatar* other = world()->player((p+1)%2);
    int toDo = randInt(1, 3);
    if (toDo == 1){
        world()->player(p)->teleport();
        world()->playSound(SOUND_PLAYER_TELEPORT);
    }
    else if (toDo == 2){
        for (int i = 0; i < 2; i++)
            playerIsHere(i, false);
        world()->player(p)->swapSpots(other);
        world()->playSound(SOUND_PLAYER_TELEPORT);
        noActivate((p+1)%2);
    }
    else{
        world()->player(p)->giveVortex();
        world()->playSound(SOUND_GIVE_VORTEX);
    }
}

// DROPPING SQUARE
//\\\\\\\\\\\\

droppingSquare::droppingSquare(int startX, int startY, StudentWorld* world):Square(IID_DROPPING_SQUARE, startX, startY, 0, world){}

void droppingSquare::playerLandsAction(int p){
    
    int toDo = randInt(0, 1);
    if (toDo == 0)
        world()->player(p)->giveCoins(-10);
    else
        world()->player(p)->giveStars(-1);
    world()->playSound(SOUND_DROPPING_SQUARE_ACTIVATE);
        
}

Vortex::Vortex(int startX, int startY, int dir, StudentWorld* world):Actor(IID_VORTEX, startX, startY, 0, 0, world), dir(dir){}

// Vortex moves and checks that it is on screen and has hit nobody. Otherwise sets self dead.
void Vortex::doSomething(){
    if (isDead())
        return;
        
    moveAtAngle(dir, 2);

    if (getX() < 0 || getY() < 0 || getX() > VIEW_WIDTH || getY() > VIEW_HEIGHT)
        setDead();
    
    if (world()->checkVortexKill(this)){
        setDead();
        world()->playSound(SOUND_HIT_BY_VORTEX);
    }
    
}

