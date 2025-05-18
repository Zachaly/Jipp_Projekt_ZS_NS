#include "titleentry.h"
#include <sstream>

TitleEntry::TitleEntry() : Entry() {}

TitleEntry::TitleEntry(string title, string description, Genre genre, string creatorId, int productionYear, int mark, bool isWatched) : Entry()
{
    this->title = title;
    this->description = description;
    this->genre = genre;
    this->creatorId = creatorId;
    this->productionYear = productionYear;
    this->mark = mark;
    this->isWatched = isWatched;
}

TitleEntry::TitleEntry(string id, string title, string description, Genre genre, string creatorId, int productionYear, int mark, bool isWatched) : Entry(id)
{
    this->title = title;
    this->description = description;
    this->genre = genre;
    this->creatorId = creatorId;
    this->productionYear = productionYear;
    this->mark = mark;
    this->isWatched = isWatched;
}

string TitleEntry::getTitle() const
{
    return title;
}

void TitleEntry::setTitle(const string &newTitle)
{
    title = newTitle;
}

string TitleEntry::getDescription() const
{
    return description;
}

void TitleEntry::setDescription(const string &newDescription)
{
    description = newDescription;
}

Genre TitleEntry::getGenre() const
{
    return genre;
}

void TitleEntry::setGenre(Genre newGenre)
{
    genre = newGenre;
}

string TitleEntry::getCreatorId() const
{
    return creatorId;
}

void TitleEntry::setCreatorId(const string &newCreatorId)
{
    creatorId = newCreatorId;
}

int TitleEntry::getProductionYear() const
{
    return productionYear;
}

void TitleEntry::setProductionYear(int newProductionYear)
{
    productionYear = newProductionYear;
}

int TitleEntry::getMark() const
{
    return mark;
}

void TitleEntry::setMark(int newMark)
{
    mark = newMark;
}

bool TitleEntry::getIsWatched() const
{
    return isWatched;
}

void TitleEntry::setIsWatched(bool newIsWatched)
{
    isWatched = newIsWatched;
}

string TitleEntry::stringify()
{
    stringstream stream;
    stream << getId() << " " << "\"" << getTitle() << "\"" << " " << "\"" << getDescription() << " " << genre << " " << creatorId << " " << productionYear << " " << mark << " " << isWatched;
    return stream.str();
}
