#define _CRT_SECURE_NO_WARNINGS
#include<iostream>
#include<algorithm>
#include<cmath>
using namespace std;
#define EPS 1e-8
#define INF 1e10

int main() {
	freopen("input.txt", "r", stdin);
	freopen("output.txt", "w", stdout);
	int n, m;
	scanf_s("%d%d", &n, &m);
	double x[333], y[333];
	double g[333][333];
	double dp[333];
	int used[333] = {};
	for (int i = 0; i < n; i++) {
		scanf_s("%lf%lf", &x[i], &y[i]);
		dp[i] = INF;
	}
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++) {
			g[i][j] = hypot(x[i] - x[j], y[i] - y[j]);
		}
	}
	dp[n - 1] = 0;
	for (int i = 0; i < n; i++) {
		int u = -1;
		for (int j = 0; j < n; j++) {
			if (used[j] == 0 && (u == -1 || dp[u] > dp[j])) {
				u = j;
			}
		}
		used[u] = 1;
		for (int j = 0; j < n; j++) {
			if (used[j]) {
				continue;
			}
			double w = g[u][j];
			if (m >= dp[u] + 2 * w) {
				dp[j] = min(dp[j], dp[u] + w);
			}
			else {
				if (m >= 3 * w) {
					double times = ceil((dp[u] - (m - 2 * w)) / (m - 3 * w));
					dp[j] = min(dp[j], dp[u] + times * (2 * w) + w);
				}
			}
		}
	}
	if (dp[0] != INF) {
		printf("%.9lf", dp[0]);
	}
	else {
		puts("-1");
	}
}