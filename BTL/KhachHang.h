#ifndef KHACHHANG_H
#define KHACHHANG_H

#include "User.h"
#include <vector>
#include <string>
#include <fstream>

class KhachHang : public User {
private:
    std::vector<std::string> lichThamKham;
    std::vector<std::string> benhAn;

public:
    KhachHang();
    KhachHang(std::string id, std::string name);

    void displayInfo() const override;
    void loadFromFile(std::ifstream &file);
    void addLichThamKham(const std::string& lich);
    void addBenhAn(const std::string& benh);
    void hienThiLichThamKham() const;
    void hienThiBenhAn() const;
    void hienThiThongTinCaNhan() const;
    void datLichThamKham(const string& lich, const string& rootPath);
};
void giaoDienKhachHang(KhachHang* kh);
#endif // KHACHHANG_H
