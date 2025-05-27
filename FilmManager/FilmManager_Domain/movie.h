#ifndef MOVIE_H
#define MOVIE_H

#include "person.h"
#include "titleentry.h"
#include <vector>

class Movie : public TitleEntry
{
public:
    Movie();
    Movie(string title, string description, Genre genre, string creatorId, int productionYear, int mark, bool isWatched, int length, vector<string> actorIds);
    Movie(string id, string title, string description, Genre genre, string creatorId, int productionYear, int mark, bool isWatched, int length, vector<string> actorIds);
    int getLength() const;
    void setLength(int newLength);
    vector<string>& getActorIds();
    void setActorIds(const vector<string> &newActorIds);
    string toString();
    void addActor(string actorId);
    void addActor(Person person);
private:
    int length;
    vector<string> actorIds;
protected:
    string stringify();
};

#endif // MOVIE_H
