#include <iostream>
#include <cstring>

using namespace std;

auto tasks1() {

    int a, b, c, d;
    int result;
    float check_res;
    cout << " Calculation of expressions using bitwise operations  \n";
    cout << "Enter A:";
    cin >> a;
    cout << "Enter B:";
    cin >> b;
    cout << "Enter C:";
    cin >> c;
    cout << "Enter D:";
    cin >> d;
    result = ((((a << 4) - a) - ((b << 3) + (b << 4) + (b << 5) + (b << 8))) >> 6) - ((c << 7) - (c << 3)) + ((d << 7) - (d << 3) + d);
    cout << "Result:" << result << endl;
    check_res = ((a * 15 - b * 312) / 64) - c * 120 + d * 121 - 1;
    printf("Check result: %0.5f", check_res);

}

auto Encryption(char S[4][33], unsigned short Rez[4][32]) {
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

            unsigned short b = 0;
            for (int j = 0; j < 15; j++) {
                if ((r & (1 << j)) != 0) {
                    b ^= 1;
                }
            }
            r |= b << 15;

            Rez[row][i] = r;
        }
    }
}

auto Decryption(unsigned short Rez[4][32], char S[4][33]) {
    for (int row = 0; row < 4; row++) {
        for (int i = 0; i < 32; i++) {
            unsigned short r = Rez[row][i];
            unsigned char c = (r >> 7) & 0xFF;

            unsigned short b = 0;
            for (int j = 0; j < 15; j++) {
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

auto tasks2() {
    char S[4][33];
    unsigned short Rez[4][32];

    cout << "Enter 4 lines of text, each up to 32 characters:" << endl;
    for (int i = 0; i < 4; i++) {
        cin.getline(S[i], 33);
    }

    Encryption(S, Rez);

    cout << "Encrypted text:" << endl;
    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 32; j++) {
            cout << hex << Rez[i][j] << " ";
        }
        cout << endl;
    }

    char DecryptedText[4][33];

    cout << "Want to decrypt?" << endl;
    cout << "1.Yes" << endl;
    cout << "2.No" << endl;
    int ch;
    cin >> ch;

    switch (ch) {
    case 1: {
        Decryption(Rez, DecryptedText);

        cout << "Decrypted text:" << endl;
        for (int i = 0; i < 4; i++) {
            cout << DecryptedText[i] << endl;
        }

        return 0; }
    case 2: return 0;
    }
}

int main()
{
	int choice;
	cout << "Choose task:" << endl;
	cout << "1.Calculation of expressions using bitwise operations." << endl;
	cout << "2.Encryption and decryption "<<endl;
	cout << "3.Exite" << endl;

	cin >> choice;
	switch (choice) {
	case 1: tasks1(); break;
	case 2: tasks2(); break;
	case 3: return 0;

	}
}

