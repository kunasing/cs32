#include "utility.h"

#include <vector>
#include <string>
#include <cctype>
using namespace std;

// separates string by commas, adds each element of comma separated list to vector and returns.
std::vector<std::string> seperate(std::string multi)
{
        std::vector<std::string> v;

        std::stringstream ss(multi);

        while (ss.good()) {
            std::string substr;
            getline(ss, substr, ',');
            v.push_back(substr);
        }

        return v;
}

// changes all characters to lowercase
string lower(string str){
    for (int i = 0; i < str.size(); i++)
        str[i] = tolower(str[i]);
    return str;
}
