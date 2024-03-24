#include <iostream>
#include <cstring>

using namespace std;

void Encryption(char S[4][33], unsigned short Rez[4][32]) {
    for (int row = 0; row < 4; ++row) {
        int len = strlen(S[row]);
        for (int i = len; i < 32; ++i) {
            S[row][i] = ' ';
        }
        S[row][32] = '\0';

        for (int i = 0; i < 32; ++i) {
            unsigned char c = S[row][i];
            unsigned short r = 0;
            r |= (row & 0x3) << 0;
            r |= (i & 0x1F) << 2;
            r |= c << 7;

            unsigned short b = 0;
            for (int j = 0; j < 15; ++j) {
                if ((r & (1 << j)) != 0) {
                    b ^= 1;
                }
            }
            r |= b << 15;

            Rez[row][i] = r;
        }
    }
}

void Decryption(unsigned short Rez[4][32], char S[4][33]) {
    for (int row = 0; row < 4; row++) {
        for (int i = 0; i < 32; i++) {
            unsigned short r = Rez[row][i];
            unsigned char c = (r >> 7) & 0xFF;

            unsigned short b = 0;
            for (int j = 0; j < 15; ++j) {
                if ((r & (1 << j)) != 0) {
                    b ^= 1;
                }
            }
            if (((r >> 15) & 0x1) != b) {
                c = '?';
            }

            S[row][i] = c;
        }
        S[row][32] = '\0';
    }
}

int main() {
    char S[4][33];
    unsigned short Rez[4][32];

    cout << "Enter 4 lines of text, each up to 32 characters:" << endl;
    for (int i = 0; i < 4; ++i) {
        cin.getline(S[i], 33);
    }

    Encryption(S, Rez);

    cout << "Encrypted text:" << endl;
    for (int i = 0; i < 4; ++i) {
        for (int j = 0; j < 32; ++j) {
            cout << hex << Rez[i][j] << " ";
        }
        cout << endl;
    }

    char DecryptedText[4][33];
    Decryption(Rez, DecryptedText);

    cout << "Decrypted text:" << endl;
    for (int i = 0; i < 4; ++i) {
        cout << DecryptedText[i] << endl;
    }

    return 0;
}

