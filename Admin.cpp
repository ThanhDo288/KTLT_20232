#include <iostream>
#include <unordered_map>
#include "KhachHang.h"
#include "NhanVien.h"
#include "Admin.h"
#include <direct.h> // Thêm dòng này cho Windows
#include <dirent.h> // Thư viện POSIX cho việc duyệt thư mục
#include <sys/stat.h>
#include <sys/types.h>
using namespace std;

Admin::Admin() : User() {}

Admin::Admin(string id, string name, string ngaySinh, string gioiTinh)
    : User(id, name, ngaySinh, gioiTinh) {}

void Admin::displayInfo() const {
    cout << "Admin ID: " << id << "\n";
    cout << "Ten: " << name << "\n";
    cout << "Ngay sinh: " << ngaySinh << "\n";
    cout << "Gioi tinh: " << gioiTinh << "\n";
}

void Admin::loadFromFile(ifstream &file) {
    getline(file, id);
    getline(file, name);
    getline(file, ngaySinh);
    getline(file, gioiTinh);
    // Bỏ qua dòng phân cách
    string separator;
    getline(file, separator);
}

bool Admin::isValidDate(const string& date) const {
    regex datePattern(R"((0[1-9]|[12][0-9]|3[01])/(0[1-9]|1[0-2])/\d{4})");
    return regex_match(date, datePattern);
}

bool Admin::isValidGender(const string& gender) const {
    return (gender == "Nam" || gender == "Nu" || gender == "Khac");
}


string Admin::getNextId(const string& filePath, const string& prefix) const {
    ifstream file(filePath);
    int maxId = 0;
    string line;
    regex idPattern(prefix + R"((\d{3}))");
    smatch match;

    while (getline(file, line)) {
        if (regex_search(line, match, idPattern)) {
            int currentId = stoi(match[1].str());
            if (currentId > maxId) {
                maxId = currentId;
            }
        }
    }
    file.close();

    int nextId = maxId + 1;
    return prefix + (nextId < 10 ? "00" + to_string(nextId) : (nextId < 100 ? "0" + to_string(nextId) : to_string(nextId)));
}

bool Admin::hasReachedMaxEmployees(const string& filePath) const {
    ifstream file(filePath);
    int count = 0;
    string line;
    while (getline(file, line)) {
        if (line.find("NV") == 0) {
            count++;
        }
    }
    return count >= 7;
}

void Admin::addKhachHang() {
    string filePath = "D:/HUST/2023.2/KTLT_ET2031/BTL_CHOT/KH.txt";
    string newId = getNextId(filePath, "KH");

    string name, ngaySinh, gioiTinh;
    cout << "Nhap ten khach hang: ";
    cin.ignore();
    getline(cin, name);

    do {
        cout << "Nhap ngay sinh (dd/mm/yyyy): ";
        getline(cin, ngaySinh);
        if (!isValidDate(ngaySinh)) {
            cout << "Ngay sinh khong hop le. Vui long nhap lai.\n";
        }
    } while (!isValidDate(ngaySinh));

    do {
        cout << "Nhap gioi tinh (Nam/Nu/Khac): ";
        getline(cin, gioiTinh);
        if (!isValidGender(gioiTinh)) {
            cout << "Gioi tinh khong hop le. Vui long nhap lai.\n";
        }
    } while (!isValidGender(gioiTinh));

    ofstream outFile(filePath, ios::app);
    if (!outFile.is_open()) {
        cout << "Khong the mo file KH.txt de ghi\n";
        return;
    }

    outFile << newId << endl;
    outFile << name << endl;
    outFile << ngaySinh << endl;
    outFile << gioiTinh << endl;
    outFile << "---------------------------------------------" << endl;

    string folderPath = "D:/HUST/2023.2/KTLT_ET2031/BTL_CHOT/DATABASE/KH/" + newId;
    _mkdir(folderPath.c_str());

    ofstream benhAnFile(folderPath + "/BenhAn.txt");
    ofstream lichKhamFile(folderPath + "/LichKham.txt");

    if (!benhAnFile.is_open() || !lichKhamFile.is_open()) {
        cout << "Khong the tao cac file BenhAn.txt va LichKham.txt\n";
        return;
    }

    cout << "Them khach hang thanh cong voi ma so: " << newId << endl;
}

