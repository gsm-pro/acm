#include<iostream>
#include<algorithm>
using namespace std;
#define mid ((l + r) >> 1)
#define lf (cur << 1)
#define rg (cur << 1 | 1)
const int NMAX = 111111;
int N, Q, cnt = 0, fa[NMAX], f[NMAX], sz[NMAX], up[NMAX], edge[NMAX], deep[NMAX],
chld[NMAX], q[NMAX], W[NMAX << 1], M[NMAX << 1], F[NMAX], ans[NMAX];

struct Event {
	int c, d, a, b;
	Event() {}
	Event(int _c, int _d, int _a, int _b) {
		c = _c, d = _d, a = _a, b = _b;
	}
} evts[NMAX << 1];

struct TreeItem {
	int ls, rs, len, val;
	TreeItem() {
		ls = 0, rs = 0, len = 0, val = 0;
	}
} ST[NMAX << 2];

bool cmp(Event x, Event y) {
	if (x.c != y.c) {
		return x.c > y.c;
	}
	return x.d < y.d;
}

void push(int a, int b) {
	++cnt, W[cnt] = b, M[cnt] = F[a], F[a] = cnt;
}

void desint() {
	int qhead = 0, qtail = 1;
	memset(chld, 0, sizeof chld);
	memset(fa, 0, sizeof fa);
	memset(deep, 0, sizeof deep);
	memset(sz, 0, sizeof sz);
	q[1] = 1, deep[1] = 0, fa[1] = 0;
	while (qhead != qtail) {
		int x = q[++qhead];
		for (int p = F[x]; p > 0; p = M[p]) {
			if (W[p] != fa[x]) {
				q[++qtail] = W[p];
				deep[W[p]] = deep[x] + 1;
				fa[W[p]] = x;
			}
		}
	}
	for (int i = N, x; i > 0; i--) {
		sz[x = q[i]]++;
		if (fa[x]) {
			sz[fa[x]] += sz[x];
			if (!chld[fa[x]] || sz[x] > sz[chld[fa[x]]]) {
				chld[fa[x]] = x;
			}
		}
	}
	int num = 0;
	for (int i = N; i > 0; i--) {
		int x = q[i];
		if (chld[x]) {
			continue;
		}
		while (fa[x] && chld[fa[x]] == x) {
			x = fa[x];
		}
		int y = x;
		while (x > 0) {
			up[x] = y, edge[x] = ++num, x = chld[x];
		}
	}
}

TreeItem operator + (const TreeItem &a, const TreeItem &b) {
	TreeItem rti;
	rti.len = a.len + b.len;
	rti.ls = a.ls;
	if (a.ls == a.len) {
		rti.ls = a.len + b.ls;
	}
	rti.rs = b.rs;
	if (b.rs == b.len) {
		rti.rs = b.len + a.rs;
	}
	rti.val = a.val + b.val - f[a.rs] - f[b.ls] + f[a.rs + b.ls];
	return rti;
}

void build(int cur, int l, int r) {
	ST[cur].len = r - l + 1;
	ST[cur].val = ST[cur].ls = ST[cur].rs = 0;
	if (l != r) {
		build(lf, l, mid), build(rg, mid + 1, r);
	}
}

void modify(int cur, int l, int r, int pos) {
	if (l == r) {
		ST[cur].val = f[1];
		ST[cur].ls = ST[cur].rs = 1;
		return;
	}
	if (pos <= mid) {
		modify(lf, l, mid, pos);
	}
	else {
		modify(rg, mid + 1, r, pos);
	}
	ST[cur] = ST[lf] + ST[rg];
}

TreeItem query(int cur, int l, int r, int ql, int qr) {
	if (ql <= l && r <= qr) {
		return ST[cur];
	}
	TreeItem qti;
	if (ql <= mid) {
		qti = qti + query(lf, l, mid, ql, qr);
	}
	if (qr > mid) {
		qti = qti + query(rg, mid + 1, r, ql, qr);
	}
	return qti;
}

void update(int a, int b) {
	if (deep[a] < deep[b]) {
		swap(a, b);
	}
	modify(1, 1, N, edge[a]);
}

int query(int x, int y) {
	TreeItem tix, tiy, tiy_inv;
	while (up[x] != up[y]) {
		if (deep[up[x]] < deep[up[y]]) {
			swap(x, y), swap(tix, tiy);
		}
		tix = query(1, 1, N, edge[up[x]], edge[x]) + tix;
		x = fa[up[x]];
	}
	if (deep[x] < deep[y]) {
		swap(x, y), swap(tix, tiy);
	}
	tiy_inv = tiy;
	swap(tiy_inv.ls, tiy_inv.rs);
	TreeItem ans = tiy_inv + query(1, 1, N, edge[y] + 1, edge[x]) + tix;
	return ans.val;
}

int main() {
	scanf_s("%d%d", &N, &Q);
	f[0] = f[N] = 0;
	for (int i = 1; i < N; i++) {
		scanf_s("%d", &f[i]);
	}
	int all = 0, u, v, l;
	for (int i = 1; i < N; i++) {
		scanf_s("%d%d%d", &u, &v, &l);
		push(u, v), push(v, u);
		evts[++all] = Event(l, 0, u, v);
	}
	for (int i = 1; i <= Q; i++) {
		scanf_s("%d%d%d", &u, &v, &l);
		evts[++all] = Event(l, i, u, v);
	}
	sort(evts + 1, evts + 1 + all, cmp);
	desint();
	build(1, 1, N);
	for (int i = 1; i <= all; i++) {
		if (evts[i].d == 0) {
			update(evts[i].a, evts[i].b);
		}
		else {
			ans[evts[i].d] = query(evts[i].a, evts[i].b);
		}
	}
	for (int i = 1; i <= Q; i++) {
		printf("%d\n", ans[i]);
	}
}