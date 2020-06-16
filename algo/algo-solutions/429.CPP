#include<iostream>
#include<string>
#include<vector>
#include<set>
#include<map>
#include<stack>
using namespace std;
#define ALPH 26
set<int> d[ALPH];
set<int> dd[ALPH][ALPH];
int in[ALPH], out[ALPH];
vector<string> wrd;
string w;
map<int, pair<int, int>> rib;
vector<int> path;
vector<string> ans;

int main() {
	int n;
	cin >> n;
	w.resize(n);
	for (int i = 0; i < n; i++) {
		cin >> w;
		wrd.push_back(w);
		int from = w[0] - 'a', to = w[w.length() - 1] - 'a';
		d[from].insert(i);
		dd[from][to].insert(i);
		rib[i] = make_pair(from, to);
		in[to]++;
		out[from]++;
	}
	bool eulerCycle = true;
	for (int i = 0; i < ALPH; i++) {
		if (in[i] != out[i]) {
			eulerCycle = false;
		}
	}
	int start = -1;
	if (eulerCycle) {
		start = (w[0] - 'a');
	}
	else {
		int finish = -1;
		bool eulerPath = true;
		for (int i = 0; i < ALPH; i++) {
			if (in[i] == out[i] - 1 && start != -1) {
				eulerPath = false;
			}
			else {
				if (in[i] == out[i] - 1 && start == -1) {
					start = i;
				}
				else {
					if (in[i] == out[i] + 1 && finish != -1) {
						eulerPath = false;
					}
					else {
						if (in[i] == out[i] + 1 && finish == -1) {
							finish = i;
						}
						else {
							if (in[i] != out[i]) {
								eulerPath = false;
							}
						}
					}
				}
			}
		}
		if (start == -1 || finish == -1 || !eulerPath) {
			cout << "NO";
			return 0;
		}
	}
	stack<int> st;
	st.push(start);
	while (!st.empty()) {
		int from = st.top();
		bool found = false;
		for (set<int>::iterator it = d[from].begin(); it != d[from].end(); it++) {
			found = true;
			int to = rib[*it].second;
			st.push(to);
			d[from].erase(it);
			break;
		}
		if (!found) {
			st.pop();
			path.push_back(from);
		}
	}
	reverse(path.begin(), path.end());
	for (int i = 1; i < (int)path.size(); i++) {
		int from = path[i - 1], to = path[i];
		if (dd[from][to].size() > 0) {
			set<int>::iterator it = dd[from][to].begin();
			ans.push_back(wrd[*it]);
			dd[from][to].erase(it);
		}
	}
	if (ans.size() != n) {
		cout << "NO";
		return 0;
	}
	for (vector<string>::iterator it = ans.begin(); it != ans.end(); it++) {
		cout << *it << endl;
	}
}