#ifndef PERSON_H
#define PERSON_H
#include "entry.h"

#include <string>

using namespace std;

class Person : Entry
{
public:
    Person();
    Person(string firstName, string lastName, int birthYear, int birthMonth, int birthDay);
    Person(string id, string firstName, string lastName, int birthYear, int birthMonth, int birthDay);
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

private:
    string firstName;
    string lastName;
    int birthYear;
    int birthMonth;
    int birthDay;
};

#endif // PERSON_H
