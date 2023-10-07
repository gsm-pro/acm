#include<bits/stdc++.h>
using namespace std;
vector<pair<pair<int, int>, int>> v;
unordered_map<int, unordered_map<int, int>> z;
int n, k, x, y, a, _x, _y;

int rec(int e, int r) {
	if (e == n - 1) return k - r;
	if (z[e].count(r)) return z[e][r];
	int ans = 0;
	for (int i = e + 1; i < n; i++) {
		if (v[i].first.first >= v[e].first.first
			&& v[i].first.second >= v[e].first.second
			&& v[i].second <= r) {
			ans = max(ans, rec(i, r - v[i].second));
		}
	}
	return z[e][r] = ans;
}

int main() {
	ifstream I("input.txt");
	v.push_back(make_pair(make_pair(1000000, 1000000), 0));
	I >> n >> k >> x >> y;
	v.push_back(make_pair(make_pair(x, y), 0));
	for (int i = 0; i < n; i++) {
		I >> _x >> _y >> a;
		if (_x >= x && _y >= y) v.push_back(make_pair(make_pair(_x, _y), a));
	}
	sort(v.begin(), v.end());
	n = (int)v.size();
	ofstream("output.txt") << rec(0, k);
}