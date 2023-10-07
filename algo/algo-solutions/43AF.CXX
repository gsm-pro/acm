#include<iostream>
#include<vector>
#include<algorithm>
using namespace std;
#define fs first
#define sc second
#define mp make_pair
#define pb push_back
typedef long double LD;
typedef pair<pair<LD, LD>, pair<LD, LD>> PL;
const LD EPS = 0.000000001L;
LD X1, Y1, Z1, X2, Y2, Z2, X3, Y3, Z3, R1, R2, R3, G, H, I, J, K, L, M, N, P;
vector<PL> $, $$;

inline bool eq(LD x, LD y) {
	return fabsl(x - y) < EPS;
}

inline bool nl(LD x) {
	return eq(x, .0);
}

inline bool ps(LD x) {
	return x > .0 && !nl(x);
}

inline LD nr(LD x) {
	return fabsl(x) < EPS ? .0 : x;
}

inline bool eqp(PL X, PL Y) {
	return eq(X.fs.fs, Y.fs.fs) && eq(X.fs.sc, Y.fs.sc)
		&& eq(X.sc.fs, Y.sc.fs) && eq(X.sc.sc, Y.sc.sc);
}

PL nrp(LD A, LD B, LD C, LD D) {
	D = -(D - A * X1 - B * Y1 - C * Z1);
	if ((!nl(A) && A < 0)
		|| (nl(A) && !nl(B) && B < 0)
		|| (nl(A) && nl(B) && !nl(C) && C < 0)
		|| (nl(A) && nl(B) && nl(C) && !nl(D) && D < 0))
		A = -A, B = -B, C = -C, D = -D;
	return mp(mp(nr(A), nr(B)), mp(nr(C), nr(D)));
}

vector<LD> sqq(LD a, LD b, LD c) {
	vector<LD> r;
	if (!nl(a) || !nl(b)) {
		if (nl(a)) r.pb(-c / b); else {
			LD d = b * b - 4. * a * c;
			if (nl(d)) r.pb(-b / 2. / a);
			if (ps(d)) {
				r.pb((-b - sqrt(d)) / 2. / a);
				r.pb((-b + sqrt(d)) / 2. / a);
			}
		}
	}
	return r;
}

LD q() {
	return J * H * H + G * G * K - L * G * H;
}

LD rG() {
	return L * G * I + N * G * G - 2. * J * I * H - G * M * H;
}

LD rH() {
	return L * H * I + M * H * H - 2. * K * I * G - G * N * H;
}

LD sG() {
	return G * M * I + J * I * I + P * G * G;
}

LD sH() {
	return H * N * I + K * I * I + P * H * H;
}

void s(LD r1, LD r2, LD r3) {
	LD E = r2 - r1, F = r3 - r1;
	if (!nl(X2)) {
		G = X2 * Y3 - X3 * Y2, H = X2 * Z3 - X3 * Z2, I = F * X2 - E * X3,
			J = Y2 * Y2 + X2 * X2, K = Z2 * Z2 + X2 * X2, L = 2. * Y2 * Z2,
			M = -2. * E * Y2, N = -2. * E * Z2, P = E * E - X2 * X2;
		if (!nl(G)) {
			for (LD C : sqq(q(), rG(), sG())) {
				LD B = (I - C * H) / G, A = (E - B * Y2 - C * Z2) / X2;
				$.pb(nrp(A, B, C, r1));
			}
		}
		else if (!nl(H)) {
			for (LD B : sqq(q(), rH(), sH())) {
				LD C = (I - B * G) / H, A = (E - B * Y2 - C * Z2) / X2;
				$.pb(nrp(A, B, C, r1));
			}
		}
	}
	else if (!nl(Y2)) {
		G = Y2 * X3 - X2 * Y3, H = Y2 * Z3 - Y3 * Z2, I = F * Y2 - E * Y3,
			J = X2 * X2 + Y2 * Y2, K = Z2 * Z2 + Y2 * Y2, L = 2. * X2 * Z2,
			M = -2. * E * X2, N = -2. * E * Z2, P = E * E - Y2 * Y2;
		if (!nl(G)) {
			for (LD C : sqq(q(), rG(), sG())) {
				LD A = (I - C * H) / G, B = (E - A * X2 - C * Z2) / Y2;
				$.pb(nrp(A, B, C, r1));
			}
		}
		else if (!nl(H)) {
			for (LD A : sqq(q(), rH(), sH())) {
				LD C = (I - A * G) / H, B = (E - A * X2 - C * Z2) / Y2;
				$.pb(nrp(A, B, C, r1));
			}
		}
	}
	else if (!nl(Z2)) {
		G = X3 * Z2 - X2 * Z3, H = Y3 * Z2 - Y2 * Z3, I = F * Z2 - E * Z3,
			J = X2 * X2 + Z2 * Z2, K = Y2 * Y2 + Z2 * Z2, L = 2. * X2 * Y2,
			M = -2. * E * X2, N = -2. * E * Y2, P = E * E - Z2 * Z2;
		if (!nl(G)) {
			for (LD B : sqq(q(), rG(), sG())) {
				LD A = (I - B * H) / G, C = (E - A * X2 - B * Y2) / Z2;
				$.pb(nrp(A, B, C, r1));
			}
		}
		else if (!nl(H)) {
			for (LD A : sqq(q(), rH(), sH())) {
				LD B = (I - A * G) / H, C = (E - A * X2 - B * Y2) / Z2;
				$.pb(nrp(A, B, C, r1));
			}
		}
	}
}

int main() {
	ios::sync_with_stdio(0);
	cin.tie(0);
	int n, i, j, k;
	cin >> n;
	cout.precision(8);
	while (n--) {
		$.clear();
		$$.clear();
		cin >> X1 >> Y1 >> Z1 >> R1 >> X2 >> Y2 >> Z2 >> R2 >> X3 >> Y3 >> Z3 >> R3;
		X2 -= X1, Y2 -= Y1, Z2 -= Z1, X3 -= X1, Y3 -= Y1, Z3 -= Z1;
		for (i = -1; i <= 1; i += 2)
			for (j = -1; j <= 1; j += 2)
				for (k = -1; k <= 1; k += 2)
					s(R1 * i, R2 * j, R3 * k);
		sort($.begin(), $.end());
		if ($.size() > 0) {
			$$.pb($[0]);
			for (size_t t = 1; t < $.size(); t++) if (!eqp($[t], $[t - 1])) $$.pb($[t]);
		}
		cout << $$.size() << "\n";
		for (PL $$$ : $$)
			cout << fixed
			<< $$$.fs.fs << " " << $$$.fs.sc << " "
			<< $$$.sc.fs << " " << $$$.sc.sc << "\n";
	}
}