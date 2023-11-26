#include "StudentWorld.h"
#include "GameConstants.h"
#include <string>
#include <sstream>
using namespace std;




GameWorld* createStudentWorld(string assetPath)
{
	return new StudentWorld(assetPath);
}

// Students:  Add code to this file, StudentWorld.h, Actor.h, and Actor.cpp

StudentWorld::StudentWorld(string assetPath): GameWorld(assetPath){}

StudentWorld::~StudentWorld(){
    cleanUp();
}

int StudentWorld::init()
{
    setupBoard();
    
	startCountdownTimer(99);
    return GWSTATUS_CONTINUE_GAME;
}

// Asks all players and other actors to do something, deletes inactive actors. Creates output string. Designates a winner if time is finished.
int StudentWorld::move()
{
    
    for (int i = 0; i < m_players.size(); i++)
        m_players[i]->doSomething();
    
    std::list<Actor*>::iterator currentActor;
    currentActor = actors.begin();
    while (currentActor != actors.end()){
        if ((*currentActor)->isDead()){
            delete (*currentActor);
            currentActor = actors.erase(currentActor);
        }
        else{
            (*currentActor)->doSomething();
            currentActor++;
        }
    }
    
    
    ostringstream oss;

    int pCoins = (m_players[0]->getCoins());
    int pStars = (m_players[0]->getStars());
    int pRoll = (m_players[0]->getRoll());
    
    int yCoins = (m_players[1]->getCoins());
    int yStars = (m_players[1]->getStars());
    int yRoll = (m_players[1]->getRoll());
    
    int time = (timeRemaining());
    string pVortex;
    if (m_players[0]->hasVortex())
        pVortex = "VOR ";
    
    string yVortex;
    if (m_players[1]->hasVortex())
        yVortex = "VOR ";
    
    string bankDisp = to_string(bankBalance());
    
    oss << "P1 Roll: " << pRoll << " Stars: " << pStars << " $$: " << pCoins << " " << pVortex << "| Time: " << time << " | Bank: " << bankDisp << " | P2 Roll: " << yRoll << " Stars: " << yStars << " $$: " << yCoins << " " << yVortex;
    
    string text = oss.str();
    
    
    
    setGameStatText(text);
    
    
    
    if (timeRemaining() <= 0){
        int winner;
        playSound(SOUND_GAME_FINISHED);
        if (pStars > yStars)
            winner = 0;
        else if (yStars > pStars)
            winner = 1;
        else{
            if (pCoins > yCoins)
                winner = 0;
            else if (yCoins > pCoins)
                winner = 1;
            else
                winner = randInt(0, 1);
        }
        
        setFinalScore(m_players[winner]->getStars(), m_players[winner]->getCoins());
        if (winner == 0)
            return GWSTATUS_PEACH_WON;
        else
            return GWSTATUS_YOSHI_WON;
    }
    
	return GWSTATUS_CONTINUE_GAME;
}

// Deallocates and removes from vector/list all players and other actors.
void StudentWorld::cleanUp()
{
    // KILL PEACH, YOSHI, AND ALL OTHER ACTORS
    while (m_players.size() > 0){
        delete m_players[0];
        m_players.erase(m_players.begin());
    }
    
    std::list<Actor*>::iterator currentActor;
    currentActor = actors.begin();
    while (actors.size() > 0){
        delete *currentActor;
        currentActor = actors.erase(currentActor);
    }
    
    
}

