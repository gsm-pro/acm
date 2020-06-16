#include<iostream>
#include<queue>
using namespace std;
const __int64 INF = 0x101010101010101LL;
const int DIM = 1001;
queue<int> q;
int n, m, start, finish, head[DIM], cnt;
__int64 a[DIM], b[DIM], cost[DIM][DIM], v[DIM];

struct node {
	int u, v, next;
	__int64 w;
} edge[DIM * DIM];

void add(int u, int v, __int64 w) {
	edge[++cnt].u = u;
	edge[cnt].v = v;
	edge[cnt].w = w;
	edge[cnt].next = head[u];
	head[u] = cnt;
}

void search(int cur) {
	for (int i = 1; i <= n; i++) {
		if (cost[cur][i] != INF) {
			if (cost[cur][i] <= b[cur]) {
				add(cur, i, a[cur]);
			}
		}
	}
}

void dijkstra(int start, int now) {
	while (q.size()) {
		q.pop();
	}
	q.push(start);
	while (q.size()) {
		int u = q.front();
		q.pop();
		for (int i = head[u]; i; i = edge[i].next) {
			int v = edge[i].v;
			if (cost[start][v] > cost[start][u] + edge[i].w) {
				cost[start][v] = cost[start][u] + edge[i].w;
				q.push(v);
			}
		}
	}
}

int main() {
	scanf_s("%d%d%d%d", &n, &m, &start, &finish);
	memset(cost, 1, sizeof cost);
	for (int i = 1; i <= m; i++) {
		int u, v;
		__int64 w;
		scanf_s("%d%d%I64d", &u, &v, &w);
		add(u, v, w);
		add(v, u, w);
	}
	for (int i = 1; i <= n; i++) {
		cost[i][i] = 0;
		scanf_s("%I64d%I64d", &b[i], &a[i]);
	}
	for (int i = 1; i <= n; i++) {
		dijkstra(i, i);
	}
	memset(head, 0, sizeof head);
	memset(edge, 0, sizeof edge);
	cnt = 0;
	for (int i = 1; i <= n; i++) {
		search(i);
	}
	memset(cost, 1, sizeof cost);
	cost[start][start] = 0;
	dijkstra(start, start);
	if (cost[start][finish] == INF) {
		cout << -1;
		return 0;
	}
	cout << cost[start][finish];
}