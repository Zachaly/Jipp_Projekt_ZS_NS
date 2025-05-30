#include "moviemanager.h"
#include <algorithm>
#include <fstream>
#include <cctype>

std::vector<Movie> MovieManager::movies;

void MovieManager::addMovie(const Movie& movie)
{
    movies.push_back(movie);
    saveToFile();
}

void MovieManager::updateMovie(const Movie& updatedMovie) {
    updateMovie(updatedMovie.getId(), updatedMovie);
    saveToFile();
}

void MovieManager::updateMovie(const std::string& id, const Movie& updatedMovie)
{
    for (auto& movie : movies) {
        if (movie.getId() == id) {
            movie = updatedMovie;
            break;
        }
    }

    saveToFile();
}

void MovieManager::removeMovie(const std::string& id)
{
    movies.erase(std::remove_if(movies.begin(), movies.end(),
                                [&id](const Movie& movie) { return movie.getId() == id; }),
                 movies.end());
    saveToFile();
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

void MovieManager::saveToFile()
{
    ofstream file("movies.txt", std::ofstream::in | std::ofstream::trunc);

    if(!file.is_open())
    {
        return;
    }

    for(auto& m : movies)
    {
        file << m.toString() << endl;
    }

    file.close();
}

void MovieManager::loadFromFile()
{
    ifstream file("movies.txt");

    if(!file.is_open())
    {
        return;
    }

    string currentLine;

    while(getline(file, currentLine))
    {
        if(currentLine.empty())
        {
            break;
        }

        auto pos = currentLine.find('_');
        string id = currentLine.substr(0, pos);
        currentLine.erase(0, pos + 1);

        pos = currentLine.find('_');
        string title = currentLine.substr(0, pos);
        currentLine.erase(0, pos + 1);

        pos = currentLine.find('_');
        string description = currentLine.substr(0, pos);
        currentLine.erase(0, pos + 1);

        pos = currentLine.find('_');
        Genre genre = (Genre)stoi(currentLine.substr(0, pos));
        currentLine.erase(0, pos + 1);

        pos = currentLine.find('_');
        string creatorId = currentLine.substr(0, pos);
        currentLine.erase(0, pos + 1);

        pos = currentLine.find('_');
        int year = stoi(currentLine.substr(0, pos));
        currentLine.erase(0, pos + 1);

        pos = currentLine.find('_');
        int mark = stoi(currentLine.substr(0, pos));
        currentLine.erase(0, pos + 1);

        pos = currentLine.find('_');
        bool isWatched = stoi(currentLine.substr(0, pos));
        currentLine.erase(0, pos + 1);

        pos = currentLine.find('_');
        bool length = stoi(currentLine.substr(0, pos));
        currentLine.erase(0, pos + 1);

        vector<string> actors;

        while (pos != string::npos) {

            // Extracting the substring up to the
            // delimiter
            string actorId = currentLine.substr(0, pos);

            // Erase the extracted part from the
            // original string
            currentLine.erase(0, pos + 1);

            // Find the next occurrence of the
            // delimiter
            pos = currentLine.find('_');

            actors.push_back(actorId);
        }

        Movie m = Movie(id, title, description, genre, creatorId, year, mark, isWatched, length, actors);
        movies.push_back(m);
    }
}
