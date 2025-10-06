#include <bits/stdc++.h>
using namespace std;

class customMap {
    public:
        customMap() {
            // intialise the map
            map = vector<string>(26, "");
        }

        void insert(string s) { // insertion
            if (search(s, hash(s[s.size() - 1])) != -1) return;
            insert(s, hash(s[s.size() - 1]));
        }

        void deletion(string s) {
            int idx = search(s, hash(s[s.size() - 1]));

            if (idx == -1) return; // not found
            map[idx] = "#";
        }

        void print() {
            for (string &s : map) {
                if (s.empty() || s == "#") continue;
                cout << s << " ";
            }

            cout << endl;
        }

    private:
        vector<string> map;

        // hash function
        int hash(char c) {
            return (int) (c - 'a');
        }

        // insert function
        void insert(string &s, int idx) {
            for (int i = 0; i < 26; i++) {
                int newIdx = (idx + i) % 26;
                if (map[newIdx].empty() || map[newIdx] == "#") {
                    map[newIdx] = s;
                    break;
                }
            }
        }

        // search function
        int search(string &s, int idx) {
            for (int i = 0; i < 26; i++) {
                int newIdx = (idx + i) % 26;
                if (map[newIdx] == s) {
                    return newIdx;
                }
            }

            return -1;
        }
};

int main() {
    customMap us;
    string str = "#";
    while (true) {
        str = "END";
        cin >> str;
        
        if (str == "END") break;

        if (str[0] == 'A') {
            us.insert(str.substr(1));
        } else {
            us.deletion(str.substr(1));
        }
    }

    us.print();

    return 0;
}