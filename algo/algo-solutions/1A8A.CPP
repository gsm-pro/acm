#include<iostream>
#include<vector>
#include<cmath>
#include<algorithm>
using namespace std;
#define LD long double
#define sqr(x) (x)*(x)
#define PDD pair<LD,LD>
const LD EPS = 1e-10;
LD x[1001], y[1001], r[1001];
vector<vector<int>> g;
vector<vector<PDD>> p;
vector<bool> used;

int intersect(LD &x1, LD &y1, LD &r1, LD &x2, LD &y2, LD &r2, vector<PDD> &r) {
	LD a = x1 - x2;
	LD b = y1 - y2;
	if (!a && !b) {
		if (r1 == r2) return -1;
		return 0;
	}
	LD l = sqr(a) + sqr(b);
	LD c = sqr(r1) - sqr(r2) + l;
	a += a;
	b += b;
	l *= 4;
	LD s = sqr(r1)*l - c * c;
	if (s < 0) {
		return 0;
	}
	if (b < 0 || (b == 0 && a > 0)) {
		a = -a;
		b = -b;
		c = -c;
	}
	LD sq = sqrt(s / l / l);
	for (int i = 1; i <= (s != 0) + 1; i++) {
		r.push_back(make_pair(-a * c / l - b * sq + x1, -b * c / l + a * sq + y1));
		sq = -sq;
	}
	return (int)r.size();
}

bool same(PDD x, PDD y) {
	return fabsl(x.first - y.first) < EPS && fabsl(x.second - y.second) < EPS;
}

void dfs(int x) {
	used[x] = true;
	for (size_t i = 0; i < g[x].size(); i++) {
		int to = g[x][i];
		if (!used[to]) {
			dfs(to);
		}
	}
}

int main() {
	int n;
	cin >> n;
	for (int i = 0; i < n; i++) {
		cin >> x[i] >> y[i] >> r[i];
	}
	g.resize(n);
	p.resize(n);
	vector<PDD> all;
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < i; j++) {
			vector<PDD> t;
			int m = intersect(x[i], y[i], r[i], x[j], y[j], r[j], t);
			if (m > 0) {
				g[i].push_back(j);
				g[j].push_back(i);
				if (t.size() > 0) {
					p[i].push_back(t[0]);
					p[j].push_back(t[0]);
					all.push_back(t[0]);
				}
				if (t.size() > 1) {
					p[i].push_back(t[1]);
					p[j].push_back(t[1]);
					all.push_back(t[1]);
				}
			}
		}
	}
	used.resize(n);
	int C = 0, V = 0, E = 0;
	for (int i = 0; i < n; i++) {
		if (!used[i]) {
			C++;
			dfs(i);
		}
	}
	for (int i = 0; i < n; i++) {
		if (p[i].size() > 1) {
			sort(p[i].begin(), p[i].end());
		}
	}
	for (int i = 0; i < n; i++) {
		if (p[i].size() > 0) {
			for (size_t j = 0; j < p[i].size(); j++) {
				if (!j || !same(p[i][j - 1], p[i][j])) {
					E++;
				}
			}
		}
	}
	sort(all.begin(), all.end());
	for (size_t j = 0; j < all.size(); j++) {
		if (!j || !same(all[j - 1], all[j])) {
			V++;
		}
	}
	cout << 1 + C + E - V;
}