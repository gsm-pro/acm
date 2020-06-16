#include<iostream>
#include<vector>
#include<algorithm>
using namespace std;
const int NMAX = 600060;

inline void fr(int &to) {
	char t = _getchar_nolock();
	to ^= to;
	while (t > 47) {
		to = (to << 3) + (to << 1) + t - 48;
		t = _getchar_nolock();
	}
}

inline void fw(const long long &what) {
	if (what > 9) {
		fw(what / 10);
	}
	_putchar_nolock(what % 10 + 48);
}

inline int Z(int a) {
	return (a + 2) << 1;
}

class FenwickTree {
private:
	int n;
	vector<int> v;
public:
	inline void add(int i, int delta) {
		for (; i < n; i |= i + 1) {
			v[i] += delta;
		}
	}

	inline int sum(int i) {
		i = min(i, n - 1);
		int res = 0;
		for (; i >= 0; i &= i + 1, i--) {
			res += v[i];
		}
		return res;
	}

	inline int sum(int l, int r) {
		if (l > r) {
			return 0;
		}
		return sum(r) - sum(l - 1);
	}

	inline void assign(int _n) {
		n = _n;
		v.assign(n, 0);
	}
};

inline void sortAndRemoveDuplicates(vector<int> &v) {
	if (v.size() < 2) {
		return;
	}
	sort(v.begin(), v.end());
	v.erase(unique(v.begin(), v.end()), v.end());
}

class FenwickTree2D {
private:
	vector<int> vals[NMAX];
	FenwickTree sums[NMAX];
public:
	inline void initAdd(int x, int y) {
		for (; x < NMAX; x |= x + 1) {
			vals[x].push_back(y);
		}
	}

	inline void prepare() {
		for (int i = 0; i < NMAX; i++) {
			sortAndRemoveDuplicates(vals[i]);
			sums[i].assign(vals[i].size());
		}
	}

	inline void add(int x, int y, int delta) {
		for (; x < NMAX; x |= x + 1) {
			vector<int> &cur = vals[x];
			int aY = (int)(lower_bound(cur.begin(), cur.end(), y) - cur.begin());
			sums[x].add(aY, delta);
		}
	}

	inline int sum(int x, int r) {
		int res = 0;
		for (; x >= 0; x &= x + 1, x--) {
			vector<int> &cur = vals[x];
			int aL = (int)(lower_bound(cur.begin(), cur.end(), 0) - cur.begin());
			int aR = (int)(upper_bound(cur.begin(), cur.end(), r) - cur.begin());
			res += sums[x].sum(aL, aR - 1);
		}
		return res;
	}
};

FenwickTree2D f0, f1, f2, f3;

int main() {
	int N, M, K, L, x1, y1, x2, y2;
	fr(N), fr(M), fr(K), fr(L);
	vector<pair<int, int>> Q0, Q1, Q2, Q3;
	while (K--) {
		fr(x1), fr(y1), fr(x2), fr(y2);
		if (x1 > x2) {
			swap(x1, x2);
		}
		if (y1 > y2) {
			swap(y1, y2);
		}
		int A = Z(x1), B = Z(y1), C = Z(x2), D = Z(y2);
		Q0.push_back(make_pair(A, B));
		Q1.push_back(make_pair(C + 1, B));
		Q2.push_back(make_pair(A, D + 1));
		Q3.push_back(make_pair(C + 1, D + 1));
	}
	sort(Q0.begin(), Q0.end());
	sort(Q1.begin(), Q1.end());
	sort(Q2.begin(), Q2.end());
	sort(Q3.begin(), Q3.end());
	for (size_t i = 0; i < Q0.size(); i++) {
		if (!i || !(Q0[i - 1].first == Q0[i].first && Q0[i - 1].second == Q0[i].second)) {
			f0.initAdd(Q0[i].first, Q0[i].second);
		}
	}
	for (size_t i = 0; i < Q1.size(); i++) {
		if (!i || !(Q1[i - 1].first == Q1[i].first && Q1[i - 1].second == Q1[i].second)) {
			f1.initAdd(Q1[i].first, Q1[i].second);
		}
	}
	for (size_t i = 0; i < Q2.size(); i++) {
		if (!i || !(Q2[i - 1].first == Q2[i].first && Q2[i - 1].second == Q2[i].second)) {
			f2.initAdd(Q2[i].first, Q2[i].second);
		}
	}
	for (size_t i = 0; i < Q3.size(); i++) {
		if (!i || !(Q3[i - 1].first == Q3[i].first && Q3[i - 1].second == Q3[i].second)) {
			f3.initAdd(Q3[i].first, Q3[i].second);
		}
	}
	f0.prepare();
	f1.prepare();
	f2.prepare();
	f3.prepare();
	for (size_t i = 0; i < Q0.size(); i++) {
		f0.add(Q0[i].first, Q0[i].second, 1);
	}
	for (size_t i = 0; i < Q1.size(); i++) {
		f1.add(Q1[i].first, Q1[i].second, 1);
	}
	for (size_t i = 0; i < Q2.size(); i++) {
		f2.add(Q2[i].first, Q2[i].second, 1);
	}
	for (size_t i = 0; i < Q3.size(); i++) {
		f3.add(Q3[i].first, Q3[i].second, 1);
	}
	while (L--) {
		fr(x1), fr(y1);
		int A = Z(x1), B = Z(y1), C = A, D = B;
		fw(f0.sum(C, D) - f2.sum(C, B - 1) - f1.sum(A - 1, D) + f3.sum(A - 1, B - 1));
		_putchar_nolock('\n');
		fflush(stdout);
	}
}