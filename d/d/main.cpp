#include <iostream>
using namespace std;


bool hasNoCapitals(string array[], int n);





int main(){
    
    string k[] = {"hello", "carrot", "frog"};
    
    
    
    cout << hasNoCapitals(k, 3) << endl;
    
    
}





int shiftLeft(string array[], int n, int amount, string placeholder){
    if (n <= 0 || amount < 0)
        return -1;

    int count = 0;

    int i;
    for (i = 0; i + amount < n; i++)
        array[i] = array[i + amount];
    for (; i < n; i++){
        array[i] = placeholder;
        count++;
    }

    return count;
}


bool hasNoCapitals(string array[], int n){
    for (int i = 0; i < n; i++)
        for (char c: array[i])
            if (isupper(c))
                return false;
    
    return true;
}
