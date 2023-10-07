#include<iostream>
using namespace std;
const int MAXN = 355;
const int MAXM = 110011;

struct Node {
	int from, to, w;
} Edges[MAXM];

int PRE[MAXN], VIS[MAXN], F[MAXN], IN[MAXN];

int get(int root, int N, int M) {
	int sum = 0;
	while (true) {
		for (int i = 0; i < N; i++) {
			IN[i] = INT_MAX;
		}
		for (int i = 0; i < M; i++) {
			int u = Edges[i].from, v = Edges[i].to;
			if (Edges[i].w < IN[v] && u != v) {
				PRE[v] = u;
				IN[v] = Edges[i].w;
			}
		}
		for (int i = 0; i < N; i++) {
			if (i == root) {
				continue;
			}
			if (IN[i] == INT_MAX) {
				return -1;
			}
		}
		int cntNode = 0;
		memset(F, -1, sizeof F);
		memset(VIS, -1, sizeof VIS);
		IN[root] = 0;
		for (int i = 0; i < N; i++) {
			sum += IN[i];
			int v = i;
			while (VIS[v] != i && F[v] == -1 && v != root) {
				VIS[v] = i;
				v = PRE[v];
			}
			if (v != root && F[v] == -1) {
				for (int u = PRE[v]; u != v; u = PRE[u]) {
					F[u] = cntNode;
				}
				F[v] = cntNode++;
			}
		}
		if (cntNode == 0) {
			break;
		}
		for (int i = 0; i < N; i++) {
			if (F[i] == -1) {
				F[i] = cntNode++;
			}
		}
		for (int i = 0; i < M; i++) {
			int v = Edges[i].to;
			Edges[i].from = F[Edges[i].from];
			Edges[i].to = F[Edges[i].to];
			if (Edges[i].from != Edges[i].to) {
				Edges[i].w -= IN[v];
			}
		}
		N = cntNode;
		root = F[root];
	}
	return sum;
}

int main() {
	int x, y, w, N, M, id = 0;
	scanf_s("%d%d", &N, &M);
	for (int i = 0; i < M; i++) {
		scanf_s("%d%d%d", &x, &y, &w);
		if (x == y) {
			continue;
		}
		x--, y--;
		Edges[id].from = x;
		Edges[id].to = y;
		Edges[id++].w = w;
	}
	printf("%d", get(0, N, id));
}