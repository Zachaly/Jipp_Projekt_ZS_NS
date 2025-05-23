#ifndef ENTRY_H
#define ENTRY_H
#include <string>
using namespace std;

class Entry
{
public:
    Entry();
    Entry(string id);
    string getId() const;
    virtual string toString() = 0;
protected:
    string id;
    string generateId();
};

#endif // ENTRY_H
