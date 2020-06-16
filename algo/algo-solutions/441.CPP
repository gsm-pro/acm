#define _CRT_SECURE_NO_DEPRECATE
#include<iostream>
#include<algorithm>
using namespace std;
const int N = 222222;
int n, m, MAXR[N << 2], ID[N << 2], T[N << 1], ANS[N];

struct nod {
	int l, r, t, id;
} L[N << 1];

inline bool cmp(nod a, nod b) {
	return a.l < b.l || (a.l == b.l && a.id < b.id);
}

void update(int L, int R, int idx, int l, int r, int t) {
	if (l == r) {
		MAXR[t] = R;
		ID[t] = idx;
		return;
	}
	int m = (l + r) >> 1;
	if (L <= m) {
		update(L, R, idx, l, m, t << 1);
	}
	else {
		update(L, R, idx, m + 1, r, t << 1 | 1);
	}
	MAXR[t] = max(MAXR[t << 1], MAXR[t << 1 | 1]);
}

int query(int pos, int R, int l, int r, int t) {
	if (R > MAXR[t]) {
		return -1;
	}
	if (l == r) {
		return ID[t];
	}
	int ans = -1, m = (l + r) >> 1;
	if (pos <= m) {
		ans = query(pos, R, l, m, t << 1);
		if (ans > 0) {
			return ans;
		}
	}
	return query(pos, R, m + 1, r, t << 1 | 1);
}

int main() {
	scanf("%d%d", &n, &m);
	for (int i = 1; i <= n + m; i++) {
		scanf("%d%d%d", &L[i].l, &L[i].r, &L[i].t);
		L[i].id = i;
		T[i] = L[i].t;
	}
	sort(T + 1, T + n + m + 1);
	sort(L + 1, L + n + m + 1, cmp);
	for (int i = 1; i <= n + m + 1; i++) {
		int p = lower_bound(T + 1, T + n + m + 1, L[i].t) - T;
		if (L[i].id <= n) {
			update(p, L[i].r, L[i].id, 1, n + m, 1);
		}
		else {
			ANS[L[i].id - n] = query(p, L[i].r, 1, n + m, 1);
		}
	}
	for (int i = 1; i <= m; i++) {
		printf("%d ", ANS[i]);
	}
}