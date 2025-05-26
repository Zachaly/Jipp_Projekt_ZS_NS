#include "seriesmanager.h"

std::vector<Serie> SeriesManager::series = vector<Serie>();

std::vector<Serie> &SeriesManager::getSeries()
{
    return series;
}

std::vector<Serie> &SeriesManager::getSeries(function<bool (Serie)> filter)
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

Serie &SeriesManager::getById(string id)
{
    for(auto& serie : series)
    {
        if(serie.getId() == id)
        {
            return serie;
        }
    }

    Serie s;

    return s;
}

void SeriesManager::addSerie(Serie &serie)
{
    series.push_back(serie);
}
