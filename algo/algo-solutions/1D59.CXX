#include<iostream>
#include<complex>
#define forn(i, n) for (int i = 0; i < int(n); ++i)
#define N 262144
typedef std::complex<double> base;
double A[505][505];

void FFT(base*& a, int n, int sgn = 1) {
	int lg = 1;
	while ((1 << lg) < n) ++lg;
	int* rev = new int[n];
	rev[0] = 0;
	forn(i, n) {
		rev[i] = (rev[i >> 1] >> 1);
		if (i & 1) rev[i] |= (1 << (lg - 1));
	}
	base* r = new base[n];
	forn(i, n) r[i] = a[rev[i]];
	for (int len = 2; len <= n; len <<= 1) {
		int h = len >> 1;
		double alpha = 6.28318530717958647692 / len * sgn;
		base wlen = base(cos(alpha), sin(alpha));
		for (int i = 0; i < n; i += len) {
			base w = 1.;
			for (int j = i; j < h + i; ++j) {
				base t = w * r[j + h];
				r[j + h] = r[j] - t;
				r[j] += t;
				w *= wlen;
			}
		}
	}
	delete[] rev;
	delete[] a;
	a = r;
}

void RFFT(base*& a, int n) {
	FFT(a, n, -1);
	forn(i, n) a[i] /= n;
}

double AA(int x1, int y1, int x2, int y2) {
	return A[x2][y2] - (x1 ? A[x1 - 1][y2] : 0) - (y1 ? A[x2][y1 - 1] : 0) + (x1 && y1 ? A[x1 - 1][y1 - 1] : 0);
}

int main() {
	base* a = new base[N], * b = new base[N], * c = new base[N];
	int n, m, t, cc = 0, p, q, pqlen, bestx = 0, besty = 0;
	double minValue = 1e20, value;
	scanf("%d%d", &n, &m);
	forn(i, n) {
		forn(j, m) {
			scanf("%d", &t);
			A[i][j] = t * t + ((i ? A[i - 1][j] : 0) + (j ? A[i][j - 1] : 0) - (i && j ? A[i - 1][j - 1] : 0));
			a[cc++] = base(t, 0);
		}
	}
	scanf("%d%d", &p, &q);
	pqlen = p * q + (p - 1) * (m - q), cc = 0;
	forn(i, p) {
		forn(j, q) {
			scanf("%d", &t);
			b[pqlen - 1 - (cc++)] = base(t, 0);
		}
		cc += (m - q);
	}
	FFT(a, N);
	FFT(b, N);
	forn(i, N) c[i] = a[i] * b[i];
	RFFT(c, N);
	for (int i = pqlen - 1, x = 0, y = 0; i < n * m; i++) {
		if (x + p <= n && y + q <= m)
			if ((value = AA(x, y, x + p - 1, y + q - 1) - 2 * trunc(c[i].real() + .5)) < minValue)
				minValue = value, bestx = x, besty = y;
		y++;
		if (y == m) y = 0, x++;
	}
	printf("%d %d", bestx + 1, besty + 1);
}