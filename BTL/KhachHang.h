#ifndef KHACHHANG_H
#define KHACHHANG_H

#include "User.h"
#include <vector>
#include <string>
#include <fstream>

class KhachHang : public User {
private:
    vector<string> lichThamKham;
    vector<string> benhAn;

public:
    KhachHang();
    KhachHang(string id, string name);

    void displayInfo() const override;
    void loadFromFile(ifstream &file);
    void addLichThamKham(const string& lich);
    void addBenhAn(const string& benh);
    void hienThiLichThamKham() const;
    void hienThiBenhAn() const;
    void hienThiThongTinCaNhan() const;
};
void giaoDienKhachHang(KhachHang* kh);
#endif // KHACHHANG_H
