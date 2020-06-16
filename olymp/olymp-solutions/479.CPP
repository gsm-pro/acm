#define _CRT_SECURE_NO_DEPRECATE
#include<cstdio>
#include<vector>
#include<map>
#include<iostream>
#include<algorithm>
using namespace std;

struct UnionFind {
	vector<int> p, sz;

	UnionFind(int n) : p(n), sz(n, 1) {
		for (int i = 0; i < n; i++)
			p[i] = i;
	}

	int Find(int x) {
		return p[x] == x ? x : (p[x] = Find(p[x]));
	}

	void Union(int x, int y) {
		x = Find(x);
		y = Find(y);
		if (x != y) {
			if (sz[x] > sz[y]) {
				swap(x, y);
			}
			p[x] = y;
			sz[y] += sz[x];
		}
	}

	int Size(int x) {
		return sz[Find(x)];
	}
};

void reLabel(vector<int> &v) {
	int n = v.size();
	vector<int> s(v);
	sort(s.begin(), s.end());
	map<int, int> mp;
	for (int i = 0; i < n; i++) {
		mp[s[i]] = i;
	}
	for (int i = 0; i < n; i++) {
		v[i] = mp[v[i]];
	}
}

int main() {
	int N;
	freopen("input.txt", "rt", stdin);
	freopen("output.txt", "wt", stdout);
	scanf("%d", &N);
	vector<int> x(N), y(N);
	for (int i = 0; i < N; i++) {
		scanf("%d%d", &x[i], &y[i]);
	}
	reLabel(x);
	reLabel(y);
	UnionFind uf(N + 10);
	vector<pair<int, int>> v(N);
	for (int i = 0; i < N; i++) {
		v[i].first = x[i];
		v[i].second = y[i];
	}
	sort(v.begin(), v.end());
	for (int i = 1; i < N; i++) {
		if (v[i - 1].first == v[i].first) {
			uf.Union(v[i - 1].second, v[i].second);
		}
	}
	long long ans = 0, j;
	for (int i = 0; i < N; i = j) {
		for (j = i + 1; j < N && v[i].first == v[j].first; j++);
		vector<int> w;
		for (int k = i; k < j; k++) {
			w.push_back(uf.Find(v[k].second));
		}
		sort(w.begin(), w.end());
		w.erase(unique(w.begin(), w.end()), w.end());
		for (int k = 0; k < (int)w.size(); k++) {
			ans += uf.Size(w[k]);
		}
	}
	cout << ans << endl;
}