#include "Admin.h"

using namespace std;

bool Admin::isValidDate(const string& date) const {
    regex datePattern(R"((0[1-9]|[12][0-9]|3[01])/(0[1-9]|1[0-2])/\d{4})");
    return regex_match(date, datePattern);
}

bool Admin::isValidGender(const string& gender) const {
    return (gender == "Nam" || gender == "Nu" || gender == "Khac");
}

bool Admin::isDayAvailable(const string& day, const string& nvId) const {
    ifstream file("NhanVien.txt");
    string line;
    while (getline(file, line)) {
        if (line == nvId) {
            for (int i = 0; i < 6; ++i) getline(file, line); // Skip other details
            string existingDay;
            getline(file, existingDay);
            if (existingDay == day) {
                return false;
            }
        }
    }
    return true;
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

void Admin::addNhanVien() {
    string filePath = "D:/HUST/2023.2/KTLT_ET2031/BTL_CHOT/NV.txt";
    // Kiểm tra số lượng nhân viên hiện tại
    if (hasReachedMaxEmployees(filePath)) {
        cout << "Da them toi da 7 nhan vien. Khong the them nhan vien moi.\n";
        return;
    }
    
    string filePath = "NV.txt";
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

    cout << "Them nhan vien thanh cong voi ma so: " << newId << endl;
}

void Admin::addLuong() {
    string nvId;
    cout << "Nhap ma nhan vien (NVxxx): ";
    cin >> nvId;
    
    string rootPath = "D:/HUST/2023.2/KTLT_ET2031/BTL_CHOT/DATABASE/NV" + nvId;
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
    do {
        cout << "Nhap ngay truc (thu2, thu3, thu4, thu5, thu6, thu7, chuNhat): ";
        cin >> day;
        if (!isDayAvailable(day, nvId)) {
            cout << "Ngay truc da co nhan vien. Vui long chon ngay khac.\n";
        }
    } while (!isDayAvailable(day, nvId));

    string rootPath = "D:/HUST/2023.2/KTLT_ET2031/BTL_CHOT/DATABASE/NV" + nvId;
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
    string filePath = rootPath + "\\BenhAn.txt";

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
