#include <iostream>
#include <string>
#include <vector>
#include <cmath>
using namespace std;

vector<char> plainText = {'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h', 'i', 'j',
                          'k', 'l', 'm', 'n', 'o', 'p', 'q', 'r', 's', 't', 
                          'u', 'v', 'w', 'x', 'y', 'z'};

vector<char> cipherText = {'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'I', 'J', 
                           'K', 'L', 'M', 'N', 'O', 'P', 'Q', 'R', 'S', 'T', 
                           'U', 'V', 'W', 'X', 'Y', 'Z'};

vector<int> value = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 
                     14, 15, 16, 17, 18, 19, 20, 21, 22, 23, 24, 25};

vector<float> frequencies = {8.2, 1.5, 2.8, 4.3, 12.7,2.2, 2.0, 6.1, 7.0, 0.02,
                             0.08,4.0, 2.4, 6.7, 7.5, 1.9, 0.01,6.0, 6.3, 9.1,
                             2.8, 1.0, 2.3, 0.01,2.0, 0.01 };

string encryptAffine(const string& text, int key1, int key2) {
    string encrypted = "";

    for (char ch : text) {
        if (ch >= 'a' && ch <= 'z') {
            int P = ch - 'a';
            int C = (key1 * P + key2) % 26;
            encrypted += cipherText[C];
        } else {
            encrypted += ch;
        }
    }
    return encrypted;
}

int modInverse(int a, int m) {
    a %= m;
    for (int x = 1; x < m; x++)
        if ((a * x) % m == 1)
            return x;
    return -1; 
}

string decryptAffine(const string& text, int key1, int key2) {
    string decrypted = "";

    int invA = modInverse(key1, 26);
    if (invA == -1) return "ERROR: key1 has no modular inverse!";

    for (char ch : text) {
        if (ch >= 'A' && ch <= 'Z') {
            int C = ch - 'A';
            int P = (invA * (C - key2 + 26)) % 26;
            decrypted += plainText[P];
        } else {
            decrypted += ch;
        }
    }
    return decrypted;
}

double chiSquared(const vector<int> &observed, int length) {
    double chi = 0;

    for (int i = 0; i < 26; i++) {
        double expected = frequencies[i] * length / 100.0;
        if (expected > 0)
            chi += pow(observed[i] - expected, 2) / expected;
    }

    return chi;
}

void statisticalAttackAffine(const string& ciphertext) {
    vector<int> validA = {1,3,5,7,9,11,15,17,19,21,23,25};

    double bestChi = 1e18;
    int bestA = 1, bestB = 0;

    cout << "\n Statistical Attack (Affine Cipher - Chi-Square) \n";

    for (int a : validA) {
        for (int b = 0; b < 26; b++) {
            string attempt = decryptAffine(ciphertext, a, b);

            vector<int> count(26, 0);
            int total = 0;

            for (char ch : attempt) {
                if (ch >= 'a' && ch <= 'z') {
                    count[ch - 'a']++;
                    total++;
                }
            }

            if (total == 0) continue;

            double score = chiSquared(count, total);

            cout << "a=" << a << ", b=" << b 
                 << " -> score=" << score 
                 << " -> " << attempt << endl;

            if (score < bestChi) {
                bestChi = score;
                bestA = a;
                bestB = b;
            }
        }
    }

    cout << "\nMost likely keys: a=" << bestA << ", b=" << bestB << endl;
    cout << "Decrypted text: " << decryptAffine(ciphertext, bestA, bestB) << endl;
}

int main() {
    string input;
    int key;

    cout << "Enter plaintext (a-z): ";
    getline(cin, input);

    int  key1 = 3, key2 = 11;
    string affineEncrypted = encryptAffine(input, key1, key2);
    cout << "encrypted: " << affineEncrypted << endl;

    cout << "decrypted: " 
     << decryptAffine(affineEncrypted, key1, key2) << endl;

    statisticalAttackAffine(affineEncrypted);


    return 0;
}
