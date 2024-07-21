#ifndef ADMIN_H
#define ADMIN_H

#include <string>
#include <vector>
#include <regex>
#include <iostream>
#include <fstream>
#include <iomanip>
#include <sys/stat.h>
#include <sys/types.h>

class Admin {
public:
    void addNhanVien();
    void addLuong();
    void addNgayTruc();
    // void editNhanVien();
    // void editLuong();
    // void editNgayTruc();
    void addBenhAn();
    // void editBenhAn();

private:
    bool isValidDate(const std::string& date) const;
    bool isValidGender(const std::string& gender) const;
    bool isDayAvailable(const std::string& day, const std::string& nvId) const;
    bool hasReachedMaxEmployees(const std::string& filePath) const;
    std::string getNextId(const std::string& filePath, const std::string& prefix) const;
};

#endif // ADMIN_H
