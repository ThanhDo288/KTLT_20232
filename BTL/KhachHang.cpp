#include "KhachHang.h"
#include <iostream>
#include <vector>
#include <fstream>

using namespace std;

KhachHang::KhachHang() : User() {}

KhachHang::KhachHang(string id, string name, string ngaySinh, string gioiTinh, string benhAn, string ngayBatDau)
    : User(id, name, ngaySinh, gioiTinh) {}

void KhachHang::displayInfo() const {
    cout << "Khach Hang ID: " << id << "\n";
    cout << "Ten: " << name << "\n";
    cout << "Ngay sinh: " << ngaySinh << "\n";
    cout << "Gioi tinh: " << gioiTinh << "\n";
}

void KhachHang::loadFromFile(ifstream &file) {
    getline(file, id);
    getline(file, name);
    getline(file, ngaySinh);
    getline(file, gioiTinh);
    getline(file, benhAn);
    getline(file, ngayBatDau);
    // Bỏ qua dòng phân cách
    string separator;
    getline(file, separator);
}


void KhachHang::addLichThamKham(const string& lich) {
    lichThamKham.push_back(lich);
}


void KhachHang::hienThiLichThamKham() const {
    cout << "Lich Tham Kham:\n";
    for (const string& lich : lichThamKham) {
        cout << "- " << lich << "\n";
    }
}

