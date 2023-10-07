#include<bits/stdc++.h>
using namespace std;
#define pb push_back
#define sci2(X,Y) scanf("%d%d",&(X),&(Y))
#define lg(X) (63 - __builtin_clzll(X))
#define LG(X) (lg(X)+((1<<lg(X)) < (X)))
#define rp(i,L,R) for (int i = L, __R = R; i <= __R; i++)
#define rpd(i,R,L) for (int i = R, __L = L; __L <= i; i--)
typedef vector<int> vi;

vi dominator_tree(const vector<vi>& dag, int source) {
	int n = dag.size();
	vi idom(n);
	rp(u, 0, n - 1) idom[u] = u;
	vi deg(n, 0);
	function<void(int)> dfs1 = [&](int u) {
		for (int v : dag[u]) {
			deg[v]++;
			if (deg[v] == 1) dfs1(v);
		}
	};
	dfs1(source);
	vector<vi> dp(n, vi(LG(n) + 5, -1));
	function<int(int, int)> f = [&](int u, int i) {
		if (i == 0) return idom[u];
		auto& ans = dp[u][i];
		if (ans >= 0) return ans;
		return ans = f(f(u, i - 1), i - 1);
	};
	vi l(n, 0);
	auto lca = [&](int u, int v) {
		if (l[u] < l[v]) swap(u, v);
		int k = LG(l[u]);
		rpd(i, k, 0) if (l[f(u, i)] >= l[v]) u = f(u, i);
		if (u == v) return v;
		rpd(i, k, 0) if (f(u, i) != f(v, i)) u = f(u, i), v = f(v, i);
		return idom[u];
	};
	function<void(int)> dfs2 = [&](int u) {
		for (int v : dag[u]) {
			idom[v] = (idom[v] == v ? u : lca(idom[v], u));
			l[v] = l[idom[v]] + 1;
			deg[v]--;
			if (deg[v] == 0) dfs2(v);
		}
	};
	dfs2(source);
	return idom;
}

int main() {
	int V, E, u, v;
	sci2(V, E);
	vector<vi> q(V);
	while (E--) {
		sci2(u, v);
		q[--u].pb(--v);
	}
	vi z = dominator_tree(q, 0);
	rp(i, 0, z.size() - 1) printf("%d ", z[i] + 1);
}