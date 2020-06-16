#include<vector>
#include<iostream>
#include<algorithm>
using namespace std;
#define forn(i, n) for(int i = 0; i < int(n); i++)
#define MAXN 111111
#define oo (1 << 25)
vector<int> g[MAXN];
int tin[MAXN], tout[MAXN], path[MAXN], p[MAXN], pos[MAXN], root[MAXN], sz[MAXN], treesz[MAXN];
int tmp[MAXN * 4], *tree[MAXN], trees = 1, timer = 1, ptr = 0;
vector<int> ans;

void dfs(int v) {
	tin[v] = timer++;
	forn(i, g[v].size()) {
		int u = g[v][i];
		if (tin[u] <= 0) {
			dfs(u);
			p[u] = v;
			sz[v] += sz[u];
		}
	}
	tout[v] = timer++;
}

void hld(int v, int path_number) {
	path[v] = path_number;
	pos[v] = treesz[path_number]++;
	int mxu = -1, mxsz = -1;
	forn(i, g[v].size()) {
		int u = g[v][i];
		if (tin[v] < tin[u] && sz[u] > mxsz) {
			mxsz = sz[u], mxu = u;
		}
	}
	if (mxu >= 0) {
		hld(mxu, path_number);
	}
	forn(i, g[v].size()) {
		int u = g[v][i];
		if (tin[v] < tin[u] && u != mxu) {
			root[trees] = u;
			int pn = trees++;
			hld(u, pn);
		}
	}
}

inline void update(int t, int v, int x) {
	v += treesz[t];
	int *tt = tree[t];
	tt[v] += x;
	v >>= 1;
	while (v) {
		tt[v] = max(tt[v << 1], tt[1 + (v << 1)]);
		v >>= 1;
	}
}

inline int rmq(int t, int l, int r) {
	int res = 0, *tt = tree[t];
	for (l += treesz[t], r += treesz[t]; l <= r; l >>= 1, r >>= 1) {
		if ((l & 1) == 1) {
			res = max(res, tt[l++]);
		}
		if ((r & 1) == 0) {
			res = max(res, tt[r--]);
		}
	}
	return res;
}

int main() {
	int n, queries, x, y, w;
	scanf_s("%d", &n);
	int edges_count = n - 1;
	vector<pair<int, int>> inc_queries;
	forn(i, edges_count) {
		scanf_s("%d%d%d", &x, &y, &w);
		--x, --y;
		g[x].push_back(n);
		g[n].push_back(x);
		g[y].push_back(n);
		g[n].push_back(y);
		inc_queries.push_back(make_pair(n, oo - w));
		++n;
	}
	dfs(0);
	hld(0, 0);
	forn(i, trees) {
		tree[i] = &tmp[ptr];
		ptr += (treesz[i] << 1);
	}
	for (int i = 0; i < (int)inc_queries.size(); i++) {
		int v = inc_queries[i].first;
		update(path[v], pos[v], inc_queries[i].second);
	}
	scanf_s("%d", &queries);
	for (int i = 0; i < queries; i++) {
		scanf_s("%d%d", &x, &y);
		--x, --y;
		int res = 0;
		forn(var, 2) {
			while (1) {
				int v = root[path[x]];
				if (tin[v] <= tin[y] && tout[y] <= tout[v]) {
					break;
				}
				res = max(res, rmq(path[x], 0, pos[x]));
				x = p[v];
			}
			swap(x, y);
		}
		if (pos[y] < pos[x]) {
			swap(x, y);
		}
		ans.push_back(oo - max(res, rmq(path[x], pos[x], pos[y])));
	}
	for (int i = 0; i < queries; i++) {
		printf("%d ", ans[i]);
	}
}