#include <bits/stdc++.h>
#include "dfs_functions.h"
#define error(x) cerr << #x << " = " << x << '\n'
using namespace std; 

set<char> ss;
map<char, vector<vector<char>> > mp; 

int main()
{
    int i, j;
    ifstream fin("grammar.txt");
    string num;
    vector<int> fs;
    vector<vector<int>> a;
    bool flag = 0;
    cout <<"Grammar: "<<'\n';
    while (getline(fin, num))
    {
        if (flag == 0)
            start = num[0], flag = 1;
        cout <<num<<'\n';
        vector<char> temp;
        char s = num[0];
        for (i = 3; i<num.size(); i++)
        {
            if (num[i] == '|')
            {
                mp[s].push_back(temp);
                temp.clear();
            }
            else
                temp.push_back(num[i]);
        }
        mp[s].push_back(temp);
    }
    map<char, set<char>> fmp;
    for (auto q : mp)
    {
        ss.clear();
        dfs(q.first, q.first, q.first, mp);
        for (auto g : ss)
            fmp[q.first].insert(g);
    }
    cout <<'\n';
    cout <<"FIRST: "<<'\n';
    for (auto q : fmp)
    {
        string ans = "";
        ans += q.first;
        ans += " = {";
        for (char r : q.second)
        {
            ans += r;
            ans += ',';
        }
        ans.pop_back();
        ans += "}";
        cout <<ans<<'\n';
    }
    map<char, set<char>> gmp;
    gmp[start].insert('$');
    int count = 10;
     while (count--)
    {
        for (auto q : mp)
        {
            for (auto r : q.second)
            {
                for (i = 0; i<r.size() - 1; i++)
                {
                    if (r[i] >= 'A'&&r[i] <= 'Z')
                    {
                        if (!(r[i + 1] >= 'A'&&r[i + 1] <= 'Z'))
                        {
                            gmp[r[i]].insert(r[i + 1]);
                        }
                        else
                        {
                            char temp = r[i + 1];
                            int j = i + 1;
                            while (temp>= 'A'&&temp<= 'Z')
                            {
                                if (*fmp[temp].begin() == 'e')
                                {
                                    for (auto g : fmp[temp])
                                    {
                                        if (g == 'e')
                                            continue;
                                        gmp[r[i]].insert(g);
                                    }
                                    j++;
                                    if (j<r.size())
                                    {
                                        temp = r[j];
                                        if (!(temp>= 'A'&&temp<= 'Z'))
                                        {
                                            gmp[r[i]].insert(temp);
                                            break;
                                        }
                                    }
                                    else
                                    {
                                        for (auto g : gmp[q.first])
                                            gmp[r[i]].insert(g);
                                        break;
                                    }
                                }
                                else
                                {
                                    for (auto g : fmp[temp])
                                    {
                                        gmp[r[i]].insert(g);
                                    }
                                    break;
                                }
                            }
                        }
                    }
                }
  if (r[r.size() - 1] >= 'A'&&r[r.size() - 1] <= 'Z')
 {
                    for (auto g : gmp[q.first])
                        gmp[r[i]].insert(g);
                }
            }
        }
    }
    cout <<'\n';
    cout <<"FOLLOW: "<<'\n';
    for (auto q : gmp)
    {
        string ans = "";
        ans += q.first;
        ans += " = {";
        for (char r : q.second)
        {
            ans += r;
            ans += ',';
        }
        ans.pop_back();
        ans += "}";
        cout <<ans<<'\n';
    }
    string temp = "";
    temp += '.';
    temp += start;
    deque<char> emp;
    deque<char> st;
    st.push_back(start);
    dfs2('!', 'k', -1, {emp, st});
    cout <<"\nProductions: "<<'\n';
    int cc = 1;
    set<char> action, go;
    map<pair<char, deque<char>>, int> pos;
    for (auto q : mp)
    {
        go.insert(q.first);
        for (auto r : q.second)
        {
            cout <<"r"<<cc<<": ";
            string ans = "";
            ans += q.first;
            ans += "->";
            deque<char>temp;
            for (auto s : r)
                ans += s, temp.push_back(s);
            pos[{q.first, temp}] = cc;
            for (auto s : r)
            {
                if (s>= 'A'&&s<= 'Z')
                    go.insert(s);
                else
                    action.insert(s);
            }
            cout <<ans<<'\n';
            cc++;
        }
    }
    cout <<"\nGraph: "<<'\n';
 for (auto mp2 : f)
    {
        cout <<'\n';
        cout <<"I";
        cout <<mp2.first<<": \n";
        for (auto q : mp2.second)
        {
            string ans = "";
            ans += q.first;
            ans += "->";
            for (auto r : q.second)
            {
                for (auto t : r.first)
                    ans += t;
                ans += '.';
                for (auto t : r.second)
                    ans += t;
                ans += '|';
            }
            ans.pop_back();
            for (auto tt : ans)
            {
                if (tt == '!')
                    cout <<start<<'\'';
                else
                    cout <<tt;
            }
            cout <<'\n';
        }
    }
    cout <<'\n';
    cout <<"Edges: "<<'\n';
    for (auto q : g)
    {
        for (auto r : q.second)
        {
            cout <<"I"<<q.first<<" -> "<<r.second<<" -> "
                 <<"I"<<r.first<<"\n";
        }
    }
    action.insert('$');
    cout <<"\nParsing Table:"<<'\n';
    cout <<"St.\t\tAction & Goto"<<'\n';
 int tot = f.size();
    cout <<"  \t";
    for (auto q : action)
        cout <<q<<'\t';
    for (auto q : go)
        cout <<q<<'\t';
    cout <<'\n';
    for (i = 0; i<tot; i++)
    {
        cout <<"I"<<i<<'\t';
        for (auto q : action)
        {
            if (g.count(i))
            {
                int flag = 0;
                for (auto r : g[i])
                {
                    if (r.second == q)
                    {
                        flag = 1;
                        cout <<"S"<<r.first<<"\t";
                        break;
                    }
                }
                if (!flag)
                    cout <<"-"<<'\t';
            }
            else
            {
                int flag = 0;
                for (auto r : f[i])
                {
 if (r.first == '!')
                    {
                        if (q == '$')
                        {
                            cout <<"AC\t";
                            flag = 1;
                        }
                        else
                            cout <<"-\t";
                    }
                }
 if (!flag)
                {
                    for (auto r : f[i])
                    {
                        char ccc = r.first;
                        deque<char> chk = (*r.second.begin()).first;
                        int cou = 1;
                        for (auto r : gmp[ccc])
                        {
                            if (q == r)
                            {
                                cout <<"r"<<pos[{ccc, chk}] <<"\t";
                            }
 cou++;
                        }
                    }
                }
            }
        }
        for (auto q : go)
        {
            if (g.count(i))
            {
                int flag = 0;
                for (auto r : g[i])
                {
                    if (r.second == q)
                    {
                        flag = 1;
                        cout <<r.first<<"\t";
                        break;
                    }
                }
                if (!flag)
                    cout <<"-"<<'\t';
            }
            else
            {
                cout <<"-"<<'\t';
            }
        }
        cout <<'\n';
    }
    return 0;
}
