#pragma comment(linker,"/STACK:200000000")
#pragma comment(linker,"/HEAP:200000000")
#include<iostream>
#include<cmath>
#include<queue>
#include<bitset>
using namespace std;
const size_t SIZE = (size_t)((1000 << 20) + (1000 << 10) + 1111);

struct qstate {
	int aa, bb, cc, m;
	qstate(int aa, int bb, int cc, int m) : aa(aa), bb(bb), cc(cc), m(m) {}
};

queue<qstate> q;

inline void check_n_push(qstate &x, bitset<SIZE> &t) {
	int hash = (x.aa << 20) + (x.bb << 10) + x.cc;
	if (!t[hash]) {
		t.set(hash);
		q.push(x);
	}
}

int main() {
	bitset<SIZE> t;
	int a, b, c, k, r, next_s;
	cin >> a >> b >> c >> k;
	if (k > max(max(a, b), c)) {
		cout << -1;
		return 0;
	}
	t.set(0);
	q.push(qstate(0, 0, 0, 0));
	while (!q.empty()) {
		qstate s = q.front();
		q.pop();
		if (s.aa == k || s.bb == k || s.cc == k) {
			cout << s.m;
			return 0;
		}
		next_s = s.m + 1;
		r = min(s.aa, b - s.bb);
		if (r > 0) check_n_push(qstate(s.aa - r, s.bb + r, s.cc, next_s), t);
		r = min(s.bb, a - s.aa);
		if (r > 0) check_n_push(qstate(s.aa + r, s.bb - r, s.cc, next_s), t);
		r = min(s.aa, c - s.cc);
		if (r > 0) check_n_push(qstate(s.aa - r, s.bb, s.cc + r, next_s), t);
		r = min(s.cc, a - s.aa);
		if (r > 0) check_n_push(qstate(s.aa + r, s.bb, s.cc - r, next_s), t);
		r = min(s.bb, c - s.cc);
		if (r > 0) check_n_push(qstate(s.aa, s.bb - r, s.cc + r, next_s), t);
		r = min(s.cc, b - s.bb);
		if (r > 0) check_n_push(qstate(s.aa, s.bb + r, s.cc - r, next_s), t);
		check_n_push(qstate(0, s.bb, s.cc, next_s), t);
		check_n_push(qstate(s.aa, 0, s.cc, next_s), t);
		check_n_push(qstate(s.aa, s.bb, 0, next_s), t);
		check_n_push(qstate(a, s.bb, s.cc, next_s), t);
		check_n_push(qstate(s.aa, b, s.cc, next_s), t);
		check_n_push(qstate(s.aa, s.bb, c, next_s), t);
	}
	cout << -1;
}