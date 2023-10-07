#include<iostream>
#include<vector>
#include<algorithm>
using namespace std;
const int NMAX = 100001;
const int NMAXLOG = 20;
int p[NMAX][NMAXLOG], h[NMAX];
vector<int> s[NMAX][NMAXLOG], g[NMAX];

vector<int> merge(const vector<int> &a, const vector<int> &b) {
	vector<int> r;
	int i = 0, j = 0;
	while ((int)r.size() < (NMAXLOG >> 1) && (i < (int)a.size() || j < (int)b.size())) {
		if (i == a.size()) {
			r.push_back(b[j]);
			j++;
		}
		else if (j == b.size() || a[i] < b[j]) {
			r.push_back(a[i]);
			i++;
		}
		else {
			r.push_back(b[j]);
			j++;
		}
	}
	return r;
}

void dfs(int u, int par, int depth) {
	h[u] = depth;
	p[u][0] = par;
	for (int i = 1; p[u][i - 1] != -1; i++) {
		p[u][i] = p[p[u][i - 1]][i - 1];
		s[u][i] = merge(s[u][i - 1], s[p[u][i - 1]][i - 1]);
	}
	for (size_t i = 0; i < g[u].size(); i++) {
		int v = g[u][i];
		if (v != par) {
			dfs(g[u][i], u, depth + 1);
		}
	}
}

vector<int> query(int a, int b) {
	if (h[a] < h[b]) {
		swap(a, b);
	}
	vector<int> r;
	for (int i = NMAXLOG - 1; h[b] < h[a]; i--) {
		if (p[a][i] != -1 && h[p[a][i]] >= h[b]) {
			r = merge(r, s[a][i]);
			a = p[a][i];
		}
	}
	for (int i = NMAXLOG - 1; p[a][0] != p[b][0]; i--) {
		if (p[a][i] != p[b][i]) {
			r = merge(r, merge(s[a][i], s[b][i]));
			a = p[a][i];
			b = p[b][i];
		}
	}
	if (a == b) {
		return merge(r, s[a][0]);
	}
	return merge(r, merge(s[a][1], s[b][0]));
}

int main() {
	memset(p, -1, NMAX * NMAXLOG * sizeof(int));
	int n, m, q, c, u, v, a;
	scanf_s("%d%d%d", &n, &m, &q);
	for (int i = 0; i < n - 1; i++) {
		scanf_s("%d%d", &u, &v);
		u--, v--;
		g[u].push_back(v);
		g[v].push_back(u);
	}
	for (int i = 0; i < m; i++) {
		cin >> c;
		s[c - 1][0].push_back(i + 1);
	}
	for (int i = 0; i < n; i++) {
		sort(s[i][0].begin(), s[i][0].end());
	}
	dfs(0, -1, 0);
	for (int i = 0; i < q; i++) {
		scanf_s("%d%d%d", &v, &u, &a);
		v--, u--;
		vector<int> r = query(v, u);
		int k = min(a, (int)r.size());
		printf("%d ", k);
		for (int j = 0; j < k; j++) {
			printf("%d ", r[j]);
		}
		puts("");
	}
}