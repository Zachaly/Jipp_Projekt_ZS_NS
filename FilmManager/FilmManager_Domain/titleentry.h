#ifndef TITLEENTRY_H
#define TITLEENTRY_H
#include "entry.h"
#include <string>
#include "genre.h"

class TitleEntry : public Entry
{
public:
    TitleEntry();
    TitleEntry(const std::string& title, const std::string& description, Genre genre,
               const std::string& creatorId, int productionYear, int mark, bool isWatched);
    TitleEntry(const std::string& id, const std::string& title, const std::string& description,
               Genre genre, const std::string& creatorId, int productionYear, int mark, bool isWatched);

    virtual ~TitleEntry() = default;

    std::string getTitle() const;
    void setTitle(const std::string &newTitle);

    std::string getDescription() const;
    void setDescription(const std::string &newDescription);

    Genre getGenre() const;
    void setGenre(Genre newGenre);

    std::string getCreatorId() const;
    void setCreatorId(const std::string &newCreatorId);

    int getProductionYear() const;
    void setProductionYear(int newProductionYear);

    int getMark() const;
    void setMark(int newMark);

    bool getIsWatched() const;
    void setIsWatched(bool newIsWatched);

protected:
    virtual std::string stringify();

private:
    std::string title;
    std::string description;
    Genre genre;
    std::string creatorId;
    int productionYear;
    int mark;
    bool isWatched;
};

#endif // TITLEENTRY_H
