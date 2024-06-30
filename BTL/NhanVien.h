#ifndef NHANVIEN_H
#define NHANVIEN_H

#include "User.h"
#include <vector>
#include <string>
#include <fstream>
#include <iostream>

using namespace std;

class NhanVien : public User {
private:
    vector<string> CaTruc;
    int luong;
public:
    NhanVien();
    NhanVien(string id, string name, string ngaySinh, string gioiTinh);

    void displayInfo() const override;
    void loadFromFile(ifstream &file);
    void hienThiCaTruc(const string& rootPath) const;
    void hienThiLuong(const string& rootPath) const;
    void addKhachHang(const string& rootPath) const;
    void timKiemKhachHang(const string& rootPath) const;
    void suaThongTinKhachHang(const string& khId, const string& rootPath) const;
};

void giaoDienNhanVien(NhanVien* nv);
void giaoDienThemKhachHang(NhanVien* nv, const string& rootPath);
void giaoDienThongTinKhachHang(const string& khId, const string& rootPath);

#endif // NHANVIEN_H
