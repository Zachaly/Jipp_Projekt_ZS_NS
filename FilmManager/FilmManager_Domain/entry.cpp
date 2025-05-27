#include "entry.h"
#include <ctime>
#include <cstdlib>
#include <string>

Entry::Entry() {
    this->id = generateId();
}

Entry::Entry(const std::string& id)
{
    this->id = id;
}

std::string Entry::getId() const {
    return id;
}

std::string Entry::generateId()
{
    static bool seeded = false;
    if (!seeded) {
        srand(static_cast<unsigned>(time(nullptr)));
        seeded = true;
    }

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
