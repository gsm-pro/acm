#include<bits/stdc++.h>
using namespace std;
#define N 110011
#define INF (1 << 30)
vector<int> g[N], cmp[N];
int cm[N], us[N], n, cc;
__int64 ans = 0;

void dfs(int x, int cur) {
	if (cm[x] == -1) {
		cm[x] = cur;
		for (auto f : g[x]) dfs(f, cur);
	}
}

int M(int v) {
	return v < 0 ? -v : v;
}

auto find(vector<tuple<int, int, int>>& m, int& val, int& curcmp) {
	auto res_up = m.begin(), res = m.begin();
	if (val < get<0>(*res_up)) {
		if (get<2>(*res_up) != curcmp) return res_up;
		while (true) {
			++res_up;
			if (get<2>(*res_up) != curcmp) return res_up;
		}
	}
	auto res_down = res = --m.end();
	if (val > get<0>(*res_down)) {
		if (get<2>(*res_down) != curcmp) return res_down;
		while (true) {
			--res_down;
			if (get<2>(*res_down) != curcmp) return res_down;
		}
	}
	res = lower_bound(m.begin(), m.end(), make_tuple(val, -INF, -INF));
	if (get<0>(*res) == val && get<2>(*res) != curcmp) return res;
	if (res != m.begin()) {
		auto prevres = std::prev(res);
		res = get<0>(*res) - val < val - get<0>(*prevres) ? res : prevres;
	}
	if (get<2>(*res) != curcmp) return res;
	res_down = res, res_up = res;
	int down_diff = INF, up_diff = INF;
	if (res_down != m.begin()) {
		while (true) {
			--res_down;
			if (get<2>(*res_down) != curcmp) {
				down_diff = val - get<0>(*res_down);
				break;
			}
			if (res_down == m.begin()) break;
		}
	}
	if (res_up != --m.end()) {
		while (true) {
			++res_up;
			if (get<2>(*res_up) != curcmp) {
				up_diff = get<0>(*res_up) - val;
				break;
			}
			if (res_up == --m.end()) break;
		}
	}
	return down_diff < up_diff ? res_down : res_up;
}

int main() {
	freopen("input.txt", "r", stdin);
	freopen("output.txt", "w", stdout);
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);
	cin >> n;
	vector<int> a(n), b(n), c(n);
	for (int i = 0; i < n; i++) cin >> a[i] >> b[i] >> c[i];
	vector<tuple<int, int, int>> st1, st2, st3;
	for (int i = 0; i < n; i++) {
		st1.push_back(make_tuple(a[i], i, -1));
		st2.push_back(make_tuple(b[i], i, -1));
		st3.push_back(make_tuple(c[i], i, -1));
	}
	sort(st1.begin(), st1.end());
	sort(st2.begin(), st2.end());
	sort(st3.begin(), st3.end());
	while (true) {
		cc = 0;
		for (int i = 0; i < n; i++) cm[i] = -1;
		for (int i = 0; i < n; i++) if (cm[i] == -1) dfs(i, cc++);
		for (int i = 0; i < cc; i++) cmp[i].clear();
		for (int i = 0; i < n; i++) cmp[cm[i]].push_back(i);
		if (cc == 1) break;
		for (int i = 0; i < n; i++) {
			st1[i] = make_tuple(get<0>(st1[i]), get<1>(st1[i]), cm[get<1>(st1[i])]);
			st2[i] = make_tuple(get<0>(st2[i]), get<1>(st2[i]), cm[get<1>(st2[i])]);
			st3[i] = make_tuple(get<0>(st3[i]), get<1>(st3[i]), cm[get<1>(st3[i])]);
		}
		memset(us, 0, sizeof us);
		for (int i = 0; i < cc; i++) {
			if (us[i]) continue;
			int v1 = -1, v2 = -1, w = INF, cw;
			for (auto y : cmp[i]) {
				auto it = find(st1, a[y], i);
				if ((cw = M(a[y] - get<0>(*it))) < w) v1 = y, v2 = get<1>(*it), w = cw;
				it = find(st2, b[y], i);
				if ((cw = M(b[y] - get<0>(*it))) < w) v1 = y, v2 = get<1>(*it), w = cw;
				it = find(st3, c[y], i);
				if ((cw = M(c[y] - get<0>(*it))) < w) v1 = y, v2 = get<1>(*it), w = cw;
			}
			ans += w, us[i] = 1, us[cm[v2]] = 1;
			g[v1].push_back(v2), g[v2].push_back(v1);
		}
	}
	cout << ans;
}