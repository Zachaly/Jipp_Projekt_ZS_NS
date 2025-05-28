#ifndef MOVIE_H
#define MOVIE_H
#include "titleentry.h"
#include <vector>

class Movie : public TitleEntry
{
public:
    Movie();
    Movie(const std::string& title, const std::string& description, Genre genre,
          const std::string& creatorId, int productionYear, int mark, bool isWatched,
          int length, const std::vector<std::string>& actorIds);
    Movie(const std::string& id, const std::string& title, const std::string& description,
          Genre genre, const std::string& creatorId, int productionYear, int mark, bool isWatched,
          int length, const std::vector<std::string>& actorIds);

    virtual ~Movie() = default;

    int getLength() const;
    void setLength(int newLength);

    const std::vector<std::string>& getActorIds() const;
    void setActorIds(const std::vector<std::string>& newActorIds);
    void addActor(const std::string& actorId);
    void removeActor(const std::string& actorId);

private:
    int length;
    std::vector<std::string> actorIds;
};

#endif // MOVIE_H
