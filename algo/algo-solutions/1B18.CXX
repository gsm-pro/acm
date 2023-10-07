#include<iostream>
#include<cstring>
using namespace std;
const int INF = 0x3f3f3f3f;
const int N = 111;
const int M = 111111;

struct Edge {
	int next, to, flow, cap;
	Edge() {}
	Edge(int a, int b, int c, int d) {
		next = a, to = b, cap = c, flow = d;
	}
} edges[M];
int nedge, gnode, superSource, superSink, start, dest, n, m, need;
int head[N], dis[N], gap[N];

void addEdge(int a, int b, int c, int d) {
	if (head[a] == -1) gnode++;
	if (head[b] == -1) gnode++;
	edges[++nedge] = Edge(head[a], b, c, d);
	head[a] = nedge;
	edges[++nedge] = Edge(head[b], a, 0, 0);
	head[b] = nedge;
}

void init() {
	memset(head, -1, sizeof(head));
	nedge = -1, gnode = 0, superSource = 0, superSink = n + 1;
	int a, b, c, d, tt[N] = { 0 };
	for (int i = 0; i < m; i++) {
		scanf("%d%d%d%d", &a, &b, &c, &d);
		if (d) {
			addEdge(a, b, c, 0);
			tt[a] -= c, tt[b] += c;
		}
		else addEdge(a, b, c, c);
	}
	need = 0;
	for (int i = 1; i <= n; i++) {
		if (tt[i] > 0) {
			need += tt[i];
			addEdge(superSource, i, tt[i], tt[i]);
		}
		else if (tt[i] < 0) addEdge(i, superSink, -tt[i], -tt[i]);
	}
}

int dfs(int u, int limit) {
	if (u == dest) return limit;
	int fl = 0, f, minh = gnode - 1;
	for (int i = head[u]; i != -1; i = edges[i].next) {
		int v = edges[i].to;
		if (edges[i].flow > 0) {
			if (dis[v] + 1 == dis[u]) {
				f = dfs(v, min(limit, edges[i].flow));
				edges[i].flow -= f;
				edges[i ^ 1].flow += f;
				limit -= f;
				fl += f;
				if (dis[start] >= gnode) return fl;
				if (limit == 0) break;
			}
			minh = min(minh, dis[v]);
		}
	}
	if (fl == 0) {
		gap[dis[u]]--;
		if (gap[dis[u]] == 0) dis[start] = gnode;
		dis[u] = minh + 1;
		gap[dis[u]]++;
	}
	return fl;
}

int getAll(int a, int b) {
	start = a, dest = b;
	memset(dis, 0, sizeof(dis));
	memset(gap, 0, sizeof(gap));
	gap[start] = gnode;
	int all = 0;
	while (dis[start] < gnode) all += dfs(start, INF);
	return all;
}

int main() {
	scanf("%d%d", &n, &m);
	init();
	int sum = getAll(superSource, superSink);
	if (sum == need) printf("0\n");	else {
		int edst = nedge + 1;
		addEdge(n, 1, INF, INF);
		sum += getAll(superSource, superSink);
		if (sum != need) return printf("Impossible"), 0;
		printf("%d\n", edges[edst].cap - edges[edst].flow);
	}
	for (int i = 0; i < m; i++) printf("%d ", edges[i * 2].cap - edges[i * 2].flow);
}