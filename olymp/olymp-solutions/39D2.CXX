#include<iostream>
#include<cstdio>
using namespace std;
int t, n, m, k, i, $ = 1000000000, color[1000002], colors[1000002], cap[1000002], diff[1000002];
char c;

int next() {
	t = 0;
	while ((c = getchar()) > 0 && c != ' ' && c != '\r' && c != '\n')
		t = t * 10 + c - '0';
	return t;
}

int main() {
	freopen("input.txt", "r", stdin);
	freopen("output.txt", "w", stdout);
	scanf("%d%d%d\n", &n, &m, &k);
	for (i = 1; i <= k; i++) color[i] = next();
	for (i = 1; i <= n; i++) colors[cap[i] = next()]++;
	for (i = 1; i <= n; i++)
		if (m - n < color[cap[i]])
			k = diff[i] = m - n - (color[cap[i]] - colors[cap[i]]), $ = min($, k);
	if ($ == 1000000000) return puts("0"), 0;
	for (i = 1; i <= n; i++) if (diff[i] == $) printf("%d ", i);
	printf("\n%d", $ + 1);
}