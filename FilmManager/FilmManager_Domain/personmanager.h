#ifndef PERSONMANAGER_H
#define PERSONMANAGER_H
#include "person.h"
#include <vector>
#include <QString>
#include <QDate>


class PersonManager {
public:
    static std::vector<Person>& getPeople() { return people; }

    static Person& getPersonById(const std::string& id);

    static std::string addPerson(const std::string& firstName, const std::string& lastName,
                                 int birthYear, int birthMonth, int birthDay);

    static void loadSampleData();

private:
    static std::vector<Person> people;
};

#endif // PERSONMANAGER_H
