#include "personmanager.h"
#include <iostream>
#include <fstream>
std::vector<Person> PersonManager::people;

std::vector<Person> &PersonManager::getPeople()
{
    return people;
}

Person& PersonManager::getPersonById(const std::string& id) {
    for (auto& person : PersonManager::people) {
        if (person.getId() == id) {
            return person;
        }
    }


    if (!people.empty()) {
        return people[0];
    }


    static Person dummyPerson;
    return dummyPerson;
}

std::string PersonManager::addPerson(const std::string& firstName, const std::string& lastName,
                      int birthYear, int birthMonth, int birthDay, bool isActor, bool isDirector) {
    Person newPerson(firstName, lastName, birthYear, birthMonth, birthDay, isActor, isDirector);
    std::string id = newPerson.getId();
    people.push_back(newPerson);
    saveToFile();
    return id;
}

void PersonManager::removePerson(const std::string& id)
{
    people.erase(std::remove_if(people.begin(), people.end(),
                                [&id](const Person& person) { return person.getId() == id; }),
                 people.end());
    saveToFile();
}

std::vector<Person> &PersonManager::getPeople(function<bool (Person)> filter)
{
    vector<Person>* res = new vector<Person>();
    for(auto i = people.begin(); i != people.end(); i++)
    {
        if(filter(*i))
        {
            (*res).push_back(*i);
        }
    }

    return *res;
}

void PersonManager::saveToFile()
{
    ofstream file("people.txt", std::ofstream::in | std::ofstream::trunc);

    if(!file.is_open())
    {
        return;
    }

    for(auto& p : people)
    {
        file << p.toString() << endl;
    }

    file.close();
}

void PersonManager::loadFromFile()
{
    ifstream file("people.txt");

    if(!file.is_open())
    {
        return;
    }

    string currentLine;

    while(getline(file, currentLine))
    {
        if(currentLine.empty())
        {
            break;
        }

        auto pos = currentLine.find('_');
        string id = currentLine.substr(0, pos);
        currentLine.erase(0, pos + 1);

        pos = currentLine.find('_');
        string fname = currentLine.substr(0, pos);
        currentLine.erase(0, pos + 1);

        pos = currentLine.find('_');
        string lname = currentLine.substr(0, pos);
        currentLine.erase(0, pos + 1);

        pos = currentLine.find('_');
        int year = stoi(currentLine.substr(0, pos));
        currentLine.erase(0, pos + 1);

        pos = currentLine.find('_');
        int month = stoi(currentLine.substr(0, pos));
        currentLine.erase(0, pos + 1);

        pos = currentLine.find('_');
        int day = stoi(currentLine.substr(0, pos));
        currentLine.erase(0, pos + 1);

        pos = currentLine.find('_');
        bool isDirector = stoi(currentLine.substr(0, pos));
        currentLine.erase(0, pos + 1);

        pos = currentLine.find('_');
        bool isActor = stoi(currentLine.substr(0, pos));
        currentLine.erase(0, pos + 1);

        Person p = Person(id, lname, fname, year, month, day, isActor, isDirector);
        people.push_back(p);
    }

    file.close();
}
