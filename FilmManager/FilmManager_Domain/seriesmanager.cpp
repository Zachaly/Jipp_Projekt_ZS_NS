#include "seriesmanager.h"

std::vector<Serie> SeriesManager::series = vector<Serie>();

inline std::vector<Serie> &SeriesManager::getSeries()
{
    return series;
}

inline std::vector<Serie> &SeriesManager::getSeries(function<bool (Serie)> filter)
{
    vector<Serie>* res = new vector<Serie>();

    for(auto serie : series)
    {
        if(filter(serie))
        {
            res->push_back(serie);
        }
    }

    return *res;
}

inline Serie &SeriesManager::getById(string id)
{
    for(auto serie : series)
    {
        if(serie.getId() == id)
        {
            return serie;
        }
    }

    Serie s;

    return s;
}

inline void SeriesManager::addSerie(Serie &serie)
{
    series.push_back(serie);
}
