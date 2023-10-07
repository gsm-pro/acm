#define _CRT_SECURE_NO_DEPRECATE
#include<iostream>
#include<vector>
#include<map>
using namespace std;
const int NMAX = 111111;
int n, queries, top, fa[NMAX], a[NMAX], st[NMAX << 1], d[NMAX];
vector<int> ans;
map<int, int> Z[NMAX];

struct Edge {
	int x, y, l, r;
} e[NMAX];

int get(int x) {
	while (fa[x] != x) {
		x = fa[x];
	}
	return x;
}

int col(int x) {
	int now = 0;
	while (x != fa[x]) {
		now ^= a[x];
		x = fa[x];
	}
	return now;
}

void link(int x, int y, int D) {
	if (d[x] > d[y]) {
		swap(x, y);
	}
	if (d[x] == d[y]) {
		d[y]++;
		st[++top] = -y;
	}
	fa[x] = y;
	a[x] = D;
	st[++top] = x;
}

void w(int t) {
	for (; t < top; top--) {
		if (st[top] >= 0) {
			fa[st[top]] = st[top];
			a[st[top]] = 0;
		}
	}
}

void solve(int l, int r, int k) {
	int now = top;
	for (int i = 1; i <= k; i++) {
		if (e[i].l <= l && e[i].r >= r) {
			int u = get(e[i].x), v = get(e[i].y);
			if (u != v) {
				link(u, v, col(e[i].x) == col(e[i].y));
			}
			else {
				if (col(e[i].x) == col(e[i].y)) {
					for (int j = l; j <= r; j++) {
						ans.push_back(0);
					}
					w(now);
					return;
				}
			}
			swap(e[i], e[k--]);
			i--;
		}
	}
	if (l == r) {
		ans.push_back(1);
	}
	else {
		int mid = l + (r - l) / 2, i, j;
		for (i = 1, j = 0; i <= k; i++) {
			if (e[i].l <= mid) {
				swap(e[i], e[++j]);
			}
		}
		solve(l, mid, j);
		for (i = 1, j = 0; i <= k; i++) {
			if (e[i].r > mid) {
				swap(e[i], e[++j]);
			}
		}
		solve(mid + 1, r, j);
	}
	w(now);
}

int main() {
	int l, r, m = 0;
	scanf("%d%d", &n, &queries);
	for (int i = 1; i <= queries; i++) {
		scanf("%d%d", &l, &r);
		if (Z[l][r]) {
			e[Z[l][r]].r = i - 1;
			Z[l][r] = 0;
		}
		else {
			Z[l][r] = ++m;
			e[m].l = i;
			e[m].x = l;
			e[m].y = r;
			e[m].r = queries;
		}
	}
	for (int i = 1; i <= n; i++) {
		fa[i] = i;
		d[i] = 1;
	}
	solve(1, queries, m);
	for (int i = 0; i < queries; i++) {
		puts(ans[i] == 0 ? "NO" : "YES");
	}
}