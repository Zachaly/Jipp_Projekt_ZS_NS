#ifndef ENTRY_H
#define ENTRY_H
#include <string>
using namespace std;

class Entry
{
public:
    Entry();
    Entry(string id);
    string getId();
    virtual string toString() = 0;
private:
    string id;
};

#endif // ENTRY_H
