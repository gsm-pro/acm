#include<iostream>
#include<vector>
#include<algorithm>
using namespace std;
#define absdef(a) ((a<0)?(-(a)):(a))
#define LL __int64

inline LL encode(int a, int b) {
	return (((LL)a) << 31) + (LL)b;
}

int qty(LL val, vector<LL> &C) {
	if (binary_search(C.begin(), C.end(), val)) {
		return upper_bound(C.begin(), C.end(), val) - lower_bound(C.begin(), C.end(), val);
	}
	return 0;
}

int main() {
	int n, ans = 0;
	cin >> n;
	pair<int, int> P[1111];
	for (int i = 0; i < n; i++) {
		cin >> P[i].first >> P[i].second;
	}
	for (int i = 0; i < n; i++) {
		vector<pair<int, int>> S;
		vector<LL> M;
		for (int j = 0; j < n; j++) {
			if (i != j) {
				int dx = P[j].first - P[i].first, dy = P[j].second - P[i].second,
					a = absdef(dx), b = absdef(dy);
				for (; b; b ^= a ^= b ^= a %= b);
				if (a != 1) {
					dx /= a, dy /= a;
				}
				S.push_back(make_pair(dx, dy));
				M.push_back(encode(dx, dy));
			}
		}
		sort(M.begin(), M.end());
		sort(S.begin(), S.end());
		for (size_t i = 0; i < S.size(); i++) {
			pair<int, int> s = S[i];
			if (i == 0 || S[i - 1].first != s.first || S[i - 1].second != s.second) {
				int a = qty(encode(s.first, s.second), M),
					b = (a == 0 ? 0 : qty(encode(-s.second, s.first), M)),
					c = (a == 0 ? 0 : qty(encode(s.second, -s.first), M));
				ans += a * (b + c);
			}
		}
	}
	cout << ans / 2 << endl;
}