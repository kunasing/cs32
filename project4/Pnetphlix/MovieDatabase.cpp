#include "MovieDatabase.h"
#include "Movie.h"
#include "utility.h"

#include <string>
#include <vector>
#include <fstream>
using namespace std;

MovieDatabase::MovieDatabase()
{
    // DOES NOTHING
}

// takes in each line until it finds an empty line
// based on the line number in sequence assigns data to descriptor
// adds each movie to 4 movie trees with different types of keys -> id, actor, director, genre
bool MovieDatabase::load(const string& filename)
{
    if (m_loaded)
        return false;

    ifstream moviefile(filename);
    string line;

    if (!moviefile)
        return false;


    while (moviefile){
        int step = 1;
        float rating = 0;
        string id, name, year, directors, actors, genres;

        while(getline(moviefile, line) && line != ""){
            switch(step){
                case 1:
                    id = line;
                    break;
                case 2:
                    name = line;
                    break;
                case 3:
                    year = line;
                    break;
                case 4:
                    directors = line;
                    break;
                case 5:
                    actors = line;
                    break;
                case 6:
                    genres = line;
                    break;
                case 7:
                    rating = stof(line);
                    break;
                default:
                    break;
            }

            step++;
        }

        if (id != ""){
            vector<string> vDirectors = seperate(directors);
            vector<string> vActors = seperate(actors);
            vector<string> vGenres = seperate(genres);

            Movie* toAdd = new Movie(id, name, year, vDirectors, vActors, vGenres, rating);
            m_moviesByID.insert(lower(id), toAdd);
            for (int i = 0; i < vDirectors.size(); i++)
                m_moviesByDirector.insert(lower(vDirectors[i]), toAdd);
            for (int i = 0; i < vActors.size(); i++)
                m_moviesByActor.insert(lower(vActors[i]), toAdd);
            for (int i = 0; i < vGenres.size(); i++)
                m_moviesByGenre.insert(lower(vGenres[i]), toAdd);
        }

    }

    return true;
}

Movie* MovieDatabase::get_movie_from_id(const string& id) const
{
    movieTree::Iterator it = m_moviesByID.find(lower(id));
    if (it.is_valid())
        return it.get_value();
    else
        return nullptr;
}

vector<Movie*> MovieDatabase::get_movies_with_director(const string& director) const
{
    movieTree::Iterator it = m_moviesByDirector.find(lower(director));
    vector<Movie*> movies;
    while (it.is_valid()){
        movies.push_back(it.get_value());
        it.advance();
    }

    return movies;
}

vector<Movie*> MovieDatabase::get_movies_with_actor(const string& actor) const
{
    movieTree::Iterator it = m_moviesByActor.find(lower(actor));
    vector<Movie*> movies;
    while (it.is_valid()){
        movies.push_back(it.get_value());
        it.advance();
    }

    return movies;
}

vector<Movie*> MovieDatabase::get_movies_with_genre(const string& genre) const
{
    movieTree::Iterator it = m_moviesByGenre.find(lower(genre));
    vector<Movie*> movies;
    while (it.is_valid()){
        movies.push_back(it.get_value());
        it.advance();
    }

    return movies;
}




