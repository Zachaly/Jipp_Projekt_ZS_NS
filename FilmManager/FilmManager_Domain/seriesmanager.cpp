#include "seriesmanager.h"

#include "episodemanager.h"
#include <fstream>

std::vector<Serie> SeriesManager::series = vector<Serie>();

std::vector<Serie> &SeriesManager::getSeries()
{
    return series;
}

std::vector<Serie> &SeriesManager::getSeries(function<bool (Serie)> filter)
{
    vector<Serie>* res = new vector<Serie>();

    for(auto serie : series)
    {
        if(filter(serie))
        {
            res->push_back(serie);
        }
    }

    return *res;
}

Serie &SeriesManager::getById(string id)
{
    for(auto& serie : series)
    {
        if(serie.getId() == id)
        {
            return serie;
        }
    }

    Serie s;

    return s;
}

void SeriesManager::addSerie(Serie &serie)
{
    series.push_back(serie);
    saveToFile();
}

void SeriesManager::removeSerie(string id)
{
    auto episodes = getById(id).getEpisodeIds();

    for(auto& epId : episodes)
    {
        EpisodeManager::removeEpisode(epId);
    }

    series.erase(std::remove_if(series.begin(), series.end(), [&id](const Serie& e) { return e.getId() == id; }), series.end());
    saveToFile();
}

void SeriesManager::saveToFile()
{
    ofstream file("series.txt", std::ofstream::in | std::ofstream::trunc);

    if(!file.is_open())
    {
        return;
    }

    for(auto& s : series)
    {
        file << s.toString() << endl;
    }

    file.close();
}

void SeriesManager::loadFromFile()
{
    ifstream file("series.txt");

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
        SerieStatus status = (SerieStatus)stoi(currentLine.substr(0, pos));
        currentLine.erase(0, pos + 1);

        pos = currentLine.find('_');
        int seasonCount = stoi(currentLine.substr(0, pos));
        currentLine.erase(0, pos + 1);

        vector<string> episodes;

        while (pos != string::npos) {

            // Extracting the substring up to the
            // delimiter
            string episodeId = currentLine.substr(0, pos);

            // Erase the extracted part from the
            // original string
            currentLine.erase(0, pos + 1);

            // Find the next occurrence of the
            // delimiter
            pos = currentLine.find('_');

            episodes.push_back(episodeId);
        }

        Serie s = Serie(id, title, description, genre, creatorId, year, mark, isWatched, status, seasonCount, episodes);
        series.push_back(s);
    }

    file.close();
}
