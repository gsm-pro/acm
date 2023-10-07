#include<iostream>
#include<algorithm>
#include<map>
using namespace std;
#define LL long long
LL n, one[18] = { 0 };

pair<map<LL, LL>, LL> go(LL n, int d, int sgn) {
	LL q = n / one[d] * d;
	if (n %	one[d] == 0) {
		map<LL, LL> m;
		m[sgn * one[d]] = n / one[d];
		return make_pair(m, q);
	}
	pair<map<LL, LL>, LL> v1 = go(one[d] - n % one[d], d - 1, -sgn);
	pair<map<LL, LL>, LL> v2 = go(n % one[d], d - 1, sgn);
	if (d + v1.second < v2.second) {
		v1.first[sgn * one[d]] += (((one[d] - n % one[d]) + n) / one[d]);
		return make_pair(v1.first, q + d + v1.second);
	}
	else {
		v2.first[sgn * one[d]] += (n / one[d]);
		return make_pair(v2.first, q + v2.second);
	}
}

int main() {
	freopen("input.txt", "r", stdin);
	freopen("output.txt", "w", stdout);
	cin >> n;
	for (int i = 1; i <= 17; i++) {
		one[i] = 10 * one[i - 1] + 1;
	}
	pair<map<LL, LL>, LL> res = go(n, 17, 1);
	LL k = 0;
	for (map<LL, LL>::iterator it = res.first.begin(); it != res.first.end(); it++) {
		k += (it->second);
	}
	cout << res.second << " " << k << endl;
	for (map<LL, LL>::iterator it = res.first.begin(); it != res.first.end(); it++) {
		for (int i = 1; i <= it->second; i++) {
			cout << it->first << endl;
		}
	}
}