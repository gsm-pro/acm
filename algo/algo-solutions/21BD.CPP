#include<iostream>
#include<cmath>
#include<complex>
#include<vector>
#include<algorithm>
using namespace std;
typedef long double LD;
typedef complex<LD> CLD;
typedef vector<CLD> VCLD;
typedef pair<VCLD, int> POLY;
const LD EPS = 1e-8;
const int MAX_ITERS = 1000;

CLD getAt(POLY p, CLD x) {
	CLD f = CLD(0, 0);
	for (int i = 0; i <= p.second; i++) {
		f = f + pow(x, i) * p.first[i];
	}
	return f;
}

VCLD findAllRoots(POLY poly) {
	VCLD r;
	POLY q, p = poly;
	q.first.resize(poly.second);
	for (int i = 0; i < poly.second; i++) {
		q.second = p.second - 1;
		for (int j = 0; j < p.second; j++) {
			q.first[j] = p.first[j + 1] * CLD(j + 1, 0);
		}
		CLD x1 = CLD(1, 1), x0;
		int iters = 0;
		do {
			x0 = x1, x1 = x0 - getAt(p, x0) / getAt(q, x0), iters++;
		} while (abs(getAt(p, x1)) > EPS && iters <= MAX_ITERS);
		r.push_back(x1);
		for (int j = p.second - 1; j >= 0; j--) {
			p.first[j] = p.first[j] + p.first[j + 1] * x1;
		}
		for (int j = 0; j < p.second; j++) {
			p.first[j] = p.first[j + 1];
		}
		p.second--;
	}
	return r;
}

VCLD findRealRootsLR(POLY poly, LD L, LD R) {
	VCLD all = findAllRoots(poly);
	VCLD allRealLR;
	for (size_t i = 0; i < all.size(); i++) {
		if (fabs(imag(all[i])) < EPS && L - EPS <= real(all[i]) && real(all[i]) <= R + EPS) {
			allRealLR.push_back(all[i]);
		}
	}
	return allRealLR;
}

POLY deriv(POLY p) {
	POLY d = p;
	for (int i = (int)d.first.size() - 1; i >= 0; i--) {
		d.first[i] *= i;
	}
	d.first.erase(d.first.begin());
	d.second--;
	return d;
}

int main() {
	int n;
	LD L, R, x;
	cin >> n >> L >> R;
	VCLD v;
	for (int i = 0; i <= n; i++) {
		cin >> x;
		v.push_back(CLD(x, 0));
	}
	POLY p = POLY(v, v.size() - 1);
	VCLD w = findRealRootsLR(deriv(p), L, R);
	LD ans = min(getAt(p, CLD(L, 0)).real(), getAt(p, CLD(R, 0)).real());
	for (size_t i = 0; i < w.size(); i++) {
		ans = min(ans, getAt(p, w[i]).real());
	}
	cout.precision(8);
	cout << fixed << ans;
}