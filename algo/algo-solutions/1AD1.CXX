#include<iostream>
#include<algorithm>
#include<cstring>
#include<unordered_map>
#include<cmath>
using namespace std;
typedef long long LL;
const int LOG = 18;
const int N = 1 << LOG;
const int ALPH = 26;
const int MAXM = 10000;
const int MAXN = 1048576;
const LL MOD = 998244353LL;
int REV[N + 8], n, m, p, x;
LL W[N + 8], F[2][N];
unordered_map<int, LL*> DP;

LL add(LL x, LL y) {
	x += y;
	return x >= MOD ? x - MOD : x;
}

LL sub(LL x, LL y) {
	x -= y;
	return x < 0 ? x + MOD : x;
}

LL mult(LL x, LL y) {
	return x * y % MOD;
}

LL binpow(LL x, LL p) {
	if (p == 0) return 1LL;
	if (p == 2 || (p & 1)) return mult(x, binpow(x, p - 1));
	return binpow(binpow(x, p / 2), 2);
}

LL revmod(LL x) {
	return binpow(x, MOD - 2);
}

void init() {
	LL w = -1;
	for (LL x = 2;; x++) {
		LL y = x;
		for (int i = 1; i < LOG; i++) y = mult(y, y);
		if (y == MOD - 1) {
			w = x;
			break;
		}
	}
	if (w == -1) throw;
	W[0] = 1;
	for (int i = 1; i < N; i++) W[i] = mult(W[i - 1], w);
	REV[0] = 0;
	for (int msk = 1, k = 0; msk < N; msk++) {
		if (msk >> (k + 1)) k++;
		REV[msk] = REV[msk ^ (1 << k)] ^ (1 << (LOG - 1 - k));
	}
}

void fft(LL* A, int k) {
	int L = 1 << k;
	for (int msk = 0; msk < L; msk++) F[0][REV[msk] >> (LOG - k)] = A[msk];
	int ct = 0, nt = 1;
	for (int lvl = 0; lvl < k; lvl++) {
		int len = 1 << lvl;
		for (int st = 0; st < L; st += (len << 1))
			for (int i = 0; i < len; i++) {
				LL s = mult(F[ct][st + len + i], W[i << (LOG - 1 - lvl)]);
				F[nt][st + i] = add(F[ct][st + i], s);
				F[nt][st + len + i] = sub(F[ct][st + i], s);
			}
		swap(ct, nt);
	}
	for (int i = 0; i < L; i++) A[i] = F[ct][i];
}

LL* multiply(LL* A, int sz1, LL* B, int sz2) {
	int k = 0, sz = sz1 + sz2 - 1;
	while ((1 << k) < sz) k++;
	int L = 1 << k;
	LL* C = new LL[L], * D = new LL[L], * RES = new LL[sz];
	memset(C, 0, L * sizeof * C);
	memset(D, 0, L * sizeof * D);
	for (int i = 0; i < sz1; i++) C[i] = A[i];
	for (int i = 0; i < sz2; i++) D[i] = B[i];
	fft(C, k);
	fft(D, k);
	for (int i = 0; i < L; i++) C[i] = mult(C[i], D[i]);
	fft(C, k);
	reverse(C + 1, C + L);
	LL revL = revmod(L);
	for (int i = 0; i < sz; i++) RES[i] = mult(C[i], revL);
	delete[] C;
	delete[] D;
	return RES;
}

int powmod(int bs, int pw, int md) {
	int res = 1;
	while (pw)
		if (pw & 1) res *= bs, res %= md, pw--;
		else bs *= bs, bs %= md, pw >>= 1;
	return res % md;
}

void calc2k(int len) {
	if (DP.count(len)) return;
	LL* RES = new LL[m];
	memset(RES, 0, m * sizeof * RES);
	if (len == 1)
		for (int i = 1; i <= ALPH; i++) RES[i % m]++;
	else {
		int a, b, p2k;
		a = b = len >> 1, p2k = powmod(p, a, m);
		calc2k(b);
		LL* C = new LL[2 * m], * D = new LL[m];
		memset(C, 0, 2 * m * sizeof * C);
		memset(D, 0, m * sizeof * D);
		for (int l = 0; l <= m - 1; l++) {
			C[l] = C[m + l] = DP[b][l];
			D[1LL * l * p2k % m] = add(D[1LL * l * p2k % m], DP[a][l]);
		}
		auto mult = multiply(C, 2 * m, D, m);
		for (int l = m; l <= 2 * m - 1; l++) RES[l - m] = mult[l];
		delete[] C;
		delete[] D;
	}
	DP[len] = RES;
}

void calcN(int len) {
	LL* RES = new LL[m];
	memset(RES, 0, m * sizeof * RES);
	RES[0] = 1;
	for (int j = int(log2(len)); j >= 0; j--) {
		if (!(n & (1 << j))) continue;
		LL* C = new LL[2 * m], * D = new LL[m];
		memset(C, 0, 2 * m * sizeof * C);
		memset(D, 0, m * sizeof * D);
		int p2k = powmod(p, 1 << j, m);
		for (int l = 0; l <= m - 1; l++) {
			C[l] = C[m + l] = DP[1 << j][l];
			D[1LL * l * p2k % m] = add(D[1LL * l * p2k % m], RES[l]);
		}
		auto mult = multiply(C, 2 * m, D, m);
		for (int l = m; l <= 2 * m - 1; l++) RES[l - m] = mult[l];
		delete[] C;
		delete[] D;
	}
	cout << RES[x];
}

int main() {
	cin >> n >> m >> p >> x;
	init();
	calc2k(MAXN);
	calcN(MAXN);
}