#ifndef HOPDONG_H
#define HOPDONG_H
#include <stdlib.h>
#include <stdio.h>
#include <iostream>
#include <QString>
#include <QTimer.h>
#include <fstream>
#include <QVector>
#include <QChar>
using namespace std;
// CLass:
class Hopdong;
class Hd_ngay;
class Hd_thang;
class Xe;

// File manipulate:
void txt_extract(string &destination, const string spare, const string filename);
void readHd(vector<Hopdong*> v, int mode);

// Vector manipulate:
void searchHd( vector<Hopdong*> v, string s, vector<int> &rank, int mode);

// String manipulate:
void encryptstr(string &s);
void decryptstr(string &s);
void lowerstr(string &s);
void upperstr(string &s);
void deletesubstr(string &mainstr, const string &substr);

// Date maipulate
unsigned int diffdays (struct tm start, struct tm end);
unsigned int diffmonths (struct tm start, struct tm end);

class Hopdong {
    protected:
    string hoten, cmt;
    public:
    string loaixe, bienso;
    struct tm start_time, end_time;
    Hopdong() {}
    Hopdong(istream &source) {}
    ~Hopdong() {
        delete this;
    }
    virtual unsigned int gia_thue() = 0;
    virtual void savetofile() = 0;
    virtual void getdata() = 0;
    virtual void show() = 0;
    friend void searchHd( vector<Hopdong*> v, string s, vector<int> &rank, int mode);
    friend void readHd(vector<Hopdong*> v, int mode);
    QChar gethoten() {
        return hoten;
    }
    QChar sethoten() {
        return hoten;
    }
    QChar getcmt() {
        return cmt;
    }
    QChar getxe() {
        return loaixe;
    }
    int getngaythue() {
        return start_time.tm_mday;
    }
    int getthangthue() {
        return start_time.tm_mon;
    }
    int getnamthue() {
        return start_time.tm_year;
    }
    int getngaytra() {
        return end_time.tm_mday;
    }
    int getthangtra() {
        return end_time.tm_mon;
    }
    int getnamtra() {
        return end_time.tm_year;
    }
    void getcmt(QChar cmt) {
        this->cmt = cmt;
    }
    void getxe(QChar xe) {
        this->loaixe = xe;
    }
    void setngaythue(int day) {
    this->start_time.tm_mday = day;
    }
    void setthangthue(int day) {
    this->start_time.tm_mon = day;
    }
    void setnamthue(int day) {
    this->start_time.tm_year = day;
    }
    void setngaytra(int day) {
    this->end_time.tm_mday = day;
    }
    void setthangtra(int day) {
    this->end_time.tm_mon = day;
    }
    void setnamtra(int day) {
    this->end_time.tm_year = day;
    }

};

class Hd_ngay: public Hopdong {
    public:
    Hd_ngay() {}
    Hd_ngay(istream &source) {
        getline(source, this->hoten);
        getline(source, this->cmt);
        getline(source, this->loaixe);
        getline(source, this->bienso);
        getline(source, (string&)this->start_time.tm_mday);
        getline(source, (string&)this->start_time.tm_mon);
        getline(source, (string&)this->start_time.tm_year);
        getline(source, (string&)this->end_time.tm_mday);
        getline(source, (string&)this->end_time.tm_mon);
        getline(source, (string&)this->end_time.tm_year);
    }
    virtual void savetofile() {
        encryptstr(this->hoten);
        encryptstr(this->cmt);
        ofstream file;
        file.open("hdngay.txt", ios::app);
        file << this->hoten << "\n";
        file << this->cmt << "\n";
        file << this->loaixe << "\n";
        file << this->bienso << "\n";
        file << this->start_time.tm_mday << "\n";
        file << this->start_time.tm_mon << "\n";
        file << this->start_time.tm_year << "\n";
        file << this->end_time.tm_mday << "\n";
        file << this->end_time.tm_mon << "\n";
        file << this->end_time.tm_year << "\n";
        file.close();
    }
    virtual void getdata() {
        fflush(stdin);
        cout << "Nhap ho ten nguoi thue: "; getline(cin, hoten);
        encryptstr(hoten);
        cout << "Nhap so CMT nguoi thue: "; getline(cin, cmt);
        encryptstr(cmt);
        cout << "Nhap loai xe: "; getline(cin, loaixe);
        deletesubstr(loaixe, " ");
        lowerstr(loaixe);
        txt_extract(bienso, loaixe, "xe.txt");
        cout << "Bat dau thue tu:\n" ;
        cout << "ngay: "; cin >> start_time.tm_mday;
        cout << "thang: "; cin >> start_time.tm_mon;
        cout << "nam: "; cin >> start_time.tm_year;
        cout << "den\n" ;
        cout << "ngay: "; cin >> end_time.tm_mday;
        cout << "thang: "; cin >> end_time.tm_mon;
        cout << "nam: "; cin >> end_time.tm_year;
    }
    virtual unsigned int gia_thue() {
        unsigned int price;
        price = diffdays(start_time, end_time) * 150000;
        return price;
    }
    virtual void show() {
        cout << "Ho ten nguoi thue: " << this->hoten << "\n";
        cout << "So CMT nguoi thue: " << this->cmt << "\n";
        cout << "Loai xe: " << this->loaixe << "\n";
        cout << "Bat dau thue tu:\n" ;
        cout << "ngay: " << this->start_time.tm_mday << "\n";
        cout << "thang: " << this->start_time.tm_mon << "\n";
        cout << "nam: " << this->start_time.tm_year << "\n";
        cout << "den\n" ;
        cout << "ngay: " << this->end_time.tm_mday << "\n";
        cout << "thang: " << this->end_time.tm_mon << "\n";
        cout << "nam: " << this->end_time.tm_year;
    }
};

