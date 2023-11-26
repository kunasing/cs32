#ifndef MOVIEDATABASE_INCLUDED
#define MOVIEDATABASE_INCLUDED

#include <string>
#include <vector>
#include "Movie.h"
#include "treemm.h"
#include "utility.h"

class MovieDatabase
{
  public:
    MovieDatabase();
    bool load(const std::string& filename);
    Movie* get_movie_from_id(const std::string& id) const;
    std::vector<Movie*> get_movies_with_director(const std::string& director) const;
    std::vector<Movie*> get_movies_with_actor(const std::string& actor) const;
    std::vector<Movie*> get_movies_with_genre(const std::string& genre) const;

  private:
    typedef TreeMultimap<std::string, Movie*> movieTree;
    
    movieTree m_moviesByID;
    movieTree m_moviesByDirector;
    movieTree m_moviesByActor;
    movieTree m_moviesByGenre;
    bool m_loaded = false;

};

#endif // MOVIEDATABASE_INCLUDED
