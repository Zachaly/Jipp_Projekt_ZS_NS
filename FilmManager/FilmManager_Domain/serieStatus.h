#ifndef SERIESTATUS_H
#define SERIESTATUS_H

#include <string>

using namespace std;

enum SerieStatus {
    Ongoing,
    Ended,
    Cancelled
};

string serieStatusString(SerieStatus status);

#endif // SERIESTATUS_H
