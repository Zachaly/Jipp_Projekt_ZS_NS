#include "displayhelpers.h"
#include <cmath>

QString getGenreIcon(Genre genre)
{
    switch (genre) {
    case Genre::Action: return "⚔️";
    case Genre::Adventure: return "🗺️";
    case Genre::Comedy: return "😄";
    case Genre::Drama: return "🎭";
    case Genre::Horror: return "👻";
    case Genre::Romance: return "💕";
    case Genre::SciFi: return "🚀";
    case Genre::Thriller: return "🔪";
    case Genre::Historical: return "🏛️";
    default: return "🎬";
    }
}

QString getGenreName(Genre genre)
{
    switch (genre) {
    case Genre::Action: return "Akcja";
    case Genre::Adventure: return "Przygodowy";
    case Genre::Comedy: return "Komedia";
    case Genre::Drama: return "Dramat";
    case Genre::Horror: return "Horror";
    case Genre::Romance: return "Romans";
    case Genre::SciFi: return "Sci-Fi";
    case Genre::Thriller: return "Thriller";
    case Genre::Historical: return "Historyczny";
    default: return "Nieznany";
    }
}

QString generateStarRating(double rating)
{
    int fullRating = static_cast<int>(round(rating));
    if (fullRating < 1) fullRating = 1;
    if (fullRating > 10) fullRating = 10;

    string stars;
    for (int i = 0; i < fullRating; ++i) {
        stars += "⭐";
    }

    return QString::fromStdString(stars);
}

QString getRoleIcon(const Person& person)
{
    if (person.getIsDirector() && person.getIsActor()) {
        return "🎭🎬";
    } else if (person.getIsDirector()) {
        return "🎬";
    } else if (person.getIsActor()) {
        return "🎭";
    }
    return "👤";
}

QString getRoleText(const Person& person)
{
    if (person.getIsDirector() && person.getIsActor()) {
        return "Reżyser & Aktor";
    } else if (person.getIsDirector()) {
        return "Reżyser";
    } else if (person.getIsActor()) {
        return "Aktor";
    }
    return "Osoba";
}

QString getStatusName(SerieStatus status)
{
    switch (status) {
    case SerieStatus::Cancelled: return "Anulowany";
    case SerieStatus::Ended: return "Zakończony";
    case SerieStatus::Ongoing: return "Trwający";
    default: return "Nieznany";
    }
}
