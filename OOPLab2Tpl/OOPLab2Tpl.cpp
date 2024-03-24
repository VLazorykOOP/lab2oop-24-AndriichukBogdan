#include <iostream>
#include <cstring>
using namespace std;

void task1() {
    int a, b, c, d, result, check_res;
    cout << "Calculation of expressions using bitwise operations\n";
    cout << "Enter A: ";
    cin >> a;
    cout << "Enter B: ";
    cin >> b;
    cout << "Enter C: ";
    cin >> c;
    cout << "Enter D: ";
    cin >> d;

    result = ((((a << 4) - a) - ((b << 3) + (b << 4) + (b << 5) + (b << 8))) >> 6) - ((c << 7) - (c << 3)) + ((d << 7) - (d << 3) + d);
    cout << "Result: " << result << endl;

    check_res = ((a * 15 - b * 312) / 64) - c * 120 + d * 121 - 1;
    cout << "Checked Result: " << check_res << endl;
}

void Encryption(char S[4][33], unsigned short Rez[4][32]) {
    for (int row = 0; row < 4; row++) {
        int len = strlen(S[row]);
        for (int i = len; i < 32; i++) {
            S[row][i] = ' ';
        }
        S[row][32] = '\0';

        for (int i = 0; i < 32; i++) {
            unsigned char c = S[row][i];
            unsigned short r = 0;
            r |= (row & 0x3) << 0;
            r |= (i & 0x1F) << 2;
            r |= c << 7;

            unsigned short parity = 0;
            for (int j = 0; j < 15; j++) {
                if (r & (1 << j)) {
                    parity ^= 1;
                }
            }
            r |= parity << 15;

            Rez[row][i] = r;
        }
    }
}

void Decryption(unsigned short Rez[4][32], char S[4][33]) {
    for (int row = 0; row < 4; row++) {
        for (int i = 0; i < 32; i++) {
            unsigned short r = Rez[row][i];
            unsigned char c = (r >> 7) & 0xFF;

            unsigned short parity = 0;
            for (int j = 0; j < 15; j++) {
                if (r & (1 << j)) {
                    parity ^= 1;
                }
            }
            if (((r >> 15) & 0x1) != parity) {
                c = '?';
            }

            S[row][i] = c;
        }
        S[row][32] = '\0';
    }
}

void task2() {
    char S[4][33];
    unsigned short Rez[4][32];

    cout << "Enter 4 lines of text, each up to 32 characters:\n";
    cin.ignore();
    for (int i = 0; i < 4; i++) {
        cin.getline(S[i], 33);
    }

    Encryption(S, Rez);

    cout << "Encrypted text:\n";
    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 32; j++) {
            cout << hex << Rez[i][j] << " ";
        }
        cout << endl;
    }

    Decryption(Rez, S);

    cout << "Decrypted text:\n";
    for (int i = 0; i < 4; i++) {
        cout << S[i] << endl;
    }
}

int main() {
    int choice;
    cout << "Choose task:\n";
    cout << "1. Calculation of expressions using bitwise operations.\n";
    cout << "2. Encryption and decryption.\n";
    cout << "3. Exit.\n";

        cout << "Enter choice: ";
        cin >> choice;

        switch (choice) {
        case 1:
            task1();
            break;
        case 2:
            task2();
            break;
        case 3:
            cout << "Exiting.\n";
            return 0;
        default:
            cout << "Invalid choice. Please choose again.\n";
        }
   

    return 0;
}
