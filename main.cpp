#include <bits/stdc++.h>
using namespace std;

int getInt(char c) {
    return (int)(c - '0');
}

string removeZero(string &s) {
    int idx = 0, n = s.size();
    while (idx + 1 < n && s[idx] == '0') idx++;
    return s.substr(idx);
}

void equalDigit(string &s1, string &s2) {
    int len = abs((int) (s1.size() - s2.size()));

    string leadZero;
    leadZero.append(len, '0');
    
    if (s1.size() < s2.size()) {
        leadZero += s1;
        s1 = leadZero;
    } else {
        leadZero += s2;
        s2 = leadZero;
    }
}

string add(string &n1, string &n2, int base) {
    equalDigit(n1, n2);
    int idx1 = n1.size() - 1, idx2 = n2.size() - 1, carry = 0, sum = 0;
    string ans;
    while (idx1 >= 0 || idx2 >= 0) {
        int temp1 = (idx1 < 0 ? 0 : getInt(n1[idx1]));
        idx1--;

        int temp2 = (idx2 < 0 ? 0 : getInt(n2[idx2]));
        idx2--;

        int ps = temp1 + temp2 + carry;
        sum = ps % base;
        carry = ps / base;

        ans += to_string(sum);
    }
    
    ans += (to_string(carry));
    reverse(ans.begin(), ans.end());

    return removeZero(ans);
}

string wrongCode(string &n1, string &n2, int base)
{
    equalDigit(n1, n2);
    int idx1 = n1.size() - 1, idx2 = n2.size() - 1, carry = 0, sum = 0;
    string ans = "0";
    while (idx1 >= 0 || idx2 >= 0)
    {
        int temp1 = getInt(n1[idx1]);
        idx1--;

        int temp2 = getInt(n2[idx2]);
        idx2--;

        int ps = temp1 + temp2 + carry;
        sum = ps % base;
        carry = ps / base;

        ans = to_string(sum) + ans;
    }

    if (carry > 0) ans = to_string(carry) + ans;
    return ans;
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
    if (n1.empty() || n2.empty()) return string("0");
    if (n1.size() == 1 && n2.size() == 1) {
        string ans = "0";
        int temp1 = getInt(n1[0]);
        for (int i = 0; i < temp1; i++) {
            ans = add(ans, n2, base);
        }

        return ans;
    }
    
    int maxLen = max(n1.size(), n2.size());

    int k = maxLen / 2;

    equalDigit(n1, n2);
    string a1 = n1.substr(0, k);
    string a0 = n1.substr(k);
    string b1 = n2.substr(0, k);
    string b0 = n2.substr(k);
    n1 = removeZero(n1);
    n2 = removeZero(n2);

    string z2 = multiply(a1, b1, base);
    string z0 = multiply(a0, b0, base); 

    string sum_a = add(a1, a0, base);
    string sum_b = add(b1, b0, base);
    string z1 = multiply(sum_a, sum_b, base);

    string temp = sub(z1, z2, base);
    temp = sub(temp, z0, base);

    z2.append(2 * (maxLen - k), '0');
    temp.append((maxLen - k), '0');

    string res1 = add(z2, temp, base);
    string result = add(res1, z0, base);
    return result;
}

int main() {
    string n1, n2;
    int base;

    cin >> n1 >> n2 >> base;

    string ad = add(n1, n2, base);
    string mul = multiply(n1, n2, base);

    cout << removeZero(ad) << " " << removeZero(mul) << " " << "0" << endl;
    return 0;
}