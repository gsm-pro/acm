#include<iostream>
using namespace std;
typedef long long LL;
const int NMAX = 2000000;
#define LF(x) ((x)<<1)
#define RG(x) (((x)<<1)|1)
LL lc[NMAX], rc[NMAX], v[NMAX], nd[NMAX], ad[NMAX], s[NMAX];
void pushUp(int u);
void pushDown(int u);

inline LL length(int u) {
	return rc[u] - lc[u] + 1;
}

inline void change(int u, LL a) {
	v[u] = 1, ad[u] = 0, nd[u] = a, s[u] = a * length(u);
}

inline void process(int u, LL a, LL d) {
	if (v[u] && lc[u] != rc[u]) {
		pushDown(u);
		pushUp(u);
	}
	LL n = length(u);
	v[u] = 0, nd[u] += a, ad[u] += d, s[u] += a * n + (((n - 1) * n) / 2) * d;
}

inline void pushUp(int u) {
	s[u] = s[LF(u)] + s[RG(u)];
}

inline void pushDown(int u) {
	if (v[u]) {
		change(LF(u), nd[u]);
		change(RG(u), nd[u]);
		v[u] = nd[u] = 0;
	}
	else {
		if (nd[u] || ad[u]) {
			process(LF(u), nd[u], ad[u]);
			process(RG(u), nd[u] + length(LF(u)) * ad[u], ad[u]);
			nd[u] = ad[u] = 0;
		}
	}
}

void build(int u, int l, int r) {
	lc[u] = l, rc[u] = r, nd[u] = ad[u] = s[u] = 0;
	if (l == r) {
		return;
	}
	int mid = (l + r) >> 1;
	build(LF(u), l, mid);
	build(RG(u), mid + 1, r);
	pushUp(u);
}

void modify(int u, int l, int r, LL a, LL d) {
	if (l <= lc[u] && rc[u] <= r) {
		process(u, a + d * (lc[u] - l), d);
		return;
	}
	pushDown(u);
	LL mid = (lc[u] + rc[u]) / 2;
	if (l <= mid) {
		modify(LF(u), l, r, a, d);
	}
	if (r > mid) {
		modify(RG(u), l, r, a, d);
	}
	pushUp(u);
}

LL query(int u, int l, int r) {
	if (l <= lc[u] && rc[u] <= r) {
		return s[u];
	}
	pushDown(u);
	LL ans = 0, mid = (lc[u] + rc[u]) >> 1;
	if (l <= mid) {
		ans += query(LF(u), l, r);
	}
	if (r > mid) {
		ans += query(RG(u), l, r);
	}
	pushDown(u);
	return ans;
}

int main() {
	int type, l, r, P, N, Q;
	LL a, b;
	scanf_s("%d%d", &N, &Q);
	build(1, 1, N);
	while (Q--) {
		cin >> type;
		if (type == 1) {
			scanf_s("%d%d%I64d%I64d", &l, &r, &a, &b);
			modify(1, l, r, a, b);
		}
		if (type == 2) {
			scanf_s("%d", &P);
			printf("%I64d\n", query(1, 1, P) - query(1, 1, P - 1));
		}
	}
}