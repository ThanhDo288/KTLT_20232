#ifndef ADMIN_H
#define ADMIN_H

#include <string>
#include <vector>
#include <regex>
#include <iostream>
#include <fstream>
#include <iomanip>
#include <unordered_map>
#include "User.h"

class Admin : public User {
public:
    Admin();
    Admin(std::string id, std::string name, std::string ngaySinh, std::string gioiTinh);

    void displayInfo() const override;
    void loadFromFile(std::ifstream &file);
    void addKhachHang();
    void addNhanVien();
    void addLuong();
    void addNgayTruc();
    void addBenhAn();
    void searchNhanVien() const;
    void searchKhachHang() const;

private:
    bool isValidDate(const std::string& date) const;
    bool isValidGender(const std::string& gender) const;
    bool isDayAvailable(const std::string& day, const std::string& nvId) const;
    bool hasReachedMaxEmployees(const std::string& filePath) const;
    std::string getNextId(const std::string& filePath, const std::string& prefix) const;
};

void giaoDienAdmin(Admin* ad);
#endif // ADMIN_H
