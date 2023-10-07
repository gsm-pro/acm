#include<iostream>
using namespace std;
#define forn(i,n) for(int i=0;i<(n);i++)
#define NMAX 105
int n, c[NMAX][NMAX], f[NMAX][NMAX], h[NMAX], e[NMAX];

int main() {
	cin >> n;
	forn(i, n) forn(j, n) cin >> c[i][j];
	forn(i, n) f[i][0] = e[0] -= c[0][i], f[0][i] = e[i] += c[0][i];
	h[0] = n;
	for (;;) {
		int p = -1;
		forn(i, n) if (i != n - 1 && e[i] > 0) {
			p = i;
			break;
		}
		if (p == -1) return cout << e[n - 1], 0;
		forn(i, n) if (c[p][i] > f[p][i] && h[p] > h[i]) {
			int a = min(c[p][i] - f[p][i], e[p]);
			f[p][i] += a, f[i][p] -= a, e[p] -= a, e[i] += a;
		}
		h[p] += (e[p] > 0);
	}
}