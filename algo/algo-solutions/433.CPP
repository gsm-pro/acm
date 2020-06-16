#include<iostream>
#include<map>
#include<cstdio>
#include<cstring>
#include<vector>
#include<algorithm>
using namespace std;
typedef long long LL;
map<int, int> g[1024];
vector<int> z[1024];
char s[1000 * 1000 * 10 + 11];

int main() {
	gets_s(s);
	int n = atoi(s);
	for (int i = 1; i <= n; i++) {
		gets_s(s);
		int h = 0;
		int len = (int)strlen(s);
		for (int j = 1; j < len; j++) {
			h = (h << 5) + h + (s[j - 1] - 'a' + 1);
			z[j & 1023].push_back(h);
		}
		h = (h << 5) + h + (s[len - 1] - 'a' + 1);
		z[len & 1023].push_back(h);
		g[len & 1023][h] = i;
	}
	gets_s(s);
	int q = atoi(s);
	char c[15], w;
	for (int v = 0; v < 1024; v++) {
		if (z[v].size() > 1) {
			sort(z[v].begin(), z[v].end());
		}
	}
	for (int i = 1; i <= q; i++) {
		int h_full = 0;
		int len = 0;
		while ((w = getchar()) > 0) {
			if (w == '\r' || w == '\n') {
				break;
			}
			len++;
			h_full = (h_full << 5) + h_full + (w - 'a' + 1);
		}
		int ans_first = 0, block = len & 1023;
		if (binary_search(z[block].begin(), z[block].end(), h_full)) {
			ans_first = upper_bound(z[block].begin(), z[block].end(), h_full) -
				lower_bound(z[block].begin(), z[block].end(), h_full);
		}
		int ans_second = g[block][h_full];
		sprintf_s(c, "%d %d", ans_first, ans_second == 0 ? -1 : ans_second);
		puts(c);
	}
}