#ifndef DISPLAYHELPERS_H
#define DISPLAYHELPERS_H

#include "FilmManager_Domain/genre.h"
#include "FilmManager_Domain/person.h"
#include "FilmManager_Domain/serieStatus.h"
#include <QString>
QString getGenreIcon(Genre genre);

QString getGenreName(Genre genre);

QString generateStarRating(double rating);
QString getRoleIcon(const Person& person);
QString getStatusName(SerieStatus status);
QString getRoleText(const Person& person);
#endif // DISPLAYHELPERS_H
