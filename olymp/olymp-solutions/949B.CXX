#include<bits/stdc++.h>
#define mp make_pair
#define fi first
#define se second
using namespace std;
typedef pair<int, int> pii;
const int N = 26;
const int oo = 2000000000;
int A[N], B[N], C[N], v[N], n, mx = -oo;
map<pii, pii> M;
pii result;

void r1(int x, int a, int b, int c, int s) {
	if (x > n / 2) {
		pii tmp = mp(b - a, c - a);
		if (!M.count(tmp) || M[tmp] < mp(a, s))
			M[tmp] = mp(a, s);
		return;
	}
	r1(x + 1, a + A[x], b + B[x], c, s * 3 + 0);
	r1(x + 1, a + A[x], b, c + C[x], s * 3 + 1);
	r1(x + 1, a, b + B[x], c + C[x], s * 3 + 2);
}

void r2(int x, int a, int b, int c, int s) {
	if (x > n) {
		pii tmp = mp(a - b, a - c);
		if (M.count(tmp) && M[tmp].fi + a > mx)
			mx = M[tmp].fi + a, result = mp(M[tmp].se, s);
		return;
	}
	r2(x + 1, a + A[x], b + B[x], c, s * 3 + 0);
	r2(x + 1, a + A[x], b, c + C[x], s * 3 + 1);
	r2(x + 1, a, b + B[x], c + C[x], s * 3 + 2);
}

int main() {
	ifstream I("input.txt");
	ofstream O("output.txt");
	I >> n;
	for (int i = 1; i < n + 1; i++) I >> A[i] >> B[i] >> C[i];
	r1(1, 0, 0, 0, 0);
	r2(n / 2 + 1, 0, 0, 0, 0);
	if (mx == -oo) O << "Impossible"; else {
		for (int i = n / 2; i; i--) v[i] = result.fi % 3, result.fi /= 3;
		for (int i = n; i > n / 2; i--) v[i] = result.se % 3, result.se /= 3;
		for (int i = 1; i < n + 1; i++) {
			if (v[i] == 0) O << "LM\n";
			if (v[i] == 1) O << "LW\n";
			if (v[i] == 2) O << "MW\n";
		}
	}
}