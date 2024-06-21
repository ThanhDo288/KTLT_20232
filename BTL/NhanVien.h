#ifndef NHANVIEN_H
#define NHANVIEN_H

#include "User.h"
#include <vector>
#include <string>
#include <fstream>
#include <iostream>

class NhanVien : public User {
private:
    std::vector<std::string> CaTruc;

public:
    NhanVien();
    NhanVien(std::string id, std::string name);

    void displayInfo() const override;
    void loadFromFile(std::ifstream &file);
    void hienThiCaTruc(const std::string& rootPath) const;
    void hienThiLuong(const std::string& rootPath) const;

};

void giaoDienNhanVien(NhanVien* nv);

#endif // NHANVIEN_H

