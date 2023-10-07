#define _CRT_SECURE_NO_DEPRECATE
#include<iostream>
#include<algorithm>
#define NMAX 1111
using namespace std;
typedef long long LL;
LL f[NMAX][NMAX][4];
int tag[NMAX], an = 0, bn = 0, n, g;

struct node {
	int cost, id;

	friend bool operator < (const node &x, const node &y) {
		return x.cost < y.cost;
	}
} a[NMAX], b[NMAX];

inline void update(int x, int y, int z, LL v) {
	if (f[x][y][z] == -1 || v < f[x][y][z]) {
		f[x][y][z] = v;
	}
}

void go(int x, int y, int z) {
	if (x == 0) {
		return;
	}
	int ty = (z >> 1) ? y : y - 1;
	for (int i = 0; i < 4; i++) {
		if ((z >> 1) > 0) {
			if ((i >> 1) == (z & 1) && i < 3 && x - y> 0 && f[x - 1][ty][i] + b[x - y - 1].cost * (g - x + 1) == f[x][y][z]) {
				if (f[x - 1][ty][i] == -1) {
					continue;
				}
				go(x - 1, ty, i);
				printf("%d ", b[x - y - 1].id + 1);
				return;
			}
		}
		else {
			if ((i >> 1) == (z & 1) && i && y && f[x - 1][ty][i] + a[y - 1].cost * (g - x + 1) == f[x][y][z]) {
				if (f[x - 1][ty][i] == -1) {
					continue;
				}
				go(x - 1, ty, i);
				printf("%d ", a[y - 1].id + 1);
				return;
			}
		}
	}
}

int main() {
	freopen("input.txt", "rt", stdin);
	freopen("output.txt", "wt", stdout);
	scanf("%d%d", &g, &n);
	for (int i = 0; i < n; i++) {
		int u, v;
		scanf("%d%d", &u, &v);
		if (!v) {
			a[an].cost = u;
			a[an++].id = i;
		}
		else {
			b[bn].cost = u;
			b[bn++].id = i;
		}
	}
	sort(a, a + an);
	sort(b, b + bn);
	memset(f, -1, sizeof f);
	for (int i = 0; i < 4; i++) {
		f[0][0][i] = 0;
	}
	for (int i = 1; i <= g; i++) {
		for (int j = 0; j < i; j++) {
			for (int k = 0; k < 4; k++) {
				if (f[i - 1][j][k] > -1) {
					if (j < an && k > 0) {
						update(i, j + 1, k >> 1, f[i - 1][j][k] + a[j].cost * (g - i + 1));
					}
					if (i - 1 - j < bn && k < 3) {
						update(i, j, (k >> 1) | 2, f[i - 1][j][k] + b[i - 1 - j].cost * (g - i + 1));
					}
				}
			}
		}
	}
	int ansx, ansy;
	LL ans = -1;
	for (int i = 0; i <= an; i++) {
		for (int j = 0; j < 4; j++) {
			if (f[g][i][j] > -1) {
				if (ans == -1 || f[g][i][j] < ans) {
					ans = f[g][i][j];
					ansx = i;
					ansy = j;
				}
			}
		}
	}
	if (ans == -1) {
		printf("Impossible");
		return 0;
	}
	go(g, ansx, ansy);
}