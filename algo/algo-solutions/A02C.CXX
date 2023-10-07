#include<iostream>
#include<vector>
#include<algorithm>
using namespace std;
int color[1111][1111];

struct Edge { int to, col, rev; };

struct MisraGries {
	int N, K = 0;
	vector<vector<Edge>> G;
	vector<vector<int>> F;
	MisraGries(int n) : N(n), G(n) {}

	void addEdge(int u, int v) {
		G[u].push_back({ v, -1, (int)G[v].size() });
		G[v].push_back({ u, -1, (int)G[u].size() - 1 });
	}

	void color(int v, int i) {
		vector<int> fan = { i };
		vector<bool> used(G[v].size());
		used[i] = true;
		for (size_t j = 0; j < G[v].size(); j++) {
			if (!used[j] && G[v][j].col >= 0 && F[G[v][fan.back()].to][G[v][j].col] < 0) {
				used[j] = true;
				fan.push_back(j), j = -1;
			}
		}
		int c = 0;
		while (F[v][c] >= 0) {
			c++;
		}
		int d = 0;
		while (F[G[v][fan.back()].to][d] >= 0) {
			d++;
		}
		int w = v, a = d, k = 0, ccol;
		while (true) {
			swap(F[w][c], F[w][d]);
			if (F[w][c] >= 0) {
				G[w][F[w][c]].col = c;
			}
			if (F[w][d] >= 0) {
				G[w][F[w][d]].col = d;
			}
			if (F[w][a ^= c ^ d] < 0) {
				break;
			}
			w = G[w][F[w][a]].to;
		}
		do {
			Edge &e = G[v][fan[k]];
			ccol = F[e.to][d] < 0 ? d : G[v][fan[k + 1]].col;
			if (e.col >= 0) {
				F[e.to][e.col] = -1;
			}
			F[e.to][ccol] = e.rev;
			F[v][ccol] = fan[k];
			e.col = G[e.to][e.rev].col = ccol;
			k++;
		} while (ccol != d);
	}

	void color() {
		for (int v = 0; v < N; v++) {
			K = max(K, (int)G[v].size() + 1);
		}
		F = vector<vector<int>>(N, vector<int>(K, -1));
		for (int v = 0; v < N; v++) {
			for (int i = G[v].size(); i--; ) {
				if (G[v][i].col < 0) {
					color(v, i);
				}
			}
		}
	}
};

int main() {
	int n, m, u, v;
	cin >> n >> m;
	MisraGries MG(n);
	vector<pair<int, int>> E;
	while (m--) {
		cin >> u >> v;
		--u, --v;
		E.push_back(make_pair(u, v));
		MG.addEdge(u, v);
	}
	MG.color();
	for (int i = 0; i < n; i++) {
		for (size_t j = 0; j < MG.G[i].size(); j++) {
			color[i][MG.G[i][j].to] = MG.G[i][j].col + 1;
		}
	}
	for (size_t i = 0; i < E.size(); i++) {
		printf("%d ", color[E[i].first][E[i].second]);
	}
}