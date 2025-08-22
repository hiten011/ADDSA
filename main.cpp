#include <bits/stdc++.h>
using namespace std;

int getInt(char c) {
    return (int)(c - '0');
}

string removeZero(string &s) {
    int idx = 0;
    while (idx + 1 < s.size() && s[idx] == '0') idx++;
    return s.substr(idx);
}

string add(string &n1, string &n2, int base) {
    int idx1 = n1.size() - 1, idx2 = n2.size() - 1, carry = 0;
    string ans;
    while (idx1 >= 0 || idx2 >= 0) {
        int temp1 = (idx1 < 0 ? 0 : getInt(n1[idx1]));
        idx1--;

        int temp2 = (idx2 < 0 ? 0 : getInt(n2[idx2]));
        idx2--;

        int sum = (temp1 + temp2 + carry) % base;
        carry = (temp1 + temp2 + carry) / base;

        ans += to_string(sum);
    }
    
    ans += (to_string(carry));
    reverse(ans.begin(), ans.end());

    return removeZero(ans);
}

string sub(string &n1, string &n2, int base) {
    if (n1 == n2) return string("0");

    int idx1 = n1.size() - 1, idx2 = n2.size() - 1, borrow = 0;
    string ans;

    while (idx1 >= 0 || idx2 >= 0) {
        int temp1 = (idx1 < 0 ? 0 : getInt(n1[idx1]));
        idx1--;

        int temp2 = (idx2 < 0 ? 0 : getInt(n2[idx2]));
        idx2--;

        int diff = temp1 - temp2 - borrow;
        if (diff < 0) {
            diff += base;
            borrow = 1;
        } else {
            borrow = 0;
        }

        ans += to_string(diff);
    }

    reverse(ans.begin(), ans.end());
    return removeZero(ans);
}

string multiply(string &n1, string &n2, int base) {
    if (n1.size() == 1 && n2.size() == 1) {
        string ans = "0";
        int temp1 = getInt(n1[0]);
        for (int i = 0; i < temp1; i++) {
            ans = add(ans, n2, base);
        }

        return ans;
    }

    int k = max(1, (int)(min(n1.size(), n2.size()) / 2));

    string a1 = (n1.size() > k) ? n1.substr(0, n1.size() - k) : string("0");
    string a0 = (n1.size() > k) ? n1.substr(n1.size() - k) : n1;
    string b1 = (n2.size() > k) ? n2.substr(0, n2.size() - k) : string("0");
    string b0 = (n2.size() > k) ? n2.substr(n2.size() - k) : n2;

    string z2 = multiply(a1, b1, base);
    string z0 = multiply(a0, b0, base); 
    string sum_a = add(a1, a0, base);
    string sum_b = add(b1, b0, base);
    string z1 = multiply(sum_a, sum_b, base);

    string temp = sub(z1, z2, base);
    temp = sub(temp, z0, base);

    z2.append(2 * k, '0');
    temp.append(k, '0');

    string res1 = add(z2, temp, base);
    string result = add(res1, z0, base);
    return removeZero(result);
}

int main() {
    string n1, n2;
    int base;

    cin >> n1 >> n2 >> base;

    cout << add(n1, n2, base) << " " << multiply(n1, n2, base) << endl;
    return 0;
}