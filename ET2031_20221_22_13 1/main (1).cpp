#include <stdlib.h>
#include <stdio.h>
#include <iostream>
#include <string>
#include <time.h>
#include <fstream>
#include <vector>
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

void txt_extract (string &destination , const string spare, const string filename) {
    /**
     * Remove str spare within a line in a text file named filename, then extract that line to destination
    */
    ifstream file;
    file.open(filename);
    ofstream ftemp("temp.txt");
    if ( file.is_open() ) {
        string temp;
        bool flag = true;   
        while ( !file.eof() ) {
            getline(file, temp);
            if (flag == true ) {
                deletesubstr(temp, spare);
                destination = temp;
                flag = false;
                }
            else {
                ftemp << temp << "\n"; 
            }
        }
        file.close();
        ftemp.close();
        remove(filename.c_str());
        rename("temp.txt", filename.c_str());
    }
    else {
        cout << "File du lieu xe bi loi!";
        exit(1);
    }
}

void readHd(vector<Hopdong*> v, int mode) {
    ifstream file;
    int i = 0;
    if ( mode == 1 ) {
        file.open("hdngay.txt");
        if ( file.is_open() ) {
            static vector<Hd_ngay> hd;
            while ( !file.eof() ) {
                hd.push_back(Hd_ngay(file));
                decryptstr(hd[i].hoten);
                decryptstr(hd[i].cmt);
                v[i] = &hd[i];
                i++;
            }
        }
        else {
            cout << "File du lieu hop dong bi loi!";
        }
        file.close();
    }
    if ( mode == 2 ) {
        file.open("hdthang.txt");
        if ( file.is_open() ) {
            static vector<Hd_thang> hd;
            while ( !file.eof() ) {
                hd.push_back(Hd_thang(file));
                decryptstr(hd[i].hoten);
                decryptstr(hd[i].cmt);
                v[i] = &hd[i];
                i++;
            }
        }
        file.close();
    }
}

void searchHd( vector<Hopdong*> v, string s, vector<int> &rank, int mode)  {
    size_t pos;
    cout << "Ket qua tim kiem: \n";
    switch (mode) {
        case 1 :
        for ( int i = 0; i < v.size(); i++ ) {
            if ( (pos  = v.at(i)->hoten.find(s)) != string::npos) {
                rank.push_back(i);
                cout << rank.size() + 1 << ".\n";
                v.at(i)->show();
            }
        }
        break;
        case 2 :
        for ( int i = 0; i < v.size(); i++ ) {
            if ( (pos  = v.at(i)->bienso.find(s)) != string::npos) {
                rank.push_back(i);
                cout << rank.size() + 1 << ".\n";
                v.at(i)->show();
            }
        }
        break;
        case 3 :
        for ( int i = 0; i < v.size(); i++ ) {
            if ( (pos  = v.at(i)->loaixe.find(s)) != string::npos) {
                rank.push_back(i);
                cout << rank.size() + 1 << ".\n";
                v.at(i)->show();
            }
        }
        break;
    }
}

void changeHd(vector<Hopdong*> v, vector<int> &rank) {
    int stt;
    cout << "Chon hop dong ban muon sua (Nhap so thu tu hien thi cua hop dong):\n";
    cout << "Lua chon cua ban: "; cin >> stt;
    v.at(rank.at(stt - 1))->getdata();
    cout << "Sua hop dong thanh cong!";
}

void deleteHd(vector<Hopdong*> v, vector<int> &rank) {
    int stt;
    cout << "Chon hop dong ban muon xoa (Nhap so thu tu hien thi cua hop dong):\n";
    cout << "Lua chon cua ban: "; cin >> stt;
    v.erase(v.begin() + rank.at(stt - 1));
    cout << "Xoa hop dong thanh cong!";
}

void encryptstr(string &s) {
    for ( int i = 0; s[i] != '\0'; i++ ) {
        if ( s[i] < 90 ) { s[i] = s[i] + 1; }
        if ( s[i] > 91 ) { s[i] = s[i] - 1; }
    }
}

void decryptstr(string &s) {
    for ( int i = 0; i < s.length(); i++ ) {
        if ( s[i] <= 90 ) { s[i] = s[i] - 1; }
        if ( s[i] >= 91 ) { s[i] = s[i] + 1; }
    }
}

void lowerstr(string &s) {
    /**
     * Lowercase all character of a str
    */
    for (int i = 0; i < s.length(); i++) {
  		s[i] = tolower(s[i]);
  	}
}

void upperstr(string &s) {
    /**
     * Uppercase all character of a str
    */
    for (int i = 0; i < s.length(); i++) {
  		s[i] = toupper(s[i]);
  	}
}

void deletesubstr(string &mainstr, const string &substr) {
    size_t pos;
    while ((pos  = mainstr.find(substr) )!= string::npos)
    {
        mainstr.erase(pos, substr.length());
    }
}

unsigned int diffdays (struct tm start, struct tm end) {
    /**
     * Calculate the different days between two calendar day
    */
    time_t x,y;
    double difference;
    x = mktime(&start);
    y = mktime(&end);
    if ( x != (time_t)(-1) && y != (time_t)(-1) ) {
        difference = difftime(y, x) / (60 * 60 * 24);
    }
    return ( (int)difference + 1 );
}

unsigned int diffmonths (struct tm start, struct tm end) {
    /**
     * Calculate the different months between two calendar day
    */
   time_t x,y;
    double difference;
    x = mktime(&start);
    y = mktime(&end);
    if ( x != (time_t)(-1) && y != (time_t)(-1) ) {
        difference = difftime(y, x) / (60 * 60 * 24 * 30);
    }
    return ( (int)difference + 1 );
}