void Admin::addNhanVien() {
    string filePath = "D:/HUST/2023.2/KTLT_ET2031/BTL_CHOT/NV.txt";

    // Kiểm tra số lượng nhân viên hiện tại
    if (hasReachedMaxEmployees(filePath)) {
        cout << "Da them toi da 7 nhan vien. Khong the them nhan vien moi.\n";
        return;
    }

    string newId = getNextId(filePath, "NV");

    string name, ngaySinh, gioiTinh;
    cout << "Nhap ten nhan vien: ";
    cin.ignore();
    getline(cin, name);

    do {
        cout << "Nhap ngay sinh (dd/mm/yyyy): ";
        getline(cin, ngaySinh);
        if (!isValidDate(ngaySinh)) {
            cout << "Ngay sinh khong hop le. Vui long nhap lai.\n";
        }
    } while (!isValidDate(ngaySinh));

    do {
        cout << "Nhap gioi tinh (Nam/Nu/Khac): ";
        getline(cin, gioiTinh);
        if (!isValidGender(gioiTinh)) {
            cout << "Gioi tinh khong hop le. Vui long nhap lai.\n";
        }
    } while (!isValidGender(gioiTinh));

    ofstream outFile(filePath, ios::app);
    if (!outFile.is_open()) {
        cout << "Khong the mo file NhanVien.txt de ghi\n";
        return;
    }

    outFile << newId << endl;
    outFile << name << endl;
    outFile << ngaySinh << endl;
    outFile << gioiTinh << endl;
    outFile << "---------------------------------------------" << endl;

    string folderPath = "D:/HUST/2023.2/KTLT_ET2031/BTL_CHOT/DATABASE/NV/" + newId;
    _mkdir(folderPath.c_str());

    ofstream luongFile(folderPath + "/Luong.txt");
    ofstream ngayTrucFile(folderPath + "/NgayTruc.txt");

    if (!luongFile.is_open() || !ngayTrucFile.is_open()) {
        cout << "Khong the tao cac file Luong.txt va NgayTruc.txt\n";
        return;
    }

    cout << "Them nhan vien thanh cong voi ma so: " << newId << endl;
}

void Admin::addLuong() {
    string nvId;
    cout << "Nhap ma nhan vien (NVxxx): ";
    cin >> nvId;

    string rootPath = "D:/HUST/2023.2/KTLT_ET2031/BTL_CHOT/DATABASE/NV/" + nvId;
    string filePath = rootPath + "/Luong.txt";

    double salary;
    cout << "Nhap luong: ";
    cin >> salary;

    ofstream file(filePath, ios::app);
    if (file.is_open()) {
        file << "Luong: " << fixed << setprecision(2) << salary << "\n";
        file.close();
        cout << "Da luu luong vao file: " << filePath << "\n";
    } else {
        cout << "Khong the tao file Luong.txt\n";
    }
}

void Admin::addNgayTruc() {
    string nvId;
    cout << "Nhap ma nhan vien (NVxxx): ";
    cin >> nvId;

    string day;
    cout << "Nhap ngay truc (thu2, thu3, thu4, thu5, thu6, thu7, chuNhat): ";
    cin >> day;

    string rootPath = "D:/HUST/2023.2/KTLT_ET2031/BTL_CHOT/DATABASE/NV/" + nvId;
    string filePath = rootPath + "/NgayTruc.txt";

    ofstream file(filePath, ios::app);
    if (file.is_open()) {
        file << "Ngay truc: " << day << "\n";
        file.close();
        cout << "Da luu ngay truc vao file: " << filePath << "\n";
    } else {
        cout << "Khong the tao file NgayTruc.txt\n";
    }
}

