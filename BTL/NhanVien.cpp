#include "NhanVien.h"
#include <fstream>
#include <iostream>
#include <regex>

using namespace std;

NhanVien::NhanVien() : User() {}

NhanVien::NhanVien(string id, string name, string ngaySinh, string gioiTinh)
    : User(id, name, ngaySinh, gioiTinh) {}

void NhanVien::displayInfo() const {
    cout << "Nhan Vien ID: " << id << "\n";
    cout << "Ten: " << name << "\n";
    cout << "Ngay sinh: " << ngaySinh << "\n";
    cout << "Gioi tinh: " << gioiTinh << "\n";
}

void NhanVien::loadFromFile(ifstream &file) {
    getline(file, id);
    getline(file, name);
    getline(file, ngaySinh);
    getline(file, gioiTinh);
    // Bỏ qua dòng phân cách
    string separator;
    getline(file, separator);
}


void NhanVien::hienThiCaTruc(const string& rootPath) const {
    string folderPath = rootPath + "/" + id; // Construct folder path using id
    ifstream file(folderPath + "/CaTruc.txt");
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

void NhanVien::hienThiLuong(const string& rootPath) const {
    string filePath = rootPath + "/" + id + "/Luong.txt"; // Đường dẫn tới file lương
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
    string rootPath = "D:/KTLT_20232-thanhdo/BTL/DATABASE/NV";
    string khRootPath = "D:/KTLT_20232-thanhdo/BTL/DATABASE/KH";

    do {
        system("cls");
        cout << "\nXin chao, " << nv->getId() << " - " << nv->getName() << "\n";
        cout << "0. Dang Xuat\n";
        cout << "1. Ca Truc\n";
        cout << "2. Luong\n";
        cout << "3. Thong Tin Ca Nhan\n";
        cout << "4. Them Khach Hang\n";
        cout << "5. Tim Kiem Thong Tin Khach Hang\n";

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
                cout << "Nhan Enter de quay lai menu...";
                cin.ignore();
                cin.get(); // Doi nguoi dung nhan Enter truoc khi tiep tuc
                break;
            case 4:
                giaoDienThemKhachHang(nv, khRootPath);
                break;
            case 5:
                nv->timKiemKhachHang(khRootPath);
                break;
            default:
                cout << "Lua chon khong hop le. Vui long nhap lai.\n";
                break;
        }
    } while (choice != 0);
}

void giaoDienThemKhachHang(NhanVien* nv, const string& rootPath) {
    int choice;
    do {
        system("cls");
        cout << "Vui long nhap thong tin khach hang:\n";
        nv->addKhachHang(rootPath);

        cout << "\n0. Quay Lai Trang Truoc\n";
        cout << "1. Them Khach Hang\n";

        cout << "Nhap lua chon: ";
        cin >> choice;

        switch (choice) {
            case 0:
                cout << "Quay lai trang truoc...\n";
                return; // Thoát khỏi hàm khi người dùng chọn quay lại
            case 1:
                break; // Continue adding customer
            default:
                cout << "Lua chon khong hop le. Vui long thu lai.\n";
                break;
        }
    } while (true); // Vòng lặp vô hạn để người dùng có thể lựa chọn quay lại
}

bool isValidDate(const string& date) {
    regex datePattern(R"(^(0[1-9]|[12][0-9]|3[01])/(0[1-9]|1[0-2])/(19[0-9]{2}|20[0-9]{2})$)");
    smatch match;

    if (regex_match(date, match, datePattern)) {
        int day = stoi(match[1]);
        int month = stoi(match[2]);
        int year = stoi(match[3]);

        // Check for valid days in months
        if ((month == 4 || month == 6 || month == 9 || month == 11) && day > 30) return false;
        if (month == 2) {
            bool isLeap = (year % 4 == 0 && year % 100 != 0) || (year % 400 == 0);
            if (day > 29 || (day == 29 && !isLeap)) return false;
        }
        return true;
    }
    return false;
}

void NhanVien::addKhachHang(const string& rootPath) const {
    string filePath = "KH.txt";
    ifstream file(filePath);
    if (!file.is_open()) {
        cout << "Khong the mo file KH.txt\n";
        return;
    }

    int maxId = 0;
    string line;
    regex idPattern(R"(KH(\d{3}))");
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
    string newId = "KH" + (nextId < 10 ? "00" + to_string(nextId) : (nextId < 100 ? "0" + to_string(nextId) : to_string(nextId)));

    string name, ngaySinh, gioiTinh, benhAn, ngayBatDau;
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
        if (gioiTinh != "Nam" && gioiTinh != "Nu" && gioiTinh != "Khac") {
            cout << "Gioi tinh khong hop le. Vui long nhap lai.\n";
        }
    } while (gioiTinh != "Nam" && gioiTinh != "Nu" && gioiTinh != "Khac");

    cout << "Nhap benh chuan doan: ";
    getline(cin, benhAn);

    do {
        cout << "Nhap ngay bat dau dieu tri (dd/mm/yyyy): ";
        getline(cin, ngayBatDau);
        if (!isValidDate(ngayBatDau)) {
            cout << "Ngay bat dau dieu tri khong hop le. Vui long nhap lai.\n";
        }
    } while (!isValidDate(ngayBatDau));

    ofstream outFile(filePath, ios::app);
    if (!outFile.is_open()) {
        cout << "Khong the mo file KH.txt de ghi\n";
        return;
    }

    outFile << newId << endl;
    outFile << name << endl;
    outFile << ngaySinh << endl;
    outFile << gioiTinh << endl;
    outFile << "Chuan doan benh: " << benhAn << endl;
    outFile << "Ngay bat dau dieu tri: " << ngayBatDau << endl;
    outFile <<  "---------------------------------------------"<<endl;

    cout << "Them khach hang thanh cong voi ma so: " <<newId<< endl;
}

