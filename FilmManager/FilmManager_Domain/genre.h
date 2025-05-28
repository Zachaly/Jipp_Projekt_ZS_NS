#ifndef GENRE_H
#define GENRE_H

#include <string>
using namespace std;

enum Genre {
    Adventure,
    Action,
    Comedy,
    Drama,
    Horror,
    Romance,
    SciFi,
    Thriller,
    Historical
};

string getGenreString(Genre genre);
Genre getGenreFromString(const string& genreStr);

#endif // GENRE_H
