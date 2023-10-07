#include<algorithm>
#include<cmath>
#include<iostream>
#include<vector>
using namespace std;
#define F first
#define S second

void dfs(vector<vector<int>>& g, vector<vector<bool>>& used, vector<int>& cycle, int v, int w) {
	for (size_t i = 0; i < g[v].size(); i++)
		if (g[v][i] == w) {
			if (++i == g[v].size()) i = 0;
			if (!used[v][i]) {
				used[v][i] = true;
				cycle.push_back(v);
				dfs(g, used, cycle, g[v][i], v);
			}
			break;
		}
}

int main() {
	int m;
	cin >> m;
	vector<pair<int, int>> a(m * 2);
	for (int i = 0; i < m; i++)
		scanf("%d%d%d%d", &a[i * 2].F, &a[i * 2].S, &a[i * 2 + 1].F, &a[i * 2 + 1].S);
	vector<pair<int, int>> ps(a);
	sort(ps.begin(), ps.end());
	ps.erase(unique(ps.begin(), ps.end()), ps.end());
	int n = (int)ps.size();
	vector<vector<int>> g(n);
	for (int i = 0; i < m; i++) {
		int id1 = int(lower_bound(ps.begin(), ps.end(), a[i * 2]) - ps.begin()),
			id2 = int(lower_bound(ps.begin(), ps.end(), a[i * 2 + 1]) - ps.begin());
		g[id1].push_back(id2), g[id2].push_back(id1);
	}
	for (int i = 0; i < n; i++) {
		vector<pair<double, int>> b(g[i].size());
		for (size_t j = 0; j < g[i].size(); j++) {
			int to = g[i][j];
			b[j].S = to;
			b[j].F = atan2(.0 + ps[to].S - ps[i].S, ps[to].F - ps[i].F);
		}
		sort(b.begin(), b.end());
		b.erase(unique(b.begin(), b.end()), b.end());
		g[i].clear();
		for (size_t j = 0; j < b.size(); j++) g[i].push_back(b[j].S);
	}
	vector<vector<bool>> used(n);
	for (int i = 0; i < n; i++) used[i].resize(g[i].size());
	vector<vector<int>> ans;
	for (int i = 0; i < n; i++)
		for (size_t j = 0; j < g[i].size(); j++)
			if (!used[i][j]) {
				vector<int> cycle;
				dfs(g, used, cycle, g[i][j], i);
				ans.push_back(cycle);
			}
	printf("%zu\n", ans.size());
	for (auto a : ans) {
		printf("%zu\n", a.size());
		for (auto aa : a) printf("%d %d\n", ps[aa].F, ps[aa].S);
		printf("\n");
	}
}