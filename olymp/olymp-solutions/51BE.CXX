#include<bits/stdc++.h>
using namespace std;

__int64 m(__int64 x) {
	__int64 y = sqrt(x);
	while (y * y > x) --y;
	while ((y + 1) * (y + 1) <= x) ++y;
	return y;
}

int main() {
	__int64 a, b, k, ans = 0;
	ifstream("input.txt") >> a >> b >> k;
	for (__int64 y = 1; y * y * y <= b; ++y) {
		__int64 yyy = y * y * y;
		if (yyy < a) continue;
		ans += max(0LL, m(min(b, yyy + k)) - (m(max(a, yyy - k) - 1) + 1) + 1);
	}
	ofstream("output.txt") << ans;
}