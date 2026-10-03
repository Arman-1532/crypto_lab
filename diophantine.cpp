#include <iostream>
using namespace std;

struct Result {
    int gcd;
    int s;
    int t;
};

int gcd(int a, int b) {
    while (b != 0) {
        int r = a % b;
        a = b;
        b = r;
    }
    return a;
}

Result egcd(int a, int b) {
    int r1 = a, r2 = b;
    int s1 = 1, s2 = 0;
    int t1 = 0, t2 = 1;
    int q, r, s, t;

    while (r2 != 0) {
        q = r1 / r2;
        r = r1 % r2;
        r1 = r2;
        r2 = r;

        s = s1 - q * s2;
        s1 = s2;
        s2 = s;

        t = t1 - q * t2;
        t1 = t2;
        t2 = t;
    }

    return {r1, s1, t1}; 
}

int main() {
    int a, b, c;
    cout << "Enter coefficients a, b and c (for ax + by = c): ";
    cin >> a >> b >> c;

    cout << "\nOriginal equation: " << a << "x + " << b << "y = " << c << "\n";

    int d = gcd(a, b);

    if (c % d != 0) {
        cout << "No integer solution exists 20 5 100since gcd(a,b) does not divide c.\n";
        return 0;
    }

    int a1 = a / d;
    int b1 = b / d;
    int c1 = c / d;

    cout << "\nReduced equation: " << a1 << "x + " << b1 << "y = " << c1 << "\n";

    Result res = egcd(a1, b1);

    int x0 = res.s * c1;
    int y0 = res.t * c1;

    cout << "\nParticular solution (x0, y0): (" << x0 << ", " << y0 << ")\n";
    cout << "General solution: x = " << x0 << " + " << b1 << "*k, y = "
         << y0 << " - " << a1 << "*k\n";

    int k_start, k_end;
    cout << "\nEnter the range of k to generate solutions (e.g., 0 5): ";
    cin >> k_start >> k_end;

    for (int k = k_start; k <= k_end; ++k) {
        int xk = x0 + b1 * k;
        int yk = y0 - a1 * k;
        cout << "For k = " << k << ": (x, y) = (" << xk << ", " << yk << ")\n";
    }

    return 0;
}
