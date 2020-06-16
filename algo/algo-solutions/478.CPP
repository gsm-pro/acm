#include<iostream>
typedef long long LL;
const LL OO = 1LL << 50;
const int Z = 606;
LL A[Z][Z], AA[Z][Z], B[Z][Z], BB[Z][Z], Q[Z][Z], QQ[Z][Z], L;
int n, nn, m, k, kk, u, v;

int main() {
	scanf_s("%d%d%d", &n, &m, &k);
	bool k2 = (k == 2);
	nn = (k2 ? 2 * n : n);
	int d = k2 ? n : 0;
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++) {
			A[i][j] = OO;
		}
	}
	for (int i = 0; i < nn; i++) {
		for (int j = 0; j < nn; j++) {
			AA[i][j] = OO;
		}
	}
	while (m--) {
		scanf_s("%d%d%I64d", &u, &v, &L);
		--u, --v;
		if (L < A[u][v]) {
			A[u][v] = A[v][u] = AA[u][v] = AA[v][u] = L;
		}
	}
	for (int i = 0; i < n; i++) {
		AA[i][i + d] = AA[i + d][i] = AA[i + d][i + d] = 0;
	}
	if (k == 0) {
		for (int i = 0; i < n; i++) {
			for (int j = 0; j < n; j++) {
				if (i == j) {
					printf("0 ");
				}
				else {
					printf("-1 ");
				}
			}
			printf("\n");
		}
		printf("\n");
		for (int i = 0; i < n; i++) {
			for (int j = 0; j < n; j++) {
				if (i == j) {
					printf("0 ");
				}
				else {
					printf("-1 ");
				}
			}
			printf("\n");
		}
		return 0;
	}
	if (k == 1) {
		for (int i = 0; i < n; i++) {
			for (int j = 0; j < n; j++) {
				if (AA[i][j] < OO) {
					printf("%I64d ", AA[i][j]);
				}
				else {
					printf("-1 ");
				}
			}
			printf("\n");
		}
		printf("\n");
		for (int i = 0; i < n; i++) {
			for (int j = 0; j < n; j++) {
				if (A[i][j] < OO) {
					printf("%I64d ", A[i][j]);
				}
				else {
					printf("-1 ");
				}
			}
			printf("\n");
		}
		return 0;
	}
	kk = k, k--;
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++) {
			B[i][j] = A[i][j];
		}
	}
	for (int i = 0; i < nn; i++) {
		for (int j = 0; j < nn; j++) {
			BB[i][j] = AA[i][j];
		}
	}
	while (kk > 0) {
		if (kk & 1) {
			for (int i = 0; i < nn; i++) {
				for (int j = 0; j < nn; j++) {
					LL tt = OO;
					for (int e = 0; e < nn; e++) {
						if (tt > BB[i][e] + AA[e][j]) {
							tt = BB[i][e] + AA[e][j];
						}
					}
					QQ[i][j] = tt;
				}
			}
			memcpy(BB, QQ, sizeof QQ);
		}
		kk >>= 1;
		for (int i = 0; i < nn; i++) {
			for (int j = 0; j < nn; j++) {
				LL tt = OO;
				for (int e = 0; e < nn; e++) {
					if (tt > AA[i][e] + AA[e][j]) {
						tt = AA[i][e] + AA[e][j];
					}
				}
				QQ[i][j] = tt;
			}
		}
		memcpy(AA, QQ, sizeof QQ);
	}
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++) {
			if (BB[i][j + d] < OO) {
				printf("%I64d ", BB[i][j + d]);
			}
			else {
				printf("-1 ");
			}
		}
		printf("\n");
	}
	printf("\n");
	while (k > 0) {
		if (k & 1) {
			for (int i = 0; i < n; i++) {
				for (int j = 0; j < n; j++) {
					LL t = OO;
					for (int e = 0; e < n; e++) {
						if (t > B[i][e] + A[e][j]) {
							t = B[i][e] + A[e][j];
						}
					}
					Q[i][j] = t;
				}
			}
			memcpy(B, Q, sizeof Q);
		}
		k >>= 1;
		for (int i = 0; i < n; i++) {
			for (int j = 0; j < n; j++) {
				LL t = OO;
				for (int e = 0; e < n; e++) {
					if (t > A[i][e] + A[e][j]) {
						t = A[i][e] + A[e][j];
					}
				}
				Q[i][j] = t;
			}
		}
		memcpy(A, Q, sizeof Q);
	}
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++) {
			if (B[i][j] < OO) {
				printf("%I64d ", B[i][j]);
			}
			else {
				printf("-1 ");
			}
		}
		printf("\n");
	}
}