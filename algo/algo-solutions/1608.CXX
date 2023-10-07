#include<iostream>
#include<vector>
#include<queue>
#include<unordered_map>
using namespace std;

struct Split {
	int ape1, ape2, timer;

	bool operator() (const Split& x, const Split& y) const {
		return x.timer < y.timer;
	}
};

unordered_map<int, unordered_map<int, Split>> edges;
vector<int> L[222222], F, A;
int N, M, u, v, i;
char c;

int read() {
	int t = 0;
	bool neg = false;
	while ((c = getchar()) > 0 && c != ' ' && c != '\r' && c != '\n')
		if (c == '-') neg = true; else t = (t << 3) + (t << 1) + c - 48;
	return neg ? -t : t;
}

void make(int v) {
	L[v] = vector<int>(1, v), F[v] = v;
}

int find(int v) {
	return F[v];
}

void unite(int a, int b, int timer) {
	a = find(a), b = find(b);
	if (a == b) return;
	if (timer != -1) for (auto e : L[b]) A[e] = timer;
	if (L[a].size() < L[b].size()) swap(a, b);
	while (!L[b].empty()) {
		int v = L[b].back();
		L[b].pop_back();
		F[v] = a;
		L[a].push_back(v);
	}
}

int main() {
	N = read(), M = read();
	F.assign(N + 1, 0);
	for (i = 1; i <= N; i++) {
		make(i);
		if ((u = read()) != -1 && u != i) edges[i][1] = Split{ i, u, -1 };
		if ((v = read()) != -1 && v != i) edges[i][2] = Split{ i, v, -1 };
	}
	for (i = 0; i < M; i++) {
		u = read(), v = read();
		if (edges[u].count(v)) edges[u][v].timer = i;
	}
	priority_queue<Split, vector<Split>, Split> splits;
	for (auto X = edges.begin(); X != edges.end(); X++)
		for (auto Y = X->second.begin(); Y != X->second.end(); Y++) {
			auto e = Y->second;
			if (e.timer == -1) unite(e.ape1, e.ape2, -1); else splits.push(e);
		}
	A.assign(N + 1, -1);
	while (!splits.empty()) {
		auto e = splits.top();
		splits.pop();
		int f = find(1), f1 = find(e.ape1), f2 = find(e.ape2);
		if (f1 == f2) continue;
		if (f == f1) unite(1, f2, e.timer);
		else if (f == f2) unite(1, f1, e.timer);
		else unite(e.ape1, e.ape2, -1);
	}
	for (i = 1; i <= N; i++) printf("%d\n", A[i]);
}