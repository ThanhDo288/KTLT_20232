#include "KhachHang.h"
#include <iostream>

using namespace std;

KhachHang::KhachHang() : User() {}

KhachHang::KhachHang(string id, string name) : User(id, name) {}

void KhachHang::displayInfo() const {
    cout << "Khach Hang ID: " << id << "\n";
    cout << "Ten: " << name << "\n";
}

void KhachHang::loadFromFile(ifstream &file) {
    getline(file, id);
    getline(file, name);
}

void KhachHang::addLichThamKham(const string& lich) {
    lichThamKham.push_back(lich);
}

void KhachHang::addBenhAn(const string& benh) {
    benhAn.push_back(benh);
}

void KhachHang::hienThiLichThamKham() const {
    cout << "Lich Tham Kham:\n";
    for (const string& lich : lichThamKham) {
        cout << "- " << lich << "\n";
    }
}

void KhachHang::hienThiBenhAn() const {
    cout << "Benh An:\n";
    for (const string& benh : benhAn) {
        cout << "- " << benh << "\n";
    }
}

void KhachHang::hienThiThongTinCaNhan() const {
    displayInfo();
}

void giaoDienKhachHang(KhachHang* kh) {
    int choice;
    do {
        system("cls"); // Clear screen for Windows
        cout << "\nXin chao, " << kh->getId() << " - " << kh->getId() << "\n";
        cout << "1. Lich Tham Kham\n";
        cout << "2. Benh An\n";
        cout << "3. Thong Tin Ca Nhan\n";
        cout << "4. Thoat\n";
        cout << "Nhap lua chon: ";
        cin >> choice;

        switch (choice) {
            case 1:
                kh->hienThiLichThamKham();
                break;
            case 2:
                kh->hienThiBenhAn();
                break;
            case 3:
                kh->hienThiThongTinCaNhan();
                break;
            case 4:
                cout << "Dang xuat...\n";
                break;
            default:
                cout << "Lua chon khong hop le. Vui long thu lai.\n";
        }
        system("pause"); // Pause for Windows
    } while (choice != 4);
}
