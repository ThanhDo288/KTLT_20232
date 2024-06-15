#ifndef NHANVIEN_H
#define NHANVIEN_H

#include "User.h"

class NhanVien : public User {
public:
    NhanVien();
    NhanVien(string id, string name);
    void displayInfo() const override;
};

#endif // NHANVIEN_H
