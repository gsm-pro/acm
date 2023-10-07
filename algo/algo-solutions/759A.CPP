#include<iostream>
#include<string>
#define forn(i, n) for(int i=0;i<int(n);i++)
#define NMAX 5555
using namespace std;
int n, m, c[NMAX << 1], ans = 0, x, y, cur, nxt;
string s;

inline int leader(int idx) {
	if (c[idx] != idx) c[idx] = leader(c[idx]);
	return c[idx];
}

inline void unite(int a, int b) {
	a = leader(a), b = leader(b), c[b] = a;
}

int main() {
	memset(c, -1, sizeof c);
	cin >> n >> m;
	forn(i, n + 1) {
		cur = i & 1;
		nxt = cur ^ 1;
		if (i < n) cin >> s;
		forn(j, m) {
			x = cur * m + j, y = nxt * m + j;
			c[x] = -1;
			if (i < n && s[j] == '1') {
				c[x] = x;
				if (j != 0 && c[x - 1] != -1) unite(x - 1, x);
				if (i != 0 && c[y] != -1) unite(x, y);
			}
		}
		forn(j, m) {
			x = cur * m + j;
			if (c[x] != -1) leader(x);
		}
		forn(j, m) {
			y = nxt * m + j;
			if (c[y] != -1 && leader(y) == y) ans++;
		}
	}
	cout << ans;
}