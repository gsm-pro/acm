#include<iostream>
#include<vector>
using namespace std;
int const NMAX = 444444;
int const MOD = 1000000007;
int sum[NMAX], sq[NMAX], down[NMAX], tin[NMAX], tout[NMAX], ans[NMAX], n, q;
vector<pair<int, int>> g[NMAX], qs[NMAX];

void add(int &a, int b) {
	if ((a += b) >= MOD) {
		a -= MOD;
	}
}

int mul(int a, int b) {
	return ((__int64)a) * b % MOD;
}

void apply(int v, int l, int r, int val) {
	add(sq[v], mul(2, mul(sum[v], val)));
	add(sq[v], mul(val, mul(val, r - l)));
	add(sum[v], mul(val, r - l));
	add(down[v], val);
}

void push(int v, int l, int r) {
	int m = (l + r) >> 1;
	apply(2 * v + 1, l, m, down[v]);
	apply(2 * v + 2, m, r, down[v]);
	down[v] = 0;
}

void add(int v, int l, int r, int from, int to, int val) {
	if (r <= from || to <= l) {
		return;
	}
	if (from <= l && r <= to) {
		apply(v, l, r, val);
		return;
	}
	push(v, l, r);
	int m = (l + r) >> 1;
	add(2 * v + 1, l, m, from, to, val);
	add(2 * v + 2, m, r, from, to, val);
	sum[v] = sum[2 * v + 1] + sum[2 * v + 2];
	add(sum[v], 0);
	sq[v] = sq[2 * v + 1] + sq[2 * v + 2];
	add(sq[v], 0);
}

int getSq(int v, int l, int r, int from, int to) {
	if (r <= from || to <= l) {
		return 0;
	}
	if (from <= l && r <= to) {
		return sq[v];
	}
	push(v, l, r);
	int m = (l + r) >> 1;
	int ans = getSq(2 * v + 1, l, m, from, to) + getSq(2 * v + 2, m, r, from, to);
	add(ans, 0);
	return ans;
}

void dfs(int v, int par) {
	static int timer = 0;
	tin[v] = timer++;
	for (size_t i = 0; i < g[v].size(); i++) {
		pair<int, int> e = g[v][i];
		if (e.first != par) {
			dfs(e.first, v);
			add(0, 0, n, tin[e.first], tout[e.first], e.second);
		}
	}
	tout[v] = timer;
}

void calc(int v, int par) {
	for (size_t i = 0; i < qs[v].size(); i++) {
		pair<int, int> q = qs[v][i];
		int cur = getSq(0, 0, n, tin[q.first], tout[q.first]);
		int all = getSq(0, 0, n, 0, n);
		ans[q.second] = mul(2, cur);
		add(ans[q.second], MOD - all);
	}
	for (size_t i = 0; i < g[v].size(); i++) {
		pair<int, int> e = g[v][i];
		if (e.first != par) {
			add(0, 0, n, 0, n, e.second);
			add(0, 0, n, tin[e.first], tout[e.first], MOD - mul(2, e.second));
			calc(e.first, v);
			add(0, 0, n, 0, n, MOD - e.second);
			add(0, 0, n, tin[e.first], tout[e.first], mul(2, e.second));
		}
	}
}

int main() {
	scanf_s("%d", &n);
	for (int i = 0; i < n - 1; i++) {
		int a, b, c;
		scanf_s("%d%d%d", &a, &b, &c);
		--a, --b;
		g[a].push_back(make_pair(b, c));
		g[b].push_back(make_pair(a, c));
	}
	dfs(0, -1);
	scanf_s("%d", &q);
	for (int i = 0; i < q; i++) {
		int u, v;
		scanf_s("%d%d", &u, &v);
		--u, --v;
		qs[u].push_back(make_pair(v, i));
	}
	calc(0, -1);
	for (int i = 0; i < q; i++) {
		printf("%d\n", ans[i]);
	}
}