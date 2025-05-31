#ifndef EPISODEMANAGER_H
#define EPISODEMANAGER_H

#include "episode.h"
#include <functional>
class EpisodeManager
{
public:
    static vector<Episode>& getEpisodes();
    static vector<Episode>& getEpisodes(function<bool(Episode)> filter);
    static Episode& getById(string id);
    static void addEpisode(Episode& episode);
    static void removeEpisode(string id);
    static void loadFromFile();
    static void saveToFile();
private:
    static vector<Episode> episodes;
};

#endif // EPISODEMANAGER_H
