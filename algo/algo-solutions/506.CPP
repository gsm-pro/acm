#include<iostream>
#include<vector>
#include<algorithm>
using namespace std;
typedef long long LL;
const int MAXN = 222222;
const int MAXNLOG = 20;
int dsu[MAXN], tin[MAXN], tout[MAXN], timer = 0, p[MAXN][MAXNLOG], maxP[MAXN][MAXNLOG];
LL ans[MAXN], MSTW = 0;
bool u[MAXN];

int dsuGet(int i) {
	return (i == dsu[i] ? i : dsu[i] = dsuGet(dsu[i]));
}

void dsuUnite(int a, int b) {
	a = dsuGet(a);
	b = dsuGet(b);
	if (rand() & 1) {
		dsu[a] = b;
	}
	else {
		dsu[b] = a;
	}
}

struct Edge {
	int a, b, w, i;
	Edge() {}
	Edge(int a, int b, int w, int i) : a(a), b(b), w(w), i(i) {}
};

vector<Edge> e, g[MAXN];

bool cmp(Edge &a, Edge &b) {
	return a.w < b.w;
}

void kruskal() {
	for (int i = 0; i < MAXN; i++) {
		dsu[i] = i;
	}
	sort(e.begin(), e.end(), cmp);
	for (int i = 0; i < (int)(e.size()); i++) {
		if (dsuGet(e[i].a) != dsuGet(e[i].b)) {
			dsuUnite(e[i].a, e[i].b);
			g[e[i].a].push_back(e[i]);
			g[e[i].b].push_back(e[i]);
			MSTW += e[i].w;
		}
	}
}

void buildLca(int v, int pr, Edge from) {
	u[v] = true;
	p[v][0] = pr;
	tin[v] = ++timer;
	maxP[v][0] = from.w;
	for (int i = 1; i < MAXNLOG; i++) {
		p[v][i] = p[p[v][i - 1]][i - 1];
		maxP[v][i] = max(maxP[v][i - 1], maxP[p[v][i - 1]][i - 1]);
	}
	for (size_t i = 0; i < g[v].size(); i++) {
		int to = (g[v][i].a == v ? g[v][i].b : g[v][i].a);
		if (!u[to]) {
			buildLca(to, v, g[v][i]);
		}
	}
	tout[v] = ++timer;
}

bool isParent(int a, int b) {
	return (tin[a] <= tin[b] && tout[a] >= tout[b]);
}

int maxUp(int a, int r, int ans = 0) {
	for (int i = MAXNLOG - 1; i >= 0; i--) {
		if (!isParent(p[a][i], r)) {
			ans = max(ans, maxP[a][i]);
			a = p[a][i];
		}
	}
	return max(ans, maxP[a][0]);
}

int lca(int a, int b, int ans = 0) {
	if (isParent(a, b)) {
		return maxUp(b, a);
	}
	if (isParent(b, a)) {
		return maxUp(a, b);
	}
	for (int i = MAXNLOG - 1; i >= 0; i--) {
		if (!isParent(p[a][i], b)) {
			ans = max(ans, maxP[a][i]);
			a = p[a][i];
		}
	}
	ans = max(ans, maxP[a][0]);
	a = p[a][0];
	return max(ans, maxUp(b, a));
}

int main() {
	int n, m, a, b, w;
	scanf_s("%d%d", &n, &m);
	for (int i = 0; i < m; i++) {
		scanf_s("%d%d%d", &a, &b, &w);
		--a, --b;
		e.push_back(Edge(a, b, w, i));
	}
	kruskal();
	buildLca(0, 0, Edge(0, 0, 0, -1));
	for (int i = 0; i < m; i++) {
		ans[e[i].i] = MSTW - lca(e[i].a, e[i].b) + e[i].w;
	}
	for (int i = 0; i < m; i++) {
		printf("%lld\n", ans[i]);
	}
}