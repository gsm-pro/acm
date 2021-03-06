#define _USE_MATH_DEFINES
#define _CRT_SECURE_NO_DEPRECATE
#include<complex>
#include<vector>
#include<cstdio>
#include<iostream>
#include<cmath>
#include<algorithm>
using namespace std;
#define PI M_PI
#define LL long long
#define LD long double
typedef complex<LD> base;

int rev(int num, int logN) {
	int res = 0;
	for (int i = 0; i < logN; i++) {
		if (num & (1 << i)) {
			res |= 1 << (logN - 1 - i);
		}
	}
	return res;
}

void fft(vector<base> &a, bool inv) {
	int n = (int)a.size();
	int logN = 0;
	while ((1 << logN) < n) {
		++logN;
	}
	for (int i = 0; i < n; ++i) {
		if (i < rev(i, logN)) {
			swap(a[i], a[rev(i, logN)]);
		}
	}
	for (int len = 2; len <= n; len <<= 1) {
		LD ang = 2 * PI / len * (inv ? -1 : 1);
		base wlen(cos(ang), sin(ang));
		for (int i = 0; i < n; i += len) {
			base w(1);
			for (int j = 0; j < len / 2; ++j) {
				base u = a[i + j], v = a[i + j + len / 2] * w;
				a[i + j] = u + v;
				a[i + j + len / 2] = u - v;
				w *= wlen;
			}
		}
	}
	if (inv) {
		for (int i = 0; i < n; ++i) {
			a[i] /= n;
		}
	}
}

void multiply(vector<LD> &a, vector<LD> &b, vector<LL> &res) {
	vector<base> fa(a.begin(), a.end()), fb(b.begin(), b.end());
	int n = 1;
	while (n < (int)max(a.size(), b.size())) {
		n <<= 1;
	}
	n <<= 1;
	fa.resize(n);
	fb.resize(n);
	fft(fa, false);
	fft(fb, false);
	for (int i = 0; i < n; ++i) {
		fa[i] *= fb[i];
	}
	fft(fa, true);
	res.resize(n);
	for (int i = 0; i < n; ++i) {
		res[i] = (LL)(fa[i].real() + 0.5);
	}
}

int main() {
	vector<LD> aa, bb;
	vector<LL> cc;
	string number;
	getline(cin, number);
	for (int i = 0; i < (int)number.size(); i++) {
		aa.push_back(number[i] - '0');
	}
	reverse(aa.begin(), aa.end());
	getline(cin, number);
	for (int i = 0; i < (int)number.size(); i++) {
		bb.push_back(number[i] - '0');
	}
	reverse(bb.begin(), bb.end());
	multiply(aa, bb, cc);
	LL carry = 0;
	for (int i = 0; i < (int)cc.size(); i++) {
		cc[i] += carry;
		carry = cc[i] / 10LL;
		cc[i] %= 10;
	}
	reverse(cc.begin(), cc.end());
	bool skip = true;
	for (int i = 0; i < (int)cc.size(); i++) {
		int digit = (int)cc[i];
		if (digit > 0) {
			skip = false;
		}
		if (!skip) {
			printf("%d", digit);
		}
	}
}