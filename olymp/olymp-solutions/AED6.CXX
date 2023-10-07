#include<fstream>
#include<string>
using namespace std;
#define TREESIZE 800008
#define lc 2 * v
#define rc 2 * v + 1
__int64 t[TREESIZE], u[TREESIZE];
string s;
int n, k;

void update(int v, int l, int r, int tl, int tr, __int64 x) {
	if (l == tl && r == tr) {
		t[v] = min(t[v], x), u[lc] = min(u[lc], x), u[rc] = min(u[rc], x);
	}
	else if (l <= r) {
		int m = (tl + tr) / 2;
		update(lc, l, min(r, m), tl, m, x);
		update(rc, max(l, m + 1), r, m + 1, tr, x);
	}
}

__int64 query(int v, int tl, int tr, int x) {
	if (tl == tr && tr == x) return t[v] = min(t[v], u[v]);
	t[v] = min(t[v], u[v]), u[lc] = min(u[lc], u[v]), u[rc] = min(u[rc], u[v]);
	int m = (tl + tr) / 2;
	if (x <= m) return query(lc, tl, m, x);
	return query(rc, m + 1, tr, x);
}

int main() {
	ifstream("input.txt") >> n >> k >> s;
	fill(t, t + TREESIZE, 1LL << 50);
	fill(u, u + TREESIZE, 1LL << 50);
	for (int i = 0; i < n; i++) {
		if (s[i] == '1') {
			__int64 w = i - k - 1 < 0
				? 0
				: query(1, 0, n - 1, i - k - 1);
			update(1,
				i - k < 0
				? 0
				: i - k,
				i + k >= n
				? n - 1
				: i + k, 0, n - 1, w + i + 1);
		}
		else {
			__int64 w = i
				? query(1, 0, n - 1, i - 1)
				: 0;
			update(1, i, i, 0, n - 1, w + i + 1);
		}
	}
	ofstream("output.txt") << query(1, 0, n - 1, n - 1);
}