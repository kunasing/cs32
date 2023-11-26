//
//  main.cpp
//  crossed
//
//  Created by Kunal Singhal on 2/10/23.
//

#include <iostream>


class Person{
public:
    Person(int drinksToBeDrunk, int hitsToBeHigh){
        numDrinks = 0;
        numHits = 0;
        toBeDrunk = drinksToBeDrunk;
        toBeHigh = hitsToBeHigh;
    }
    void drink(){
        numDrinks++;
    }
    void smoke(){
        numHits++;
    }
    void timePasses(){
        if (numHits > 0)
            numHits--;
        if (numDrinks > 0)
            numDrinks--;
    }
    
    
    bool isCrossed(){
        return isDrunk() && isHigh();
    }
    
    bool isDrunk(){
        return numDrinks >= toBeDrunk;
    }
    bool isHigh(){
        return numHits >= toBeHigh;
    }
    
private:
    int numDrinks;
    int numHits;
    int toBeDrunk;
    int toBeHigh;
    
    
};




int main(int argc, const char * argv[]) {
    // insert code here...

    Person sean(7, 8);
    
    sean.drink();
    sean.drink();
    sean.drink();
    sean.drink();

    sean.smoke();
    sean.smoke();
    sean.smoke();
    sean.smoke();
    sean.smoke();
    sean.smoke();
    sean.smoke();
    sean.smoke();
    sean.smoke();
    sean.smoke();
    sean.smoke();
    sean.smoke();

    std::cout << sean.isCrossed() << std::endl;


    return 0;
}
