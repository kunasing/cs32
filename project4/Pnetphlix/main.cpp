#include "UserDatabase.h"
#include "MovieDatabase.h"
#include "User.h"
#include "Movie.h"
#include "Recommender.h"

#include <iostream>
#include <string>
#include <vector>
using namespace std;

const string USER_DATAFILE  = "/Users/kunalsinghal/Library/CloudStorage/OneDrive-Personal/old_classes/cs32/project4/users.txt";
const string MOVIE_DATAFILE = "/Users/kunalsinghal/Library/CloudStorage/OneDrive-Personal/old_classes/cs32/project4/movies.txt";

//
//////////////////////////i/////////////////////////////////////////////////////
//
// You are free to do whatever you want with this file, since you won't
// be turning it in.  Presumably, you will make changes to help you test
// your classes.  For example, you might try to implement only some User
// member functions to start out with, and so replace our main routine with
// one that simply creates a User and verifies that the member functions you
// implemented work correctly.
//
//////////////////////////i/////////////////////////////////////////////////////
//
//

void printVector(vector<Movie*> vector){
    for (int i = 0; i < vector.size(); i++)
        cout << "   " + to_string(i + 1) + ". " << vector[i]->get_title() << endl;
}

void printVector(vector<string> vector){
    for (int i = 0; i < vector.size(); i++)
        cout << "    " + to_string(i + 1) + ". " << vector[i] << endl;
}

int userDbTest(){
    UserDatabase udb;
    if (!udb.load(USER_DATAFILE))  // In skeleton, load always return false
    {
        cout << "Failed to load user data file " << USER_DATAFILE << "!" << endl;
        return 1;
    }
    for (;;)
    {
        cout << "Enter user email address (or quit): ";
        string email;
        getline(cin, email);
        if (email == "quit")
            return 0;
        User* u = udb.get_user_from_email(email);
        if (u == nullptr)
            cout << "No user in the database has that email address." << endl;
        else
            cout << "Found " << u->get_full_name() << endl;
    }
}

int movieDbTest(){
    MovieDatabase mdb;
    if (!mdb.load(MOVIE_DATAFILE))  // In skeleton, load always return false
    {
        cout << "Failed to load user data file " << MOVIE_DATAFILE << "!" << endl;
        return 1;
    }
    for (;;)
    {
        cout << "Enter actor (or quit): ";
        string actor;
        getline(cin, actor);
        if (actor == "quit")
            return 0;
        vector<Movie*> u = mdb.get_movies_with_actor(actor);
        if (u.size() == 0)
            cout << "Does Not Exist." << endl;
        else{
            cout << "Found these:" << endl;
            printVector(u);
        }
    }
}

int movieTest(){
    MovieDatabase mdb;
    mdb.load(MOVIE_DATAFILE);
    string actor = "Tom Cruise";
    vector<Movie*> u = mdb.get_movies_with_actor(actor);

    printVector(u[0]->get_actors());

    return 0;
}

int findMoviesBy(){
    MovieDatabase movies;
    movies.load(MOVIE_DATAFILE);

    vector<Movie*> moviesWithDir = movies.get_movies_with_actor("tom cruise");

    printVector(moviesWithDir);

    return 0;
}


void findMatches(const Recommender& r, const MovieDatabase& md,const string& user_email, int num_recommendations) {
    // get up to ten movie recommendations for the user
    vector<MovieAndRank> recommendations = r.recommend_movies(user_email, num_recommendations);
    if (recommendations.empty())
        cout << "We found no movies to recommend :(.\n";
    else {
        for (int i = 0; i < recommendations.size(); i++) {
            const MovieAndRank& mr = recommendations[i];
            Movie* m = md.get_movie_from_id(mr.movie_id);
                cout << i + 1 << ". " << m->get_title() << " (" << m->get_release_year() << ")\n    Rating: "
                << m->get_rating() << "\n   Compatibility Score: " << mr.compatibility_score << "\n";

        }

    }
}


int main()
{

    MovieDatabase movies;
    UserDatabase users;
    movies.load(MOVIE_DATAFILE);
    users.load(USER_DATAFILE);

    Recommender recs(users, movies);

    findMatches(recs, movies, "BrunB@yahoo.com", 10);
}

