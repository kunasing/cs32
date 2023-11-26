#include "StudentWorld.h"
#include "GameConstants.h"
#include <string>
using namespace std;



GameWorld* createStudentWorld(string assetPath)
{
	return new StudentWorld(assetPath);
}

// Students:  Add code to this file, StudentWorld.h, Actor.h, and Actor.cpp

StudentWorld::StudentWorld(string assetPath)
: GameWorld(assetPath)
{
}

StudentWorld::~StudentWorld(){
    cleanUp();
    
    // NOTE: GameController already runs cleanup, so running cleanup again in this destructor attempts to redelete already deallocated pointers such as yoshi and peach
    // Solution: set peach and yoshi to nullptr and only delete if != nullptr
}

int StudentWorld::init()
{
    
    
    setupBoard();
    
    // we need to make a board
    
    // intialize peach
    // intialize yoshi
    // place peach and yoshi
    
    // intialize and place baddies
    // intialize and place squares
    
    
    // CHANGE COUNTDOWN
	startCountdownTimer(5);  // this placeholder causes timeout after 5 seconds
    return GWSTATUS_CONTINUE_GAME;
}


int StudentWorld::move()
{
    // This code is here merely to allow the game to build, run, and terminate after you hit ESC.
    // Notice that the return value GWSTATUS_NOT_IMPLEMENTED will cause our framework to end the game.

    peach->doSomething();
    yoshi->doSomething();
    std::list<Actor*>::iterator currentActor;
    currentActor = actors.begin();
    while (currentActor != actors.end()){
        (*currentActor)->doSomething();
        currentActor++;
    }
    
    
//    currentActor = actors.begin();
//    for ()
    
    setGameStatText("Game will end in a few seconds");
    
    if (timeRemaining() <= 0)
        return GWSTATUS_CONTINUE_GAME;
//		return GWSTATUS_NOT_IMPLEMENTED;
    
	return GWSTATUS_CONTINUE_GAME;
}

void StudentWorld::cleanUp()
{
    // KILL PEACH, YOSHI, AND ALL OTHER ACTORS
    if (peach != nullptr)
        delete peach;
    if (yoshi != nullptr)
        delete yoshi;
    std::list<Actor*>::iterator currentActor;
    currentActor = actors.begin();
    while (actors.size() > 0){
        delete *currentActor;
        currentActor = actors.erase(currentActor);
    }
    
    peach = nullptr;
    yoshi = nullptr;
    
//    for (int i = 0; i < actors.size(); i++){
//        delete *currentActor;
//        currentActor++;
//    }

}

void StudentWorld::setupBoard(){

    string board_file = assetPath() + "board0" + char (getBoardNumber() + '0') + ".txt";
    Board::LoadResult result = bd.loadBoard(board_file);
    
    if (result == Board::load_fail_file_not_found)
        cerr << "Could not find board01.txt data file\n";
    else if (result == Board::load_fail_bad_format)
        cerr << "Your board was improperly formatted\n";
    else if (result == Board::load_success) {
        cerr << "Successfully loaded board\n";
        
        std::list<Actor*>::iterator currentActor;
        currentActor = actors.begin();
        
        cout << getBoardNumber();
            
        for (int x = 0; x < 16; x++){
            for (int y = 0; y < 16; y++){
                Actor* newSquare = nullptr;
            
                Board::GridEntry ge = bd.getContentsOf(x, y);
                switch (ge) {
                    case Board::empty:
                        break;
                        // PLAYERS AND BADDIES AND COIN SQUARES
                    case Board::boo:
                        newSquare = new coinSquare(false, IID_BLUE_COIN_SQUARE, x, y);
                        // ADD BOWSER AND BOO SPAWNS
                        break;
                    case Board::bowser:
                        newSquare = new coinSquare(false, IID_BLUE_COIN_SQUARE, x, y);
                        break;
                    case Board::player:
                        peach = new playerAvatar(IID_PEACH, x, y, this, 1);
                        yoshi = new playerAvatar(IID_YOSHI, x, y, this, 2);
                        newSquare = new coinSquare(false, IID_BLUE_COIN_SQUARE, x, y);
                        break;
                    case Board::red_coin_square:
                        newSquare = new coinSquare(true, IID_RED_COIN_SQUARE, x, y);
                        break;
                    case Board::blue_coin_square:
                        newSquare = new coinSquare(false, IID_BLUE_COIN_SQUARE, x, y);
                        break;
                        
//
//                        // OTHER SQUARES
                    case Board::event_square:
                        newSquare = new eventSquare(x, y);
                        break;
                    case Board::bank_square:
                        newSquare = new bankSquare(x, y);
                        break;
                    case Board::star_square:
                        newSquare = new starSquare(x, y);
                        break;

                        // DIRECTIONAL SQUARES
                    case Board::up_dir_square:
                        newSquare = new directionSquare(1, x, y);
                        break;
                    case Board::down_dir_square:
                        newSquare = new directionSquare(3, x, y);
                        break;
                    case Board::left_dir_square:
                        newSquare = new directionSquare(2, x, y);
                        break;
                    case Board::right_dir_square:
                        newSquare = new directionSquare(0, x, y);
                        break;
                    default:
                        newSquare = new coinSquare(false, IID_VORTEX, x, y);
                }
                if (newSquare != nullptr)
                    actors.insert(currentActor, newSquare);
            }
        }
    }
}



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
