#include<vector>
#include<iostream>
#include<algorithm>
using namespace std;
#define INF 100
#define ITERATIONS 5000
double d[1 << 6][6];
vector<int> p;
int n, i, j, k, iters;

int main() {
	cin >> n;
	p.resize(n);
	for (i = 0; i < n; i++) cin >> p[i];
	for (i = 1; i < (1 << n); i++)
		for (j = 0; j < n; j++)
			d[i][j] = INF;
	for (j = 0; j < n; j++) d[0][j] = d[1 << j][j] = 0;
	for (i = 1; i < (1 << n); i++) {
		if (!((i & (i - 1)))) {
			continue;
		}
		for (iters = 0; iters < ITERATIONS; iters++) {
			for (j = 0; j < n; j++) {
				int n1 = -1, n2 = -1;
				for (k = (j + 1) % n; n2 == -1; k = (k + 1) % n) {
					if ((i >> k) & 1) {
						if (n1 == -1) n1 = k; else n2 = k;
					}
				}
				double w = INF;
				for (k = 0; k < n; k++) {
					if (((i >> k) & 1) && k != j) {
						w = min(w, d[i - (1 << k)][(k == n1) ? n2 : n1]);
					}
				}
				d[i][j] = 1 + (d[i][n1] * (100 - p[j]) + w * p[j]) / 100.0;
			}
		}
	}
	cout.precision(15);
	cout << fixed << d[(1 << n) - 1][0];
}