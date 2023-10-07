#include<bits/stdc++.h>
using namespace std;
#define pb push_back
#define mp make_pair
#define sz(a) (int)(a).size()
#define forn(i, n) for (int i = 0; i < int(n); i++)

struct edge {
	int from, to, cap, flow;
};

int n, m, x, NM, S, T, LL = 0, d[222], r[222], q[222];
vector<edge> e;
vector<vector<int>> g;

void addEdge(int a, int b, int c) {
	edge e1 = { a, b, c, 0 };
	edge e2 = { b, a, 0, 0 };
	g[a].pb(sz(e));
	e.pb(e1);
	g[b].pb(sz(e));
	e.pb(e2);
}

void split(int a, int b, int l, int r) {
	addEdge(S, b, l);
	addEdge(a, T, l);
	addEdge(a, b, r - l);
}

bool bfs() {
	int qh = 0, qt = 0;
	q[qt++] = S;
	memset(d, -1, sizeof d);
	d[S] = 0;
	while (qh < qt && d[T] == -1) {
		int v = q[qh++];
		forn(i, sz(g[v])) {
			int rib = g[v][i], to = e[rib].to,
				cap = e[rib].cap, flow = e[rib].flow;
			if (d[to] == -1 && cap - flow > 0)
				q[qt++] = to, d[to] = d[v] + 1;
		}
	}
	return d[T] != -1;
}

int dfs(int v, int flow) {
	if (flow) {
		if (v == T) return flow;
		for (; r[v] < sz(g[v]); r[v]++) {
			int rib = g[v][r[v]], to = e[rib].to,
				tCap = e[rib].cap, tFlow = e[rib].flow;
			if (d[to] != d[v] + 1) continue;
			int push = dfs(to, min(flow, tCap - tFlow));
			if (push) {
				e[rib].flow += push, e[rib ^ 1].flow -= push;
				return push;
			}
		}
	}
	return 0;
}

void calcFlow() {
	while (true) {
		if (!bfs()) break;
		memset(r, 0, sizeof r);
		while (dfs(S, 1000000000));
	}
}

bool check(int k) {
	e[sz(e) - 1].cap = e[sz(e) - 2].cap = k;
	forn(i, sz(e)) e[i].flow = 0;
	calcFlow();
	int res = 0;
	forn(i, sz(g[S])) res += max(e[g[S][i]].flow, 0);
	return res >= LL;
}

int main() {
	scanf("%d%d%d", &n, &m, &x);
	NM = n + m;
	vector<pair<int, int>> rib;
	for (int i = 0, u, v; i < x; i++) {
		scanf("%d%d", &u, &v);
		rib.push_back(make_pair(u + 1, v + 1 + n));
	}
	for (int i = 1; i <= n; i++) rib.push_back(make_pair(1, i + 1));
	for (int i = 1; i <= m; i++) rib.push_back(make_pair(n + 1 + i, n + m + 2));
	n += (m + 2), m = sz(rib);
	g.resize(n + 2);
	S = n, T = n + 1;
	vector<pair<int, int>> order;
	forn(i, m) {
		int a = rib[i].first - 1, b = rib[i].second - 1,
			L = (a == 0 || b == n - 1 ? 2 : 0),
			R = (a == 0 || b == n - 1 ? 1000 : 1);
		if (L == 0) {
			order.pb(mp(sz(e), sz(e) + 1));
			addEdge(a, b, R);
		}
		else {
			order.pb(mp(-1, L));
			split(a, b, L, R);
			LL += L;
		}
	}
	addEdge(n - 1, 0, 1000000000);
	int l = 0, r = 1000000, k;
	while (r - l > 1) {
		k = (l + r) / 2;
		if (check(k)) r = k; else l = k;
	}
	k = -1;
	if (check(r)) k = r;
	if (check(l)) k = l;
	if (k == -1) return cout << 0, 0;
	check(k);
	vector<int> ans;
	forn(i, m - NM) {
		int fs = order[i].first, sc = order[i].second,
			flow = (fs == -1 ? sc : max(e[fs].flow, 0) + max(e[sc].flow, 0));
		if (flow) ans.push_back(i + 1);
	}
	cout << sz(ans) << endl;
	copy(ans.begin(), ans.end(), ostream_iterator<int>(cout, " "));
}