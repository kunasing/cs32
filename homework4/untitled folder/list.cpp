void listAll(string path, const File* f)  // two-parameter overload
{
    if (f == nullptr)
        return;
    
    if (f->files() == nullptr){
        cout << path << endl;
        return;
    }
    
    // in a directory, add slash and move into directory
    path += "/";
    cout << path << endl;
    for (int i = 0; i < f->files()->size(); i++){
        File* sub = (*(f->files()))[i];
        listAll(path + sub->name(), sub);
    }
}
