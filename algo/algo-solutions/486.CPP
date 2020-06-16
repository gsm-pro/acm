#include<iostream>
#include<algorithm>
using namespace std;
int f[100001][43];
__int64 w[100001][43], m[100001][43];

int main() {
	__int64 n, k;
	cin >> n >> k;
	for (int i = 0; i < n; i++) {
		cin >> f[i][0];
	}
	for (int i = 0; i < n; i++) {
		cin >> w[i][0];
		m[i][0] = w[i][0];
	}
	for (int p = 1; p <= 42; p++) {
		for (int i = 0; i < n; i++) {
			int next = f[i][p - 1];
			f[i][p] = f[next][p - 1];
			w[i][p] = w[next][p - 1] + w[i][p - 1];
			m[i][p] = min(m[next][p - 1], m[i][p - 1]);
		}
	}
	for (int i = 0; i < n; i++) {
		__int64 s = 0, mn = INT_MAX;
		int j = i;
		for (int p = 0; p <= 42; p++) {
			if (k & (1LL << p)) {
				s += w[j][p];
				mn = min(mn, m[j][p]);
				j = f[j][p];
			}
		}
		printf("%I64d %I64d\n", s, mn);
	}
}