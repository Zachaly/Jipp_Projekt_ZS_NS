#ifndef PERSON_H
#define PERSON_H
#include "entry.h"

#include <string>

using namespace std;

class Person : public Entry
{
public:
    Person();
    Person(string firstName, string lastName, int birthYear, int birthMonth, int birthDay, bool isActor, bool isDirector);
    Person(string id, string firstName, string lastName, int birthYear, int birthMonth, int birthDay, bool isActor, bool isDirector);
    string toString();
    string getFirstName() const;
    void setFirstName(const string &newFirstName);
    string getLastName() const;
    void setLastName(const string &newLastName);
    int getBirthYear() const;
    void setBirthYear(int newBirthYear);
    int getBirthMonth() const;
    void setBirthMonth(int newBirthMonth);
    int getBirthDay() const;
    void setBirthDay(int newBirthDay);
    bool getIsDirector() const;
    void setIsDirector(bool value);
    bool getIsActor() const;
    void setIsActor(bool value);
private:
    string firstName;
    string lastName;
    int birthYear;
    int birthMonth;
    int birthDay;
    bool isActor;
    bool isDirector;
};

#endif // PERSON_H
