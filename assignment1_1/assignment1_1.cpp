
#include <stdio.h>

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
        printf("nhap so can tinh giai thua: ");
        scanf("%d", &number);
        if (number < 0) {
            printf("so khong hop le\n");
        } else {
            printf("giai thua cua %d la %ld.\n", number, factorial(number));
        }
        printf("ban muon tiep tuc hay khong? (Y/N): ");
        scanf(" %c", &choice);
    } while (choice == 'y' || choice == 'Y');

    return 0;
}
