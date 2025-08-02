#include <bits/stdc++.h>
using namespace std;

int add(int num1, int num2, int base) {
    int ans = 0, carry = 0, len = 1;
    while (num1 > 0) {
        int n1 = num1 % 10;
        int n2 = num2 % 10;

        num1 /= 10;
        num2 /= 10;
        
        int sum = n1 + n2 + carry;
        carry = sum / base;

        int curSum = sum % base;
        ans += curSum * len;
        len *= 10;
    }

    ans += carry * len;

    return ans;
}

int multiply() {
    return 0;
}

int main() {
    int num1; cin >> num1;
    int num2; cin >> num2;
    int base; cin >> base;

    cout << add(max(num1, num2), min(num1, num2), base) << endl;
    cout << multiply() << endl;
    cout << 0 << endl;

    return 0;
}