#include <iostream>
#include <string>
using namespace std;

string rotor1 = "EKMFLGDQVZNTOWYHXUSPAIBRCJ";
string rotor2 = "AJDKSIRUXBLHWTMCQGZNPYFVOE";
string rotor3 = "BDFHJLCPRTXVZNYEIGAKMUSQO";

void rotate(int &pos)
{
    pos = (pos + 1) % 26;
}

char encryptChar(char ch, string rotor, int pos)
{
    int index = ch - 'A';
    index = (index + pos) % 26;
    return rotor[index];
}

char decryptChar(char ch, string rotor, int pos)
{
    for (int i = 0; i < 26; i++)
    {
        int index = (i + pos) % 26;

        if (rotor[index] == ch)
            return char(i + 'A');
    }

    return ch;
}

string encryptMessage(string text, int p1, int p2, int p3)
{
    for (int i = 0; i < text.size(); i++)
    {
        rotate(p1);

        if (i > 0 && i % 26 == 0)
            rotate(p2);

        if (i > 0 && i % (26 * 26) == 0)
            rotate(p3);

        text[i] = encryptChar(text[i], rotor1, p1);
        text[i] = encryptChar(text[i], rotor2, p2);
        text[i] = encryptChar(text[i], rotor3, p3);
    }

    return text;
}

string decryptMessage(string text, int p1, int p2, int p3)
{
    for (int i = 0; i < text.size(); i++)
    {
        rotate(p1);

        if (i > 0 && i % 26 == 0)
            rotate(p2);

        if (i > 0 && i % (26 * 26) == 0)
            rotate(p3);

        text[i] = decryptChar(text[i], rotor3, p3);
        text[i] = decryptChar(text[i], rotor2, p2);
        text[i] = decryptChar(text[i], rotor1, p1);
    }

    return text;
}

int main()
{
    string text = "ARMAN";

    int pos1 = 5;
    int pos2 = 10;
    int pos3 = 1;

    cout << "Original: " << text << endl;

    string encrypted = encryptMessage(text, pos1, pos2, pos3);
    cout << "Encrypted: " << encrypted << endl;

    string decrypted = decryptMessage(encrypted, pos1, pos2, pos3);
    cout << "Decrypted: " << decrypted << endl;

    return 0;
}