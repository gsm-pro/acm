#include<iostream>
#include<vector>
#include<string>
#include<set>
#include<queue>
using namespace std;
vector<multiset<int>> c(505);
vector<string> $;
int m, n, lastbox;

string type1(int from, int to) {
	return "1 " + to_string(from + 1) + " " + to_string(to + 1);
}

string type2(int from, int to) {
	return "2 " + to_string(from + 1) + " " + to_string(to + 1) + " " + to_string(to + 1);
}

vector<pair<string, int>> go2(int box) {
	vector<pair<string, int>> ans;
	queue<int> q;
	q.push(box);
	while (!q.empty()) {
		box = q.front();
		q.pop();
		if (!c[box].empty()) {
			int to = *c[box].begin();
			c[box].erase(c[box].begin());
			ans.push_back(make_pair(type2(box, to), to));
			q.push(to);
		}
	}
	return ans;
}

vector<string> go1(int box) {
	vector<string> ans;
	auto p = go2(box);
	for (auto it = p.begin(); it != p.end(); it++) {
		ans.push_back(it->first);
		if (!c[it->second].empty()) {
			auto q = go1(it->second);
			ans.insert(ans.end(), q.begin(), q.end());
		}
	}
	return ans;
}

int main() {
	cin >> m >> n;
	for (int box = 0, t; box < m; box++)
		for (int cube = 0; cube < n; cube++) {
			cin >> t;
			if ((--t) != box) c[box].insert(t);
		}
	for (int box = 0; box < m; box++)
		if (!c[box].empty()) {
			if (!$.empty()) $.push_back(type1(lastbox, box));
			auto r = go1(box);
			$.insert($.end(), r.begin(), r.end());
			string lastmove = $.back();
			lastbox = stoi(lastmove.substr(lastmove.find_last_of(' ') + 1)) - 1;
		}
	for (auto $$ : $) cout << $$ << endl;
}