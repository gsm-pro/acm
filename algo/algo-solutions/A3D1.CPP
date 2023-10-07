#include<iostream>
using namespace std;
#define N 130
#define L 16
#define V 10
typedef long long I64;
int a1, a2, b1, b2, l1, l2, L1, L2, OL1, OL2;
I64 g1[N][N], g2[N][N];
I64 r1[L][N], r2[L][N];
I64 rr[V][N * 2];
I64 ans = 0;

inline void unpack(int v, int *w) {
	for (int i = 0; i < V; i++) w[i] = v & 1, v = v >> 1;
}

int get(int v1, int v2, int l) {
	int a[V], b[V], r[V + 5];
	unpack(v1, a);
	unpack(v2, b);
	memset(r, 0, sizeof r);
	r[0] = 1;
	for (int i = 0; i <= l; i++) {
		if (!a[i]) {
			if (!b[i]) {
				if ((!a[i + 1]) && (b[i + 1])) {
					r[i + 2] += r[i];
				}
				else {
					continue;
				}
			}
			else {
				if (!a[i + 1]) {
					if (!b[i + 1]) {
						r[i + 2] += r[i];
					}
					else {
						if ((b[i + 2]) && (!a[i + 2])) {
							r[i + 3] += 2 * r[i];
						}
						else {
							continue;
						}
					}
				}
				else {
					if (b[i + 1]) {
						r[i + 2] += r[i];
					}
					else {
						continue;
					}
				}
			}
		}
		else {
			if (!b[i]) {
				r[i + 1] += r[i];
			}
			else {
				if ((!a[i + 1]) && (b[i + 1])) {
					r[i + 2] += r[i];
				}
				else {
					continue;
				}
			}
		}
	}
	return r[l];
}

I64 go1(int v1, int v2) {
	if ((v1 & 1) && (v2 & 1)) return 0LL;
	for (int i = 0; i < V; i++) for (int j = 0; j < N; j++) rr[i][j] = 0LL;
	for (int i = 0; i < L1; i++) rr[0][i] = 0LL;
	rr[0][v1] = 1LL;
	for (int i = 0; i < l2; i++) {
		for (int j = 0; j < L1; j++) {
			if ((v1 & 1) && (v2 & 1)) continue;
			for (int k = 0; k < L1; k++) rr[i + 1][j] += rr[i][k] * g1[k | (v2 & 1)][j];
		}
		v2 = v2 >> 1;
	}
	return rr[l2][0];
}

I64 go2(int v1, int v2) {
	v1 = v1 << 1;
	v2 = (v2 << 1) + 1;
	if ((v1 & 1) && (v2 & 1)) return 0LL;
	for (int i = 0; i < V; i++) for (int j = 0; j < N; j++) rr[i][j] = 0LL;
	for (int i = 0; i < L1; i++) rr[0][i] = 0LL;
	rr[0][v1] = 1LL;
	for (int i = 0; i < l2; i++) {
		for (int j = 0; j < L1; j++) {
			if (((v2 >> 1) & 1) && (j & 1) && (i != 0)) continue;
			for (int k = 0; k < L1; k++) rr[i + 1][j] += rr[i][k] * g1[k | (v2 & 1)][j];
		}
		v2 = v2 >> 1;
	}
	return rr[l2][0];
}

int main() {
	cin >> a1 >> b1 >> a2 >> b2;
	if (a1 == b1 && a2 == b2) {
		cout << 1;
		return 0;
	}
	if ((a1*a2 - b1*b2) % 3 != 0) {
		cout << 0;
		return 0;
	}
	l1 = a1 - b1;
	l2 = a2 - b2;
	L1 = 1 << l1;
	L2 = 1 << l2;
	for (int i = 0; i < L; i++) for (int j = 0; j < N; j++) r1[i][j] = 0LL, r2[i][j] = 0LL;
	for (int i = 0; i < L1; i++) for (int j = 0; j < L1; j++) g1[i][j] = (I64)get(i, j, l1);
	for (int i = 0; i < L2; i++) for (int j = 0; j < L2; j++) g2[i][j] = (I64)get(i, j, l2);
	for (int i = 0; i < L1; i++) r1[0][i] = 0LL;
	r1[0][0] = 1LL;
	for (int i = 0; i < b2; i++) for (int j = 0; j < L1; j++) for (int k = 0; k < L1; k++) {
		r1[i + 1][j] += r1[i][k] * g1[k][j];
	}
	for (int i = 0; i < L2; i++) r2[0][i] = 0LL;
	r2[0][0] = 1LL;
	for (int i = 0; i < b1; i++) for (int j = 0; j < L2; j++) for (int k = 0; k < L2; k++) {
		r2[i + 1][j] += r2[i][k] * g2[k][j];
	}
	if (b1 == 0 || b2 == 0) {
		if (b1 == 0) l1 = a1, l2 = a2, L1 = 1 << l1;
		if (b2 == 0) l1 = a2, l2 = a1, L1 = 1 << l1;
		for (int i = 0; i < L1; i++) for (int j = 0; j < L1; j++) g1[i][j] = (I64)get(i, j, l1);
		for (int i = 0; i <= l2; i++) for (int j = 0; j < L1; j++) r1[i][j] = 0LL;
		r1[0][0] = 1LL;
		for (int i = 0; i < l2; i++) for (int j = 0; j < L1; j++) for (int k = 0; k < L1; k++) {
			r1[i + 1][j] += r1[i][k] * g1[k][j];
		}
		cout << r1[l2][0];
		return 0;
	}
	OL1 = L1, OL2 = L2;
	l1++, l2++;
	L1 = 1 << l1, L2 = 1 << l2;
	for (int i = 0; i < L1; i++) for (int j = 0; j < L1; j++) g1[i][j] = get(i, j, l1);
	for (int i = 0; i < OL1; i++) for (int j = 0; j < OL2; j++) {
		if (r1[b2 - 1][i] > 0 && r2[b1 - 1][j] > 0) {
			ans += r1[b2 - 1][i] * r2[b1 - 1][j] * go2(i, j);
		}
	}
	cout << ans;
}