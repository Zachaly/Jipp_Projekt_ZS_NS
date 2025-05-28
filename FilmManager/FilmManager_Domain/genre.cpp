#include "genre.h"

string getGenreString(Genre genre)
{
    string res = "";
    switch(genre)
    {
    case Adventure:
        res = "Adventure";
        break;
    case Action:
        res = "Action";
        break;
    case Comedy:
        res = "Comedy";
        break;
    case Drama:
        res = "Drama";
        break;
    case Horror:
        res = "Horror";
        break;
    case Romance:
        res = "Romance";
        break;
    case SciFi:
        res = "Sci-Fi";
        break;
    case Thriller:
        res = "Thriller";
        break;
    case Historical:
        res = "Historical";
        break;
    }
    return res;
}

Genre getGenreFromString(const string& genreStr) {
    if (genreStr == "Adventure") return Adventure;
    if (genreStr == "Action") return Action;
    if (genreStr == "Comedy") return Comedy;
    if (genreStr == "Drama") return Drama;
    if (genreStr == "Horror") return Horror;
    if (genreStr == "Romance") return Romance;
    if (genreStr == "Sci-Fi") return SciFi;
    if (genreStr == "Thriller") return Thriller;
    if (genreStr == "Historical") return Historical;
    return Adventure; // domyślny
}
