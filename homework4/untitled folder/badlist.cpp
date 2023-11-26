void removeBad(list<Movie*>& li)
{
    list<Movie*>::iterator i;
    i = li.begin();
    while (i != li.end()) {
        if ((*i)->rating() < 50){
            delete (*i);
            i = li.erase(i);
        }
        else
            i++;
    }
}