void KhachHang::hienThiBenhAn() const {
    cout << "Benh An:\n";
    cout <<"\n";
    cout << benhAn << "\n";
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

void KhachHang::xoaLichThamKham(const string& rootPath) {
    system("cls");
    cout << "Lich Tham Kham:\n";
    string folderPath = rootPath + "\\" + id;
    ifstream file(folderPath + "\\LichKham.txt");
    if (file.is_open()) {
        string line;
        vector<string> lichList;
        int index = 1;
        while (getline(file, line)) {
            lichList.push_back(line);
            cout << index++ << ". " << line << "\n";
        }
        file.close();

        int choice;
        cout << "Chon lich muon xoa (nhap so)(0. Quay Lai) : ";
        cin >> choice;
        if (choice > 0 && choice <= lichList.size()) {
            lichList.erase(lichList.begin() + choice - 1);
            ofstream outFile(folderPath + "\\LichKham.txt");
            for (const auto& lich : lichList) {
                outFile << lich << "\n";
            }
            outFile.close();
            cout << "Xoa lich tham kham thanh cong.\n";
        } else {
            cout << "Lua chon khong hop le.\n";
        }
    } else {
        cout << "Khong the mo file LichKham.txt\n";
    }
    system("pause");
}

void KhachHang::chinhSuaLichThamKham(const string& rootPath) {
    system("cls");
    cout << "Lich Tham Kham:\n";
    string folderPath = rootPath + "\\" + id;
    ifstream file(folderPath + "\\LichKham.txt");
    if (file.is_open()) {
        string line;
        vector<string> lichList;
        int index = 1;
        while (getline(file, line)) {
            lichList.push_back(line);
            cout << index++ << ". " << line << "\n";
        }
        file.close();

        int choice;
        cout << "Chon lich muon chinh sua (nhap so)(0. Quay Lai): ";
        cin >> choice;
        if (choice > 0 && choice <= lichList.size()) {
            cout << "Nhap thoi gian moi cho lich tham kham: ";
            string newLich;
            cin.ignore();
            getline(cin, newLich);
            lichList[choice - 1] = newLich;
            ofstream outFile(folderPath + "\\LichKham.txt");
            for (const auto& lich : lichList) {
                outFile << lich << "\n";
            }
            outFile.close();
            cout << "Chinh sua lich tham kham thanh cong.\n";
        } else {
            cout << "Lua chon khong hop le.\n";
        }
    } else {
        cout << "Khong the mo file LichKham.txt\n";
    }
    system("pause");
}

void KhachHang::timKiemLichThamKham(const string& rootPath) {
    system("cls");
    cout << "Nhap thoi gian can tim kiem (VD: 10:00 12/12/2023): ";
    string keyword;
    cin.ignore();
    getline(cin, keyword);

    string folderPath = rootPath + "\\" + id;
    ifstream file(folderPath + "\\LichKham.txt");
    if (file.is_open()) {
        string line;
        cout << "Ket qua tim kiem:\n";
        while (getline(file, line)) {
            if (line.find(keyword) != string::npos) {
                cout << line << "\n";
            }
        }
        file.close();
    } else {
        cout << "Khong the mo file LichKham.txt\n";
    }
    system("pause");
}

void giaoDienDatLichThamKham(KhachHang* kh, const string& rootPath) {
    int choice;
    string lich;
    do {
        system("cls");
        cout << "0. Quay Lai Trang Truoc\n";
        cout << "1. Xac Nhan Thoi Gian\n";

        cout << "Nhap lua chon: ";
        cin >> choice;
        cin.ignore();

        switch (choice) {
            case 1:
                cout << "Nhap thoi gian tham kham (VD: 10:00 12/12/2023): ";
                getline(cin, lich);
                kh->datLichThamKham(lich, rootPath);
                break;
            case 0:
                cout << "Quay lai trang truoc...\n";
                break;
            default:
                cout << "Lua chon khong hop le. Vui long thu lai.\n";
        }
        system("pause");
    } while (choice != 2);
}

void giaoDienXemLichThamKham(KhachHang* kh, const string& rootPath) {
    int choice;
    do {
        system("cls");
        cout << "Lich Tham Kham:\n";
        string folderPath = rootPath + "\\" + kh->getId();
        ifstream file(folderPath + "\\LichKham.txt");
        vector<string> lichThamKhamList;
        if (file.is_open()) {
            string line;
            int index = 1;
            while (getline(file, line)) {
                lichThamKhamList.push_back(line);
                cout << index << ". " << line << "\n";
                index++;
            }
            file.close();
        } else {
            cout << "Khong the mo file LichKham.txt\n";
        }

        cout << "Chon lua chon:\n";
        cout << "0. Quay lai\n";
        cout << "1. Xoa lich tham kham\n";
        cout << "2. Chinh sua lich tham kham\n";
        cout << "3. Tim kiem lich tham kham\n";
        cout << "Nhap lua chon: ";
        cin >> choice;

        switch (choice) {
            case 0:
                return;
            case 1:
                kh->xoaLichThamKham(rootPath);
                break;
            case 2:
                kh->chinhSuaLichThamKham(rootPath);
                break;
            case 3:
                kh->timKiemLichThamKham(rootPath);
                break;
            default:
                cout << "Lua chon khong hop le. Vui long thu lai.\n";
        }
        system("pause");
    } while (choice != 0);
}

void giaoDienLichThamKham(KhachHang* kh, const string& rootPath) {
    int choice;
    do {
        system("cls");
        cout << "0. Quay Lai Trang Truoc\n";
        cout << "1. Dat Lich Tham Kham\n";
        cout << "2. Xem Lich Tham Kham\n";

        cout << "Nhap lua chon: ";
        cin >> choice;

        switch (choice) {
            case 1:
                giaoDienDatLichThamKham(kh, rootPath);
                break;
            case 2:
                giaoDienXemLichThamKham(kh, rootPath);
                break;
            case 0:
                cout << "Quay lai trang truoc...\n";
                break;
            default:
                cout << "Lua chon khong hop le. Vui long thu lai.\n";
        }
    } while (choice != 3);
}

void giaoDienKhachHang(KhachHang* kh) {
    int choice;
     string rootPath = "D:\\choi c++\\BTL20232\\KTLT_20232\\BTL\\DATABASE\\KH";
    do {
        system("cls");
        cout << "\nXin chao, " << kh->getId() << " - " << kh->getName() << "\n";
        cout << "0. Dang Xuat\n";
        cout << "1. Lich Tham Kham\n";
        cout << "2. Benh An\n";
        cout << "3. Thong Tin Ca Nhan\n";

        cout << "Nhap lua chon: ";
        cin >> choice;

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
            case 0:
                cout << "Dang xuat...\n";
                system("cls");
                break;
            default:
                cout << "Lua chon khong hop le. Vui long thu lai.\n";
        }
        system("pause");
    } while (choice != 4);
}


