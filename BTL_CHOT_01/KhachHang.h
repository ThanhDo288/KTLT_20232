#ifndef KHACHHANG_H
#define KHACHHANG_H

#include "User.h"
#include <vector>
#include <string>
#include <fstream>

class NhanVien;

class KhachHang : public User {
private:
    std::vector<std::string> lichThamKham;
    std::string benhAn;
    std::string ngayBatDau;

    friend class NhanVien;

public:
    KhachHang();
    KhachHang(std::string id, std::string name, std::string ngaySinh, std::string gioiTinh,std::string benhAn,std::string ngayBatDau);

    void displayInfo() const override;
    void loadFromFile(std::ifstream &file);
    void addLichThamKham(const std::string& lich);
    void hienThiLichThamKham() const;
    void hienThiBenhAn() const;
    void hienThiThongTinCaNhan() const;
    void datLichThamKham(const std::string& lich, const std::string& rootPath);
    void xoaLichThamKham(const std::string& rootPath);
    void chinhSuaLichThamKham(const std::string& rootPath);
    void timKiemLichThamKham(const std::string& rootPath);
    void timKiemBenhAn(const std::string& rootPath);
    void chinhSuaThongTinCaNhan(const std::string& rootPath);
};

void giaoDienKhachHang(KhachHang* kh);
void giaodienBenhAn(KhachHang* kh,const std::string& rootPath);
#endif // KHACHHANG_H
