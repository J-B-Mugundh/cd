#include<iostream>
#include<vector>
#include<map>
#include<algorithm>
#include <bits/stdc++.h>

using namespace std;

struct Prod{
    char left;
    string right;
};

bool allnotvisited(vector<bool> visited){
    for(int i=0; i<visited.size(); i++){
        if(visited[i] == false)
            return true;
    }
    return false;
}

string printstack(stack<char> st){
	string s = "";
	while(!st.empty()){
		s = st.top() + s;
		st.pop();
	}
	return s;
}

bool checkstring(char start, string in, map<char, map<char, string> > pars_table){
	stack<char> st;
	st.push('$');
	st.push(start);
	int i=0;
	cout << "$" << start << " \t::\t " << in << endl;
	while(i < in.length()){
		if(st.top() == '$' && in[i] == '$'){
			return true;
		}
		else if(st.top() == '$'){
			return false;
		}
		else if(st.top() == in[i]){
			i++;
			st.pop();
		}
		else if( pars_table[st.top()].find(in[i]) != pars_table[st.top()].end()){
			if(pars_table[st.top()][in[i]] == "#"){
				st.pop();
			}
			else{
				string s = pars_table[st.top()][in[i]] ;
				st.pop();
				for(int j=s.length()-1; j>-1; j-- ){
					st.push(s[j]);
				}
			}
		}
		else{
			return false;
		}
		cout << printstack(st) << " \t::\t " << in.substr(i, in.length()-i) << endl;
	}
	return true;
	
}


int main(){
    int p=8;
    int ch;
    char start;
    vector<Prod> Pr(p);
    map<char, vector<char> > first;
    map<char, vector<char> > follow;    
    map<char, map<char, string> > pars_table;

    start='E';
    Pr[0].left = 'E';
    Pr[0].right = "TX";
    Pr[1].left = 'X';
    Pr[1].right = "+TX";
    Pr[2].left = 'X';
    Pr[2].right = "#";
    Pr[3].left = 'T';
    Pr[3].right = "FY";
    Pr[4].left = 'Y';
    Pr[4].right = "*FY";
    Pr[5].left = 'Y';
    Pr[5].right = "#";
    Pr[6].left = 'F';
    Pr[6].right = "(E)";
    Pr[7].left = 'F';
    Pr[7].right = "i";

    first['E'] = { '(', 'i', '}' };
    first['F'] = { '(', 'i', '}' };
    first['T'] = { '(', 'i', '}' };
    first['X'] = { '+', '#', '}' };
    first['Y'] = { '*', '#', '}' };

    follow['E'] = { '$', ')' };
    follow['F'] = { '*', '+', '$', ')' };
    follow['T'] = { '+', '$', ')' };
    follow['X'] = { '$', ')' };
    follow['Y'] = { '+', '$', ')' };

    pars_table = {
        {'E', { {'(', "TX"}, {'i', "TX"}, {'}', "TX"} }},
        {'F', { {'(', "(E)"}, {'i', "i"} }},
        {'T', { {'(', "FY"}, {'i', "FY"}, {'}', "FY"} }},
        {'X', { {'$', "#"}, {')', "#"}, {'+', "+TX"} }},
        {'Y', { {'$', "#"}, {')', "#"}, {'*', "*FY"}, {'+', "#"} }}
    };

    cout << "Productions: " << endl;
    for(int i=0;i<p;i++)
    {
    	cout<<Pr[i].left<<"->"<<Pr[i].right<<endl;
    }
    
    for(map<char, vector<char> >::iterator it = first.begin(); it != first.end(); it++){
        cout << it->first << " = { ";
        for(int i=0; i<it->second.size(); i++){
            cout << it->second[i] << ", ";
        }
        cout << " }" << endl;
    }
    cout<<endl;

    cout << "Follow sets: " << endl;
    for(map<char, vector<char> >::iterator it = follow.begin(); it != follow.end(); it++){
        cout << it->first << " = { ";
        for(int i=0; i<it->second.size(); i++){
            cout << it->second[i] << ", ";
        }
        cout << " }" << endl;
    }

    cout << "\nParsing Table: "<<endl;
    for(map<char, map<char, string> >::iterator it = pars_table.begin(); it != pars_table.end(); it++){
	cout << it->first << "\t";
	map <char, string> temp = it->second;
	for( map<char, string>::iterator it2 = temp.begin(); it2 != temp.end(); it2++){
	    cout << it2->first << " : " << it2->second << "\t";
	}
	cout << endl;
    }

    string in;
    cout << "Enter the input string: ";
    cin >> in;
    in += '$';
    if(checkstring(start, in, pars_table)){
    	printf("String is accepted..");
	}
	else
		printf("String is not accepted...");
    return 0;
}