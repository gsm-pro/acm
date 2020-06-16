#include<iostream>
#include<cassert>
#include<vector>
#include<map>
#include<set>
using namespace std;
#define MAXV 2222

struct Edge {
	int a, b, color;
	Edge() {}
	Edge(const int _a, const int _b, const int _color) : a(_a), b(_b), color(_color) {}
};

int A, N, M, K;
vector<Edge> vEdges;
vector<int> G[MAXV];
map<int, int> mColors[MAXV];
set<int> sRemain[MAXV];

void doUpdate(int &a, const int b) {
	if (b > a) {
		a = b;
	}
}

void doUnColor(const int u, const int color) {
	if (color == -1) {
		return;
	}
	auto it = mColors[u].find(color);
	assert(it != mColors[u].end());
	mColors[u].erase(it);
	sRemain[u].insert(color);
	assert((int)(mColors[u].size() + sRemain[u].size()) == K);
}

void doColor(const int u, const int color, const int ei) {
	assert(mColors[u].find(color) == mColors[u].end());
	auto it = sRemain[u].find(color);
	assert(it != sRemain[u].end());
	mColors[u][color] = ei;
	sRemain[u].erase(it);
	assert((int)(mColors[u].size() + sRemain[u].size()) == K);
}

int findColor(const int a, const int ei, const int except) {
	const int b = (a == vEdges[ei].a ? vEdges[ei].b : vEdges[ei].a);
	for (set<int>::iterator it = sRemain[a].begin(); it != sRemain[a].end(); it++) {
		const int c = *it;
		if (c != except && sRemain[b].find(c) != sRemain[b].end()) {
			return c;
		}
	}
	for (set<int>::iterator it = sRemain[a].begin(); it != sRemain[a].end(); it++) {
		const int c = *it;
		if (c != except) {
			return c;
		}
	}
	assert(0);
	return -1;
}

void doColorEdge(const int u, const int ei, const int color) {
	const Edge &e = vEdges[ei];
	const int pre_color = e.color;
	if (pre_color == color) {
		return;
	}
	vEdges[ei].color = color;
	doUnColor(u, pre_color);
	doColor(u, color, ei);
	const int nxt = (u == e.a ? e.b : e.a);
	if (true) {
		doUnColor(nxt, pre_color);
		auto it = mColors[nxt].find(color);
		if (it != mColors[nxt].end()) {
			const int nxt_ei = it->second;
			doColorEdge(nxt, nxt_ei, pre_color != -1 ? pre_color : findColor(nxt, nxt_ei, color));
		}
		doColor(nxt, color, ei);
	}
}

void doColorVertex(const int u) {
	for (size_t i = 0; i < G[u].size(); i++) {
		const int ei = G[u][i];
		if (vEdges[ei].color == -1) {
			doColorEdge(u, ei, findColor(u, ei, -1));
		}
	}
}

int main() {
	scanf_s("%d%d%d", &A, &N, &M);
	N += A;
	for (int i = 0; i < N; i++) {
		G[i].clear();
		mColors[i].clear();
		sRemain[i].clear();
	}
	for (int i = 0, a, b; i < M; i++) {
		scanf_s("%d%d", &a, &b);
		a--;
		b--;
		b += A;
		vEdges.push_back(Edge(a, b, -1));
		G[a].push_back(i);
		G[b].push_back(i);
	}
	K = 0;
	for (int i = 0; i < N; i++) {
		doUpdate(K, (int)G[i].size());
	}
	for (int i = 0; i < N; i++) {
		for (int c = 0; c < K; c++) {
			sRemain[i].insert(c);
		}
	}
	for (int i = 0; i < N; i++) {
		doColorVertex(i);
	}
	printf("%d\n", K);
	assert(M == (int)vEdges.size());
	for (int i = 0; i < M; i++) {
		if (i) {
			putchar(' ');
		}
		printf("%d", vEdges[i].color + 1);
	}
}