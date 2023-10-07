#include<iostream>
#include<complex>
#include<vector>
#include<algorithm>
#include<string>
using namespace std;
const int NMAX = (1 << 19);
const double PI = acos((double)-1.);
const char dna[] = { 'A', 'T', 'G', 'C' };
complex<double> a[NMAX], b[NMAX], r[NMAX], h[NMAX];
int cnt[NMAX], delta[NMAX], base;

void fft(complex<double> *x) {
	int size = 0, mask = (1 << (base - 1)) - 1;
	for (int i = base - 1; i >= 0; i--, size = (size << 1) | 1, mask >>= 1) {
		for (int j = 0; j < NMAX; j++) {
			int front = (j >> i), back = j & mask;
			int a = (front & size) << 1, b = a | 1;
			r[j] = x[(a << i) | back] + h[front << i] * x[(b << i) | back];
		}
		for (int j = 0; j < NMAX; j++) {
			x[j] = r[j];
		}
	}
}

void rfft(complex<double> *x) {
	fft(x);
	reverse(x + 1, x + NMAX);
	for (int i = 0; i < NMAX; i++) {
		x[i] /= NMAX;
	}
}

int main() {
	for (int i = 0; i < NMAX; i++) {
		h[i] = exp(2 * PI * i / NMAX * complex<double>(0, 1));
	}
	while ((1 << base) < NMAX) {
		++base;
	}
	int slen, tlen, k;
	string s, t;
	cin >> slen >> tlen >> k >> s >> t;
	reverse(t.begin(), t.end());
	for (size_t z = 0; z < 4; z++) {
		char c = dna[z];
		memset(a, 0, sizeof a);
		memset(b, 0, sizeof b);
		for (int i = 0; i < tlen; i++) {
			a[i] = complex<double>(t[i] == c, 0);
		}
		memset(delta, 0, sizeof delta);
		for (int i = 0; i < slen; i++) {
			if (s[i] == c) {
				++delta[max(0, i - k)];
				--delta[i + k + 1];
			}
		}
		for (int i = 1; i < NMAX; i++) {
			delta[i] += delta[i - 1];
		}
		for (int i = 0; i < NMAX; i++) {
			b[i] = complex<double>(!!delta[i], 0);
		}
		fft(a);
		fft(b);
		for (int i = 0; i < NMAX; i++) {
			a[i] *= b[i];
		}
		rfft(a);
		for (int i = 0; i < NMAX; i++) {
			cnt[i] += int(a[i].real() + 0.5);
		}
	}
	int ans = 0;
	for (int i = 0; i < slen; ++i) {
		ans += (cnt[i] == tlen);
	}
	cout << ans;
}