#include<iostream>
#include<map>
#include<cstdio>
#include<algorithm>
using namespace std;
typedef long long LL;
const int MOD = 399989;
const int P = 31;
map<LL, int> g[MOD];
map<LL, int> g_full[MOD];
char s[1000 * 1000 * 10 + 11];

int main() {
	gets_s(s);
	int n = atoi(s);
	for (int i = 1; i <= n; i++) {
		gets_s(s);
		LL h = 0LL;
		int len = (int)strlen(s);
		for (int j = 1; j < len; j++) {
			h = h * P * (h & 1 ? P : 1) + (s[j - 1] - 'a' + 1);
			g[j % MOD][h]++;
		}
		h = h * P * (h & 1 ? P : 1) + (s[len - 1] - 'a' + 1);
		g_full[len % MOD][h] = i;
	}
	gets_s(s);
	int q = atoi(s);
	for (int i = 1; i <= q; i++) {
		gets_s(s);
		LL h_full = 0LL;
		for (size_t j = 1; j <= strlen(s); j++) {
			h_full = h_full * P * (h_full & 1 ? P : 1) + (s[j - 1] - 'a' + 1);
		}
		int block = strlen(s) % MOD;
		int ans_first = 0, ans_second = -1;
		if (g[block].count(h_full)) {
			ans_first = g[block][h_full];
		}
		if (g_full[block].count(h_full)) {
			ans_first++;
			ans_second = g_full[block][h_full];
		}
		printf("%d %d\n", ans_first, ans_second);
	}
}