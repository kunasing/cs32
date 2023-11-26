#ifndef USERDATABASE_INCLUDED
#define USERDATABASE_INCLUDED

#include <string>
#include <fstream>
#include "User.h"
#include "treemm.h"

class User;

class UserDatabase
{
  public:
    UserDatabase();
    bool load(const std::string& filename);
    User* get_user_from_email(const std::string& email) const;

  private:
    TreeMultimap<std::string, User> m_users;
    bool m_loaded = false;
};

#endif // USERDATABASE_INCLUDED
