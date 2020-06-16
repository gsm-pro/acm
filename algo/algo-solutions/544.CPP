#include<iostream>
#include<algorithm>
#include<cmath>
using namespace std;
#define LD long double
const LD EPS = 1e-9;
const int ITERS = 10000;
const LD PI = acos((LD)(-1.0));
LD phi, p[4];
int x[2], y[2], r;

LD dist(LD phi, LD x, LD y) {
	return sqrt((x - r * cos(phi)) * (x - r * cos(phi))	+ (y - r * sin(phi)) * (y - r * sin(phi)));
}

LD diff(int i, LD phi) {
	return (x[i] * sin(phi) - y[i] * cos(phi)) / dist(phi, x[i], y[i]);
}

LD sumDiff(LD phi) {
	return diff(0, phi) + diff(1, phi);
}

int signum(LD a) {
	if (a < -EPS) {
		return -1;
	}
	if (a > EPS) {
		return 1;
	}
	return 0;
}

bool diffSign(LD a, LD b) {
	if (abs(a) <= EPS && abs(b) <= EPS) {
		return false;
	}
	return signum(a) * signum(b) <= 0;
}

void solve(LD l, LD r) {
	LD dl = sumDiff(l);
	LD dr = sumDiff(r);
	if (diffSign(dl, dr)) {
		for (int i = 0; i < ITERS; i++) {
			LD m = (l + r) / 2;
			LD dm = sumDiff(m);
			if (diffSign(dm, dl)) {
				r = m;
				dr = dm;
			}
			else {
				l = m;
				dl = dm;
			}
		}
		phi = l;
	}
}

void add(LD x, LD y, int pMin, int pMax) {
	LD d = sqrt(x * x + y * y), phi = acos(r / d), theta = atan2(y, x);
	p[pMin] = theta - phi;
	p[pMax] = theta + phi;
}

int main() {
	cout.precision(9);
	int n;
	cin >> n;
	for (int i = 0; i < n; i++) {
		cin >> r >> x[0] >> y[0] >> x[1] >> y[1];
		add(x[0], y[0], 0, 2);
		add(x[1], y[1], 1, 3);
		LD pMin = max(p[0], p[1]), pMax = min(p[2], p[3]);
		if (pMin > pMax + EPS) {
			if (p[0] < p[1]) {
				p[0] += 2 * PI;
				p[2] += 2 * PI;
			}
			else {
				p[1] += 2 * PI;
				p[3] += 2 * PI;
			}
			pMin = max(p[0], p[1]);
			pMax = min(p[2], p[3]);
		}
		solve(pMin, pMax);
		cout << fixed << cos(phi) * r << " " << sin(phi) * r << endl;
	}
}