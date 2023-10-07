#include<fstream>
#include<vector>
#include<algorithm>
#include<cmath>
#include<unordered_map>
using namespace std;
ifstream I("input.txt");
ofstream O("output.txt");
unordered_map<int, double> Z;
double w[16][16][16];
int n, a[16];

double rec(int m) {
	if (m == (1 << n) - 1) return .0;
	if (Z.count(m)) return Z[m];
	int cur = 0;
	while ((m >> cur) & 1) cur++;
	double res = rec(m | (1 << cur));
	for (int i = cur; i < n; i++) {
		if (!((m >> i) & 1)) {
			for (int j = i + 1; j < n; j++) {
				if (!((m >> j) & 1)) {
					for (int k = j + 1; k < n; k++) {
						if (!((m >> k) & 1)) {
							if (w[i][j][k] > 0) {
								res = max(res, w[i][j][k] + rec(m | (1 << i) | (1 << j) | (1 << k)));
							}
						}
					}
				}
			}
		}
	}
	return Z[m] = res;
}

int main() {
	O.precision(12);
	I >> n;
	for (int i = 0; i < n; i++) I >> a[i];
	for (int i = 0; i < n; i++)
		for (int j = 0; j < n; j++)
			for (int k = 0; k < n; k++)
				if (i != j && i != k && j != k) {
					vector<double> e;
					e.push_back(a[i]);
					e.push_back(a[j]);
					e.push_back(a[k]);
					sort(e.begin(), e.end());
					if (e[2] <= e[0] + e[1]) {
						double p = .5 * (a[i] + a[j] + a[k]);
						w[i][j][k] = sqrt(p * (p - a[i]) * (p - a[j]) * (p - a[k]));
					}
					else {
						w[i][j][k] = -1.;
					}
				}
	O << fixed << rec(0);
}