class Hd_thang: public Hopdong {
    public:
    Hd_thang() {
            fflush(stdin);
            cout << "Nhap ho ten nguoi thue: "; getline(cin, hoten);
            cout << "Nhap so CMT nguoi thue: "; getline(cin, cmt );
            cout << "Nhap loai xe: "; getline(cin, loaixe);
            deletesubstr(loaixe, " ");
            lowerstr(loaixe);
            txt_extract(bienso, loaixe, "xe.txt");
            cout << "Bat dau thue tu:\n" ;
            cout << "thang: "; cin >> start_time.tm_mon;
            cout << "nam: "; cin >> start_time.tm_year;
            cout << "den\n" ;
            cout << "thang: "; cin >> end_time.tm_mon;
            cout << "nam: "; cin >> end_time.tm_year;
        }
    Hd_thang(istream &source) {
        getline(source, this->hoten);
        getline(source, this->cmt);
        getline(source, this->loaixe);
        getline(source, this->bienso);
        getline(source, (string&)this->start_time.tm_mon);
        getline(source, (string&)this->start_time.tm_year);
        getline(source, (string&)this->end_time.tm_mon);
        getline(source, (string&)this->end_time.tm_year);
    }
    virtual unsigned int gia_thue() {
        unsigned int price;
        price = diffmonths(start_time, end_time) * 3000000 + 1000000;
        return price;
    }
    virtual void savetofile() {
        encryptstr(this->hoten);
        encryptstr(this->cmt);
        ofstream file;
        file.open("hdngay.txt", ios::app);
        file << this->hoten << "\n";
        file << this->cmt << "\n";
        file << this->loaixe << "\n";
        file << this->bienso << "\n";
        file << this->start_time.tm_mon << "\n";
        file << this->start_time.tm_year << "\n";
        file.close();
    }
    virtual void getdata() {
        fflush(stdin);
            cout << "Nhap ho ten nguoi thue: "; getline(cin, hoten);
            cout << "Nhap so CMT nguoi thue: "; getline(cin, cmt );
            cout << "Nhap loai xe: "; getline(cin, loaixe);
            deletesubstr(loaixe, " ");
            lowerstr(loaixe);
            txt_extract(bienso, loaixe, "xe.txt");
            cout << "Bat dau thue tu:\n" ;
            cout << "thang: "; cin >> start_time.tm_mon;
            cout << "nam: "; cin >> start_time.tm_year;
            cout << "den\n" ;
            cout << "thang: "; cin >> end_time.tm_mon;
            cout << "nam: "; cin >> end_time.tm_year;
    }
    virtual void show() {
        cout << "Ho ten nguoi thue: " << this->hoten << "\n";
        cout << "So CMT nguoi thue: " << this->cmt << "\n";
        cout << "Loai xe: " << this->loaixe << "\n";
        cout << "Bat dau thue tu:\n" ;
        cout << "thang: " << this->start_time.tm_mon << "\n";
        cout << "nam: " << this->start_time.tm_year << "\n";
        cout << "den\n" ;
        cout << "thang: " << this->end_time.tm_mon << "\n";
        cout << "nam: " << this->end_time.tm_year;
    }
};

class Xe: public Hopdong {
    public:
    Xe () {
    fflush(stdin);
    cout << "Nhap loai xe: "; getline(cin, loaixe);
    deletesubstr(loaixe, " ");
    lowerstr(loaixe);
    cout << "Nhap bien so xe (VD: 27-B1258.88): "; getline(cin, bienso);
    deletesubstr(bienso, " ");
    upperstr(bienso);
    }
    virtual void savetofile() {
        ofstream file;
        file.open("xe.txt", ios::app);
        file << loaixe << bienso << "\n";
        file.close();
    }
    virtual unsigned int gia_thue() {}
    virtual void getdata() {}
    virtual void show() {}
};
#endif // HOPDONG_H
