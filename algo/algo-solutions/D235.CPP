#include<iostream>
#include<complex>
#include<vector>
#include<algorithm>
#define CD complex<double>
#define PI acos(double(-1.))
using namespace std;

void fft(vector<CD> &v, int inv) {
	int n = v.size();
	for (int i = 1; i < n; i++) {
		int j = i, l = 0;
		for (int k = 1; k < n; k <<= 1) {
			l <<= 1;
			l += (j & 1);
			j >>= 1;
		}
		if (l > i) {
			swap(v[i], v[l]);
		}
	}
	for (int i = 2; i <= n; i <<= 1) {
		double ang = 2 * PI * inv / i;
		CD w(cos(ang), sin(ang));
		for (int j = 0; j < n; j += i) {
			CD t = 1;
			for (int l = 0; l < (i >> 1); l++) {
				CD tmp = v[j + l + (i >> 1)];
				v[j + l + (i >> 1)] = v[j + l] - t * tmp;
				v[j + l] = v[j + l] + t * tmp;
				t *= w;
			}
		}
	}
	if (inv > 0) {
		return;
	}
	for (int i = 0; i < n; i++) {
		v[i] /= n;
	}
}

vector<int> conv(vector<int> &a, vector<int> &b) {
	vector<CD> fa(a.begin(), a.end()), fb(b.begin(), b.end());
	size_t n = 1;
	while (n < max(a.size(), b.size())) {
		n <<= 1;
	}
	n <<= 1;
	fa.resize(n);
	fb.resize(n);
	fft(fa, 1);
	fft(fb, 1);
	for (size_t i = 0; i < n; i++) {
		fa[i] *= fb[i];
	}
	fft(fa, -1);
	vector<int> c(n);
	for (size_t i = 0; i < n; i++) {
		c[i] = fabs(fa[i].real()) > 0.5;
	}
	return c;
}

vector<int> exp(vector<int> &a, int k) {
	vector<int> b;
	b.push_back(1);
	while (k) {
		if (k & 1) {
			b = conv(b, a);
		}
		k >>= 1;
		if (k) {
			a = conv(a, a);
		}
	}
	return b;
}

int main() {
	int n, k, a;
	cin >> n >> k;
	vector<int> v(1111);
	for (int i = 0; i < n; i++) {
		cin >> a;
		v[a] = 1;
	}
	vector<int> res = exp(v, k);
	for (size_t i = 0; i < res.size(); i++) {
		if (res[i]) {
			printf("%d ", i);
		}
	}
}