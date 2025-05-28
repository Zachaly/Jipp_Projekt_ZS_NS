#include "moviemanager.h"
#include <algorithm>
#include <fstream>
#include <sstream>
#include <cctype>

std::vector<Movie> MovieManager::movies;

void MovieManager::addMovie(const Movie& movie)
{
    movies.push_back(movie);
}

void MovieManager::updateMovie(const Movie& updatedMovie) {
    updateMovie(updatedMovie.getId(), updatedMovie);
}

void MovieManager::updateMovie(const std::string& id, const Movie& updatedMovie)
{
    for (auto& movie : movies) {
        if (movie.getId() == id) {
            movie = updatedMovie;
            break;
        }
    }
}

void MovieManager::removeMovie(const std::string& id)
{
    movies.erase(std::remove_if(movies.begin(), movies.end(),
                                [&id](const Movie& movie) { return movie.getId() == id; }),
                 movies.end());
}

Movie& MovieManager::getMovieById(const std::string& id)
{
    for (auto& movie : movies) {
        if (movie.getId() == id) {
            return movie;
        }
    }
    static Movie emptyMovie;
    return emptyMovie;
}


std::vector<Movie> MovieManager::filterByTitle(const std::string& title)
{
    std::vector<Movie> result;
    std::string lowerTitle = title;
    std::transform(lowerTitle.begin(), lowerTitle.end(), lowerTitle.begin(),
                   [](unsigned char c){ return std::tolower(c); });

    for (const auto& movie : movies) {
        std::string movieTitle = movie.getTitle();
        std::transform(movieTitle.begin(), movieTitle.end(), movieTitle.begin(),
                       [](unsigned char c){ return std::tolower(c); });
        if (movieTitle.find(lowerTitle) != std::string::npos) {
            result.push_back(movie);
        }
    }
    return result;
}

std::vector<Movie> MovieManager::filterByDirector(const std::string& directorId)
{
    std::vector<Movie> result;
    for (const auto& movie : movies) {
        if (movie.getCreatorId() == directorId) {
            result.push_back(movie);
        }
    }
    return result;
}

std::vector<Movie> MovieManager::filterByActor(const std::string& actorId)
{
    std::vector<Movie> result;
    for (const auto& movie : movies) {
        const auto& actors = movie.getActorIds();
        if (std::find(actors.begin(), actors.end(), actorId) != actors.end()) {
            result.push_back(movie);
        }
    }
    return result;
}

std::vector<Movie> MovieManager::filterByGenre(Genre genre)
{
    std::vector<Movie> result;
    for (const auto& movie : movies) {
        if (movie.getGenre() == genre) {
            result.push_back(movie);
        }
    }
    return result;
}

std::vector<Movie> MovieManager::filterByYear(int year)
{
    std::vector<Movie> result;
    for (const auto& movie : movies) {
        if (movie.getProductionYear() == year) {
            result.push_back(movie);
        }
    }
    return result;
}

std::vector<Movie> MovieManager::filterByWatched(bool watched)
{
    std::vector<Movie> result;
    for (const auto& movie : movies) {
        if (movie.getIsWatched() == watched) {
            result.push_back(movie);
        }
    }
    return result;
}
