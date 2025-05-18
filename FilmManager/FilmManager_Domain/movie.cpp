#include "movie.h"
#include <sstream>

using namespace std;

Movie::Movie() : TitleEntry() {}

Movie::Movie(string title, string description, Genre genre, string creatorId, int productionYear, int mark, bool isWatched, int length, vector<string> actorIds)
    : TitleEntry(title, description, genre, creatorId, productionYear, mark, isWatched)
{
    this->length = length;
    this->actorIds = actorIds;
}

Movie::Movie(string id, string title, string description, Genre genre, string creatorId, int productionYear, int mark, bool isWatched, int length, vector<string> actorIds)
    : TitleEntry(id, title, description, genre, creatorId, productionYear, mark, isWatched)
{
    this->length = length;
    this->actorIds = actorIds;
}


int Movie::getLength() const
{
    return length;
}

void Movie::setLength(int newLength)
{
    length = newLength;
}

vector<string> Movie::getActorIds() const
{
    return actorIds;
}

void Movie::setActorIds(const vector<string> &newActorIds)
{
    actorIds = newActorIds;
}

string Movie::toString()
{
    stringstream stream;
    stream << stringify() << " " << length;
    for(auto i = actorIds.cbegin(); i != actorIds.cend(); i++)
    {
        stream << " " << *i;
    }
    return stream.str();
}

string Movie::stringify()
{
    return TitleEntry::stringify();
}
