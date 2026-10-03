#include <iostream>
#include <string>
#include <numeric>
using namespace std;

int modInverse(int a)
{
    for (int i = 1; i < 26; i++)
    {
        if ((a * i) % 26 == 1)
            return i;
    }
    return -1;
}

int gcd(int a, int b)
{
    while (b != 0)
    {
        int temp = b;
        b = a % b;
        a = temp;
    }
    return a;
}

string encrypt(string text, int a, int b)
{
    string cipher = "";

    for (char ch : text)
    {
        if (ch >= 'A' && ch <= 'Z')
        {
            int x = ch - 'A';
            int y = (a * x + b) % 26;
            cipher += char(y + 'A');
        }
        else if (ch >= 'a' && ch <= 'z')
        {
            int x = ch - 'a';
            int y = (a * x + b) % 26;
            cipher += char(y + 'a');
        }
        else
        {
            cipher += ch;
        }
    }

    return cipher;
}

string decrypt(string text, int a, int b)
{
    string plain = "";
    int a_inv = modInverse(a);

    for (char ch : text)
    {
        if (ch >= 'A' && ch <= 'Z')
        {
            int x = ch - 'A';
            int y = (a_inv * (x - b + 26)) % 26;
            plain += char(y + 'A');
        }
        else if (ch >= 'a' && ch <= 'z')
        {
            int x = ch - 'a';
            int y = (a_inv * (x - b + 26)) % 26;
            plain += char(y + 'a');
        }
        else
        {
            plain += ch;
        }
    }

    return plain;
}

int main()
{
    string text;
    int a, b;

    cout << "Enter text: ";
    getline(cin, text);

    cout << "Enter value of a: ";
    cin >> a;

    cout << "Enter value of b: ";
    cin >> b;

    if (gcd(a, 26) != 1)
    {
        cout << "a must be coprime with 26";
        return 0;
    }

    string encrypted = encrypt(text, a, b);
    cout << "Encrypted Text: " << encrypted << endl;

    string decrypted = decrypt(encrypted, a, b);
    cout << "Decrypted Text: " << decrypted << endl;

    return 0;
}