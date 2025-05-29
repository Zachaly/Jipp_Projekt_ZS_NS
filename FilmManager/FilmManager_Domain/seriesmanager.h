#ifndef SERIESMANAGER_H
#define SERIESMANAGER_H

#include "serie.h"
#include <functional>
class SeriesManager {
public:
    static std::vector<Serie>& getSeries();
    static std::vector<Serie>& getSeries(function<bool(Serie)> filter);

    static Serie& getById(string id);
    static void addSerie(Serie& serie);
    static void removeSerie(string id);
private:
    static std::vector<Serie> series;
};

#endif // SERIESMANAGER_H
