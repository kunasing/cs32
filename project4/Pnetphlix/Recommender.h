#ifndef RECOMMENDER_INCLUDED
#define RECOMMENDER_INCLUDED

#include <string>
#include <vector>
#include <map>
#include <unordered_map>

class UserDatabase;
class MovieDatabase;
class Movie;

struct MovieAndRank
{
    MovieAndRank(const std::string& id, int score)
     : movie_id(id), compatibility_score(score)
    {}

    std::string movie_id;
    int compatibility_score;
};




class Recommender
{
  public:
    Recommender(const UserDatabase& user_database,
                const MovieDatabase& movie_database);
    std::vector<MovieAndRank> recommend_movies(const std::string& user_email,
                                               int movie_count) const;

  private:
    typedef std::map<std::string, int> movieMap;
    // use the movie map to map the scores to movies
    
    const UserDatabase* userDatabase;
    const MovieDatabase* movieDatabase;
    void gradeMovies(std::string movieId,  movieMap& movieScores) const;
    void gradeActor(std::string actor, movieMap& movieScores) const;
    void gradeDirector(std::string director,  movieMap& movieScores) const;
    void gradeGenre(std::string genre,  movieMap& movieScores) const;
    
    // movie rank and name. used to sort movies by score and name.
    struct mrn{
        mrn(const std::string& id, int score, std::string name)
        : mAndR(id, score), name(name)
        {}
        
        MovieAndRank mAndR;
        std::string name;
    
        
        bool operator<(const mrn m1) const{
            if (mAndR.compatibility_score == m1.mAndR.compatibility_score){
                return name < m1.name;
            }
            else
                return mAndR.compatibility_score > m1.mAndR.compatibility_score;
            return false;
        }
    };
    
    
};



#endif // RECOMMENDER_INCLUDED
