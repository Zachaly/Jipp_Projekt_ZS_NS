#include "serie.h"
#include <sstream>

Serie::Serie() : TitleEntry() {}

Serie::Serie(string title, string description, Genre genre, string creatorId, int productionYear, int mark, bool isWatched, SerieStatus status, int seasonCount, vector<string> episodeIds)
    : TitleEntry(title, description, genre, creatorId, productionYear, mark, isWatched)
{
    this->status = status;
    this->seasonCount = seasonCount;
    this->episodeIds = episodeIds;
}

Serie::Serie(string id, string title, string description, Genre genre, string creatorId, int productionYear, int mark, bool isWatched, SerieStatus status, int seasonCount, vector<string> episodeIds)
    : TitleEntry(id, title, description, genre, creatorId, productionYear, mark, isWatched)
{
    this->status = status;
    this->seasonCount = seasonCount;
    this->episodeIds = episodeIds;
}

SerieStatus Serie::getStatus() const
{
    return status;
}

void Serie::setStatus(SerieStatus newStatus)
{
    status = newStatus;
}

int Serie::getSeasonCount() const
{
    return seasonCount;
}

void Serie::setSeasonCount(int newSeasonCount)
{
    seasonCount = newSeasonCount;
}

vector<string> Serie::getEpisodeIds() const
{
    return episodeIds;
}

void Serie::setEpisodeIds(const vector<string> &newEpisodeIds)
{
    episodeIds = newEpisodeIds;
}

string Serie::toString()
{
    stringstream stream;
    stream << getId() << "_" << getTitle() << "_" << getDescription() << "_" << static_cast<int>(getGenre()) << "_" << getCreatorId() << "_" << getProductionYear() << "_"
           << getMark() << "_" << getIsWatched() << "_" << status << "_" << seasonCount;
    for(auto& id : episodeIds)
    {
        stream << "_" << id;
    }

    return stream.str();
}
