#include <bits/stdc++.h>
#include "dfs_functions.h"

#define error(x) cerr << #x << " = " << x << '\n'
using namespace std;

map<int, map<char, set<pair<deque<char>, deque<char>>>>> f;
map<int, vector<pair<int, char>>> g;
int num = -1;
int start;

bool dfs(char i, char org, char last, map<char, vector<vector<char>>>& mp) {
    bool rtake = false;
    for (auto r : mp[i]) {
        bool take = true;
        for (auto s : r) {
            if (s == i)
                break;
            if (!take)
                break;
            if (!(s >= 'A' && s <= 'Z') && s != 'e') {
                ss.insert(s);
                break;
            } else if (s == 'e') {
                if (org == i || i == last)
                    ss.insert(s);
                rtake = true;
                break;
            } else {
                take = dfs(s, org, r[r.size() - 1], mp);
                rtake |= take;
            }
        }
    }
    return rtake;
}
void dfs2(char c, char way, int last, pair<deque<char>, deque<char>> curr) {
    map<char, set<pair<deque<char>, deque<char>>> > mp2;
    int rep = -2;
    if (last != -1) {
        for (auto q : g[last]) {
            if (q.second == way) {
                rep = q.first;
                mp2 = f[q.first];
            }
        }
    }
   mp2[c].insert(curr);
    int count = 10; 
    while (count--) {
        for (auto q : mp2) {
            for (auto r : q.second) {
                if (!r.second.empty()) {
                    if (r.second.front() >= 'A' && r.second.front() <= 'Z') {
                        for (auto s : mp[r.second.front()]) {
                            deque<char> st, emp;
                            for (auto t : s)
                                st.push_back(t);
                            mp2[r.second.front()].insert({emp, st});
                        }
                    }
                }
            }
        }
    }
    for (auto q : f) {
        if (q.second == mp2) {
            g[last].push_back({q.first, way});
            return;
        }
    }
    if (rep == -2) {
        f[++num] = mp2;
        if (last != -1)
            g[last].push_back({num, way});
    } else {
        f[rep] = mp2;
    }
    int cc = num; 
    for (auto q : mp2) {
        for (auto r : q.second) {
            if (!r.second.empty()) {
                r.first.push_back(r.second.front());
                r.second.pop_front();
                dfs2(q.first, r.first.back(), cc, r);
            }
        }
    }
}



