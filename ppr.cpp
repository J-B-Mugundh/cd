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


map<char, map<char, string> > generateparsingtable(map<char, vector<char> > first, map<char, vector<char> > follow, struct Prod Pr[], int p){
	map<char, map<char, string> > pars_table;
	for(int i=0; i<p; i++){
		string s = Pr[i].right;
		if((Pr[i].right[0] < 'A' || Pr[i].right[0] > 'Z' ) && Pr[i].right[0] != '#'){
			//cout << s << endl;
			pars_table[Pr[i].left][Pr[i].right[0]] = s;
		}
		if(Pr[i].right[0] >= 'A' && Pr[i].right[0] <= 'Z'){
			//cout << s << endl;
			vector<char> temp = first[Pr[i].right[0]];
			for(int c=0; c<temp.size(); c++){
				pars_table[Pr[i].left][temp[c]] = s;
			}
		}
		if(Pr[i].right[0] == '#'){
			vector<char> temp = follow[Pr[i].left];
			//cout << s << endl;
			for(int c=0; c<temp.size(); c++){
				pars_table[Pr[i].left][temp[c]] = s;
			}
		}
	}
	return pars_table;
}

int main(){
    int p;
    int ch;
    char start;
    struct Prod Pr[p];
    map<char, vector<char> > first;
    map<char, vector<char> > follow;

    cout << "Enter 1 for user input and 2 for default input: ";
    cin >> ch;
    switch(ch){
        case 1:
            cout << "Enter starting symbol: ";
            cin >> start;
            cout << "Enter the no of Productions: ";
            cin >> p;
            cout << "Enter the Productions: ";
            for(int i=0; i<p; i++){
                cin >> Pr[i].left;
                cin >> Pr[i].right;
            }
            int n;
            for(int i=0;i<n;i++){
                char nonTerminal;
                cout << "Enter Non-terminal: ";
                cin >> nonTerminal;
                vector<char> firstSet;
                vector<char> followSet;
                cout << "Enter the no of elements in first set: ";
                cin >> n;
                cout << "Enter the elements of first set: ";
                for(int i=0; i<n; i++){
                    char c;
                    cin >> c;
                    firstSet.push_back(c);
                }
                first[nonTerminal] = firstSet;
                cout << "Enter the no of elements in follow set: ";
                cin >> n;
                cout << "Enter the elements of follow set: ";
                for(int i=0; i<n; i++){
                    char c;
                    cin >> c;
                    followSet.push_back(c);
                }
                follow[nonTerminal] = followSet;
            }
            break;
        case 2:
            p = 8;
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
            break;         
    }

    cout << "Productions: " << endl;
    for(int i=0;i<p;i++)
    {
    	cout<<Pr[i].left<<"->"<<Pr[i].right<<endl;
    }
    
    cout << "First sets: " << endl;
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
    
    map<char, map<char, string> > pars_table = generateparsingtable(first, follow, Pr, p);

    cout << "\nParsing Table: "<<endl;
    for(map<char, map<char, string> >::iterator it = pars_table.begin(); it != pars_table.end(); it++){
	cout << it->first << "\t";
	map <char, string> temp = it->second;
	for( map<char, string>::iterator it2 = temp.begin(); it2 != temp.end(); it2++){
	    cout << it2->first << " : " << it2->second << "\t";
	}
	cout << endl;
    }
    
    return 0;
}