void removeOdd(vector<int>& v){
    vector<int>::iterator i;
    i = v.begin();
    while(i != v.end()){
        if (*i % 2 == 1)
            i = v.erase(i);
        else
            i++;
    }
}
