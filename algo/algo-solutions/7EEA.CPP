#define _CRT_SECURE_NO_DEPRECATE
#include<iostream>
#include<vector>
#include<map>
using namespace std;
typedef long long LL;
const int N = 111111;
const int INF = (1 << 30);
LL ans[N];
int n, color[N], u, v;
vector<int> g[N];

void dfs(int u, int from, map<int, LL> &m) {
	for (size_t j = 0; j < g[u].size(); j++) {
		int v = g[u][j];
		if (v == from) {
			continue;
		}
		map<int, LL> h;
		dfs(v, u, h);
		if (h.size() > m.size()) {
			m.swap(h);
		}
		for (map<int, LL>::iterator it = h.begin(); it != h.end(); it++) {
			if (it->first >= INF) {
				continue;
			}
			m[it->first] += it->second;
			if (m[it->first] > m[INF]) {
				m[INF] = m[it->first];
				m[INF + 1] = it->first;
			}
			else {
				if (m[it->first] == m[INF]) {
					m[INF + 1] += it->first;
				}
			}
		}
	}
	m[color[u]]++;
	if (m[color[u]] > m[INF]) {
		m[INF] = m[color[u]];
		m[INF + 1] = color[u];
	}
	else {
		if (m[color[u]] == m[INF]) {
			m[INF + 1] += color[u];
		}
	}
	ans[u] = m[INF + 1];
}

int main() {
	scanf("%d", &n);
	for (int i = 1; i <= n; ++i) {
		scanf("%d", &color[i]);
	}
	for (int i = 1; i < n; ++i) {
		scanf("%d%d", &u, &v);
		g[u].push_back(v);
		g[v].push_back(u);
	}
	map<int, LL> m;
	dfs(1, 1, m);
	for (int i = 1; i <= n; ++i) {
		printf("%lld ", ans[i]);
	}
}