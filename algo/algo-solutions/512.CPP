#include<iostream>
#include<vector>
#include<algorithm>
using namespace std;
const int MAXN = 222222;
int n, k, a[MAXN], t[MAXN], sz[MAXN], dp[MAXN], t_cnt[MAXN], ans, cnt;
vector<int> g[MAXN];

void reInit(int val) {
	ans = cnt = 0;
	for (int i = 1; i <= n; i++) {
		t[i] = a[i] >= val;
		cnt += t[i];
	}
	memset(t_cnt, 0, sizeof t_cnt);
}

void dfs1(int cur, int fa) {
	sz[cur] = 1;
	for (size_t i = 0; i < g[cur].size(); i++) {
		int u = g[cur][i];
		if (u == fa) {
			continue;
		}
		dfs1(u, cur);
		sz[cur] += sz[u];
	}
}

void dfs2(int cur, int fa) {
	if (ans >= k) {
		return;
	}
	int all = 0, max1 = 0, max2 = 0;
	for (size_t i = 0; i < g[cur].size(); i++) {
		int u = g[cur][i];
		if (u == fa) {
			continue;
		}
		dfs2(u, cur);
		t_cnt[cur] += t_cnt[u];
		if (dp[u] == sz[u]) {
			all += dp[u];
		}
		else {
			if (dp[u] > max1) {
				max2 = max1, max1 = dp[u];
			}
			else {
				if (dp[u] > max2) {
					max2 = dp[u];
				}
			}
		}
	}
	if (!t[cur]) {
		dp[cur] = 0;
	}
	else {
		dp[cur] = all + max1 + 1;
		t_cnt[cur]++;
	}
	if (n - sz[cur] == cnt - t_cnt[cur]) {
		all += n - sz[cur];
	}
	if (t[cur]) {
		ans = max(ans, all + max1 + max2 + 1);
	}
}

int main() {
	scanf_s("%d%d", &n, &k);
	for (int i = 1; i <= n; i++) {
		scanf_s("%d", &a[i]);
	}
	for (int i = 1; i < n; i++) {
		int u, v;
		scanf_s("%d%d", &u, &v);
		g[u].push_back(v);
		g[v].push_back(u);
	}
	int l = 1, r = (1 << 24);
	dfs1(1, 0);
	while (l <= r) {
		int mid = (l + r) >> 1;
		reInit(mid);
		dfs2(1, 0);
		if (ans >= k) {
			l = mid + 1;
		}
		else {
			r = mid - 1;
		}
	}
	cout << r;
}