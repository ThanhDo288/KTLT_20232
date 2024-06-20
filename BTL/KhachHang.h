
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
    void datLichThamKham(const std::string& lich, const std::string& rootPath);
    void xoaLichThamKham(const std::string& rootPath);
    void chinhSuaLichThamKham(const std::string& rootPath);
    void timKiemLichThamKham(const std::string& rootPath);
};

void giaoDienKhachHang(KhachHang* kh);
#endif // KHACHHANG_H
