#pragma GCC optimize("Ofast")
#pragma GCC optimize("unroll-loops")
#pragma GCC target("avx,avx2,tune=native")
#include<cstdio>
#include<iostream>
using namespace std;
#define SIZE 404
#define COLORS 3
int n, m, r[SIZE][SIZE], g[SIZE][SIZE], b[SIZE][SIZE], y[SIZE][SIZE], w[SIZE][SIZE], tp, lf, bt;

inline void update(int i, int j, int d, int(&z)[SIZE][SIZE]) {
	z[i][j] = d + z[i - 1][j] + z[i][j - 1] - z[i - 1][j - 1];
}

inline int query(int& x1, int& y1, int& x2, int& y2, int(&z)[SIZE][SIZE]) {
	return z[x2][y2] - z[x1 - 1][y2] - z[x2][y1 - 1] + z[x1 - 1][y1 - 1];
}

inline int colqty(int x1, int y1, int x2, int y2) {
	return (query(x1, y1, x2, y2, r) > 0)
		+ (query(x1, y1, x2, y2, g) > 0) + (query(x1, y1, x2, y2, b) > 0)
		+ (query(x1, y1, x2, y2, y) > 0) + (query(x1, y1, x2, y2, w) > 0);
}

inline int colqty(int rg) {
	return colqty(tp, lf, bt, rg);
}

using f_type = int(*)(int);
template<f_type F>
struct f_iter {
	using iterator_category = forward_iterator_tag;
	using difference_type = size_t;
	using value_type = int;
	using pointer = int*;
	using reference = int&;
	int index;
	f_iter(int index) : index(index) {}

	f_iter& operator ++ () {
		++index;
		return *this;
	}

	int operator * () {
		return F(index);
	}

	bool operator != (const f_iter& other) {
		return index != other.index;
	}

	bool operator == (const f_iter& other) {
		return index == other.index;
	}

	bool operator < (const f_iter& other) {
		return index < other.index;
	}
};

template<f_type F>
pair<f_iter<F>, f_iter<F>> f_range(int begin, int end) {
	return { {begin}, {end} };
}

int main() {
	freopen("input.txt", "r", stdin);
	freopen("output.txt", "w", stdout);
	scanf("%d%d\n", &n, &m);
	int i = 0, j;
	for (;;) {
		i++, j = 1;
		for (;;) {
			char s = getchar();
			if (s == EOF) goto nxt;
			if (s == '\r' || s == '\n') break;
			update(i, j, s == 'r', r);
			update(i, j, s == 'g', g);
			update(i, j, s == 'b', b);
			update(i, j, s == 'y', y);
			update(i, j, s == 'w', w);
			j++;
		}
	}
nxt:
	long long ans = 0;
	for (tp = 1; tp <= n; tp++) {
		int anstmp = 0;
		for (lf = 1; lf <= m; lf++) {
			auto fun = f_range<colqty>(lf, m);
			for (bt = tp; bt <= n; bt++) {
				int qty1 = colqty(tp, lf, bt, lf), qty2 = colqty(tp, lf, bt, m);
				if (qty1 < COLORS) {
					if (qty2 > COLORS)
						anstmp += lower_bound(fun.first, fun.second, COLORS + 1).index - lower_bound(fun.first, fun.second, COLORS).index;
					else if (qty2 == COLORS)
						anstmp += m + 1 - lower_bound(fun.first, fun.second, COLORS).index;
				}
				else {
					if (qty1 == COLORS) {
						if (qty2 > COLORS)
							anstmp += lower_bound(fun.first, fun.second, COLORS + 1).index - lf;
						else if (qty2 == COLORS)
							anstmp += m + 1 - lf;
					}
				}
			}
		}
		ans += anstmp;
	}
	cout << ans;
}