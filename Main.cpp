#include <iostream>
#include <unordered_map>
#include "KhachHang.h"
#include "NhanVien.h"
#include "Admin.h"
#include "KhachHang.cpp"
#include "NhanVien.cpp"
#include "Admin.cpp"

using namespace std;

unordered_map<string, KhachHang> khachHangMap;
unordered_map<string, NhanVien> nhanVienMap;
unordered_map<string, Admin> adminMap;
void khoiTaoDuLieu() {
    // Đọc dữ liệu từ KH.txt
    ifstream fileKH("KH.txt");
    if (fileKH.is_open()) {
        while (!fileKH.eof()) {
            KhachHang kh;
            kh.loadFromFile(fileKH);
            if (!kh.getId().empty()) { // Kiểm tra xem ID có trống không
                khachHangMap[kh.getId()] = kh;
            }
        }
        fileKH.close();
    } else {
        cout << "Khong the mo file KH.txt de doc du lieu.\n";
    }

    // Đọc dữ liệu từ NV.txt
    ifstream fileNV("NV.txt");
    if (fileNV.is_open()) {
        while (!fileNV.eof()) {
            NhanVien nv;
            nv.loadFromFile(fileNV);
            if (!nv.getId().empty()) { // Kiểm tra xem ID có trống không
                nhanVienMap[nv.getId()] = nv;
            }
        }
        fileNV.close();
    } else {
        cout << "Khong the mo file NV.txt de doc du lieu.\n";
    }

    // Đọc dữ liệu từ Admin.txt
    ifstream fileAdmin("Admin.txt");
    if (fileAdmin.is_open()) {
        while (!fileAdmin.eof()) {
            Admin ad;
            ad.loadFromFile(fileAdmin);
            if (!ad.getId().empty()) { // Kiểm tra xem ID có trống không
                adminMap[ad.getId()] = ad;
            }
        }
        fileAdmin.close();
    } else {
        cout << "Khong the mo file Admin.txt de doc du lieu.\n";
    }
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
    } else if (loai == 3) { // Admin
        if (adminMap.find(id) != adminMap.end()) {
            return &adminMap[id];
        } else {
            cout << "Ma Admin khong ton tai.\n";
        }
    }
    return nullptr;
}

int main() {
    khoiTaoDuLieu();

    int choice;
    while (true) {
        cout << "Chao mung ban den voi phong kham nha khoa, ban la:\n";
        cout << "1. Admin\n";
        cout << "2. User\n";
        cout << "3. Thoat chuong trinh\n";
        cout << "Nhap lua chon: ";
        cin >> choice;
        cin.ignore();

        if (choice == 3) {
            cout << "Thoat chuong trinh...\n";
            break;
        }

        if (choice == 1) {
            User* user = dangNhap(3); // Admin
            if (user != nullptr) {
                cout << "Dang nhap thanh cong!\n";
                user->displayInfo();
                Admin* ad = dynamic_cast<Admin*>(user);
                giaoDienAdmin(ad);
            } else {
                cout << "Dang nhap that bai.\n";
            }
        } else if (choice == 2) {
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
                } else if (choice == 2) {
                    NhanVien* nv = dynamic_cast<NhanVien*>(user);
                    giaoDienNhanVien(nv);
                }
            } else {
                cout << "Dang nhap that bai.\n";
            }
        } else {
            cout << "Lua chon khong hop le. Vui long nhap lai.\n";
        }
    }

    return 0;
}
