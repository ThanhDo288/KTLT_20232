
#ifndef USER_H
#define USER_H

#include <string>

using namespace std;

class User {
protected:
    string id;
    string name;
    string ngaySinh;
    string gioiTinh;

public:
    User() {}
    User(string id, string name, string ngaySinh, string gioiTinh)
        : id(id), name(name), ngaySinh(ngaySinh), gioiTinh(gioiTinh) {}
    virtual void displayInfo() const = 0;
    string getId() const { return id; }
    string getName() const { return name; }
    string getNgaySinh() const { return ngaySinh; }
    string getGioiTinh() const { return gioiTinh; }
};

#endif // USER_H
