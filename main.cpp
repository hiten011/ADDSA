// #include <bits/stdc++.h>
// using namespace std;

// vector<string> getAdj(string &str) {
//     str += ",";
//     vector<string> vec;
//     string prev = "";
//     for (char c : str) {
//         if (c == ',') {
//             vec.push_back(prev);
//             prev = "";
//             continue;
//         }

//         prev += c;
//     }

//     return vec;
// }

// int getScore(char c) {
//     if (isupper(c)) return (int) (c - 'A');
//     return (int) (c - 'a') + 26;
// }

// int main() {
//     string c, b, d;
//     cin >> c >> b >> d;

//     vector<string> country = getAdj(c);
//     vector<string> build = getAdj(b);
//     vector<string> destroy = getAdj(d);

//     for (auto i : country) {
//         for (auto j : i) cout << j << " ";
//         cout << endl;
//     }

//     cout << endl;

//     for (auto i : build)
//     {
//         for (auto j : i)
//             cout << j << " ";
//         cout << endl;
//     }

//     cout << endl;

//     for (auto i : destroy)
//     {
//         for (auto j : i)
//             cout << j << " ";
//         cout << endl;
//     }

//     cout << endl;

//     int n = destroy.size();
//     int totalCost = 0;

//     priority_queue<pair<int, pair<int, int>>> pq;

//     // mst
//     vector<bool> visited(n, false);
//     pq.push({0, {-1, 0}});

//     while (!pq.empty())
//     {
//         auto [cost, temp] = pq.top();
//         auto [par, dest] = temp;

//         pq.pop();

//         if (cost < 0) {
//             // build road
//             if (visited[dest]) continue; // already visited

//             totalCost += abs(cost);
//         } else if (visited[dest]) {
//             totalCost += cost;
//             continue;
//         }

//         visited[dest] = true;
//         cout << dest << endl;
//         for (int i = 0; i < n; i++) {
//             if (i == par || i == dest) continue;

//             if (country[dest][i] == '1') {
//                 // edge exists
//                 // cout << getScore(destroy[dest][i]) << " " << i << endl;
//                 pq.push({getScore(destroy[dest][i]), {dest, i}});
//             } else {
//                 // build edge
//                 pq.push({-1 * getScore(build[dest][i]), {dest, i}});
//             }
//         }
//     }

//     cout << totalCost << endl;
    
// }

#include <bits/stdc++.h>
using namespace std;

vector<string> getAdj(string &str)
{
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

int getScore(char c)
{
    if (isupper(c))
        return (int)(c - 'A');
    return (int)(c - 'a') + 26;
}

int main()
{
    string c, b, d;
    cin >> c >> b >> d;

    vector<string> country = getAdj(c);
    vector<string> build = getAdj(b);
    vector<string> destroy = getAdj(d);

    // for (auto i : country)
    // {
    //     for (auto j : i)
    //         cout << j << " ";
    //     cout << endl;
    // }

    // cout << endl;

    // for (auto i : build)
    // {
    //     for (auto j : i)
    //         cout << j << " ";
    //     cout << endl;
    // }

    // cout << endl;

    // for (auto i : destroy)
    // {
    //     for (auto j : i)
    //         cout << j << " ";
    //     cout << endl;
    // }

    // cout << endl;

    int n = destroy.size();
    int totalCost = 0;

    priority_queue<pair<int, pair<int, int>>> pq;

    // mst
    vector<bool> visited(n, false);
    pq.push({0, {-1, 0}});

    while (!pq.empty()) {
        auto [cost, temp] = pq.top();
        auto [par, dest] = temp;

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
        // cout << dest << endl;
        for (int i = 0; i < n; i++) {
            if (i == dest || country[dest][i] == '2') continue;

            if (country[dest][i] == '1') {
                // edge exists
                // cout << getScore(destroy[dest][i]) << " " << i << endl;
                pq.push({getScore(destroy[dest][i]), {dest, i}});
            }
            else if (country[dest][i] == '0')
            {
                // build edge
                pq.push({-1 * getScore(build[dest][i]), {dest, i}});
            }

            country[i][dest] = '2'; // process road
            country[dest][i] = '2';   // process road
        }
    }

    // for (auto i : country)
    // {
    //     for (auto j : i)
    //         cout << j << " ";
    //     cout << endl;
    // }

    cout << totalCost << endl;
}