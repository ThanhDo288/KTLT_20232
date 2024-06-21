#include "NhanVien.h"
#include <iostream>

using namespace std;

NhanVien::NhanVien() : User() {}

NhanVien::NhanVien(string id, string name) : User(id, name) {}

void NhanVien::displayInfo() const {
    cout << "Nhan Vien ID: " << id << "\n";
    cout << "Ten: " << name << "\n";
}

void NhanVien::loadFromFile(ifstream &file) {
    getline(file, id);
    getline(file, name);
}

void NhanVien::hienThiCaTruc(const std::string& rootPath) const {
    string folderPath = rootPath + "\\" + id; // Construct folder path using id
    ifstream file(folderPath + "\\CaTruc.txt");
    if (!file.is_open()) {
        cout << "Khong the mo file CaTruc.txt\n";
        return;
    }

    string line;

    while (getline(file, line)) {
        cout << line << "\n";
    }

    file.close();
}

void giaoDienXemCaTruc(NhanVien* nv, const string& rootPath) {
    int choice;
    do {
        system("cls");
        cout << "CaTruc:\n";
        nv->hienThiCaTruc(rootPath); // Display the schedule

        cout << "\n0. Quay Lai Trang Truoc\n";
        cout << "1. Dang Xuat\n";

        cout << "Nhap lua chon: ";
        cin >> choice;

        switch (choice) {
            case 0:
                cout << "Quay lai trang truoc...\n";
                break;
            case 1:
                cout << "Dang xuat...\n";
                break;
            default:
                cout << "Lua chon khong hop le. Vui long thu lai.\n";
        }
    } while (choice != 0 && choice != 1); // Continue looping until user chooses to go back or logout
}

void NhanVien::hienThiLuong(const std::string& rootPath) const {
    string filePath = rootPath + "\\" + id + "\\Luong.txt"; // Đường dẫn tới file lương
    ifstream file(filePath);
    if (!file.is_open()) {
        cout << "Khong the mo file Luong.txt\n";
        return;
    }

    int luong;
    file >> luong;
    cout << "Luong: " << luong << " VND\n";

    file.close();
}

void giaoDienLuong(NhanVien* nv, const string& rootPath) {
    int choice;
    do {
        system("cls");
        nv->hienThiLuong(rootPath); // Hiển thị thông tin lương của nhân viên

        cout << "\n0. Quay Lai Trang Truoc\n";
        cout << "Nhap lua chon: ";
        cin >> choice;

        switch (choice) {
            case 0:
                cout << "Quay lai trang truoc...\n";
                return; // Thoát khỏi hàm khi người dùng chọn quay lại
            default:
                cout << "Lua chon khong hop le. Vui long thu lai.\n";
                break;
        }
    } while (true); // Vòng lặp vô hạn để người dùng có thể lựa chọn quay lại
}

void giaoDienNhanVien(NhanVien* nv) {
    int choice;
    bool displayInfoShown = false; // Biến để kiểm tra xem thông tin cá nhân đã được hiển thị chưa
    string rootPath = "D:\\KTLT_20232-thanhdo\\BTL\\DATABASE\\NV";

    do {
        system("cls");
        cout << "\nXin chao, " << nv->getId() << " - " << nv->getName() << "\n";
        cout << "0. Dang Xuat\n";
        cout << "1. CaTruc\n";
        cout << "2. Luong\n";
        cout << "3. Thong Tin Ca Nhan\n";



        cout << "Nhap lua chon: ";
        cin >> choice;

        switch (choice) {
            case 0:
                cout << "Dang xuat...\n";
                break;
            case 1:
                giaoDienXemCaTruc(nv, rootPath);
                break;
            case 2:
                giaoDienLuong(nv, rootPath);
                break;
            case 3:
                nv->displayInfo();
                displayInfoShown = true; // Đánh dấu rằng đã hiển thị thông tin cá nhân
                cout << "Nhan Enter de quay lai menu...";
                cin.ignore();
                cin.get(); // Đợi người dùng nhấn Enter trước khi tiếp tục
                break;
            default:
                cout << "Lua chon khong hop le. Vui long nhap lai.\n";
                break;
        }
    } while (choice != 0);
}
