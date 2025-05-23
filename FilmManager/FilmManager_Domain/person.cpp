#include "person.h"

#include <stdexcept>
#include <sstream>

using namespace std;

Person::Person() : Entry() {}

string Person::getFirstName() const
{
    return firstName;
}

Person::Person(string firstName, string lastName, int birthYear, int birthMonth, int birthDay) : Entry()
{
    this->firstName = firstName;
    this->lastName = lastName;

    if(birthYear < 0)
    {
        throw invalid_argument("Invalid year");
    }

    if(birthMonth < 0 || birthMonth > 12)
    {
        throw invalid_argument("Invalid birth month");
    }

    if(birthDay < 0 ||
        (birthDay > 31 && ((birthMonth <= 7 && birthMonth % 2 == 1) || (birthMonth >= 8 && birthMonth % 2 == 0))) ||
        (birthDay > 30 && ((birthMonth <= 7 && birthMonth % 2 == 0 && birthMonth != 2) || (birthMonth >= 8 && birthMonth % 2 == 1))) ||
        (birthDay > 29 && birthMonth == 2))
    {
        throw invalid_argument("Invalid birth day");
    }

    this->birthDay = birthDay;
    this->birthMonth = birthMonth;
    this->birthYear = birthYear;
}

Person::Person(string id, string firstName, string lastName, int birthYear, int birthMonth, int birthDay) : Entry(id)
{
    this->firstName = firstName;
    this->lastName = lastName;

    if(birthYear < 0)
    {
        throw invalid_argument("Invalid year");
    }

    if(birthMonth < 0 || birthMonth > 12)
    {
        throw invalid_argument("Invalid birth month");
    }

    if(birthDay < 0 ||
        (birthDay > 31 && ((birthMonth <= 7 && birthMonth % 2 == 1) || (birthMonth >= 8 && birthMonth % 2 == 0))) ||
        (birthDay > 30 && ((birthMonth <= 7 && birthMonth % 2 == 0 && birthMonth != 2) || (birthMonth >= 8 && birthMonth % 2 == 1))) ||
        (birthDay > 29 && birthMonth == 2))
    {
        throw invalid_argument("Invalid birth day");
    }

    this->birthDay = birthDay;
    this->birthMonth = birthMonth;
    this->birthYear = birthYear;
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

string Person::toString()
{
    stringstream stream;
    stream << getId() << " " << firstName << " " << lastName << " " << birthYear << " " << birthMonth << " " << birthDay;
    return stream.str();

}
