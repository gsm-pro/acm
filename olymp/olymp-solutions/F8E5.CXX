#include<fstream>
#include<vector>
#include<map>
#include<queue>
#include<algorithm>
using namespace std;
typedef pair<short, pair<short, short>> entry;
priority_queue<entry, vector<entry>, greater<entry>> pq;
map<short, vector<short>> ans, leavesGraph;
vector<short> replacements, component;
short n;

void u() {
	short v = pq.top().second.first, w = pq.top().second.second;
	pq.pop();
	while (replacements[v] != -1) v = replacements[v];
	while (replacements[w] != -1) w = replacements[w];
	leavesGraph[v].push_back(w);
	leavesGraph[w].push_back(v);
}

int main() {
	ifstream I("input.txt");
	ofstream O("output.txt");
	I >> n;
	replacements.assign(555, -1);
	for (short i = 0, v; i < n; i++) {
		for (short j = 0; j < n; j++) {
			I >> v;
			if (i == j) ans[i].push_back(v);
			if (i < j) pq.push(make_pair(v, make_pair(i, j)));
		}
	}
	while (!pq.empty()) {
		short curSalary = pq.top().first;
		leavesGraph.clear();
		u();
		while (!pq.empty() && pq.top().first == curSalary) u();
		vector<bool> used(555, false);
		for (auto it = leavesGraph.begin(); it != leavesGraph.end(); it++) {
			sort(it->second.begin(), it->second.end());
			it->second.erase(unique(it->second.begin(), it->second.end()), it->second.end());
		}
		for (auto it1 = leavesGraph.begin(); it1 != leavesGraph.end(); it1++) {
			if (used[it1->first]) continue;
			component.clear();
			queue<short> q;
			used[it1->first] = true;
			component.push_back(it1->first);
			q.push(it1->first);
			while (!q.empty()) {
				short v = q.front();
				q.pop();
				for (auto it2 = leavesGraph[v].begin(); it2 != leavesGraph[v].end(); it2++) {
					if (used[*it2]) continue;
					used[*it2] = true;
					component.push_back(*it2);
					q.push(*it2);
				}
			}
			short newNode = (short)ans.size();
			ans[newNode].push_back(curSalary);
			for (auto it3 = component.begin(); it3 != component.end(); it3++) {
				if (curSalary <= ans[*it3][0]) return O << "NO SOLUTION", 0;
				replacements[*it3] = newNode;
				ans[newNode].push_back(*it3 + 1);
			}
		}
	}
	O << ans.size() << endl;
	for (auto it = ans.begin(); it != ans.end(); it++) {
		O << it->first + 1 << " ";
		for (short i = 0; i < it->second.size(); i++) O << it->second[i] << " ";
		O << endl;
	}
}