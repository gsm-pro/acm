#define _CRT_SECURE_NO_WARNINGS
#include<vector>
#include<queue>
#include<algorithm>
#include<iostream>
#include<list>
using namespace std;
const int NMAX = 77;

struct Edge {
	int t_vertex;
	int capacity;
	int reverse;
	Edge(int _t_vertex, int _capacity, int _reverse) {
		t_vertex = _t_vertex;
		capacity = _capacity;
		reverse = _reverse;
	}
};

vector<vector<Edge>> G;
vector<int> h, e;
list<int> vertex;
bool field[NMAX][NMAX];
int N, M, w, b, g;
char c;

inline int getVertexNum(int i, int j) {
	return i * M + j + 2;
}

void addEdge(int v1, int v2, int c1, int c2) {
	Edge e1(v2, c1, (int)G[v2].size()), e2(v1, c2, (int)G[v1].size());
	G[v1].push_back(e1);
	G[v2].push_back(e2);
}

bool addPath(int source, int target) {
	queue<int> W;
	vector<int> prev(G.size(), -1);
	W.push(source);
	prev[source] = 0;
	while (prev[target] < 0 && !W.empty()) {
		int current = W.front();
		W.pop();
		for (int i = 0; i<int(G[current].size()); i++) {
			if (prev[G[current][i].t_vertex] < 0 && G[current][i].capacity > 0) {
				prev[G[current][i].t_vertex] = current;
				W.push(G[current][i].t_vertex);
			}
		}
	}
	return (prev[target] >= 0);
}

void push(int a, int i) {
	int d = min(e[a], G[a][i].capacity);
	G[a][i].capacity -= d;
	G[G[a][i].t_vertex][G[a][i].reverse].capacity += d;
	e[a] -= d;
	e[G[a][i].t_vertex] += d;
}

void lift(int a) {
	int n = (int)1e9;
	for (int i = 0; i < (int)G[a].size(); i++) {
		if (G[a][i].capacity > 0) {
			n = min(n, h[G[a][i].t_vertex]);
		}
	}
	h[a] = n + 1;
}

void discharge(int a) {
	int i = 0;
	while (e[a] > 0) {
		if (i == (int)G[a].size()) {
			lift(a);
			i = 0;
		}
		if (h[a] == h[G[a][i].t_vertex] + 1) {
			push(a, i);
		}
		i++;
	}
}

int maxFlow() {
	h.assign(N * M + 2, 0);
	e.assign(N * M + 2, 0);
	list<int> L;
	for (int i = 2; i < N * M + 2; i++) {
		L.push_back(i);
	}
	do {
		h[0] += (int)1e2;
		e[0] = (int)1e9;
		for (int i = 0; i < (int)G[0].size(); i++) {
			push(0, i);
		}
		list<int>::iterator current = L.begin();
		while (current != L.end()) {
			if (e[*current] > 0) {
				discharge(*current);
				int old = *current;
				L.erase(current);
				L.push_front(old);
				current = L.begin();
			}
			current++;
		}
	} while (addPath(0, 1));
	return e[1];
}

int main() {
	freopen("input.txt", "r", stdin);
	freopen("output.txt", "w", stdout);
	cin >> N >> M >> w >> b >> g;
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < M; j++) {
			cin >> c;
			field[i][j] = (c == 'W');
		}
	}
	G.assign(N * M + 2, vector<Edge>());
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < M; j++) {
			if (field[i][j]) {
				addEdge(getVertexNum(i, j), 1, b, 0);
			}
			else {
				addEdge(0, getVertexNum(i, j), w, 0);
			}
			if (i < N - 1) {
				addEdge(getVertexNum(i, j), getVertexNum(i + 1, j), g, g);
			}
			if (j < M - 1) {
				addEdge(getVertexNum(i, j), getVertexNum(i, j + 1), g, g);
			}
		}
	}
	cout << maxFlow();
}