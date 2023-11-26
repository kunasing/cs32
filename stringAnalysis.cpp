#include <iostream>
#include <cctype>
#include <cassert>
using namespace std;


int passQC(string results);
int passBatch(string results);

int defectQC(string results);
int defectBatch(string results);

int batches(string results);

int totalQC(string results);

bool isValidQC(string results);
bool isValidBatch(string results);

int main(){

        
}




int passQC(string results ){
    
    if (isValidQC(results) == false)
        return -1;
        
    size_t qLoc = results.find('Q' , 1);
    string batch;
    int total = 0;
    
    while (results.size() > qLoc){
        batch = results.substr(0, qLoc);
        results = results.substr(qLoc);
        
        total += passBatch(batch);
        
        qLoc = results.find('Q' , 1);
    }
    
    total += passBatch(results);
    
    return total;
}

int defectQC(string results){
    
    if (isValidQC(results) == false)
        return -1;
        
    size_t qLoc = results.find('Q' , 1);
    string batch;
    int total = 0;
    
    while (results.size() > qLoc){
        batch = results.substr(0, qLoc);
        results = results.substr(qLoc);
        
        total += defectBatch(batch);
        
        qLoc = results.find('Q' , 1);
    }
    
    total += defectBatch(results);
    
    return total;
}

int batches(string results){
    if (isValidQC(results) == false)
        return -1;
    
    int totalQ = 0;
    for (int i = 0; i < results.size(); i++){
        if (results[i] == 'Q')
            totalQ++;
    }
    return totalQ;
}

int totalQC(string results){
    if (isValidQC(results) == false)
        return -1;
    
    return passQC(results) + defectQC(results);
}






int passBatch(string results){
    
    size_t pLoc = results.find('p');
    size_t dLoc = results.find('d');
    string num;
    
    if (pLoc < dLoc) // p comes before d
        num = results.substr(pLoc + 1, dLoc - (pLoc + 1));
    else            // p comes after d
        num = results.substr(pLoc + 1);
    
    return stoi(num);
}

int defectBatch(string results){
    
    size_t pLoc = results.find('p');
    size_t dLoc = results.find('d');
    string num;
    
    if (dLoc < pLoc) // d comes before p
        num = results.substr(dLoc + 1, pLoc - (dLoc + 1));
    else            // d comes after p
        num = results.substr(dLoc + 1);
    
    return stoi(num);
}




bool isValidQC(string results){
    
    size_t qLoc = results.find('Q' , 1);
    string batch;
    
    while (results.size() > qLoc){
        batch = results.substr(0, qLoc);
        results = results.substr(qLoc);
        
        if(isValidBatch(batch) == false)
            return false;
        
        qLoc = results.find('Q' , 1);
    }
    
    if(isValidBatch(results) == false)
        return false;
    
    return true;
    
}



bool isValidBatch(string results){
    if (results[0] != 'Q' || results[1] == '0' || results.length() < 6 || !isdigit(results[results.length() - 1]))
        return false;
    
    bool pastD = false;
    bool pastP = false;
    
    
    for (int i = 1; i < results.size() - 1; i++){
        
        char current = results[i];
        
        switch (current) {
            case '0':
                if ((results[i-1] == 'p' || results[i-1] == 'd') && isdigit(results[i+1]))
                    return false;
            case '1':
            case '2':
            case '3':
            case '4':
            case '5':
            case '6':
            case '7':
            case '8':
            case '9':
                break;
            case 'p':
                if(pastP)
                    return false;
                pastP = true;
                if (isdigit(results[i+1]) == false)
                    return false;
                break;

            case 'd':
                if (pastD)
                    return false;
                pastD = true;
                if (isdigit(results[i+1]) == false)
                    return false;
                break;

            case 'Q':
            default:
                return false;
        }
    }
    
    if (pastP == false || pastD == false)
        return false;
    
    
    size_t pLoc = results.find('p');
    size_t dLoc = results.find('d');
    string pass;
    string defect;
    string qtotal;

    
    
    if (pLoc < dLoc){ // p comes before d
        pass = results.substr(pLoc + 1, dLoc - (pLoc + 1));
        defect = results.substr(dLoc + 1);
        qtotal = results.substr(1, pLoc - 1);
    }
    else{            // p comes after d
        defect = results.substr(dLoc + 1, pLoc - (dLoc + 1));
        pass = results.substr(pLoc + 1);
        qtotal = results.substr(1, dLoc - 1);
    }
    
    if (stoi(pass) + stoi(defect) != stoi(qtotal))
        return false;
    
    
    return true;
    
    
}


