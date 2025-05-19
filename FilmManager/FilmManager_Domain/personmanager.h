#ifndef PERSONMANAGER_H
#define PERSONMANAGER_H
#include "person.h"
#include <vector>
#include <QString>
#include <QDate>


class PersonManager {
public:
    static std::vector<Person>& getPeople() { return people; }

    static Person& getPersonById(const std::string& id) {
        for (auto& person : people) {
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

    static std::string addPerson(const std::string& firstName, const std::string& lastName,
                                 int birthYear, int birthMonth, int birthDay) {
        Person newPerson(firstName, lastName, birthYear, birthMonth, birthDay);
        std::string id = newPerson.getId();
        people.push_back(newPerson);
        return id;
    }

    static void loadSampleData() {

        if (people.empty()) {
            try {
                people.push_back(Person("John", "Doe", 1980, 5, 15));
                people.push_back(Person("Jane", "Smith", 1985, 8, 22));
                people.push_back(Person("Robert", "Johnson", 1975, 3, 10));
            } catch (const std::invalid_argument& e) {

            }
        }
    }

private:
    static std::vector<Person> people;
};


inline QString toQString(const std::string& str) {
    return QString::fromStdString(str);
}

inline std::string fromQString(const QString& qstr) {
    return qstr.toStdString();
}


#endif // PERSONMANAGER_H
