#include <stdio.h>

void padding(char *str, int *bitstr, int len)
{
    for (int i = 0; i < len; i++)
    {
        char ch = str[i];
        for (int j = 7; j >= 0; j--)
        {
            bitstr[i * 8 + (7 - j)] = (ch >> j) & 1;
        }
    }

    bitstr[len * 8] = 1;

    int totalBits = len * 8 + 1;
    while (totalBits % 512 != 448)
    {
        totalBits++;
    }

    long long originalBitLength = (long long)len * 8;
    for (int i = 0; i < 64; i++)
    {
        bitstr[totalBits + i] = (originalBitLength >> (63 - i)) & 1;
    }
}

int main()
{
    char str[50] = "hello";
    int len = sizeof(str) - 1;
    printf("String: %s\n", str);
    int bitstr[512] = {0};
    padding(str, bitstr, len);
    printf("Padded bit string:\n");
    for (int i = 0; i < 512; i++)
    {
        printf("%d", bitstr[i]);
        if ((i + 1) % 8 == 0)
        {
            printf(" ");
        }
    }
    printf("\n");

    int h0 = 0x67452301;
    int h1 = 0xEFCDAB89;
    int h2 = 0x98BADCFE;
    int h3 = 0x10325476;
    int h4 = 0xC3D2E1F0;

    int W[80];
    for (int i = 0; i < 16; i++)
    {
        W[i] = 0;
        for (int j = 0; j < 32; j++)
        {
            W[i] = W[i] * 2 + bitstr[i * 32 + j];
        }
    }

    for (int i = 16; i < 80; i++)
    {
        int temp = W[i - 3] ^ W[i - 8] ^ W[i - 14] ^ W[i - 16];
        W[i] = (temp << 1) | (temp >> 31);
    }

    int a = h0;
    int b = h1;
    int c = h2;
    int d = h3;
    int e = h4;

    for (int t = 0; t < 80; t++)
    {
        int f, k;
        
        if (t < 20)
        {
            f = (b & c) | ((~b) & d);
            k = 0x5A827999;
        }
        else if (t < 40)
        {
            f = b ^ c ^ d;
            k = 0x6ED9EBA1;
        }
        else if (t < 60)
        {
            f = (b & c) | (b & d) | (c & d);
            k = 0x8F1BBCDC;
        }
        else
        {
            f = b ^ c ^ d;
            k = 0xCA62C1D6;
        }

        int temp = a;
        temp = temp << 5;
        int a_shifted = temp | (a >> 27);
        
        int sum = a_shifted + f + e + W[t] + k;
        
        int temp_a = a;
        int temp_e = d;
        e = d;
        d = c;
        c = b;
        c = (c << 30) | (c >> 2);
        b = a;
        a = sum;
    }

    h0 = h0 + a;
    h1 = h1 + b;
    h2 = h2 + c;
    h3 = h3 + d;
    h4 = h4 + e;

    printf("SHA-1 Hash: %08x%08x%08x%08x%08x\n", h0, h1, h2, h3, h4);

    return 0;
}