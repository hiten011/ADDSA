#include <bits/stdc++.h>
using namespace std;

vector<string> getAdj(string &str) {
    str += ",";
    vector<string> vec;
    string prev = "";
    for (char c : str)
    {
        if (c == ',')
        {
            vec.push_back(prev);
            prev = "";
            continue;
        }

        prev += c;
    }

    return vec;
}

int getScore(char c) {
    if (isupper(c)) return (int)(c - 'A');
    return (int)(c - 'a') + 26;
}

int main() {
    string c, b, d;
    cin >> c >> b >> d;

    vector<string> country = getAdj(c);
    vector<string> build = getAdj(b);
    vector<string> destroy = getAdj(d);

    int n = destroy.size();
    int totalCost = 0;

    priority_queue<pair<int, int>> pq;

    // mst
    vector<bool> visited(n, false);
    pq.push({0, 0});

    while (!pq.empty()) {
        pair<int, int> top = pq.top();    
        int cost = top.first;   
        int dest = top.second;

        pq.pop();

        if (cost < 0) {
            // build road
            if (visited[dest]) {
                continue;
            }

            totalCost += abs(cost);
        } else if (visited[dest]) {
            totalCost += cost;
            continue;
        }

        visited[dest] = true;
        for (int i = 0; i < n; i++) {
            if (i == dest || country[dest][i] == '2') continue;

            if (country[dest][i] == '1') {
                // edge exists
                pq.push({getScore(destroy[dest][i]), i});
            }
            else if (country[dest][i] == '0') {
                // build edge
                pq.push({-1 * getScore(build[dest][i]), i});
            }

            country[i][dest] = '2'; // process road
            country[dest][i] = '2';   // process road
        }
    }

    cout << totalCost << endl;
}