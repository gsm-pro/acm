#define _CRT_SECURE_NO_DEPRECATE
#include<iostream>
#include<cmath>
#include<algorithm>
#define MID ((L+R)>>1)
#define X (1 << 16)
#define N 111
#define K 22222
#define PI ((double)acos(-1.0))
#define INF ((double)1e16)
using namespace std;
int n, m, dis[N], r[X], s[N], t[N], cost[N], T, fine;
double f[N][K], g[N][K], p[N][K], sum[N][K];

struct cp {
	double x, y;
	cp(double x = 0.0, double y = 0.0) : x(x), y(y) {}
	cp operator + (cp c) { 
		return cp(x + c.x, y + c.y);
	}
	cp operator - (cp c) { 
		return cp(x - c.x, y - c.y); 
	}
	cp operator * (cp c) { 
		return cp(x*c.x - y*c.y, x*c.y + y*c.x); 
	}
	cp operator / (int c) { 
		return cp(x / c, y / c); 
	}
}a[X], b[X];

void FFT(cp *a, int n, int op) {
	for (int i = 1; i < n; i++) {
		if (i < r[i]) {
			cp t = a[i];
			a[i] = a[r[i]];
			a[r[i]] = t;
		}
	}
	for (int i = 1; i < n; i <<= 1) {
		cp wn = cp(cos(PI / i), sin(PI / i) * op), w;
		for (int j = 0, k; j < n; j += (i << 1)) {
			for (k = 0, w = cp(1, 0); k < i; ++k, w = w * wn) {
				cp x = a[j + k], y = a[j + k + i] * w;
				a[j + k] = x + y; a[j + k + i] = x - y;
			}
		}
	}
	if (op == -1) {
		for (int i = 0; i < n; ++i) {
			a[i] = a[i] / n;
		}
	}
}

int process(cp *a, cp *b, int n) {
	int m, l;
	for (m = n, n = 1, l = 0; n <= m; n <<= 1, ++l);
	for (int i = 1; i < n; i++) {
		r[i] = (r[i >> 1] >> 1) | ((i & 1) << (l - 1));
	}
	FFT(a, n, 1);
	FFT(b, n, 1);
	for (int i = 0; i < n; i++) {
		a[i] = a[i] * b[i];
	}
	FFT(a, n, -1); 
	return n;
}

void trans(int x, int L, int R) {
	int len = R - MID - 1 + R - L - 1;
	for (int i = 0; i <= R - MID - 1; i++) {
		a[i].x = f[t[x]][i + MID + 1];
	}
	for (int i = 0; i <= R - L - 1; i++) {
		b[i].x = p[x][R - L - i];
	}
	int o = process(a, b, len);
	for (int i = L; i <= MID; i++) {
		g[x][i] += a[R - L + i - MID - 1].x;
	}
	memset(a, 0, sizeof(cp) * o); 
	memset(b, 0, sizeof(cp) * o);
}

void solve(int L, int R) {
	if (L == R) {
		for (int i = 1; i <= m; i++) {
			if (f[s[i]][L] > g[i][L] + cost[i]) {
				f[s[i]][L] = g[i][L] + cost[i];
			}
		}
		return;
	}
	solve(MID + 1, R);
	for (int i = 1; i <= m; i++) {
		trans(i, L, R);
	}
	solve(L, MID);
}

int main() {
	scanf("%d%d%d%d", &n, &m, &T, &fine);
	for (int i = 1; i <= m; i++) {
		scanf("%d%d%d", &s[i], &t[i], &cost[i]);
		for (int j = 1; j <= T; j++) {
			int o;
			scanf("%d", &o);
			p[i][j] = o / 100000.0;
		}
		for (int j = T; j >= 1; j--) {
			sum[i][j] = sum[i][j + 1] + p[i][j];
		}
	}
	memset(dis, 63, sizeof dis);
	dis[n] = 0;
	for (int i = 1; i <= n; i++) {
		for (int j = 1; j <= m; j++) {
			if (dis[s[j]] > dis[t[j]] + cost[j]) {
				dis[s[j]] = dis[t[j]] + cost[j];
			}
		}
	}
	for (int i = 0; i <= T; i++) {
		for (int j = 1; j <= n; j++) {
			f[j][i] = INF;
		}
	}
	for (int i = 1; i <= n; i++) {
		f[i][T + 1] = dis[i] + fine;
	}
	for (int i = 0; i <= T; i++) {
		f[n][i] = 0.0;
	}
	for (int i = 1; i <= m; i++) {
		for (int j = 0; j <= T; j++) {
			g[i][j] += f[t[i]][T + 1] * sum[i][T + 1 - j];
		}
	}
	solve(0, T);
	cout.precision(9);
	cout << fixed << (double)(f[1][0]);
}