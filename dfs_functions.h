#ifndef DFS_FUNCTIONS_H
#define DFS_FUNCTIONS_H

#include <bits/stdc++.h>

extern std::set<char> ss;
extern std::map<char, std::vector<std::vector<char>>> mp;
extern std::map<int, std::map<char, std::set<std::pair<std::deque<char>, std::deque<char>>>>> f;
extern std::map<int, std::vector<std::pair<int, char>>> g;
extern int num;
extern int start;
bool dfs(char i, char org, char last, std::map<char, std::vector<std::vector<char>>>& mp);
void dfs2(char c, char way, int last, std::pair<std::deque<char>, std::deque<char>> curr);
void displayProductionsAndEdges();

#endif