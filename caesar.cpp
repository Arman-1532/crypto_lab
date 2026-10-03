#include <iostream>
#include <string>
using namespace std;

string encrypt(string text, int key)
{
    string result = "";

    for (char ch : text)
    {
        if (ch >= 'a' && ch <= 'z')
        {
            int x = ch - 'a';
            int y = (x + key) % 26;
            result += char(y + 'A');
        }
        else
        {
            result += ch;
        }
    }

    return result;
}

string decrypt(string text, int key)
{
    string result = "";

    for (char ch : text)
    {
        if (ch >= 'A' && ch <= 'Z')
        {
            int x = ch - 'A';
            int y = (x - key + 26) % 26;
            result += char(y + 'a');
        }
        else
        {
            result += ch;
        }
    }

    return result;
}

void keyFinder(string text)
{
    for (int key = 0; key < 26; key++)
    {
        cout << "Key " << key << " : " << decrypt(text, key) << endl;
    }
}

int main()
{
    string word;

    cout << "Enter text: ";
    getline(cin, word);

    int key;
    cout << "Enter key: ";
    cin >> key;

    string encrypted = encrypt(word, key);
    cout << "Encrypted: " << encrypted << endl;

    string decrypted = decrypt(encrypted, key);
    cout << "Decrypted: " << decrypted << endl;

    keyFinder(encrypted);

    return 0;
}