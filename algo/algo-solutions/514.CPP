#include<iostream>
#include<vector>
#include<algorithm>
using namespace std;
#define forn(i, n) for (int (i) = 0; (i) < (n); (i)++)
#define foreach(i, a) for (int (i) = 0; (i) < (int((a).size())); (i)++)
#define fill(a, val) memset((a), val, sizeof(a))
#define add push_back
#define NMAX 111111
int n, queriesCount, u, v, timer = 0, cnt = 1;
vector<int> g[NMAX];
int v_next[NMAX], sz[NMAX], p[NMAX], c[NMAX], time[NMAX], c_sz[NMAX], topEdge[NMAX], depth[NMAX], maximum[NMAX];

class SegmentTree {
private:
	int t[NMAX << 2];

public:
	void update(int v, int tl, int tr, int pos, int val) {
		if (tl == tr) {
			t[v] += val;
			return;
		}
		int mid = (tl + tr) >> 1;
		if (pos <= mid) {
			update(v << 1, tl, mid, pos, val);
		}
		else {
			update((v << 1) + 1, mid + 1, tr, pos, val);
		}
		t[v] = max(t[v << 1], t[(v << 1) + 1]);
	}

	int get(int v, int tl, int tr, int l, int r) {
		if (l > tr || r < tl) {
			return 0;
		}
		if (l <= tl && r >= tr) {
			return t[v];
		}
		int mid = (tl + tr) >> 1;
		return max(get(v << 1, tl, mid, l, r), get((v << 1) + 1, mid + 1, tr, l, r));
	}
} segmentTree;

int query(int a, int b) {
	int result = 0;
	while (c[a] != c[b]) {
		if (depth[topEdge[c[a]]] < depth[topEdge[c[b]]]) {
			swap(a, b);
		}
		int start = topEdge[c[a]];
		if (time[a] == time[start] + c_sz[c[a]] - 1) {
			result = max(result, maximum[c[a]]);
		}
		else {
			result = max(result, segmentTree.get(1, 0, n - 1, time[start], time[a]));
		}
		a = p[start];
	}
	if (depth[a] > depth[b]) {
		swap(a, b);
	}
	return max(result, segmentTree.get(1, 0, n - 1, time[a], time[b]));
}

void go(int v, int t) {
	p[v] = t;
	sz[v] = 1;
	foreach(i, g[v]) {
		int to = g[v][i];
		if (to == t) {
			continue;
		}
		depth[to] = depth[v] + 1;
		go(to, v);
		sz[v] += sz[to];
		if (v_next[v] == -1 || sz[to] > sz[v_next[v]]) {
			v_next[v] = to;
		}
	}
}

void heavy_light(int v, int t) {
	c[v] = cnt - 1;
	time[v] = timer++;
	if (c_sz[cnt - 1] == 0) {
		topEdge[cnt - 1] = v;
	}
	c_sz[cnt - 1]++;
	if (v_next[v] != -1) {
		heavy_light(v_next[v], v);
	}
	foreach(i, g[v]) {
		int to = g[v][i];
		if (to == t || to == v_next[v]) {
			continue;
		}
		cnt++;
		heavy_light(to, v);
	}
}

void prepare() {
	fill(v_next, -1);
	go(0, 0);
	heavy_light(0, -1);
}

void increase(int v, int val) {
	segmentTree.update(1, 0, n - 1, time[v], val);
	int s = time[topEdge[c[v]]];
	maximum[c[v]] = segmentTree.get(1, 0, n - 1, s, s + c_sz[c[v]] - 1);
}

int main() {
	cin >> n;
	forn(i, n - 1) {
		cin >> u >> v;
		u--, v--;
		g[u].add(v);
		g[v].add(u);
	}
	prepare();
	cin >> queriesCount;
	forn(i, queriesCount) {
		char q;
		cin >> q >> u >> v;
		if (q == 'I') {
			u--;
			increase(u, v);
		}
		if (q == 'G') {
			u--, v--;
			cout << query(u, v) << endl;
		}
	}
}