void NhanVien::timKiemKhachHang(const string& rootPath) const {
    system("cls"); // Clear the console for a new page
    string filePath = "KH.txt";
    ifstream file(filePath);
    if (!file.is_open()) {
        cout << "Khong the mo file KH.txt\n";
        return;
    }

    string khId;
    cout << "Nhap ma khach hang (KHxxx): ";
    cin >> khId;

    string line;
    bool found = false;
    while (getline(file, line)) {
        if (line == khId) {
            found = true;
            break;
        }
    }
    file.close();

    if (found) {
        giaoDienThongTinKhachHang(khId, rootPath);
    } else {
        cout << "Khong tim thay khach hang voi ma so: " << khId << "\n";
    }
}

void giaoDienThongTinKhachHang(const string& khId, const string& rootPath) {
    system("cls"); // Clear the console for a new page
    string filePath = "KH.txt";
    ifstream file(filePath);
    if (!file.is_open()) {
        cout << "Khong the mo file KH.txt\n";
        return;
    }

    string line;
    bool found = false;
    while (getline(file, line)) {
        if (line == khId) {
            found = true;
            cout << "Thong tin khach hang ma so: " << khId << "\n";

            string ten, ngaySinh, gioiTinh, benhAn, ngayBatDau;

    getline(file, ten);
    getline(file, ngaySinh);
    getline(file, gioiTinh);
    getline(file, benhAn);
    getline(file, ngayBatDau);

            cout << "Ten: " << ten << "\n";
            cout << "Ngay sinh: " << ngaySinh << "\n";
            cout << "Gioi tinh: " << gioiTinh << "\n";
            cout << "*" << benhAn<<"\n";
            cout << "**" << ngayBatDau << "\n";

            break;

        }
    }
    file.close();

    if (!found) {
        cout << "Khong tim thay thong tin khach hang.\n";
        cout << "Nhan Enter de quay lai menu...";
        cin.ignore();
        cin.get(); // Wait for the user to press Enter
        return;
    }

    NhanVien nv;
    int choice;
    do {
        cout << "\n0. Quay Lai Trang Truoc\n";
        cout << "1. Sua Thong Tin Khach Hang\n";
        cout << "Nhap lua chon: ";
        cin >> choice;

        switch (choice) {
            case 0:
                cout << "Quay lai trang truoc...\n";
                break;
            case 1:
                nv.suaThongTinKhachHang(khId, rootPath);
                break;
            default:
                cout << "Lua chon khong hop le. Vui long nhap lai.\n";
                break;
        }
    } while (choice != 0);

    cout << "Nhan Enter de quay lai menu...";
    cin.ignore();
    cin.get(); // Wait for the user to press Enter
}

void NhanVien::suaThongTinKhachHang(const string& khId, const string& rootPath) const {
    string filePath = "KH.txt";
    ifstream file(filePath);
    if (!file.is_open()) {
        cout << "Khong the mo file KH.txt\n";
        return;
    }

    vector<string> lines;
    string line;
    bool found = false;
    while (getline(file, line)) {
        lines.push_back(line);
        if (line == khId) {
            found = true;
            for (int i = 0; i < 6; ++i) {
                getline(file, line);
                lines.push_back(line);
            }
        }
    }
    file.close();

    if (!found) {
        cout << "Khong tim thay khach hang voi ma so: " << khId << "\n";
        return;
    }

    string newName, newNgaySinh, newGioiTinh;
    cout << "Nhap ten khach hang moi (hoac Enter de giu nguyen): ";
    cin.ignore(); // Ignore any leftover newline characters
    getline(cin, newName);
    if (newName.empty()) {
        newName = lines[1].substr(11); // Keep the current name
    }

    do {
        cout << "Nhap ngay sinh moi (dd/mm/yyyy) (hoac Enter de giu nguyen): ";
        getline(cin, newNgaySinh);
        if (newNgaySinh.empty()) {
            newNgaySinh = lines[2].substr(11); // Keep the current birthdate
        }
        if (!isValidDate(newNgaySinh)) {
            cout << "Ngay sinh khong hop le. Vui long nhap lai.\n";
        }
    } while (!isValidDate(newNgaySinh));

    do {
        cout << "Nhap gioi tinh moi (Nam/Nu/Khac) (hoac Enter de giu nguyen): ";
        getline(cin, newGioiTinh);
        if (newGioiTinh.empty()) {
            newGioiTinh = lines[3].substr(11); // Keep the current gender
        }
        if (newGioiTinh != "Nam" && newGioiTinh != "Nu" && newGioiTinh != "Khac") {
            cout << "Gioi tinh khong hop le. Vui long nhap lai.\n";
        }
    } while (newGioiTinh != "Nam" && newGioiTinh != "Nu" && newGioiTinh != "Khac");

    lines[1] = newName;
    lines[2] = newNgaySinh;
    lines[3] = newGioiTinh;

    ofstream outFile(filePath);
    if (!outFile.is_open()) {
        cout << "Khong the mo file KH.txt de ghi\n";
        return;
    }

    for (const auto& l : lines) {
        outFile << l << "\n";
    }
    outFile.close();

    cout << "Sua thong tin khach hang thanh cong.\n";
}
