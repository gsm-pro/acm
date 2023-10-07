#include<iostream>
#include<algorithm>
#define MAXN 100001
#define MAXM 200002
using namespace std;
const char ans[][15] = { "none", "at least one", "any" };
int head[MAXN], dfn[MAXN], low[MAXN], tag[MAXM], pre[MAXN], c_mst = 0, idx = 0;

struct IEdge {
	int u, v, w, id;
} graph[MAXM];

struct Edge {
	int ed, id, next;
} mst[MAXM];

void addEdge(int a, int b, int id) {
	mst[c_mst].ed = b;
	mst[c_mst].id = id;
	mst[c_mst].next = head[a];
	head[a] = c_mst++;
	mst[c_mst].ed = a;
	mst[c_mst].id = id;
	mst[c_mst].next = head[b];
	head[b] = c_mst++;
}

void tarjan(int x, int p) {
	int y;
	dfn[x] = low[x] = idx++;
	for (int i = head[x]; ~i; i = mst[i].next) {
		if ((i | 1) != (p | 1)) {
			if (~dfn[y = mst[i].ed]) {
				low[x] = min(low[x], dfn[y]);
			}
			else {
				tarjan(y, i);
				low[x] = min(low[x], low[y]);
				if (dfn[x] < low[y]) {
					tag[mst[i].id] = 2;
				}
			}
		}
	}
}

inline bool cmp(const IEdge &a, const IEdge &b) {
	return a.w < b.w;
}

int root(int x) {
	int r, nxt;
	for (r = x; ~pre[r]; r = pre[r]);
	for (int i = x; i != r; i = nxt) {
		nxt = pre[i];
		pre[i] = r;
	}
	return r;
}

int kruskal(int n, int m) {
	int ra, rb, cnt = 0, ret = 0;
	memset(head, -1, sizeof head);
	memset(tag, 0, sizeof tag);
	memset(dfn, -1, sizeof dfn);
	memset(pre, -1, sizeof pre);
	sort(graph, graph + m, cmp);
	for (int i = 0, j; i < m && cnt < n - 1; i = j) {
		for (j = i; graph[j].w == graph[i].w; j++) {
			ra = root(graph[j].u);
			rb = root(graph[j].v);
			if (ra == rb) {
				tag[graph[j].id] = 0;
			}
			if (ra != rb) {
				tag[graph[j].id] = 1;
				addEdge(ra, rb, graph[j].id);
			}
		}
		for (j = i; graph[j].w == graph[i].w; j++) {
			ra = root(graph[j].u);
			rb = root(graph[j].v);
			if (ra != rb) {
				if (dfn[ra] == -1) {
					tarjan(ra, -1);
				}
				head[ra] = dfn[ra] = head[rb] = dfn[rb] = -1;
			}
		}
		for (j = i; graph[j].w == graph[i].w; j++) {
			ra = root(graph[j].u);
			rb = root(graph[j].v);
			if (ra != rb) {
				pre[ra] = rb;
				ret += graph[j].w;
				++cnt;
			}
		}
	}
	return ret;
}

int main() {
	int n, m;
	scanf_s("%d%d", &n, &m);
	for (int i = 0; i < m; i++) {
		scanf_s("%d%d%d", &graph[i].u, &graph[i].v, &graph[i].w);
		--graph[i].u;
		--graph[i].v;
		graph[i].id = i;
	}
	kruskal(n, m);
	for (int i = 0; i < m; i++) {
		puts(ans[tag[i]]);
	}
}