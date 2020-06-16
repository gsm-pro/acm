#include<memory.h>
#include<iostream>
#include<vector>
#include<map>
#include<bitset>
#include<tuple>
using namespace std;
#define MAXN 10005
#define MAXM 200005
typedef bitset<MAXN> BS;
vector<tuple<int, int, int, int>> edges;
map<int, int> best_weight;
bitset<MAXM> exclude;
vector<int> G[MAXN];
BS B[MAXN], C[MAXN];
bool used[MAXN];
int n, m;

inline int encode(int &u, int &v) {
	return (u << 15) + v;
}

BS dfs(int v) {
	if (used[v]) {
		return C[v];
	}
	size_t sz = G[v].size();
	if (sz == 0) {
		C[v][v] = 1;
	}
	else {
		for (size_t i = 0; i < sz; i++) {
			int to = G[v][i];
			C[v][to] = 1;
			C[v] |= dfs(to);
		}
	}
	used[v] = true;
	return C[v];
}

int main() {
	freopen("input.txt", "rt", stdin);
	freopen("output.txt", "wt", stdout);
	scanf("%d%d", &n, &m);
	for (int i = 1; i <= m; i++) {
		int u, v, w;
		scanf("%d%d%d", &u, &v, &w);
		u--, v--;
		edges.emplace_back(u, v, w, i);
		int enc = encode(u, v);
		if (!best_weight.count(enc)) {
			best_weight[enc] = w;
		}
		else {
			best_weight[enc] = min(best_weight[enc], w);
		}
	}
	for (auto tp : edges) {
		int u = get<0>(tp), v = get<1>(tp), enc = encode(u, v),
			curW = get<2>(tp), num = get<3>(tp), bestW = best_weight[enc];
		if (curW > bestW) {
			exclude.set(num);
			continue;
		}
		if (curW == bestW) {
			best_weight[enc] = -1;
		}
		B[u][v] = 1;
		G[u].push_back(v);
	}
	memset(used, false, sizeof used);
	for (int i = 0; i < n; i++) {
		if (!used[i]) {
			dfs(i);
		}
	}
	for (int i = 0; i < n; i++) {
		C[i][i] = 0;
		C[i] = ~C[i];
	}
	for (auto tp : edges) {
		B[get<0>(tp)] &= C[get<1>(tp)];
	}
	for (auto tp : edges) {
		if (!B[get<0>(tp)][get<1>(tp)]) {
			exclude.set(get<3>(tp));
		}
	}
	printf("%d\n", exclude.count());
	for (int i = 1; i <= m; i++) {
		if (exclude.test(i)) {
			printf("%d ", i);
		}
	}
}