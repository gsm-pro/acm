#define _CRT_SECURE_NO_WARNINGS
#include<cstdio>
#include<algorithm>
int dist[2][2000002], len[2][2000002], t[2000002], s[52];
int d, n, m, g, e, i, j, cur, prev;
char c;

inline void min3(int a, int b, int c) {
	if (c <= 1 + std::min(a, b)) {
		g = c;
		e = 3;
	}
	else {
		if (b <= a) {
			g = b + 1;
			e = 2;
		}
		else {
			g = a + 1;
			e = 1;
		}
	}
}

int main() {
	freopen("input.txt", "r", stdin);
	freopen("output.txt", "w", stdout);
	while ((c = getchar()) > 0) {
		if (c == '\r' || c == '\n') {
			break;
		}
		t[m++] = c;
	}
	scanf("\n");
	while ((c = getchar()) > 0) {
		if (c == '\r' || c == '\n') {
			break;
		}
		s[n++] = c;
	}
	scanf("\n%d", &d);
	for (i = 1; i <= n; i++) {
		cur = i & 1;
		prev = cur ^ 1;
		dist[cur][0] = i;
		len[cur][0] = 0;
		for (j = 1; j <= m; j++) {
			min3(dist[prev][j], dist[cur][j - 1], dist[prev][j - 1] + (t[j - 1] == s[i - 1] ? 0 : 1));
			dist[cur][j] = g;
			len[cur][j] = ((e == 1) ? len[prev][j] : (e == 2) ? len[cur][j - 1] + 1 : len[prev][j - 1] + 1);
		}
	}
	for (i = 1; i <= m; i++) {
		if (dist[cur][i] <= d) {
			printf("%d %d", i - len[cur][i], len[cur][i]);
			return 0;
		}
	}
}