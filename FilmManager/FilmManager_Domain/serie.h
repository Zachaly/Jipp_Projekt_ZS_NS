#ifndef SERIE_H
#define SERIE_H

#include "serieStatus.h"
#include "titleentry.h"

#include <vector>


class Serie : TitleEntry
{
public:
    Serie();
    Serie(string title, string description, Genre genre, string creatorId, int productionYear, int mark, bool isWatched, SerieStatus status, int seasonCount, vector<string> episodeIds);
    Serie(string id, string title, string description, Genre genre, string creatorId, int productionYear, int mark, bool isWatched, SerieStatus status, int seasonCount, vector<string> episodeIds);
    SerieStatus getStatus() const;
    void setStatus(SerieStatus newStatus);
    int getSeasonCount() const;
    void setSeasonCount(int newSeasonCount);
    vector<string> getEpisodeIds() const;
    void setEpisodeIds(const vector<string> &newEpisodeIds);
    string toString();

private:
    SerieStatus status;
    int seasonCount;
    vector<string> episodeIds;
};

#endif // SERIE_H
