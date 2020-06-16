#pragma comment(linker, "/STACK:251658240")
#include<iostream>
#include<vector>
#include<algorithm>
#define MAXN 111111
#define LL long long
using namespace std;
int startSeed, maxDist, threshold, N, Q, parent[MAXN], queryType[MAXN], queryNode[MAXN], curValue;
int tp[MAXN], num[MAXN], h, sz[MAXN], maxs[MAXN], y_to_id[MAXN], vis[MAXN], used[MAXN];
LL dep[MAXN], ans[MAXN], sum[MAXN], dist[MAXN];
vector<int> a[MAXN], b[MAXN];
vector<LL> w[MAXN];

int genNextRandom() {
	curValue = (curValue * 1999 + 17) % 1000003;
	return curValue;
}

void generateInput() {
	curValue = startSeed;
	for (int i = 0; i < N - 1; i++) {
		dist[i] = (LL)(genNextRandom() % maxDist);
		parent[i] = genNextRandom();
		if (parent[i] < threshold) {
			parent[i] = i;
		}
		else {
			parent[i] = parent[i] % (i + 1);
		}
	}
	for (int i = 0; i < Q; i++) {
		queryType[i] = genNextRandom() % 2 + 1;
		queryNode[i] = genNextRandom() % N;
	}
}

struct TNode {
	int id, tag, pos;
} nodes[MAXN];

vector<TNode> q[MAXN];

void dfs1(int x, int fa) {
	sz[x] = 1;
	maxs[x] = 0;
	for (size_t i = 0; i < a[x].size(); i++) {
		if (a[x][i] != fa && used[a[x][i]] == 0) {
			dfs1(a[x][i], x);
			sz[x] += sz[a[x][i]];
			maxs[x] = max(maxs[x], sz[a[x][i]]);
		}
	}
}

void dfs2(int x, int fa, int sum) {
	maxs[x] = max(maxs[x], sum - sz[x]);
	if (maxs[x] < maxs[h] || h == 0) {
		h = x;
	}
	for (size_t i = 0; i < a[x].size(); i++) {
		if (a[x][i] != fa && used[a[x][i]] == 0) {
			dfs2(a[x][i], x, sum);
		}
	}
}

int findh(int x) {
	dfs1(x, 0);
	h = 0;
	dfs2(x, 0, sz[x]);
	return h;
}

void prepare(int x, int fa, int anc, LL deep) {
	dep[x] = deep, tp[x] = anc;
	for (size_t i = 0; i < a[x].size(); i++) {
		if (a[x][i] != fa && used[a[x][i]] == 0) {
			prepare(a[x][i], x, anc, deep + w[x][i]);
		}
	}
}

void solve(int x) {
	used[x] = 1;
	for (size_t i = 0; i < a[x].size(); i++) {
		if (used[a[x][i]] == 0) {
			b[x].push_back(findh(a[x][i]));
			y_to_id[a[x][i]] = b[x].size() - 1;
		}
	}
	for (size_t i = 0; i < a[x].size(); i++) {
		if (used[a[x][i]] == 1) {
			continue;
		}
		sum[a[x][i]] = num[a[x][i]] = 0;
		prepare(a[x][i], x, a[x][i], w[x][i]);
	}
	sum[x] = num[x] = 0;
	for (size_t i = 0; i < q[x].size(); i++) {
		int id = q[x][i].id;
		int pos = q[x][i].pos;
		int tag = q[x][i].tag;
		if (pos == x) {
			if (tag == 1) {
				num[x]++;
			}
			if (tag == 2) {
				ans[id] += sum[x];
			}
			continue;
		}
		int y = tp[pos];
		if (tag == 1) {
			sum[x] += dep[pos];
			sum[y] += dep[pos];
			num[x]++;
			num[y]++;
		}
		else {
			ans[id] += (sum[x] - sum[y] + 1LL * (num[x] - num[y]) * dep[pos]);
		}
		q[b[x][y_to_id[y]]].push_back(q[x][i]);
	}
	for (size_t i = 0; i < b[x].size(); i++) {
		solve(b[x][i]);
	}
}

class Solution522 {
public:
	LL process() {
		generateInput();
		int cnt = 0;
		for (int i = 0; i < Q; i++) {
			if (queryType[i] == 1 && vis[queryNode[i]] == 1) {
				continue;
			}
			if (queryType[i] == 1) {
				vis[queryNode[i]] = 1;
			}
			nodes[cnt].pos = queryNode[i] + 1;
			nodes[cnt].tag = queryType[i];
			nodes[cnt].id = cnt;
			cnt++;
		}
		Q = cnt;
		for (int i = 2; i <= N; i++) {
			int u = i, v = parent[i - 2] + 1;
			a[u].push_back(v);
			a[v].push_back(u);
			w[u].push_back(dist[i - 2]);
			w[v].push_back(dist[i - 2]);
		}
		int x = findh(1);
		for (int i = 0; i < Q; i++) {
			q[x].push_back(nodes[i]);
		}
		solve(x);
		LL res = 0;
		for (int i = 0; i < Q; i++) {
			res ^= ans[i];
		}
		return res;
	}
} processor;

int main() {
	cin >> N >> Q >> startSeed >> threshold >> maxDist;
	cout << processor.process();
}