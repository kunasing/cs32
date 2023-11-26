//// rabbits.cpp
//
//#include <iostream>
//#include <string>
//#include <random>
//#include <utility>
//#include <cstdlib>
//#include <cctype>
//
//#include "globals.h"
//#include "Rabbit.h"
//#include "Player.h"
//#include "Arena.h"
//#include "Game.h"
//using namespace std;
//
//int main()
//{
//      // Create a game
//      // Use this instead to create a mini-game:   Game g(3, 5, 2);
//    //Game g(10, 12, 40);
//    Game g(3, 5, 2);
//
//      // Play the game
//    g.play();
//}




#include "Rabbit.h"
#include "Player.h"
#include "Arena.h"
#include "globals.h"
#include "Game.h"
#include "History.h"

#include <iostream>
#include <string>
#include <random>
#include <utility>
#include <cstdlib>
#include <cctype>

using namespace std;

int main()
{
    /*Game g(10, 12, 5);
    g.play();*/
    History h(20, 25);
    
    for (int k = 0; k <= 30; k++) {
        for (int i = 1; i <= 20; i++) {
            for (int j = 1; j <= 25; j++) {
                h.record(i, j);
                h.display();
                cout << "\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n";
            }
        }
    }
}
