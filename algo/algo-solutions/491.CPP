#include<iostream>
#include<algorithm>
#include<vector>
#include<map>
using namespace std;
typedef unsigned long long UI64;

bool witness(int a, int n) {
	UI64 d = 1ULL;
	int b = n - 1;
	for (int i = 31; i >= 0; i--) {
		UI64 x = d;
		d = (d * d) % n;
		if (d == 1ULL && x != 1ULL && x != (UI64)(n - 1)) {
			return true;
		}
		if (b & (1 << i)) {
			d = (d * a) % n;
		}
	}
	return d != 1ULL;
}

bool MillerRabin(int n, int tries = 3) {
	while (tries-- > 0) {
		if (witness(rand() % (n - 1) + 1, n)) return false;
	}
	return true;
}

bool prime(int n) {
	if ((n > 7) && !((n % 2) && (n % 3) && (n % 5) && (n % 7))) {
		return false;
	}
	if (n == 1 || !MillerRabin(n)) {
		return false;
	}
	return true;
}

vector<pair<int, int>> fac(int n) {
	vector<pair<int, int>> result;
	int d = 5, p = 0;
	bool p2 = true;
	while (n % 2 == 0) {
		n /= 2;
		p++;
	}
	if (p > 0) {
		result.push_back(make_pair(2, p));
	}
	p = 0;
	while (n % 3 == 0) {
		n /= 3;
		p++;
	}
	if (p > 0) {
		result.push_back(make_pair(3, p));
	}
	p = 0;
	while (!prime(n) && n != 1) {
		while (n % d != 0) {
			d += (p2 ? 2 : 4);
			p2 = !p2;
		}
		while (n % d == 0) {
			p++;
			n = n / d;
		}
		result.push_back(make_pair(d, p));
		p = 0;
	}
	if (n > 1) {
		result.push_back(make_pair(n, 1));
	}
	return result;
}

int main() {
	int n, m, a, ans = (1 << 30);
	scanf_s("%d%d", &n, &m);
	map<int, int> nok;
	while (n--) {
		scanf_s("%d", &a);
		vector<pair<int, int>> fa = fac(a);
		for (size_t i = 0; i < fa.size(); i++) {
			nok[fa[i].first] = max(nok[fa[i].first], fa[i].second);
		}
	}
	vector<pair<int, int>> fm = fac(m);
	for (size_t i = 0; i < fm.size(); i++) {
		ans = min(ans, nok[fm[i].first] / fm[i].second);
	}
	printf("%d", ans);
}