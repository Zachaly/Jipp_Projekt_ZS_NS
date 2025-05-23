#include "personmanager.h"
std::vector<Person> PersonManager::people;

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
                      int birthYear, int birthMonth, int birthDay) {
    Person newPerson(firstName, lastName, birthYear, birthMonth, birthDay);
    std::string id = newPerson.getId();
    people.push_back(newPerson);
    return id;
}

void PersonManager::loadSampleData() {

    if (people.empty()) {
        try {
            people.push_back(Person("John", "Doe", 1980, 5, 15));
            people.push_back(Person("Jane", "Smith", 1985, 8, 22));
            people.push_back(Person("Robert", "Johnson", 1975, 3, 10));
        } catch (const std::invalid_argument& e) {

        }
    }
}
