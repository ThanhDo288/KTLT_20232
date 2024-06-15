#include "NhanVien.h"
#include <iostream>

using namespace std;

NhanVien::NhanVien() : User() {}

NhanVien::NhanVien(string id, string name) : User(id, name) {}

void NhanVien::displayInfo() const {
    cout << "Nhan Vien ID: " << id << "\n";
    cout << "Ten: " << name << "\n";
}
