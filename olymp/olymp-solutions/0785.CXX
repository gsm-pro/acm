#include<bits/stdc++.h>
#define int __int64

struct node {
	int a, b, c;
};

const int inf = 2147483647;
int to[1000010][26], w[1000010], k[1000010], n, m, t, cnt, scnt, S, T, ans, ansf, tot = 1;
int fa[1000010], son[1000010], v[260026], d[260026], pre[260026], head[260026],
ver[520052], next[520052], flow[520052], cost[520052], mode[520052];
std::vector<node> $;
char c[505], s[1000010];

void insert(char* s, int l, int ww, int mm) {
	int p = 0;
	for (int i = l - 1; i >= 0; i--) {
		int ch = s[i] - 'a';
		if (!to[p][ch]) to[p][ch] = ++cnt;
		p = to[p][ch];
	}
	if (!w[p])
		w[p] = ww, k[p] = mm;
	else if (w[p] > ww)
		w[p] = ww, k[p] = mm;
}

int spfa() {
	std::queue<int> q;
	for (int i = 1; i <= T; i++) d[i] = 100000000000001;
	memset(v, 0, sizeof v);
	memset(pre, 0, sizeof pre);
	d[S] = 0, v[S] = 1;
	q.push(S);
	while (q.size()) {
		int u = q.front();
		q.pop();
		v[u] = 0;
		for (int i = head[u]; i; i = next[i]) {
			if (!flow[i]) continue;
			if (d[ver[i]] > d[u] + cost[i]) {
				d[ver[i]] = d[u] + cost[i];
				pre[ver[i]] = i;
				if (!v[ver[i]]) {
					q.push(ver[i]);
					v[ver[i]] = 1;
				}
			}
		}
	}
	return d[T] <= 100000000000000;
}

void addflow() {
	int i = T, mn = 2147483647;
	while (pre[i]) {
		mn = std::min(mn, flow[pre[i]]);
		i = ver[pre[i] ^ 1];
	}
	ans += mn * d[T];
	ansf += mn;
	i = T;
	while (pre[i]) {
		flow[pre[i]] -= mn;
		flow[pre[i] ^ 1] += mn;
		i = ver[pre[i] ^ 1];
	}
}

void add(int u, int v, int f, int c) {
	ver[++tot] = v, next[tot] = head[u], flow[tot] = f, cost[tot] = c, head[u] = tot;
	ver[++tot] = u, next[tot] = head[v], flow[tot] = 0, cost[tot] = -c, head[v] = tot;
}

signed main() {
	freopen("input.txt", "r", stdin);
	freopen("output.txt", "w", stdout);
	scanf("%lld %lld %lld", &n, &m, &t);
	for (int i = 2; i <= n; i++) scanf("%lld %c", &fa[i], &c[i]), son[fa[i]]++;
	for (int i = 1, x; i <= m; i++) {
		scanf("%lld ", &x);
		scanf("%s", s);
		insert(s, strlen(s), x, i);
	}
	S = n + 1, T = n + 2;
	for (int i = 2; i <= n; i++) {
		for (int x = i, p = 0; x != 1; x = fa[x]) {
			int ch = c[x] - 'a';
			if (!to[p][ch]) break;
			p = to[p][ch];
			if (w[p]) add(i, fa[x], inf, w[p]), mode[tot - 1] = k[p];
		}
		add(fa[i], i, inf, 0);
		if (son[i] >= 2) add(i, T, son[i] - 1, 0);
		if (!son[i]) add(S, i, 1, 0), scnt++;
	}
	add(1, T, son[1], 0);
	while (spfa()) addflow();
	if (ansf != scnt) return puts("-1"), 0;
	printf("%lld", ans);
	if (!t) return 0;
	for (int i = 2; i <= tot; i++)
		if (mode[i] && flow[i ^ 1]) $.push_back((node) { ver[i], ver[i ^ 1], mode[i] });
	printf("\n%d\n", $.size());
	for (int i = 0; i != $.size(); i++) printf("%lld %lld %lld\n", $[i].a, $[i].b, $[i].c);
}