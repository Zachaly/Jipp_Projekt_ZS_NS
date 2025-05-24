#include "entry.h"
#include <ctime>
#include <string>

Entry::Entry() {
    this->id = generateId();
}

Entry::Entry(string id)
{
    this->id = id;
}

string Entry::getId() const {
    return id;
}

string Entry::generateId()
{
    srand((unsigned)time(NULL));
    static const char alphanum[] =
        "0123456789"
        "ABCDEFGHIJKLMNOPQRSTUVWXYZ"
        "abcdefghijklmnopqrstuvwxyz";
    std::string tmp_s;
    tmp_s.reserve(50);

    for (int i = 0; i < 50; ++i) {
        tmp_s += alphanum[rand() % (sizeof(alphanum) - 1)];
    }

    return tmp_s;
}
