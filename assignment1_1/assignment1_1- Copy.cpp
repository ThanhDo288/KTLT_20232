
#include <iostream>
using namespace std;

long factorial(int n) {
    long result = 1;
    while (n > 1) {
        result *= n--;
    }
    return result;
}

int main() {
    int number;
    char choice;

    do {
        cout << "nhap so can tinh giai thua : ";
        cin >> number;
        if (number < 0) {
            cout << "so khong hop le.\n";
        } else {
            cout << "gia thua cua " << number << " la " << factorial(number) << ".\n";
        }
        cout << "ban muon tiep tuc? (Y/N): ";
        cin >> choice;
        choice = tolower(choice);
    } while (choice == 'y');

    return 0;
}