void Admin::addBenhAn() {
    string khId;
    cout << "Nhap ma khach hang (KHxxx): ";
    cin >> khId;

    string rootPath = "D:/HUST/2023.2/KTLT_ET2031/BTL_CHOT/DATABASE/KH" + khId;
    string filePath = rootPath + "/BenhAn.txt";

    string benhAn;
    cout << "Nhap benh an: ";
    cin.ignore();
    getline(cin, benhAn);

    ofstream file(filePath, ios::app);
    if (file.is_open()) {
        file << "Benh an: " << benhAn << "\n";
        file.close();
        cout << "Da luu benh an vao file: " << filePath << "\n";
    } else {
        cout << "Khong the tao file BenhAn.txt\n";
    }
}

void Admin::searchNhanVien() const {
    cout << "Danh sach nhan vien:\n";
    ifstream file("D:/HUST/2023.2/KTLT_ET2031/BTL_CHOT/NV.txt");
    if (file.is_open()) {
        string line;
        while (getline(file, line)) {
            cout << line << "\n";
        }
        file.close();
    } else {
        cout << "Khong the mo file NV.txt\n";
    }
}

void Admin::searchKhachHang() const {
    cout << "Danh sach khach hang:\n";
    ifstream file("D:/HUST/2023.2/KTLT_ET2031/BTL_CHOT/KH.txt");
    if (file.is_open()) {
        string line;
        while (getline(file, line)) {
            cout << line << "\n";
        }
        file.close();
    } else {
        cout << "Khong the mo file KH.txt\n";
    }
}

void Admin::thongKeNhanh() {
    // Đếm số lượng nhân viên
    ifstream nvFile("NV.txt");
    if (!nvFile.is_open()) {
        cout << "Khong the mo file NV.txt\n";
        return;
    }
    
    int nvCount = 0;
    string line;
    while (getline(nvFile, line)) {
        if (!line.empty() && line.find("NV") == 0) {
            nvCount++;
        }
    }
    nvFile.close();
    
    // Đếm số lượng khách hàng
    ifstream khFile("KH.txt");
    if (!khFile.is_open()) {
        cout << "Khong the mo file KH.txt\n";
        return;
    }
    
    int khCount = 0;
    while (getline(khFile, line)) {
        if (!line.empty() && line.find("KH") == 0) {
            khCount++;
        }
    }
    khFile.close();
    
    // Hiển thị kết quả thống kê
    cout << "So luong nhan vien: " << nvCount << endl;
    cout << "So luong khach hang: " << khCount << endl;
}

void giaoDienAdmin(Admin* ad ) {
    int choice;

    do {
        system("cls"); // Xóa màn hình console để hiển thị giao diện
        cout << "Chao Admin, ban chon:\n";
        cout << "1. Them Khach Hang\n";
        cout << "2. Them Nhan Vien\n";
        cout << "3. Tra cuu Danh Sach Nhan Vien\n";
        cout << "4. Tra cuu Danh Sach Khach Hang\n";
        cout << "5. Them Luong\n";
        cout << "6. Them Ngay Truc\n";
        cout << "7. Thong ke nhanh\n";
        cout << "0. Dang xuat\n";
        cout << "Nhap lua chon: ";
        cin >> choice;
        cin.ignore();

        switch (choice) {
            case 0:
                cout << "Dang xuat...\n";
                break;
            case 1:
                ad->addKhachHang();
                break;
            case 2:
                ad->addNhanVien();
                break;
            case 3:
                ad->searchNhanVien();
                break;
            case 4:
                ad->searchKhachHang();
                break;
            case 5:
                ad->addLuong();
                break;
            case 6:
                ad->addNgayTruc();
                break;
            case 7:
                ad->thongKeNhanh();
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
