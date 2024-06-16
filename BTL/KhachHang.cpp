#include "KhachHang.h"
#include <iostream>
#include <windows.h>  // Thêm thư viện này

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

void KhachHang::datLichThamKham(const string& lich, const string& rootPath) {
    lichThamKham.push_back(lich);
    cout << "Lich tham kham da duoc dat: " << lich << "\n";

    // Tạo đường dẫn đầy đủ
    string folderPath = rootPath + "\\" + id;

    // Tạo file LichKham.txt trong thư mục đó
    ofstream file(folderPath + "\\LichKham.txt", ios::app);
    if (file.is_open()) {
        file << lich << "\n";
        file.close();
        //cout << "Da luu lich tham kham vao file: " << folderPath + "\\LichKham.txt\n";
    } else {
        cout << "Khong the tao file LichKham.txt\n";
    }
}

void giaoDienDatLich(KhachHang* kh, const string& rootPath) {
    int choice;
    string lich;
    do {
        system("cls");
        cout << "1. Xac Nhan Thoi Gian\n";
        cout << "2. Quay Lai Trang Truoc\n";
        cout << "Nhap lua chon: ";
        cin >> choice;
        cin.ignore();

        switch (choice) {
            case 1:
                cout << "Nhap thoi gian tham kham (VD: 10:00 12/12/2023): ";
                getline(cin, lich);
                kh->datLichThamKham(lich, rootPath);
                break;
            case 2:
                cout << "Quay lai trang truoc...\n";
                break;
            default:
                cout << "Lua chon khong hop le. Vui long thu lai.\n";
        }
        system("pause");
    } while (choice != 2);
}
void giaoDienXemLich(KhachHang* kh, const string& rootPath) {
    system("cls");
    cout << "Lich Tham Kham:\n";

    // Tạo đường dẫn đầy đủ
    string folderPath = rootPath + "\\" + kh->getId();

    // Mở file LichKham.txt để đọc nội dung
    ifstream file(folderPath + "\\LichKham.txt");
    if (file.is_open()) {
        string line;
        while (getline(file, line)) {
            cout << line << "\n";
        }
        file.close();
    } else {
        cout << "Khong the mo file LichKham.txt\n";
    }
    system("pause");
}

void giaoDienLichThamKham(KhachHang* kh, const string& rootPath) {
    int choice;

    do {
        system("cls");
        cout << "1. Dat Lich Tham Kham\n";
        cout << "2. Xem Lich Tham Kham\n";
        cout << "3. Quay Lai Trang Truoc\n";
        cout << "Nhap lua chon: ";
        cin >> choice;
        cin.ignore();

        switch (choice) {
            case 1:
                giaoDienDatLich(kh, rootPath);
                break;
            case 2:
                giaoDienXemLich(kh, rootPath);;
                break;
            case 3:
                cout << "Quay lai trang truoc...\n";
                break;
            default:
                cout << "Lua chon khong hop le. Vui long thu lai.\n";
        }
        //system("pause");
    } while (choice != 3);
}
void giaoDienKhachHang(KhachHang* kh) {
    int choice;
    do {
        system("cls"); // Clear screen for Windows
        cout << "\nXin chao, " << kh->getId() << " - " << kh->getName() << "\n";
        cout << "1. Lich Tham Kham\n";
        cout << "2. Benh An\n";
        cout << "3. Thong Tin Ca Nhan\n";
        cout << "4. Dang Xuat\n";
        cout << "Nhap lua chon: ";
        cin >> choice;
        string rootPath = "D:\\choi c++\\BTL20232\\KTLT_20232\\BTL\\DATABASE\\KH";

        switch (choice) {
            case 1:
                giaoDienLichThamKham(kh, rootPath);
                break;
            case 2:
                kh->hienThiBenhAn();
                break;
            case 3:
                kh->hienThiThongTinCaNhan();
                break;
            case 4:
                cout << "Dang xuat...\n";
                system("cls");
                break;
            default:
                cout << "Lua chon khong hop le. Vui long thu lai.\n";
        }
        system("pause"); // Pause for Windows
    } while (choice != 4);
}
