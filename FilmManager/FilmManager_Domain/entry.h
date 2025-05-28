#ifndef ENTRY_H
#define ENTRY_H
#include <string>
using namespace std;

class Entry
{
public:
    Entry();
    Entry(const string& id);
    virtual ~Entry() = default;

    string getId() const;

protected:
    string generateId();

private:
    string id;
};

#endif // ENTRY_H
