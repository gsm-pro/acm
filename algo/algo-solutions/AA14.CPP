#include<vector>
#include<cstdio>
#include<algorithm>
using namespace std;
const int N = 111111;

struct Edge {
	int v, pre;
	Edge() {}
	Edge(int v, int pre) : v(v), pre(pre) {}
} edges[N << 3];

int head[N], nEdge = 0, dfn[N], low[N], nId = 0, n, m, a, b;
vector<pair<int, int>> ans;

void addEdge(int u, int v) {
	edges[nEdge] = Edge(v, head[u]);
	head[u] = nEdge++;
}

bool tarjan(int u, int pre) {
	dfn[u] = low[u] = ++nId;
	bool flag = 0;
	for (int i = head[u]; i != -1; i = edges[i].pre) {
		int v = edges[i].v;
		if (v == pre && flag == 0) {
			flag = 1;
			continue;
		}
		if (dfn[v]) {
			if (dfn[v] > dfn[u]) {
				continue;
			}
			low[u] = min(low[u], dfn[v]);
			ans.push_back(make_pair(u, v));
		}
		else {
			if (tarjan(v, u) == 0) {
				return false;
			}
			low[u] = min(low[u], low[v]);
			if (low[v] > dfn[u]) {
				return false;
			}
			ans.push_back(make_pair(u, v));
		}
	}
	return true;
}

int main() {
	scanf_s("%d%d", &n, &m);
	memset(head, -1, sizeof head);
	memset(dfn, 0, sizeof dfn);
	memset(low, 0, sizeof low);
	for (int i = 0; i < m; i++) {
		scanf_s("%d%d", &a, &b);
		addEdge(a, b);
		addEdge(b, a);
	}
	if (!tarjan(1, -1)) {
		return puts("0"), 0;
	}
	for (size_t i = 0; i < ans.size(); i++) {
		printf("%d %d\n", ans[i].first, ans[i].second);
	}
}