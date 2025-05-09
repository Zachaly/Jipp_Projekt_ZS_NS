#include "serieStatus.h"

string serieStatusString(SerieStatus status)
{
    string res = "";

    switch(status)
    {
    case Ongoing:
        res = "Ongoing";
        break;
    case Cancelled:
        res = "Cancelled";
        break;
    case Ended:
        res = "Ended";
        break;
    }

    return res;
}
