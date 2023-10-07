#define _CRT_SECURE_NO_WARNINGS
#include<iostream>
#include<cstdio>
#include<cstring>
#include<algorithm>
#include<cmath>
#define INF (1<<29)
#define N 303
using namespace std;
typedef long long llg;
int n, m, h[N][N], ans;
int f[9][N][N], g[N][N];

int getint() {
	int w = 0;
	bool q = 0;
	char c = getchar();
	while ((c > '9' || c < '0') && c != '-') {
		c = getchar();
	}
	if (c == '-') {
		c = getchar(), q = 1;
	}
	while (c >= '0'&&c <= '9') {
		w = w * 10 + c - '0', c = getchar();
	}
	return q ? -w : w;
}

bool check() {
	for (int i = 1; i <= n; i++) {
		if (g[i][i] < 0) {
			return 1;
		}
	}
	return 0;
}

int main() {
	n = getint(), m = getint();
	for (int i = 1; i <= n; i++) {
		for (int j = 1; j <= n; j++) {
			f[0][i][j] = h[i][j] = INF;
		}
	}
	for (int i = 1; i <= n; i++) {
		f[0][i][i] = h[i][i] = 0;
	}
	for (int i = 1; i <= m; i++) {
		int u = getint(), v = getint();
		f[0][u][v] = min(f[0][u][v], -getint());
		f[0][v][u] = min(f[0][v][u], -getint());
	}
	for (int i = 1; i < 9; i++) {
		for (int u = 1; u <= n; u++) {
			for (int v = 1; v <= n; v++) {
				f[i][u][v] = f[i - 1][u][v];
			}
		}
		for (int u = 1; u <= n; u++) {
			for (int v = 1; v <= n; v++) {
				for (int k = 1; k <= n; k++) {
					f[i][u][k] = min(f[i][u][k], f[i - 1][u][v] + f[i - 1][v][k]);
				}
			}
		}
	}
	for (int i = 8; i >= 0; i--) {
		for (int u = 1; u <= n; u++) {
			for (int v = 1; v <= n; v++) {
				g[u][v] = h[u][v];
			}
		}
		for (int u = 1; u <= n; u++) {
			for (int v = 1; v <= n; v++) {
				for (int k = 1; k <= n; k++) {
					g[u][k] = min(g[u][k], f[i][u][v] + h[v][k]);
				}
			}
		}
		if (!check()) {
			ans += 1 << i;
			for (int u = 1; u <= n; u++) {
				for (int v = 1; v <= n; v++) {
					h[u][v] = g[u][v];
				}
			}
		}
	}
	printf("%d", ans > n ? 0 : ans + 1);
}