void searchHdMenu(vector<Hopdong*> v, vector<int> &rank) {
    int choice1, choice2;
    string hoten, loaixe, bienso;
    ifstream file;
    cout << "Chon loai hop dong can tim kiem:\n";
    cout << "1. Hop dong ngay                (nhap 1)          **\n";
    cout << "2. Hop dong thang               (nhap 2)          **\n";
    cout << "Nhap lua chon: "; cin >> choice1;
    switch (choice1) {
        case 1:
        readHd(v, choice1);
        break;
        case 2:
        readHd(v, choice2);
        break;
    }
    cout << "Chon phuong thuc tim kiem:\n";
    cout << "1. Tim theo ten chu xe\n";
    cout << "2. Tim theo bien so xe\n" ;
    cout << "3. Tim theo loai xe\n";
    cout << "Nhap phuong thuc ban chon: "; cin >> choice2;
    switch (choice2) {
        case 1:
        cout << "Nhap ten chu xe: "; getline(cin, hoten);
        searchHd(v, hoten, rank, 1);
        break;
        case 2:
        cout << "Nhap bien so xe: "; getline(cin, bienso);
        searchHd(v, bienso, rank, 2);
        break;
        case 3:
        cout << "Nhap loai xe: "; getline(cin, loaixe);
        searchHd(v, loaixe, rank, 3);
        break;
    }
}

void menu1() {
    int choice;
    char ch = 'c';
    Hopdong* p;
    while ( ch == 'c' ) {
        cout << "Chon loai hop dong ban muon them:\n";
        cout << "1. Hop dong ngay                (nhap 1)          **\n";
        cout << "2. Hop dong thang               (nhap 2)          **\n";
        cout << "Nhap lua chon: "; cin >> choice;
        if ( choice == 1 ) {
            Hd_ngay hd1;
            p = &hd1;
            p->getdata();
            p->savetofile();
            cout << "Tao hop dong thanh cong!";
            cout << "\nBien so xe la: " << hd1.bienso << "\n";
        }
        if ( choice == 2 ) {
            Hd_thang hd2;
            p = &hd2;
            p->savetofile();
            cout << "Tao hop dong thanh cong!";
            cout << "\nBien so xe la: " << hd2.bienso << "\n";
        }
        system("pause");
        fflush(stdin);
        cout << "Ban co muon tao them hop dong khong (c/k) ?" << endl;
        cout << "Nhap c (co) hoac k (khong): "; ch = getc(stdin);
    }
}

void menu3(vector<Hopdong*> v, vector<int> rank) {
    char ch = 'c';
    while ( ch == 'c' ) {
        system("cls");
        searchHdMenu(v, rank);
        changeHd(v, rank);
        cout << "Ban co muon tiep tuc xoa hop dong khong (c/k) ?" << endl;
        cout << "Nhap c (co) hoac k (khong): "; ch = getc(stdin);
    }
}

void menu4(vector<Hopdong*> v, vector<int> rank) {
    char ch = 'c';
    while ( ch == 'c' ) {
        system("cls"); 
        searchHdMenu(v, rank);
        cout << "Ban co muon tiep tuc tim kiem hop dong khong (c/k) ?" << endl;
        cout << "Nhap c (co) hoac k (khong): "; ch = getc(stdin);
    }
}
void menu7() {
    char ch = 'c';
    ofstream file;
    file.open("xe.txt", ios::app);
    while ( ch == 'c' ) {
        Xe xe;
        xe.savetofile();
        cout << "Them xe thanh cong!\n";
        system("pause");
        cout << "Ban co muon nhap them xe khong (c/k) ?" << endl;
        cout << "Nhap c (co) hoac k (khong): "; ch = getc(stdin);
    }
    file.close();
}

void mainmenu() {
    vector<Hopdong*> v;
    vector<int> rank;
    int choice;
    bool flag = true;
    while (flag)
    {
    system("cls");
		cout << "CHUONG TRINH QUAN LY HOP DONG THUE XE\n"  ;
        cout << "Chon thao tac ban muon thuc hien:\n ";
        cout << "*************************MENU****************************\n";
        cout << "**  1. Them hop dong.                (nhap 1)          **\n";
        cout << "**  2. Sua hop dong.                 (nhap 2)          **\n";
        cout << "**  3. Xoa hop dong.                 (nhap 3)          **\n";
        cout << "**  4. Tim kiem hop dong             (nhap 4)          **\n";
        cout << "**  5. Cap nhat chi phi cho thue xe  (nhap 5)          **\n";
    	cout << "**  6. Tinh tong phi thu duoc        (nhap 6)          **\n";
        cout << "**  7. Them xe vao danh sach         (nhap 7)          **\n";
        cout << "**  0. Thoat                                           **\n";
        cout << "*********************************************************\n";
        cout << "Nhap lua chon: "; cin >> choice;
        switch (choice) {
            case 1 :
            system("cls");
            menu1();
            rank.clear();
            v.clear();
            break;
            case 2:
            system("cls");
            cout << "Tim kiem hop dong can sua:\n";
            searchHdMenu(v, rank);
            rank.clear();
            v.clear();
            break;
            case 4 :
            menu4(v, rank);
            rank.clear();
            v.clear();
            break;
            case 7 :
            system("cls");
            break;
            case 0 : 
            exit(0);
        }
    }
}

int main() {
    mainmenu();
}