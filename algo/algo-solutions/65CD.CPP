#include<vector>
#include<iostream>
#include<set>
#include<algorithm>
using namespace std;
const int N = 111;
vector<int> g[N];
int match[N], p[N], base[N], q[N];
bool used[N], blossom[N];
int n, m;

int lca(int a, int b) {
	bool used[N] = { 0 };
	for (;;) {
		a = base[a];
		used[a] = true;
		if (match[a] == -1) {
			break;
		}
		a = p[match[a]];
	}
	for (;;) {
		b = base[b];
		if (used[b]) {
			return b;
		}
		b = p[match[b]];
	}
}

void mark_path(int v, int b, int children) {
	while (base[v] != b) {
		blossom[base[v]] = blossom[base[match[v]]] = true;
		p[v] = children;
		children = match[v];
		v = p[match[v]];
	}
}

int edmonds_find_path(int root) {
	memset(used, 0, sizeof used);
	memset(q, 0, sizeof q);
	memset(p, -1, sizeof p);
	for (int i = 0; i < n; i++) {
		base[i] = i;
	}
	used[root] = true;
	int qh = 0, qt = 0;
	q[qt++] = root;
	while (qh < qt) {
		int v = q[qh++];
		for (size_t j = 0; j < g[v].size(); j++) {
			int to = g[v][j];
			if (base[v] == base[to] || match[v] == to) {
				continue;
			}
			if (to == root || match[to] != -1 && p[match[to]] != -1) {
				int curbase = lca(v, to);
				memset(blossom, 0, sizeof blossom);
				mark_path(v, curbase, to);
				mark_path(to, curbase, v);
				for (int i = 0; i < n; i++) {
					if (blossom[base[i]]) {
						base[i] = curbase;
						if (!used[i]) {
							used[i] = true;
							q[qt++] = i;
						}
					}
				}
			}
			else if (p[to] == -1) {
				p[to] = v;
				if (match[to] == -1) {
					return to;
				}
				to = match[to];
				used[to] = true;
				q[qt++] = to;
			}
		}
	}
	return -1;
}

int main() {
	while (cin >> n >> m) {
		for (int i = 0; i < N; i++) {
			g[i].clear();
		}
		for (int i = 0; i < m; i++) {
			int a, b;
			cin >> a >> b;
			--a, --b;
			g[a].push_back(b);
			g[b].push_back(a);
		}
		memset(match, -1, sizeof match);
		for (int i = 0; i < n; i++) {
			if (match[i] == -1) {
				int v = edmonds_find_path(i);
				while (v != -1) {
					int pv = p[v], ppv = match[pv];
					match[v] = pv, match[pv] = v;
					v = ppv;
				}
			}
		}
		set<pair<int, int>> r;
		for (int i = 0; i < n; i++) {
			if (match[i] != -1) {
				r.insert(make_pair(min(i + 1, match[i] + 1), max(i + 1, match[i] + 1)));
			}
		}
		cout << r.size() << endl;
		for (set<pair<int, int>>::iterator it = r.begin(); it != r.end(); it++) {
			cout << it->first << " " << it->second << endl;
		}
		cout << endl;
	}
}