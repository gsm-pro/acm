#include<iostream>
#include<queue>
#include<vector>
#include<cassert>
using namespace std;
#define forn(i, n) for (int (i) = 0; (i) < (n); (i)++)
#define foreach(i, a) for (int (i) = 0; (i) < (int((a).size())); (i)++)
#define fill(a, val) memset((a), val, sizeof(a))
#define add push_back
#define NMAX 111111
#define KMAX 20
int enabledQty = 0;
int par[NMAX][KMAX];
vector<int> g[NMAX];
vector<int> clc;
int used[NMAX], level[NMAX], treeRoot[NMAX], k[NMAX], topEdge[NMAX], p[NMAX], have[NMAX], c[NMAX];

class SegmentTree {
private:
	struct Node {
		int val;
		int inv;
		Node() {
			val = inv = 0;
		}
	};
	vector<Node> t;
	int n;

	void add(int v, int tl, int tr) {
		if (tl != tr && t[v].inv) {
			int mid = (tl + tr) >> 1;
			t[v << 1].inv ^= 1;
			t[v << 1].val = (mid + 1 - tl) - t[v << 1].val;
			t[(v << 1) + 1].inv ^= 1;
			t[(v << 1) + 1].val = (tr - mid) - t[(v << 1) + 1].val;
		}
		t[v].inv = 0;
	}

	void update(int v, int tl, int tr, int l, int r) {
		if (tl == l && tr == r) {
			enabledQty -= t[v].val;
			t[v].val = (tr - tl + 1) - t[v].val;
			enabledQty += t[v].val;
			t[v].inv ^= 1;
			return;
		}
		add(v, tl, tr);
		int mid = (tl + tr) >> 1;
		if (r <= mid) {
			update(v << 1, tl, mid, l, r);
		}
		else if (mid < l) {
			update((v << 1) + 1, mid + 1, tr, l, r);
		}
		else {
			update((v << 1), tl, mid, l, mid);
			update((v << 1) + 1, mid + 1, tr, mid + 1, r);
		}
		t[v].val = t[v << 1].val + t[(v << 1) + 1].val;
	}

	int get(int v, int tl, int tr, int l, int r) {
		if (tl == l && tr == r) {
			return t[v].val;
		}
		add(v, tl, tr);
		int mid = (tl + tr) >> 1;
		if (r <= mid) {
			return get(v << 1, tl, mid, l, r);
		}
		if (mid < l) {
			return get((v << 1) + 1, mid + 1, tr, l, r);
		}
		return get(v << 1, tl, mid, l, mid) + get((v << 1) + 1, mid + 1, tr, mid + 1, r);
	}

public:
	SegmentTree() {
	}

	SegmentTree(int _n) {
		n = _n;
		t.assign(((n + 1) << 2), Node());
	}

	int get(int l, int r) {
		assert(1 <= l && l <= r && r <= n);
		return get(1, 1, n, l, r);
	}

	void update(int l, int r) {
		assert(1 <= l && l <= r && r <= n);
		update(1, 1, n, l, r);
	}
} segmentTrees[NMAX];

int dsu_find(int v) {
	if (p[v] == v) {
		return v;
	}
	return p[v] = dsu_find(p[v]);
}

void dsu_unite(int u, int v) {
	u = dsu_find(u);
	v = dsu_find(v);
	p[u] = v;
	have[v] += have[u];
}

class TreeDecomposition {
private:
	int root;
	queue<int> q;

	void dfs1(int v, int p) {
		k[v] = 1;
		used[v] = 1;
		level[v] = level[p] + 1;
		par[v][0] = p;
		for (int i = 1; i < KMAX; ++i) {
			par[v][i] = par[par[v][i - 1]][i - 1];
		}
		treeRoot[v] = treeRoot[p];
		int toMax = -1;
		foreach(i, g[v]) {
			int to = g[v][i];
			if (used[to] == 0) {
				dfs1(to, v);
				k[v] += k[to];
				if (toMax == -1 || k[to] > k[toMax]) {
					toMax = to;
				}
			}
		}
		if (toMax != -1 && k[v] < (k[toMax] << 1)) {
			dsu_unite(toMax, v);
		}
	}

	void dfs2(int v) {
		if (p[v] == v && have[v] > 1) {
			segmentTrees[v] = SegmentTree(have[v] - 1);
		}
		used[v] = 1;
		foreach(i, g[v]) {
			int to = g[v][i];
			if (used[to] == 0) {
				dfs2(to);
			}
		}
	}

public:
	TreeDecomposition() {
	}

