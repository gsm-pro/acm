#define _CRT_SECURE_NO_DEPRECATE
#include<iostream>
#define NMAX 101010
#define INF 10000000
int p[NMAX], a[3], total[8], con[20][20], b[3][8], q[20], g[20], f[20], n;

inline int min(int x, int y) {
	return x < y ? x : y;
}

int bfs() {
	int i, p, an;
	memset(g, -1, sizeof g);
	an = 1, q[0] = 11, f[11] = INF, g[11] = 0;
	for (p = 0; p < an; p++) {
		for (i = 0; i < 13; i++) {
			if (con[q[p]][i] > 0 && g[i] == -1) {
				f[i] = min(f[q[p]], con[q[p]][i]);
				g[i] = q[p];
				q[an++] = i;
			}
		}
	}
	return g[12] > -1;
}

int check() {
	int i, j, k;
	memset(b, 0, sizeof b);
	for (i = 0; i < 3; i++) {
		for (j = 0; j < 8; j++) {
			b[i][j] = con[3 + j][i];
		}
	}
	for (i = 0; i < 3; i++) {
		k = a[i] - (con[i][11] * 2);
		for (j = 0; j < 8 && k > 0; j++) {
			if (con[3 + j][12] > 0) {
				int tmp = min(k, con[3 + j][12]);
				k -= tmp;
				con[3 + j][12] -= tmp;
				b[i][j] += tmp;
			}
		}
		if (k > 0) {
			return 0;
		}
	}
	for (i = 0; i < n; i++) {
		k = p[i];
		for (j = 0; j < 3; j++) {
			if (b[j][k] > 0 || j == 2) {
				p[i] = j;
				b[j][k]--;
				break;
			}
		}
	}
	return 1;
}

int main() {
	freopen("input.txt", "rt", stdin);
	freopen("output.txt", "wt", stdout);
	int i, j, k;
	for (i = 0; i < 3; i++) {
		scanf("%d", a + i);
	}
	memset(total, 0, sizeof total);
	scanf("%d", &n);
	for (i = 0; i < n; i++) {
		char s[10];
		scanf("%s", s);
		for (j = k = 0; j < 3; j++) {
			if (s[j] == 'B') {
				k |= 1 << j;
			}
		}
		total[k]++;
		p[i] = k;
	}
	memset(con, 0, sizeof con);
	for (i = 0; i < 3; i++) {
		con[11][i] = a[i] >> 1;
	}
	for (i = 0; i < 8; i++) {
		con[3 + i][12] = total[i];
	}
	for (i = 0; i < 3; i++) {
		for (j = 0; j < 8; j++) {
			if ((j & (1 << i)) > 0) {
				con[i][3 + j] = INF;
			}
		}
	}
	while (1) {
		if (!bfs()) {
			break;
		}
		for (i = 12; i != 11; i = g[i]) {
			con[g[i]][i] -= f[12];
			con[i][g[i]] += f[12];
		}
	}
	if (check()) {
		for (i = 0; i < n; i++) {
			if (p[i] == 0) {
				printf("P");
			}
			else {
				if (p[i] == 1) {
					printf("O");
				}
				else {
					printf("S");
				}
			}
		}
		return 0;
	}
	printf("no solution");
}