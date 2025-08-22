#include <bits/stdc++.h>
using namespace std;

int getInt(char c) {
    return (int)(c - '0');
}

string add(string n1, string n2, int base) {
    int idx1 = n1.size() - 1, idx2 = n2.size() - 1, carry = 0;
    string ans;
    while (idx1 >= 0 || idx2 >= 0) {
        int temp1 = (idx1 < 0 ? 0 : getInt(n1[idx1]));
        idx1--;

        int temp2 = (idx2 < 0 ? 0 : getInt(n2[idx2]));
        idx2--;

        int sum = (temp1 + temp2 + carry) % base;
        carry = (temp1 + temp2) / base;

        ans += (to_string(sum));
    }
    
    if (carry != 0) ans += (to_string(carry));
    reverse(ans.begin(), ans.end());

    return ans;
}

string multiply(string n1, string n2, int base) {
    return "0";
}

int main() {
    string n1, n2;
    int base;

    cin >> n1 >> n2 >> base;

    cout << add(n1, n2, base) << " " << multiply(n1, n2, base) << endl;
    return 0;
}