	void build(int _root) {
		root = _root;
		treeRoot[root] = root;
		dfs1(root, root);
	}

	void decompose() {
		dfs2(root);
	}

	int lca(int v, int u) {
		int d = level[v] - level[u];
		if (d < 0) {
			swap(v, u);
			d = -d;
		}
		for (int i = KMAX; i--; ) {
			if (i >= 0 && ((d >> i) & 1)) {
				v = par[v][i];
			}
		}
		if (u == v) {
			return v;
		}
		for (int i = KMAX; i--;) {
			if (i >= 0 && par[v][i] != par[u][i]) {
				v = par[v][i];
				u = par[u][i];
			}
		}
		return par[u][0];
	}

	void switchEdges(int a, int b) {
		while (dsu_find(a) != dsu_find(b)) {
			int p = dsu_find(b);
			if (p == b) {
				enabledQty -= topEdge[b];
				topEdge[b] ^= 1;
				enabledQty += topEdge[b];
				b = par[b][0];
			}
			else {
				segmentTrees[p].update(1, level[b] - level[p]);
				b = p;
			}
		}
		if (a != b) {
			segmentTrees[dsu_find(a)].update(level[a] - level[dsu_find(a)] + 1, level[b] - level[dsu_find(a)]);
		}
	}
} treeDecompositions[NMAX];

bool go(int v, int p) {
	clc.add(v);
	used[v] = 1;
	foreach(i, g[v]) {
		int to = g[v][i];
		if (to == p) {
			continue;
		}
		if (used[to] == 1) {
			clc.add(to);
			return true;
		}
		if (go(to, v)) {
			return true;
		}
	}
	clc.pop_back();
	return false;
}

int main() {
	int n, queriesCount;
	cin >> n >> queriesCount;
	forn(i, n) {
		int u, v;
		cin >> u >> v;
		--v, --u;
		g[v].add(u);
		g[u].add(v);
	}
	go(0, -1);
	foreach(i, clc) {
		if (clc[i] == clc.back()) {
			assert(i + 1 != clc.size());
			rotate(clc.begin(), clc.begin() + i + 1, clc.end());
			clc.resize(clc.size() - i - 1);
			break;
		}
	}
	fill(c, -1);
	fill(used, 0);
	foreach(i, clc) {
		int v = clc[i];
		c[v] = i;
		treeRoot[v] = v;
		used[v] = 1;
	}
	forn(i, n) {
		have[i] = 1, p[i] = i;
	}
	foreach(i, clc) {
		treeDecompositions[clc[i]].build(clc[i]);
	}
	fill(used, 0);
	foreach(i, clc) {
		used[clc[i]] = 1;
	}
	foreach(i, clc) {
		treeDecompositions[clc[i]].decompose();
	}
	SegmentTree clcSegmentTree(clc.size());
	forn(i, queriesCount) {
		int u, v;
		cin >> u >> v;
		--u, --v;
		if (treeRoot[u] == treeRoot[v]) {
			int idx = treeRoot[u];
			int w = treeDecompositions[idx].lca(u, v);
			treeDecompositions[idx].switchEdges(w, u);
			treeDecompositions[idx].switchEdges(w, v);
		}
		else {
			int idx1 = c[treeRoot[u]], idx2 = c[treeRoot[v]];
			int len1 = abs(idx2 - idx1), len2 = clc.size() - len1;
			int left = clc[(idx1 - 1 + clc.size()) % clc.size()];
			int right = clc[(idx1 + 1) % clc.size()];
			if (idx1 > idx2) {
				swap(idx1, idx2);
				swap(left, right);
			}
			if (len1 < len2 || (len1 == len2 && left > right)) {
				clcSegmentTree.update(idx1 + 1, idx2);
			}
			else {
				if (idx1 > 0) {
					clcSegmentTree.update(1, idx1);
				}
				clcSegmentTree.update(idx2 + 1, clc.size());
			}
			treeDecompositions[treeRoot[v]].switchEdges(treeRoot[u], u);
			treeDecompositions[treeRoot[u]].switchEdges(treeRoot[v], v);
		}
		cout << n - enabledQty + (clcSegmentTree.get(1, clc.size()) == clc.size()) << endl;
	}
}