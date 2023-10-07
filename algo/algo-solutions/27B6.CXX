#define _CRT_SECURE_NO_DEPRECATE
#include<cstdio>
#include<cstring>
#include<iostream>
#include<algorithm>
using namespace std;
typedef long long LL;
const LL MODULO = 1000000007LL;
const int NMAX = 222222;
LL ST1[NMAX << 2], ST2[NMAX << 2];
int id[NMAX], pos[NMAX], minv[NMAX], maxv[NMAX], f[NMAX], a[NMAX], timer, e, n, m;
int to[NMAX << 1], nxt[NMAX << 1], st[NMAX], dpth[NMAX], sz[NMAX], son[NMAX], top[NMAX];

int read() {
	int x = 0;
	char ch = getchar();
	while (!isdigit(ch)) {
		ch = getchar();
	}
	while (isdigit(ch)) {
		x = (x << 3) + (x << 1) + ch - '0', ch = getchar();
	}
	return x;
}

void init() {
	e = 0;
	timer = 0;
	memset(f, 0, sizeof f);
	memset(st, 0, sizeof st);
	memset(ST1, 0, sizeof ST1);
	memset(ST2, 0, sizeof ST2);
	memset(maxv, 0, sizeof maxv);
	memset(son, 0, sizeof son);
}

void add(int x, int y) {
	to[++e] = y;
	nxt[e] = st[x];
	st[x] = e;
}

void dfs1(int x, int fa) {
	int maxsize = 0;
	sz[x] = 1;
	f[x] = fa;
	for (int i = st[x]; i; i = nxt[i]) {
		if (to[i] == fa) {
			continue;
		}
		dpth[to[i]] = dpth[x] + 1;
		dfs1(to[i], x);
		sz[x] += sz[to[i]];
		if (sz[to[i]] > maxsize) {
			maxsize = sz[to[i]];
			son[x] = to[i];
		}
	}
}

void dfs2(int x) {
	pos[x] = ++timer;
	id[timer] = x;
	minv[x] = maxv[x] = timer;
	if (x == 1) {
		top[x] = x;
	}
	else {
		if (son[f[x]] == x) {
			top[x] = top[f[x]];
		}
		else {
			top[x] = x;
		}
	}
	if (son[x]) {
		dfs2(son[x]);
		maxv[x] = max(maxv[x], maxv[son[x]]);
	}
	for (int i = st[x]; i; i = nxt[i]) {
		if (to[i] == f[x] || to[i] == son[x]) {
			continue;
		}
		dfs2(to[i]);
		maxv[x] = max(maxv[x], maxv[to[i]]);
	}
}

void alter(LL ST[], int h, int l, int r, int L, int R, int val) {
	if (L <= l && r <= R) {
		ST[h] += (r - l + 1) * val;
		ST[h] %= MODULO;
		return;
	}
	int mid = (l + r) >> 1;
	if (L <= mid) {
		alter(ST, h << 1, l, mid, L, R, val);
	}
	if (R > mid) {
		alter(ST, h << 1 | 1, mid + 1, r, L, R, val);
	}
	ST[h] = (ST[h << 1] + ST[h << 1 | 1]) % MODULO;
}

LL select(LL ST[], int h, int l, int r, int L, int R) {
	if (L <= l && r <= R) {
		return ST[h];
	}
	int mid = (l + r) >> 1;
	LL ans = 0;
	if (L <= mid) {
		ans += select(ST, h << 1, l, mid, L, R);
	}
	if (R > mid) {
		ans += select(ST, h << 1 | 1, mid + 1, r, L, R);
	}
	return ans % MODULO;
}

void update(int pos, int val) {
	int x = top[pos];
	while (f[x]) {
		LL sum = select(ST1, 1, 1, n, minv[x], maxv[x]);
		alter(ST2, 1, 1, n, minv[f[x]], minv[f[x]],
			((1LL * (a[pos] - val) * (a[pos] - val) - 2 * sum * (a[pos] - val)) % MODULO + MODULO) % MODULO);
		x = top[f[x]];
	}
	alter(ST1, 1, 1, n, minv[pos], minv[pos], val - a[pos]);
	a[pos] = val;
}

LL calc(int s, int t) {
	int top1 = top[s], top2 = top[t];
	LL res = 0;
	while (top1 != top2) {
		if (dpth[top1] < dpth[top2]) {
			swap(top1, top2);
			swap(s, t);
		}
		res = (res + select(ST2, 1, 1, n, pos[top1], pos[s])) % MODULO;
		if (son[s]) {
			LL sum = select(ST1, 1, 1, n, minv[son[s]], maxv[son[s]]);
			res = (res + sum * sum) % MODULO;
		}
		LL sum = select(ST1, 1, 1, n, minv[top[top1]], maxv[top[top1]]);
		res = (res - sum * sum) % MODULO;
		s = f[top1];
		top1 = top[s];
	}
	if (dpth[s] > dpth[t]) {
		swap(s, t);
	}
	res = (res + select(ST2, 1, 1, n, pos[s], pos[t])) % MODULO;
	if (son[t]) {
		LL sum = select(ST1, 1, 1, n, minv[son[t]], maxv[son[t]]);
		res = (res + sum * sum) % MODULO;
	}
	if (f[s]) {
		LL sum = select(ST1, 1, 1, n, 1, n) - select(ST1, 1, 1, n, minv[s], maxv[s]);
		res = (res + sum * sum) % MODULO;
	}
	return res;
}

int main() {
	scanf("%*d");
	while (scanf("%d%d", &n, &m) == 2) {
		init();
		for (int i = 1; i <= n; i++) {
			a[i] = read();
		}
		for (int i = 1; i < n; i++) {
			int x, y;
			x = read();
			y = read();
			add(x, y);
			add(y, x);
		}
		dfs1(1, 0);
		dfs2(1);
		for (int i = 1; i <= n; i++) {
			int tmp = a[i];
			a[i] = 0;
			update(i, tmp);
		}
		for (int i = 1; i <= m; i++) {
			int type = read();
			if (type == 1) {
				int pos = read(), val = read();
				update(pos, val);
			}
			else {
				int s = read(), t = read();
				LL sum = select(ST1, 1, 1, n, 1, n);
				sum = (sum * sum) % MODULO;
				sum = ((sum - calc(s, t)) % MODULO + MODULO) % MODULO;
				printf("%lld\n", sum);
			}
		}
	}
}