#include<iostream>
#include<vector>
#include<deque>
#include<unordered_map>
#include<algorithm>
using namespace std;
vector<int> color012, parent, subtree, d;
deque<int> cycle;
vector<char> used;
vector<vector<int>> g;
int dst[1001][1001] = { 0 }, n, q, v1, v2, w, CYC_S, CYC_F, F1, F2;
unordered_map<int, unordered_map<int, int>> rib, frib;

struct query {
	int v1, v2, w, C;
	__int64 ans;
};

vector<query> queries;

void bfs(int u) {
	d.assign(n, 0);
	used.assign(n, 0);
	used[u] = true;
	deque<int> q;
	q.push_back(u);
	while (!q.empty()) {
		int cur = q.front();
		q.pop_front();
		used[cur] = true;
		for (int a : g[cur])
			if (!used[a]) {
				used[a] = true;
				d[a] = d[cur] + rib[min(a, cur)][max(a, cur)];
				q.push_back(a);
			}
	}
}

int dfs(int u = 0, int p = 0) {
	int sz = 1;
	for (int a : g[u])
		if (a != p) {
			int val = dfs(a, u);
			frib[min(a, u)][max(a, u)] = val * (n - val), sz += val;
		}
	return sz;
}

bool dfs2(int u = 0, int p = -1) {
	color012[u] = 1;
	for (int a : g[u]) {
		if (a == p) continue;
		if (color012[a] == 0) {
			parent[a] = u;
			if (dfs2(a, u)) return true;
		}
		else if (color012[a] == 1) {
			CYC_F = u, CYC_S = a;
			return true;
		}
	}
	color012[u] = 2;
	return false;
}

int dfs3(int u, int p = -1) {
	int sz = 1;
	for (int a : g[u])
		if (a != cycle[F1] && a != cycle[F2] && a != p) sz += dfs3(a, u);
	return sz;
}

int main() {
	freopen("input.txt", "r", stdin);
	freopen("output.txt", "w", stdout);
	scanf("%d", &n);
	n++;
	g.resize(n);
	for (int i = 0; i < n - 1; i++) {
		scanf("%d%d%d", &v1, &v2, &w);
		g[v1].push_back(v2);
		g[v2].push_back(v1);
		rib[min(v1, v2)][max(v1, v2)] = w;
	}
	dfs();
	__int64 OF = 0, ww;
	for (int i = 0; i < n; i++) {
		bfs(i);
		for (int j = i + 1; j < n; j++) dst[i][j] = dst[j][i] = d[j], OF += d[j];
	}
	scanf("%d", &q);
	for (int i = 1; i <= q; i++) {
		scanf("%d%d%d", &v1, &v2, &w);
		queries.push_back(query{ min(v1, v2), max(v1, v2), w, i, 0LL });
	}
	sort(queries.begin(), queries.end(),
		[](const auto& L, const auto& R) { return L.v1 < R.v1 || (L.v1 == R.v1 && L.v2 < R.v2); });
	printf("%d\n", q);
	int prev_v1 = -1, prev_v2 = -1;
	for (auto& que : queries) {
		v1 = que.v1, v2 = que.v2, w = que.w, que.ans = OF;
		if (w >= dst[v1][v2]) continue;
		if (rib[v1].count(v2)) {
			que.ans -= (__int64)(dst[v1][v2] - w) * frib[v1][v2];
			continue;
		}
		g[v1].push_back(v2);
		g[v2].push_back(v1);
		if (v1 != prev_v1 || v2 != prev_v2) {
			color012.assign(n, 0);
			parent.assign(n, -1);
			dfs2();
			subtree.assign(n, 0);
			cycle.clear();
			cycle.push_back(CYC_S);
			for (int v = CYC_F; v != CYC_S; v = parent[v]) cycle.push_back(v);
			while (true) {
				cycle.push_back(cycle.front());
				cycle.pop_front();
				if ((cycle[0] == v1 && cycle[1] == v2) || (cycle[0] == v2 && cycle[1] == v1)) break;
			}
			int csz = (int)cycle.size();
			F1 = csz - 1, F2 = 1;
			for (int e : cycle) {
				subtree[e] = dfs3(e);
				F1++, F2++;
				if (F1 == csz) F1 = 0;
				if (F2 == csz) F2 = 0;
			}
		}
		int csum = dst[v1][v2] + w;
		deque<int>::iterator it1 = cycle.begin(), it2;
		int q1 = subtree[*it1];
		for (it2 = it1 + 1; it2 != cycle.end(); it2++)
			if ((ww = (dst[*it1][*it2] << 1) - csum) > 0) que.ans -= ww * q1 * subtree[*it2];
		it1++;
		for (; it1 != cycle.end() - 1; it1++) {
			q1 = subtree[*it1];
			it2 = cycle.end() - 1;
			for (; it2 != it1; it2--) {
				if ((ww = (dst[*it1][*it2] << 1) - csum) > 0) que.ans -= ww * q1 * subtree[*it2];
				else break;
			}
		}
		g[v1].pop_back();
		g[v2].pop_back();
		prev_v1 = v1, prev_v2 = v2;
	}
	sort(queries.begin(), queries.end(), [](const auto& L, const auto& R) {	return L.C < R.C; });
	for (auto& que : queries) printf("%lld\n", que.ans);
}