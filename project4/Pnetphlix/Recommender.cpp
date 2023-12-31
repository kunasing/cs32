#include "Recommender.h"
#include "UserDatabase.h"
#include "MovieDatabase.h"
#include "utility.h"

#include <string>
#include <vector>
#include <map>
#include <algorithm>
using namespace std;

Recommender::Recommender(const UserDatabase& user_database, const MovieDatabase& movie_database)
:userDatabase(&user_database), movieDatabase(&movie_database)
{}


// Every movie in our person's list -> find it's actors, genre, and directors
// Compile this into one big list of our actors, genres, and directors, which includes duplicates.
// For each of the actors(or dirs or genres) in our list, add all they movies they are in to our map of unordered movies.
// Move values to vector and sort by score.
// Add only the necessary number of movies to a return vector, erase movies already seen.
// Return final vector.

vector<MovieAndRank> Recommender::recommend_movies(const string& user_email, int movie_count) const
{
    
    
    User* user = userDatabase->get_user_from_email(user_email);
    if (user == nullptr || movie_count <= 0)
        return vector<MovieAndRank>();
    
    movieMap movieScores;
    std::vector<mrn> moviesOrdered;
    
    // uses all movies in watch history as basis for grading
    vector<string> movies = user->get_watch_history();
    for (int i = 0; i < movies.size(); i++)
        gradeMovies(movies[i], movieScores);

    // move map data into vector and sort
    movieMap::iterator it = movieScores.begin();
    for (; it != movieScores.end(); it++){
        string title =  movieDatabase->get_movie_from_id((*it).first)->get_title();
        moviesOrdered.push_back(mrn((*it).first, (*it).second, title));
    }
    
    sort(moviesOrdered.begin(), moviesOrdered.end());
    
    // creating final return list
    vector<MovieAndRank> rankedMoviesReturn;
    for (int i = 0; i < movie_count && i < moviesOrdered.size() && moviesOrdered[i].mAndR.compatibility_score > 0; i++){
        if (find(movies.begin(), movies.end(), moviesOrdered[i].mAndR.movie_id) == movies.end())
            rankedMoviesReturn.push_back(moviesOrdered[i].mAndR);
        else
            movie_count++;
    }
    
    return rankedMoviesReturn;
}

// Takes list of actors, directors, and genres each movie contains, and sends those to individual functions as the basis for scoring other movies.
// Each grade function finds the list of movies with a given actor (or director or genre), and adds x to their score. Every movie starts with a score of 0 and gains points for each trait it shares from the movies in the user's watch history.

void Recommender::gradeMovies(string movieId,  movieMap& movieScores) const{
    Movie* movie = movieDatabase->get_movie_from_id(movieId);
    vector<string> actors = movie->get_actors();
    vector<string> directors = movie->get_directors();
    vector<string> genres = movie->get_genres();
    
    for (int i = 0; i < actors.size(); i++)
        gradeActor(actors[i], movieScores);
    
    for (int i = 0; i < directors.size(); i++)
        gradeDirector(directors[i], movieScores);
    
    for (int i = 0; i < genres.size(); i++)
        gradeGenre(genres[i], movieScores);
}

void Recommender::gradeActor(string actor,  movieMap& movieScores) const{
    vector<Movie*> movies = movieDatabase->get_movies_with_actor(actor);
    
    for (int i = 0; i < movies.size(); i++){
        string ID = movies[i]->get_id();
        movieScores[ID] += 30;
    }
}

void Recommender::gradeGenre(string genre,  movieMap& movieScores) const{
    vector<Movie*> movies = movieDatabase->get_movies_with_genre(genre);
    
    for (int i = 0; i < movies.size(); i++){
        string ID = movies[i]->get_id();
        movieScores[ID] += 1;
    }
    
}

void Recommender::gradeDirector(string director,  movieMap& movieScores) const{
    vector<Movie*> movies = movieDatabase->get_movies_with_director(director);
    
    for (int i = 0; i < movies.size(); i++){
        string ID = movies[i]->get_id();
        movieScores[ID] += 20;
    }
    
}






