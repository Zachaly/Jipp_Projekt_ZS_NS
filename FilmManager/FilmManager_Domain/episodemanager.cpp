#include "episodemanager.h"
#include <fstream>

vector<Episode> EpisodeManager::episodes = vector<Episode>();

vector<Episode> &EpisodeManager::getEpisodes()
{
    return episodes;
}

vector<Episode> &EpisodeManager::getEpisodes(function<bool (Episode)> filter)
{
    vector<Episode>* res = new vector<Episode>;

    for(auto& e : episodes)
    {
        if(filter(e))
        {
            res->push_back(e);
        }
    }

    return *res;
}

Episode &EpisodeManager::getById(string id)
{
    for(auto& e : episodes)
    {
        if(e.getId() == id)
        {
            return e;
        }
    }

    Episode e;
    return e;
}

void EpisodeManager::addEpisode(Episode &episode)
{
    episodes.push_back(episode);
    saveToFile();
}

void EpisodeManager::removeEpisode(string id)
{
    episodes.erase(std::remove_if(episodes.begin(), episodes.end(), [&id](const Episode& e) { return e.getId() == id; }), episodes.end());
    saveToFile();
}

void EpisodeManager::loadFromFile()
{
    ifstream file("episodes.txt");

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
        int length = stoi(currentLine.substr(0, pos));
        currentLine.erase(0, pos + 1);

        pos = currentLine.find('_');
        int episodeNumber = stoi(currentLine.substr(0, pos));
        currentLine.erase(0, pos + 1);

        pos = currentLine.find('_');
        int seasonNumber = stoi(currentLine.substr(0, pos));
        currentLine.erase(0, pos + 1);

        pos = currentLine.find('_');
        string seriesId = currentLine.substr(0, pos);
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

        if(!currentLine.empty())
        {
            actors.push_back(currentLine);
        }

        Episode m = Episode(id, title, description, genre, creatorId, year, mark, isWatched, length, episodeNumber, seasonNumber, seriesId, actors);
        episodes.push_back(m);
    }
}

void EpisodeManager::saveToFile()
{
    ofstream file("episodes.txt", std::ofstream::in | std::ofstream::trunc);

    if(!file.is_open())
    {
        return;
    }

    for(auto& ep : episodes)
    {
        file << ep.toString() << endl;
    }

    file.close();
}
