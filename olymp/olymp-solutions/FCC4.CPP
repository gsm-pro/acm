#define _CRT_SECURE_NO_DEPRECATE
#include<iostream>
#include<set>
#include<algorithm>
using namespace std;
char s[200020], q;
int sumFT[200022], n, m, l, r, position, i;
set<int> indexes[64];

void add(int pos, int val) {
	while (pos <= 200020) {
		sumFT[pos] += val, pos |= (pos + 1);
	}
}

int sum(int r) {
	int res = 0;
	while (r > 0) {
		res += sumFT[r], r = (r & (r + 1)) - 1;
	}
	return res;
}

int at(int x) {
	return sum(x) - sum(x - 1);
}

int toIndex(char c) {
	if (c <= '9') {
		return c - '0';
	}
	if (c >= 'a') {
		return c - 'a' + 10;
	}
	return c - 'A' + 36;
}

int toRealIndex(int D) {
	int L = 0, R = n + 1;
	while (R - L > 1) {
		int M = (L + R) / 2, S = sum(M);
		if (S > D)
			R = M;
		else {
			if (S < D)
				L = M;
			else {
				while (at(M) == 0) M--;
				return M;
			}
		}
	}
	throw;
}

int main() {
	freopen("input.txt", "rt", stdin);
	freopen("output.txt", "wt", stdout);
	scanf("%d%d\n%s", &n, &m, &s);
	for (i = 0; i < n; i++) {
		indexes[toIndex(s[i])].insert(i + 1);
		add(i + 1, 1);
	}
	while (m--) {
		scanf("%d%d %c", &l, &r, &q);
		l = toRealIndex(l), r = toRealIndex(r);
		auto& v = indexes[toIndex(q)];
		for (auto p = v.lower_bound(l); p != v.end() && *p <= r; v.erase(p++)) {
			add(*p, -1);
		}
	}
	for (i = 0; i < n; i++) {
		if (at(i + 1) == 1) {
			putchar(s[i]);
		}
	}
}