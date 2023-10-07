#pragma GCC optimize("Ofast")
#pragma GCC optimize("unroll-loops")
#pragma GCC target("avx,avx2,tune=native")
#include<cstdio>
int TOP[707], n;

int main() {
	freopen("input.txt", "r", stdin);
	freopen("output.txt", "w", stdout);
	scanf("%d\n", &n);
	long long ans = 0;
	for (;;) {
		int LEFT = 0, j = 0, anstmp = 0, h;
		for (;;) {
			char s = getchar();
			if (s == EOF) return printf("%I64d", ans + anstmp), 0;
			if (s == '\r' || s == '\n') break;
			if (s == '#') LEFT = TOP[j] = 0;
			if (s == '.') {
				LEFT++;
				h = ++TOP[j];
				for (int k = j; k >= j - LEFT + 1 && h > 0; k--) {
					if (TOP[k] < h) h = TOP[k];
					anstmp += h;
				}
			}
			j++;
		}
		ans += anstmp;
	}
}