#include<vector>
#include<iostream>
#include<algorithm>
#include<queue>
using namespace std;
const long long INF = 6LL * 1000000LL * 1000000LL * 1000000LL;
struct edge {
	int a, b;
	long long c;
};
vector<edge> e;
vector<vector<int>> g;
queue<int> q;

int main() {
	int n, m, s;
	cin >> n >> m >> s;
	vector<long long> d(n, INF);
	vector<bool> isUndefined(n, false);
	g.resize(n);
	for (int i = 0; i < m; i++) {
		edge rib;
		cin >> rib.a >> rib.b >> rib.c;
		--rib.a;
		--rib.b;
		g[rib.a].push_back(rib.b);
		e.push_back(rib);
	}
	d[--s] = 0;
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < m; j++) {
			if (d[e[j].a] < INF) {
				if (d[e[j].b] > d[e[j].a] + e[j].c) {
					d[e[j].b] = max(-INF, d[e[j].a] + e[j].c);
					if (i == n - 1 && !isUndefined[e[j].b]) {
						q.push(e[j].b);
						isUndefined[e[j].b] = true;
					}
				}
			}
		}
	}
	vector<bool> isUsed(n, false);
	while (!q.empty()) {
		int v = q.front();
		q.pop();
		isUsed[v] = true;
		isUndefined[v] = true;
		for (size_t i = 0; i < g[v].size(); i++) {
			int next = g[v][i];
			if (!isUsed[next]) q.push(next);
		}
	}
	for (int i = 0; i < n; i++) {
		if (d[i] == INF) cout << "*"; else {
			if (isUndefined[i]) cout << "-"; else {
				cout << d[i];
			}
		}
		cout << endl;
	}
}