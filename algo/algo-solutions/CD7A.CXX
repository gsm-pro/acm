#include<bits/stdc++.h>
using namespace std;
unordered_map<int, unordered_map<int, double>> z;
int a[16], n;

double rec(int P, int L) {
	if (L == 333) return 0;
	if (z[P].count(L)) return z[P][L];
	double r = .0, p = pow(6, -L);
	for (int k = 1; k <= 6; k++)
		r += (p * a[(P + k) % n] + rec((P + k) % n, L + 1));
	return z[P][L] = max(r, .0);
}

int main() {
	cin >> n;
	for (int i = 0; i < n; i++) cin >> a[i];
	cout << setprecision(14) << fixed << rec(0, 1);
}