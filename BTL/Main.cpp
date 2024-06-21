#include <iostream>
#include <unordered_map>
#include "KhachHang.h"
#include "NhanVien.h"

using namespace std;

unordered_map<string, KhachHang> khachHangMap;
unordered_map<string, NhanVien> nhanVienMap;

void khoiTaoDuLieu() {
    // Đọc dữ liệu từ KH.txt
    ifstream fileKH("KH.txt");
    if (fileKH.is_open()) {
        while (!fileKH.eof()) {
            KhachHang kh;
            kh.loadFromFile(fileKH);
            if (fileKH.fail()) break; // Check for failure
            khachHangMap[kh.getId()] = kh;
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
            if (fileNV.fail()) break; // Check for failure
            nhanVienMap[nv.getId()] = nv;
        }
        fileNV.close();
    } else {
        cout << "Khong the mo file NV.txt de doc du lieu.\n";
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
    }
    return nullptr;
}

// Hàm hiển thị giao diện cho Admin
void giaoDienAdmin() {
    int choice;
    do {
        system("cls"); // Xóa màn hình console để hiển thị giao diện
        cout << "Chao Admin, ban chon:\n";
        cout << "1. Them Khach Hang\n";
        cout << "2. Them Nhan Vien\n";
        cout << "3. Tra cuu Danh Sach Nhan Vien\n";
        cout << "4. Tra cuu Danh Sach Khach Hang\n";
        cout << "5. Tra cuu Doanh Thu\n";
        cout << "0. Dang xuat\n";
        cout << "Nhap lua chon: ";
        cin >> choice;
        cin.ignore();

        switch (choice) {
            case 0:
                cout << "Dang xuat...\n";
                break;
            case 1:
                //themKhachHang();
                break;
            case 2:
                //themNhanVien();
                break;
            case 3:
                //traCuuDoanhThu();
                break;
            default:
                cout << "Lua chon khong hop le. Vui long nhap lai.\n";
                break;
        }

        // Sau mỗi lựa chọn, đợi người dùng nhấn Enter để tiếp tục
        cout << "Nhan Enter de tiep tuc...";
        cin.ignore();
        cin.get();

    } while (choice != 0);
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
            string password;
            cout << "Nhap mat khau he thong: ";
            cin >> password;
            cin.ignore();

            if (password == "DaylaprojectC++") {
                giaoDienAdmin();

            } else {
                cout << "Sai mat khau he thong.\n";
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
