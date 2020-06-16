#include<cstdio>
#include<algorithm>
int TOP[707], n, mn;

int main() {
	freopen("input.txt", "r", stdin);
	freopen("output.txt", "w", stdout);
	scanf("%d", &n);
	__int64 ans = 0;
	while (true) {
		int WHITE_LEFT = 0, j = 0;
		while (true) {
			char s = getchar();
			if (s == EOF) {
				printf("%I64d", ans);
				exit(0);
			}
			if (s == '\r' || s == '\n') {
				break;
			}
			if (s == '#') {
				WHITE_LEFT = TOP[j] = 0;
			}
			if (s == '.') {
				WHITE_LEFT++;
				mn = ++TOP[j];
				for (int k = j; k >= j - WHITE_LEFT + 1 && mn > 0; k--) {
					mn = std::min(mn, TOP[k]), ans += mn;
				}
			}
			++j;
		}
	}
}