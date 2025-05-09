#include "genre.h"

string getGenreString(Genre genre)
{
    string res = "";

    switch(genre)
    {
        case Adventure:
            res = "Adventure";
            break;
    }

    return res;
}
