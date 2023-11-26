#include "UserDatabase.h"
#include "User.h"
#include "treemm.h"

#include <string>
#include <vector>
#include <iostream>
using namespace std;

UserDatabase::UserDatabase()
{}

// takes in user data and adds users to tree based on email
bool UserDatabase::load(const string& filename)
{
    if (m_loaded)
        return false;
    m_loaded = true;
    
    ifstream userfile(filename);
    string line;
    
    if (!userfile)
        return false;
    
    while (userfile){
        int step = 1;
        string name, email;
        vector<string> movies;
        
        while(getline(userfile, line) && line != ""){
            switch(step){
                case 1:
                    name = line;
                    break;
                case 2:
                    email = line;
                    break;
                case 3:
                    break;
                default:
                    movies.push_back(line);
                    break;
            }
            step++;
        }
        
        if (name != "")
            m_users.insert(email, User(name, email, movies));
        
    }
    return true;
}


User* UserDatabase::get_user_from_email(const string& email) const
{
    TreeMultimap<std::string, User>::Iterator it = m_users.find(email);
    if (it.is_valid())
        return &it.get_value();
    else
        return nullptr;
}
