#include "entry.h"

Entry::Entry() {
    this->id = "random"; //TODO: generate random id
}

Entry::Entry(string id)
{
    this->id = id;
}

string Entry::getId() const {
    return id;
}
