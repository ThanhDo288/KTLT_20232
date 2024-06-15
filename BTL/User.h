#ifndef USER_H
#define USER_H

#include <string>

using namespace std;

class User {
protected:
    string id;
    string name;

public:
    User() {}
    User(string id, string name) : id(id), name(name) {}
    virtual void displayInfo() const = 0;
    string getId() const { return id; }
};

#endif // USER_H
