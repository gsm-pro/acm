#include<iostream>
#include<algorithm>
#include<vector>
using namespace std;
#define ITER(i, n) for(int i = 0; i < n; i++)
vector<vector<int>> g;
int n, m, c[1100011], u[1100011];
vector<int> p;

void dfs(int v) {
	if (u[v]) {
		return;
	}
	u[v] = 1;
	if (g[v].size() & 1) {
		c[v] = 1;
	}
	ITER(i, g[v].size()) {
		int nxt = g[v][i];
		if (!u[nxt]) {
			dfs(nxt);
			c[v] += c[nxt];
		}
	}
}

int main() {
	scanf_s("%d%d", &n, &m);
	g.resize(n);
	ITER(i, m) {
		int x, y;
		scanf_s("%d%d", &x, &y);
		--x, --y;
		g[x].push_back(y);
		g[y].push_back(x);
	}
	ITER(i, n) {
		if (!u[i]) {
			if (i && !g[i].size()) {
				continue;
			}
			dfs(i);
			p.push_back(c[i]);
		}
	}
	int ans = 0;
	if (p.size() == 1) {
		ans = p[0] >> 1;
	}
	else {
		ITER(i, p.size()) {
			ans += max(2, p[i]);
		}
		ans >>= 1;
	}
	cout << ans;
}