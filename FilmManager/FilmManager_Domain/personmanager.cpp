#include "personmanager.h"
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
    return id;
}

void PersonManager::removePerson(const std::string& id)
{
    people.erase(std::remove_if(people.begin(), people.end(),
                                [&id](const Person& person) { return person.getId() == id; }),
                 people.end());
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
