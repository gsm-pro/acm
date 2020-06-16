#include<iostream>
#include<vector>
#include<algorithm>
using namespace std;
#define NMAX 3003
#define LL long long
#define LD long double
#define INF (LD)(100000000.)
#define key first
#define freq second
LD cost[NMAX][NMAX], s[NMAX] = { .0 };
int n, r[NMAX][NMAX];
pair<LL, LD> items[NMAX];

LD sum(int i, int j) {
	if (i > j) {
		return .0;
	}
	return s[j] - s[i - 1];
}

LD rec(int i, int j) {
	if (i > j) {
		return .0;
	}
	if (cost[i][j] == INF) {
		int left = (r[i][j - 1] != -1 ? r[i][j - 1] : i);
		int right = (r[i + 1][j] != -1 ? r[i + 1][j] : j);
		int bestroot = -1;
		for (int root = left; root <= right; root++) {
			LD best_cost = rec(i, root - 1) + rec(root + 1, j) + sum(i, root - 1) + sum(root + 1, j);
			if (best_cost < cost[i][j]) {
				cost[i][j] = best_cost;
				bestroot = root;
			}
		}
		r[i][j] = bestroot;
	}
	return cost[i][j];
}

int main() {
	cin >> n;
	for (int i = 1; i <= n; i++) {
		cin >> items[i].key >> items[i].freq;
	}
	sort(items + 1, items + (n + 1));
	for (int i = 1; i <= n; i++) {
		s[i] = s[i - 1] + items[i].freq;
	}
	memset(r, -1, sizeof r);
	for (int i = 1; i <= n; i++) {
		for (int j = 1; j <= n; j++) {
			cost[i][j] = INF;
		}
		cost[i][i] = .0;
	}
	cout.precision(10);
	cout << fixed << rec(1, n);
}