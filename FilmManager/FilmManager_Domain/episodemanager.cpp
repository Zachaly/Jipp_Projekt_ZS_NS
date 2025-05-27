#include "episodemanager.h"

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
        res->push_back(e);
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
}
