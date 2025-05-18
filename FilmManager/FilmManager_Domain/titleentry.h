#ifndef TITLEENTRY_H
#define TITLEENTRY_H
#include "entry.h"
#include <string>
#include "genre.h"

using namespace std;

class TitleEntry : public Entry
{
public:
    TitleEntry();
    TitleEntry(string title, string description, Genre genre, string creatorId, int productionYear, int mark, bool isWatched);
    TitleEntry(string id, string title, string description, Genre genre, string creatorId, int productionYear, int mark, bool isWatched);

    string getTitle() const;
    void setTitle(const string &newTitle);
    string getDescription() const;
    void setDescription(const string &newDescription);
    Genre getGenre() const;
    void setGenre(Genre newGenre);
    string getCreatorId() const;
    void setCreatorId(const string &newCreatorId);
    int getProductionYear() const;
    void setProductionYear(int newProductionYear);
    int getMark() const;
    void setMark(int newMark);
    bool getIsWatched() const;
    void setIsWatched(bool newIsWatched);
private:
    string title;
    string description;
    Genre genre;
    string creatorId;
    int productionYear;
    int mark;
    bool isWatched;
protected:
    string stringify();
};

#endif // TITLEENTRY_H
