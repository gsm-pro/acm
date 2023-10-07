#include<bits/stdc++.h>
#define Z 111111
int ch[Z][2], fa[Z], rev[Z], mn[Z], val[Z], ls[Z << 4], rs[Z << 4], siz[Z << 4],
rt[Z], f[Z], a[Z], b[Z], s[Z], st[Z], stp, total;
char c;

int root(int x) {
	return x == f[x] ? x : f[x] = root(f[x]);
}

int read() {
	int t = 0;
	while ((c = getchar()) > 0 && c != ' ' && c != '\r' && c != '\n')
		t = (t << 3) + (t << 1) + c - 48;
	return t;
}

bool ir(int x) {
	return ch[fa[x]][1] != x && ch[fa[x]][0] != x;
}

void rv(int x) {
	rev[x] ^= 1;
}

void pd(int x) {
	if (rev[x]) std::swap(ch[x][0], ch[x][1]), rv(ch[x][0]), rv(ch[x][1]), rev[x] = 0;
}

void pu(int x) {
	mn[x] = x;
	if (val[mn[ch[x][0]]] < val[mn[x]]) mn[x] = mn[ch[x][0]];
	if (val[mn[ch[x][1]]] < val[mn[x]]) mn[x] = mn[ch[x][1]];
}

void rotate(int x) {
	int y = fa[x], z = fa[y], R = (ch[y][1] == x);
	if (!ir(y)) ch[z][ch[z][1] == y] = x;
	fa[x] = z, fa[y] = x, fa[ch[x][R ^ 1]] = y, ch[y][R] = ch[x][R ^ 1], ch[x][R ^ 1] = y;
	pu(y), pu(x);
}

void splay(int x) {
	stp = 0, st[++stp] = x;
	for (int y = x; !ir(y); y = fa[y]) st[++stp] = fa[y];
	for (int i = stp; i; --i) pd(st[i]);
	while (!ir(x)) {
		int y = fa[x], z = fa[y];
		if (!ir(y)) {
			if ((ch[z][1] == y) != (ch[y][1] == x)) rotate(x); else rotate(y);
		}
		rotate(x);
	}
}

void access(int x) {
	for (int y = 0; x; y = x, x = fa[x]) splay(x), ch[x][1] = y, pu(x);
}

void makeroot(int x) {
	access(x), splay(x), rv(x);
}

void split(int x, int y) {
	makeroot(x), access(y), splay(y);
}

void link(int x, int y) {
	makeroot(x), fa[x] = y;
}

inline void cut(int x, int y) {
	split(x, y), ch[y][0] = 0, fa[x] = 0, pu(y);
}

void insert(int& p, int q, int l, int r, int x) {
	if (!p) p = ++total;
	siz[p] = siz[q] + 1;
	if (l == r) return;
	int mid = (l + r) >> 1;
	if (x <= mid)
		rs[p] = rs[q], insert(ls[p], ls[q], l, mid, x);
	else
		ls[p] = ls[q], insert(rs[p], rs[q], mid + 1, r, x);
}

int query(int p, int q, int l, int r, int x) {
	if (r <= x) return siz[p] - siz[q];
	int mid = (l + r) >> 1;
	if (x > mid) return siz[ls[p]] - siz[ls[q]] + query(rs[p], rs[q], mid + 1, r, x);
	return query(ls[p], ls[q], l, mid, x);
}

int main() {
	int n = read(), m = read(), x, y, i, pos, q;
	val[0] = 1000000000;
	for (i = 1; i <= n; i++) f[i] = i, val[i] = 1000000000;
	for (i = 1; i <= m; i++) {
		a[i] = x = read(), b[i] = y = read();
		val[i + n] = i, mn[i + n] = i + n;
		if (x == y) {
			insert(rt[i], rt[i - 1], 0, m, m);
			continue;
		}
		if (root(x) ^ root(y)) link(x, i + n), link(i + n, y), f[root(x)] = root(y);
		else {
			split(x, y);
			pos = mn[y], s[i] = pos - n;
			cut(pos, a[pos - n]), cut(pos, b[pos - n]), link(x, i + n), link(i + n, y);
		}
		insert(rt[i], rt[i - 1], 0, m, s[i]);
	}
	q = read();
	while (q--) x = read(), printf("%d\n", n - query(rt[read()], rt[x - 1], 0, m, x - 1));
}