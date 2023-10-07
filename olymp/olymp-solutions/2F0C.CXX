#include<bits/stdc++.h>
__int64 i, j, k, n, d, x, s, mn = 1e9, a[100010];

int main() {
    std::ifstream I("input.txt");
	I >> n;
	for (i = 0; i < n; i++) I >> a[i];
	for (i = -1; i <= 1; i++)
		for (j = -1; j <= 1; j++) {
			d = a[1] + j - a[0] - i;
			s = abs(i);
			for (k = 1; k < n; k++) {
				x = abs(a[k] - (a[0] + i + k * d));
				if (x > 1) break;
				s += x;
			}
			if (k == n) mn = std::min(mn, s);
		}
	std::ofstream("output.txt") << (mn < 1e9 ? mn : -1);
}