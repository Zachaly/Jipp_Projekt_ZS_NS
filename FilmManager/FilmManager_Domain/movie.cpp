#include "movie.h"
#include <algorithm>

#include <sstream>

Movie::Movie() : TitleEntry(), length(0) {}

Movie::Movie(const std::string& title, const std::string& description, Genre genre,
             const std::string& creatorId, int productionYear, int mark, bool isWatched,
             int length, const std::vector<std::string>& actorIds)
    : TitleEntry(title, description, genre, creatorId, productionYear, mark, isWatched),
    length(length), actorIds(actorIds)
{
}

Movie::Movie(const std::string& id, const std::string& title, const std::string& description,
             Genre genre, const std::string& creatorId, int productionYear, int mark, bool isWatched,
             int length, const std::vector<std::string>& actorIds)
    : TitleEntry(id, title, description, genre, creatorId, productionYear, mark, isWatched),
    length(length), actorIds(actorIds)
{
}

int Movie::getLength() const
{
    return length;
}

void Movie::setLength(int newLength)
{
    length = newLength;
}

const vector<string>& Movie::getActorIds() const
{
    return actorIds;
}

void Movie::setActorIds(const std::vector<std::string>& newActorIds)
{
    actorIds = newActorIds;
}

void Movie::addActor(const std::string& actorId)
{
    if (std::find(actorIds.begin(), actorIds.end(), actorId) == actorIds.end()) {
        actorIds.push_back(actorId);
    }
}

void Movie::removeActor(const std::string& actorId)
{
    actorIds.erase(std::remove(actorIds.begin(), actorIds.end(), actorId), actorIds.end());
}

string Movie::toString()
{
    stringstream stream;
    stream << getId() << "_" << getTitle() << "_" << getDescription() << "_"
           << static_cast<int>(getGenre()) << "_" << getCreatorId() << "_" << getProductionYear() << "_"
           << getMark() << "_" << getIsWatched() << "_" << length;

    for(auto id : actorIds)
    {
        stream << "_" << id;
    }

    return stream.str();
}
