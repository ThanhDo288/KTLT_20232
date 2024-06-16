#include <iostream>
#include <unordered_map>
#include "KhachHang.h"
#include "NhanVien.h"

using namespace std;

unordered_map<string, KhachHang> khachHangMap;
unordered_map<string, NhanVien> nhanVienMap;

void khoiTaoDuLieu() {
    ifstream file("KH.txt");
    if (file.is_open()) {
        while (!file.eof()) {
            KhachHang kh;
            kh.loadFromFile(file);
            if (file.fail()) break; // Check for failure
            khachHangMap[kh.getId()] = kh;
        }
        file.close();
    } else {
        cout << "Khong the mo file KH.txt de doc du lieu.\n";
    }

    nhanVienMap["NV001"] = NhanVien("NV001", "Le Van C");
    nhanVienMap["NV002"] = NhanVien("NV002", "Hoang Thi D");
}

User* dangNhap(int loai) {
    string id;
    cout << "Nhap ma so: ";
    cin >> id;
    cin.ignore();

    if (loai == 1) { // Khach hang
        if (khachHangMap.find(id) != khachHangMap.end()) {
            return &khachHangMap[id];
        } else {
            cout << "Ma khach hang khong ton tai.\n";
        }
    } else if (loai == 2) { // Nhan vien
        if (nhanVienMap.find(id) != nhanVienMap.end()) {
            return &nhanVienMap[id];
        } else {
            cout << "Ma nhan vien khong ton tai.\n";
        }
    }
    return nullptr;
}


int main() {
    khoiTaoDuLieu();

    int choice;
    while (true) {
        cout << "Chon loai dang nhap:\n";
        cout << "1. Dang nhap khach hang (nhan 1)\n";
        cout << "2. Dang nhap nhan vien (nhan 2)\n";
        cout << "3. Thoat chuong trinh\n";
        cout << "Nhap lua chon: ";
        cin >> choice;
        cin.ignore();

        if (choice == 3) {
            cout << "Thoat chuong trinh...\n";
            break;
        }

        User* user = dangNhap(choice);
        if (user != nullptr) {
            cout << "Dang nhap thanh cong!\n";
            user->displayInfo();

            if (choice == 1) {
                KhachHang* kh = dynamic_cast<KhachHang*>(user);
                giaoDienKhachHang(kh);
            } else {
                // Giao diện cho nhân viên (nếu cần)
            }
        } else {
            cout << "Dang nhap that bai.\n";
        }
    }

    return 0;
}