// Uses board files to create new squares and actors where necessary, adds them to list of actors.
void StudentWorld::setupBoard(){

    string board_file = assetPath() + "board0" + char (getBoardNumber() + '0') + ".txt";
    Board::LoadResult result = bd.loadBoard(board_file);
    
    if (result == Board::load_fail_file_not_found)
        cerr << "Could not find board01.txt data file\n";
    else if (result == Board::load_fail_bad_format)
        cerr << "Your board was improperly formatted\n";
    else if (result == Board::load_success) {
        cerr << "Successfully loaded board\n";
        
        cout << getBoardNumber();
            
        for (int x = 0; x < 16; x++){
            for (int y = 0; y < 16; y++){
                Actor* newSquare = nullptr;
            
                Board::GridEntry ge = bd.getContentsOf(x, y);
                switch (ge) {
                    case Board::empty:
                        break;
                        // PLAYERS AND BADDIES AND COIN SQUARES
                    case Board::boo:{
                        Actor* boo = new Boo(x, y, this);
                        actors.push_back(boo);
                        newSquare = new coinSquare(false, IID_BLUE_COIN_SQUARE, x, y, this);
                    }
                        break;
                    case Board::bowser:{
                        Actor* bowser = new Bowser(x, y, this);
                        actors.push_back(bowser);
                        newSquare = new coinSquare(false, IID_BLUE_COIN_SQUARE, x, y, this);
                    }
                        break;
                    case Board::player:{
                        playerAvatar* peach = new playerAvatar(IID_PEACH, x, y, this, 1);
                        playerAvatar* yoshi = new playerAvatar(IID_YOSHI, x, y, this, 2);
                        m_players.push_back(peach);
                        m_players.push_back(yoshi);
                        newSquare = new coinSquare(false, IID_BLUE_COIN_SQUARE, x, y, this);
                    }
                        break;
                    case Board::red_coin_square:
                        newSquare = new coinSquare(true, IID_RED_COIN_SQUARE, x, y, this);
                        break;
                    case Board::blue_coin_square:
                        newSquare = new coinSquare(false, IID_BLUE_COIN_SQUARE, x, y, this);
                        break;
                        
//                        // OTHER SQUARES
                    case Board::event_square:
                        newSquare = new eventSquare(x, y, this);
                        break;
                    case Board::bank_square:
                        newSquare = new bankSquare(x, y, this);
                        break;
                    case Board::star_square:
                        newSquare = new starSquare(x, y, this);
                        break;

                        // DIRECTIONAL SQUARES
                    case Board::up_dir_square:
                        newSquare = new directionSquare(Actor::up, x, y, this);
                        break;
                    case Board::down_dir_square:
                        newSquare = new directionSquare(Actor::down, x, y, this);
                        break;
                    case Board::left_dir_square:
                        newSquare = new directionSquare(Actor::left, x, y, this);
                        break;
                    case Board::right_dir_square:
                        newSquare = new directionSquare(Actor::right, x, y, this);
                        break;
                    default:
                        break;
                }
                if (newSquare != nullptr)
                    actors.push_back(newSquare);
            }
        }
    }
}


// Checks that the position on the board has a square and is not empty.
bool StudentWorld::bdPositionExists(int x, int y){
    if (x < 0 || y < 0)
        return false;
    
    Board::GridEntry ge = bd.getContentsOf(x, y);
    switch (ge) {
        case Board::empty:
            return false;
        default:
            return true;
    }
}

// Checks if the position on the board is a direction square.
bool StudentWorld::directionSquareHere(int x, int y){
    Board::GridEntry ge = bd.getContentsOf(x, y);
    
    switch (ge) {
        case Board::up_dir_square:
        case Board::down_dir_square:
        case Board::left_dir_square:
        case Board::right_dir_square:
            return true;
        default:
            return false;
    }
    
}

// Checks that the board position exists not just underneath the character, but must have the exact same x and y coordinates in terms of graphical position.
bool StudentWorld::bdPositionExistsExactly(int graphX, int graphY){
    if (graphX % 16 != 0 || graphY % 16 != 0)
        return false;
    
    return bdPositionExists(graphX/16, graphY/16);
    
}

// Checks that any two actors have the same location exactly.
bool StudentWorld::sameLocation(Actor* actor1, Actor* actor2) const{
    return actor1->getX() == actor2->getX() && actor1->getY() == actor2->getY();
}

// Deletes square at a given location and replaces with a dropping square.
void StudentWorld::replaceWithDroppingSquare(int x, int y){
    std::list<Actor*>::iterator currentActor;
    currentActor = actors.begin();
    Actor* current = nullptr;
    do{
   
        current = *currentActor;
        if (current->getX() == x && current->getY() == y && current->canBeKilled()){
            current->setDead();
            break;
        }
        currentActor++;
    } while (currentActor != actors.end());
    
    
    Actor* newSquare = new droppingSquare(x/16, y/16, this);
    actors.push_back(newSquare);
}

// Returns true if vortex collides with any vortex impactable actors. Teleports them if hit. Returns false otherwise.
bool StudentWorld::checkVortexKill(Actor* vortex){
    
    int leftBound = vortex->getX();
    int downBound = vortex->getY();
    int rightBound = leftBound + SPRITE_WIDTH - 1;
    int upBound = downBound + SPRITE_HEIGHT - 1;
    
    std::list<Actor*>::iterator currentActor;
    currentActor = actors.begin();
    Actor* current = nullptr;
    do{
   
        current = *currentActor;
        int x = current->getX();
        int y = current->getY();
        if (current->vortexHittable() && (leftBound <= x && rightBound >= x) && (downBound <= y && upBound >= y)){
            current->teleport();
            return true;
        }
        
        currentActor++;
    } while (currentActor != actors.end());
    
    
    
    
    return false;
}

// Spawns a new vortex with desired traits.
void StudentWorld::shootVortex(int x, int y, int dir){
    
    Actor* vortex = new Vortex(x, y, dir, this);
    actors.push_back(vortex);
    
}
