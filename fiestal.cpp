#include <iostream>
#include <vector>
#include <string>

using namespace std;

const int BLOCK_SIZE = 16;

vector<int> stringToBits(const string &text)
{
    vector<int> bits;

    for (char ch : text)
    {
        unsigned char c = static_cast<unsigned char>(ch);
        for (int i = 7; i >= 0; i--)
        {
            bits.push_back((c >> i) & 1);
        }
    }
    return bits;
}

string bitsToString(const vector<int> &bits, int originalBits)
{
    string result;

    for (int i = 0; i < originalBits; i += 8)
    {
        unsigned char c = 0;
        for (int j = 0; j < 8; j++)
        {
            c = (c << 1) | bits[i + j];
        }
        result.push_back(static_cast<char>(c));
    }

    return result;
}

vector<int> functionF(const vector<int> &half, const vector<int> &key)
{
    vector<int> output(half.size());
    for (int i = 0; i < half.size(); i++)
    {
        output[i] = half[i] ^ key[i];
    }
    return output;
}

void feistelEncrypt(vector<int> &block,
                    const vector<int> &key1,
                    const vector<int> &key2,
                    int rounds)
{

    int half = BLOCK_SIZE / 2;

    vector<int> left(block.begin(), block.begin() + half);
    vector<int> right(block.begin() + half, block.end());

    for (int r = 0; r < rounds; r++)
    {

        vector<int> key = (r % 2 == 0) ? key1 : key2;
        vector<int> fOutput = functionF(right, key);

        vector<int> newRight(half);

        for (int i = 0; i < half; i++)
            newRight[i] = left[i] ^ fOutput[i];

        left = right;
        right = newRight;
    }

    for (int i = 0; i < half; i++)
    {
        block[i] = left[i];
        block[i + half] = right[i];
    }
}

void feistelDecrypt(vector<int> &block,
                    const vector<int> &key1,
                    const vector<int> &key2,
                    int rounds)
{

    int half = BLOCK_SIZE / 2;

    vector<int> left(block.begin(), block.begin() + half);
    vector<int> right(block.begin() + half, block.end());

    for (int r = rounds - 1; r >= 0; r--)
    {

        vector<int> key = (r % 2 == 0) ? key1 : key2;
        vector<int> fOutput = functionF(left, key);

        vector<int> newLeft(half);

        for (int i = 0; i < half; i++)
            newLeft[i] = right[i] ^ fOutput[i];

        right = left;
        left = newLeft;
    }

    for (int i = 0; i < half; i++)
    {
        block[i] = left[i];
        block[i + half] = right[i];
    }
}

int main()
{

    string plainText = "arman";

    vector<int> key1 = {1, 1, 0, 0, 1, 1, 0, 0};
    vector<int> key2 = {1, 1, 0, 1, 0, 1, 0, 1};

    vector<int> bits = stringToBits(plainText);
    int originalBits = bits.size();

    while (bits.size() % BLOCK_SIZE != 0)
        bits.push_back(0);

    cout << "Original Text: " << plainText << endl;

    for (int i = 0; i < bits.size(); i += BLOCK_SIZE)
    {
        vector<int> block(bits.begin() + i, bits.begin() + i + BLOCK_SIZE);
        feistelEncrypt(block, key1, key2, 2);

        for (int j = 0; j < BLOCK_SIZE; j++)
            bits[i + j] = block[j];
    }

    cout << "\nEncrypted Bits:\n";
    for (int i = 0; i < bits.size(); i++)
    {
        cout << bits[i];
        if ((i + 1) % 8 == 0)
            cout << " ";
    }
    cout << endl;

    for (int i = 0; i < bits.size(); i += BLOCK_SIZE)
    {
        vector<int> block(bits.begin() + i, bits.begin() + i + BLOCK_SIZE);
        feistelDecrypt(block, key1, key2, 2);

        for (int j = 0; j < BLOCK_SIZE; j++)
            bits[i + j] = block[j];
    }

    string decrypted = bitsToString(bits, originalBits);

    cout << "Decrypted Bits:\n";
    for (int i = 0; i < bits.size(); i++)
    {
        cout << bits[i];
        if ((i + 1) % 8 == 0)
            cout << " ";
    }
    cout << endl;
    cout << "Decrypted Text: " << decrypted << endl;

    return 0;
}