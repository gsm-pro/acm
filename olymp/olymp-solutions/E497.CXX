#include<bits/stdc++.h>
using namespace std;
ifstream I("input.txt");
ofstream O("output.txt");
vector<vector<pair<int, int>>> g;
map<pair<int, int>, vector<pair<int, int>>> rib;
vector<int> $;
int n, m, ans = 0;

vector<int> dij(int s = 0) {
	vector<int> d(n, 1100000000);
	d[s] = 0;
	priority_queue<pair<int, int>> q;
	q.push({ 0, s });
	while (!q.empty()) {
		int curV = q.top().second,
			curD = -q.top().first;
		q.pop();
		if (curD > d[curV]) continue;
		for (auto e : g[curV]) {
			int to = e.first, len = e.second;
			if (d[curV] + len < d[to]) {
				d[to] = d[curV] + len;
				q.push({ -d[to], to });
			}
		}
	}
	return d;
}

int main() {
	I >> n >> m;
	g.resize(n);
	for (int i = 1, u, v, w; i <= m; i++) {
		I >> u >> v >> w;
		u--, v--;
		rib[{min(u, v), max(u, v)}].push_back({ w, i });
	}
	for (auto it = rib.begin(); it != rib.end(); it++)
		sort(it->second.begin(), it->second.end());
	for (auto it = rib.begin(); it != rib.end(); it++) {
		int u = it->first.first,
			v = it->first.second,
			w = it->second[0].first;
		g[u].push_back({ v, w });
		g[v].push_back({ u, w });
		if (it->second.size() >= 2) {
			auto it2 = ++it->second.begin();
			for (; it2 != it->second.end(); it2++) {
				$.push_back(it2->second);
				ans += it2->first;
			}
		}
	}
	auto dijD = dij();
	set<pair<int, int>> tree, candidates;
	for (int v = 1, len; v < n; v++) {
		candidates.clear();
		for (int p = 0; p < n; p++)
			if (p != v
				&& rib.count({ min(v, p), max(v, p) })
				&& dijD[p] + (len = rib[{min(v, p), max(v, p)}].begin()->first) == dijD[v])
				candidates.insert({ len, p });
		int pp = candidates.begin()->second;
		tree.insert({ min(v, pp), max(v, pp) });
	}
	for (auto it = rib.begin(); it != rib.end(); it++) {
		int u = it->first.first,
			v = it->first.second;
		if (!tree.count({ u, v })) {
			$.push_back(it->second[0].second);
			ans += it->second[0].first;
		}
	}
	O << ans << " " << $.size() << endl;
	copy($.begin(), $.end(), ostream_iterator<int>(O, " "));
}