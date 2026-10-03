#include <iostream>
#include <vector>
using namespace std;

long long gcd(long long a, long long b) {
    while(b != 0) {
        long long temp = b;
        b = a % b;
        a = temp;
    }
    return a;
}

long long modExp(long long base, long long exp, long long mod) {
    long long result = 1;
    base %= mod;
    while(exp > 0) {
        if(exp & 1) {
            result = (result * base) % mod;
        }
        base = (base * base) % mod;
        exp >>= 1;
    }
    return result;
}

long long modInverse(long long e, long long phi) {
    long long t = 0, newt = 1;
    long long r = phi, newr = e;

    while(newr != 0) {
        long long quotient = r / newr;

        long long temp = newt;
        newt = t - quotient * newt;
        t = temp;

        temp = newr;
        newr = r - quotient * newr;
        r = temp;
    }

    if(t < 0)
        t += phi;

    return t;
}

int main() {
    long long p = 61;
    long long q = 53;

    long long n = p * q;
    long long phi = (p - 1) * (q - 1);

    long long e = 17;
    long long d = modInverse(e, phi);

    cout << "Public Key (e, n): (" << e << ", " << n << ")\n";
    cout << "Private Key (d, n): (" << d << ", " << n << ")\n\n";

    string message;
    cout << "Enter message: ";
    getline(cin, message);

    vector<long long> encrypted;

    for(char ch : message) {
        long long m = (int)ch;
        encrypted.push_back(modExp(m, e, n));
    }

    cout << "\nEncrypted values:\n";
    for(long long c : encrypted)
        cout << c << " ";

    string decrypted = "";
    for(long long c : encrypted) {
        long long m = modExp(c, d, n);
        decrypted += (char)m;
    }

    cout << "\n\nDecrypted message:\n" << decrypted << endl;

    return 0;
}