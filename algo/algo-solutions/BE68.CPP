#include<iostream>
#include<vector>
#include<set>
using namespace std;
typedef pair<int, int> SEGMENT_TREE_ITEM;
const int N = 333333;
int dsuP[N], dsuR[N];
vector<pair<int*, int>> HISTORY;

int DSU_root(int v) {
	while (dsuP[v] != -1) {
		v = dsuP[v];
	}
	return v;
}

void DSU_unite(int a, int b) {
	a = DSU_root(a);
	b = DSU_root(b);
	if (a == b) {
		return;
	}
	if (dsuR[a] > dsuR[b]) {
		HISTORY.emplace_back(make_pair(&dsuP[b], dsuP[b]));
		dsuP[b] = a;
	}
	else if (dsuR[a] < dsuR[b]) {
		HISTORY.emplace_back(make_pair(&dsuP[a], dsuP[a]));
		dsuP[a] = b;
	}
	else {
		HISTORY.emplace_back(make_pair(&dsuP[a], dsuP[a]));
		HISTORY.emplace_back(make_pair(&dsuR[b], dsuR[b]));
		dsuP[a] = b;
		dsuR[b]++;
	}
}

struct Query {
	int qtype, u, v;
	bool ans;
} QUERIES[N];
int n, m;
vector<SEGMENT_TREE_ITEM> SEGMENT_TREE[N << 2];

void addEdge(int l, int r, SEGMENT_TREE_ITEM z, int c, int cl, int cr) {
	if (l > cr || r < cl) {
		return;
	}
	if (l <= cl && cr <= r) {
		SEGMENT_TREE[c].push_back(z);
		return;
	}
	int m = (cl + cr) >> 1;
	addEdge(l, r, z, (c << 1) + 1, cl, m);
	addEdge(l, r, z, (c << 1) + 2, m + 1, cr);
}

void dfs(int c, int cl, int cr) {
	int startSize = HISTORY.size();
	for (int i = 0; i < (int)SEGMENT_TREE[c].size(); i++) {
		SEGMENT_TREE_ITEM z = SEGMENT_TREE[c][i];
		DSU_unite(z.first, z.second);
	}
	if (cl == cr) {
		if (QUERIES[cl].qtype == 1) {
			QUERIES[cl].ans = (DSU_root(QUERIES[cl].u) == DSU_root(QUERIES[cl].v));
		}
	}
	else {
		int m = (cl + cr) >> 1;
		dfs((c << 1) + 1, cl, m);
		dfs((c << 1) + 2, m + 1, cr);
	}
	while ((int)HISTORY.size() > startSize) {
		*HISTORY.back().first = HISTORY.back().second;
		HISTORY.pop_back();
	}
}

int main() {
	cin >> n >> m;
	for (int i = 0; i < n; i++) {
		dsuP[i] = -1;
	}
	set<pair<SEGMENT_TREE_ITEM, int>> edges;
	for (int i = 0; i < m; ++i) {
		cin >> QUERIES[i].qtype >> QUERIES[i].u >> QUERIES[i].v;
		if (QUERIES[i].u > QUERIES[i].v) {
			swap(QUERIES[i].u, QUERIES[i].v);
		}
		if (QUERIES[i].qtype == 2) {
			edges.emplace(make_pair(SEGMENT_TREE_ITEM(QUERIES[i].u, QUERIES[i].v), i));
		}
		else if (QUERIES[i].qtype == 3) {
			set<pair<SEGMENT_TREE_ITEM, int>>::iterator iter = edges.lower_bound(make_pair(SEGMENT_TREE_ITEM(QUERIES[i].u, QUERIES[i].v), 0));
			addEdge(iter->second, i, iter->first, 0, 0, m - 1);
			edges.erase(iter);
		}
	}
	for (set<pair<SEGMENT_TREE_ITEM, int>>::iterator it = edges.begin(); it != edges.end(); it++) {
		addEdge(it->second, m - 1, it->first, 0, 0, m - 1);
	}
	dfs(0, 0, m - 1);
	for (int i = 0; i < m; i++) {
		if (QUERIES[i].qtype == 1) {
			puts(QUERIES[i].ans ? "1" : "0");
		}
	}
}