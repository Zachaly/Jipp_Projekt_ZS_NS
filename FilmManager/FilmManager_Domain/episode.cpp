#include "episode.h"
#include <sstream>

Episode::Episode() : Movie() {}

Episode::Episode(string title, string description, Genre genre, string creatorId, int productionYear, int mark, bool isWatched, int length, int episodeNumber,
                 int seasonNumber, string seriesId, vector<string> actorIds) : Movie(title, description, genre, creatorId, productionYear, mark, isWatched, length, actorIds)
{
    this->episodeNumber = episodeNumber;
    this->seasonNumber = seasonNumber;
    this->seriesId = seriesId;
}

Episode::Episode(string id, string title, string description, Genre genre, string creatorId, int productionYear, int mark, bool isWatched, int length, int episodeNumber,
                 int seasonNumber, string seriesId, vector<string> actorIds) : Movie(id, title, description, genre, creatorId, productionYear, mark, isWatched, length, actorIds)
{
    this->episodeNumber = episodeNumber;
    this->seasonNumber = seasonNumber;
    this->seriesId = seriesId;
}

string Episode::toString()
{
    stringstream stream;
    stream << stringify() << getLength() << " " << episodeNumber << " " << seasonNumber << " " << seriesId;
    auto actors = getActorIds();
    for(auto i = actors.cbegin(); i != actors.cend(); i++)
    {
        stream << " " << *i;
    }

    return stream.str();
}

int Episode::getSeasonNumber() const
{
    return seasonNumber;
}

void Episode::setSeasonNumber(int newSeasonNumber)
{
    seasonNumber = newSeasonNumber;
}

int Episode::getEpisodeNumber() const
{
    return episodeNumber;
}

void Episode::setEpisodeNumber(int newEpisodeNumber)
{
    episodeNumber = newEpisodeNumber;
}

string Episode::getSeriesId() const
{
    return seriesId;
}

void Episode::setSeriesId(const string &newSeriesId)
{
    seriesId = newSeriesId;
}
