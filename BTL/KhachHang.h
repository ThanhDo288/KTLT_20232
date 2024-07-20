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
    void addBenhAn(const std::string& benh, const std::string& ngay, const std::string& tenKH, const std::string& tenBS, const std::string& idBS, const std::string& rootPath);
    void hienThiLichThamKham() const;
    void hienThiBenhAn(const std::string& rootPath) const;
    void hienThiThongTinCaNhan() const;
     void chinhSuaThongTinCaNhan();
    void datLichThamKham(const std::string& lich, const std::string& rootPath);
    void xoaLichThamKham(const std::string& rootPath);
    void chinhSuaLichThamKham(const std::string& rootPath);
    void timKiemLichThamKham(const std::string& rootPath);
    void timKiemBenhAn(const std::string& keyword, const std::string& rootPath) const;
};

void giaoDienKhachHang(KhachHang* kh);
void giaoDienLichThamKham(KhachHang* kh, const std::string& rootPath);
void giaoDienDatLichThamKham(KhachHang* kh, const std::string& rootPath);
void giaoDienXemLichThamKham(KhachHang* kh, const std::string& rootPath);
void giaoDienBenhAn(KhachHang* kh, const std::string& rootPath);

#endif // KHACHHANG_H
