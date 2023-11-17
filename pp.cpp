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

map<char, vector<char> > findfirst(struct Prod Pr[], int p){
    map<char, vector<char> > first;
    vector<bool> visited(p, false);
    for(int i=0; i<p; i++){
        if(visited[i] == false && ( Pr[i].right[0] <'A' || Pr[i].right[0]>'Z') ){
            first[Pr[i].left].push_back(Pr[i].right[0]);
            visited[i] = true;
        }
        
    }
    while(allnotvisited(visited)){
        for(int i=0; i<p; i++){
            if(visited[i] == false && Pr[i].right[0] >='A' && Pr[i].right[0] <='Z'){
                if(first.find(Pr[i].right[0]) != first.end()){
                    int flag = 0, k=0;
                    do{
                        flag = 0;
                        vector<char> temp = first[Pr[i].right[k]];
                        for(int j=0; j<temp.size(); j++){
                            if(temp[j] == '#'){
                                flag = 1;
                                continue;
                            }
                            first[Pr[i].left].push_back(temp[j]);
                        }
                        k++;
                    } while(flag == 1 && k < Pr[i].right.size());
                    if(flag == 1){
                        first[Pr[i].left].push_back('#');
                    }
                    visited[i] = true;
                }
            }
        }
    }
    return first;
}

map<char, vector<char> > findfollow(struct Prod Pr[], int p, map<char, vector<char> > first){
    map<char, vector<char> > follow;
    /*for(int i=0; i<nt; i++){
        follow[Pr[i].left] = vector<char>();
    }*/
    follow[Pr[0].left].push_back('$');
    bool changed = true;
    while(changed){
        changed = false;
        for(int i=0; i<p; i++){
            for(int j=0; j<Pr[i].right.length(); j++){
                if(Pr[i].right[j] >= 'A' && Pr[i].right[j] <= 'Z'){
                    if(j == Pr[i].right.length() - 1){
                        for(int c=0; c<follow[Pr[i].left].size(); c++){
                            if(find(follow[Pr[i].right[j]].begin(), follow[Pr[i].right[j]].end(), follow[Pr[i].left][c]) == follow[Pr[i].right[j]].end()){
                                follow[Pr[i].right[j]].push_back(follow[Pr[i].left][c]);
                                changed = true;
                            }
                        }
                    } else {
                        if(Pr[i].right[j+1] >= 'A' && Pr[i].right[j+1] <= 'Z'){
                            vector<char> temp = first[Pr[i].right[j+1]];
                            bool hasEmpty = false;
                            for(int c=0; c<temp.size(); c++){
                                if(temp[c] == '#'){
                                    hasEmpty = true;
                                } else {
                                    if(find(follow[Pr[i].right[j]].begin(), follow[Pr[i].right[j]].end(), temp[c]) == follow[Pr[i].right[j]].end()){
                                        follow[Pr[i].right[j]].push_back(temp[c]);
                                        changed = true;
                                    }
                                }
                            }
                            if(hasEmpty){
                                for(int c=0; c<follow[Pr[i].left].size(); c++){
                                    if(find(follow[Pr[i].right[j]].begin(), follow[Pr[i].right[j]].end(), follow[Pr[i].left][c]) == follow[Pr[i].right[j]].end()){
                                        follow[Pr[i].right[j]].push_back(follow[Pr[i].left][c]);
                                        changed = true;
                                    }
                                }
                            }
                        } else {
                            if(find(follow[Pr[i].right[j]].begin(), follow[Pr[i].right[j]].end(), Pr[i].right[j+1]) == follow[Pr[i].right[j]].end()){
                                follow[Pr[i].right[j]].push_back(Pr[i].right[j+1]);
                                changed = true;
                            }
                        }
                    }
                }
            }
        }
    }
    return follow;
}

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
    cout << "Enter starting symbol: ";
    char start;
    cin >> start;
    cout << "Enter the no of Productions: ";
    cin >> p;
    struct Prod Pr[p];
    cout << "Enter the Productions: ";
    for(int i=0; i<p; i++){
        cin >> Pr[i].left;
        cin >> Pr[i].right;
    }
    map<char, vector<char> > first = findfirst(Pr, p);
    
    for(map<char, vector<char> >::iterator it = first.begin(); it != first.end(); it++){
        cout << it->first << " = { ";
        for(int i=0; i<it->second.size(); i++){
            cout << it->second[i] << ", ";
        }
        cout << " }" << endl;
    }
    cout<<endl;
    map<char, vector<char> > follow = findfollow(Pr, p, first);
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
