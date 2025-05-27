#ifndef MOVIEMANAGER_H
#define MOVIEMANAGER_H
#include <vector>
#include <string>
#include "movie.h"

class MovieManager
{
public:
    static std::vector<Movie> movies;

    static void addMovie(const Movie& movie);
    static void updateMovie(const Movie& updatedMovie);
    static void updateMovie(const std::string& id, const Movie& updatedMovie);
    static void removeMovie(const std::string& id);
    static Movie& getMovieById(const std::string& id);
    static const std::vector<Movie>& getAllMovies() { return movies; }
    static void saveToFile(const std::string& filename);
    static void loadFromFile(const std::string& filename);

    static std::vector<Movie> filterByTitle(const std::string& title);
    static std::vector<Movie> filterByDirector(const std::string& directorId);
    static std::vector<Movie> filterByActor(const std::string& actorId);
    static std::vector<Movie> filterByGenre(Genre genre);
    static std::vector<Movie> filterByYear(int year);
    static std::vector<Movie> filterByWatched(bool watched);
};

#endif // MOVIEMANAGER_H
