#include "person.h"

Person::Person() {}

string Person::getFirstName() const
{
    return firstName;
}

void Person::setFirstName(const string &newFirstName)
{
    firstName = newFirstName;
}

string Person::getLastName() const
{
    return lastName;
}

void Person::setLastName(const string &newLastName)
{
    lastName = newLastName;
}

int Person::getBirthYear() const
{
    return birthYear;
}

void Person::setBirthYear(int newBirthYear)
{
    birthYear = newBirthYear;
}

int Person::getBirthMonth() const
{
    return birthMonth;
}

void Person::setBirthMonth(int newBirthMonth)
{
    birthMonth = newBirthMonth;
}

int Person::getBirthDay() const
{
    return birthDay;
}

void Person::setBirthDay(int newBirthDay)
{
    birthDay = newBirthDay;
}

Person::Person(const string &firstName, const string &lastName, int birthYear, int birthMonth, int birthDay) : firstName(firstName),
    lastName(lastName),
    birthYear(birthYear),
    birthMonth(birthMonth),
    birthDay(birthDay)
{}
