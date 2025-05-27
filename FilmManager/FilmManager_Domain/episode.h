#ifndef EPISODE_H
#define EPISODE_H

#include "movie.h"


class Episode : public Movie
{
public:
    Episode();
    Episode(string title, string description, Genre genre, string creatorId, int productionYear, int mark, bool isWatched,
            int length, int episodeNumber, int seasonNumber, string seriesId, vector<string> actorIds);
    Episode(string id, string title, string description, Genre genre, string creatorId, int productionYear, int mark, bool isWatched,
            int length, int episodeNumber, int seasonNumber, string seriesId, vector<string> actorIds);
    string toString();
    int getSeasonNumber() const;
    void setSeasonNumber(int newSeasonNumber);
    int getEpisodeNumber() const;
    void setEpisodeNumber(int newEpisodeNumber);
    string getSeriesId() const;
    void setSeriesId(const string &newSeriesId);

private:
    int seasonNumber;
    int episodeNumber;
    string seriesId;

};

#endif // EPISODE_H
