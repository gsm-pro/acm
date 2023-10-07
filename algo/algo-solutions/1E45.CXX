#include<bits/stdc++.h>
#define forn(i, n) for (int i = 0; i < int(n); i++)
#define fore(i, l, r) for (int i = int(l); i < int(r); i++)
#define x first
#define y second
using namespace std;
typedef long long li;
typedef long double ld;
typedef complex<ld> base;
const ld PI = acosl(-1);
const int LOGN = 18, N = (1 << LOGN) + 3;
const int m = 1000000007;
int n, pw[N], z1[N], z2[N], a[N], b[N], ab[N], fact[N], ifact[N];

int reverse(int x, int logn) {
	int ans = 0;
	forn(i, logn) if (x & (1 << i)) ans |= 1 << (logn - 1 - i);
	return ans;
}

void fft(base a[N], int n, bool inv) {
	static base vv[LOGN][N];
	static bool prepared = false;
	if (!prepared) {
		prepared = true;
		forn(i, LOGN) {
			ld ang = 2 * PI / (1 << (i + 1));
			forn(j, 1 << i) vv[i][j] = base(cos(ang * j), sin(ang * j));
		}
	}
	int logn = 0;
	while ((1 << logn) < n) logn++;
	forn(i, n) {
		int ni = reverse(i, logn);
		if (i < ni) swap(a[i], a[ni]);
	}
	for (int i = 0; (1 << i) < n; i++)
		for (int j = 0; j < n; j += (1 << (i + 1)))
			for (int k = j; k < j + (1 << i); k++) {
				base cur = inv ? conj(vv[i][k - j]) : vv[i][k - j];
				base l = a[k], r = cur * a[k + (1 << i)];
				a[k] = l + r;
				a[k + (1 << i)] = l - r;
			}
	if (inv) forn(i, n) a[i] /= ld(n);
}

void mul(li a[N], int n, li b[N], int m, li ans[N]) {
	static base fp[N], p1[N], p2[N];
	int cnt = n + m;
	while (cnt & (cnt - 1)) cnt++;
	forn(i, cnt) fp[i] = base(i < n ? a[i] : 0, i < m ? b[i] : 0);
	fft(fp, cnt, false);
	forn(i, cnt) {
		p1[i] = (fp[i] + conj(fp[(cnt - i) % cnt])) / base(2, 0);
		p2[i] = (fp[i] - conj(fp[(cnt - i) % cnt])) / base(0, 2);
	}
	forn(i, cnt) fp[i] = p1[i] * p2[i];
	fft(fp, cnt, true);
	forn(i, cnt) ans[i] = li(fp[i].real() + 0.5);
}

void mul(int* a, int* b, int n, const int mod) {
	int smod = int(sqrt((ld)mod));
	static li a1[N], a2[N], b1[N], b2[N], za[N], zb[N];
	forn(i, n) {
		a1[i] = a[i] % smod, a2[i] = a[i] / smod;
		b1[i] = b[i] % smod, b2[i] = b[i] / smod;
		za[i] = a1[i] + a2[i];
		zb[i] = b1[i] + b2[i];
	}
	mul(a1, n, b1, n, a1);
	mul(a2, n, b2, n, a2);
	mul(za, n, zb, n, za);
	forn(i, 2 * n) {
		li cur = a1[i] % mod;
		cur += a2[i] % mod * smod * smod % mod;
		cur += (za[i] - a1[i] - a2[i]) % mod * smod % mod;
		cur %= mod;
		a[i] = int(cur < 0 ? (cur + mod) : cur);
	}
}

int gcd(int a, int b, int& x, int& y) {
	if (!a) {
		x = 0, y = 1;
		return b;
	}
	int xx, yy, g = gcd(b % a, a, xx, yy);
	x = yy - b / a * xx;
	y = xx;
	return g;
}

int inv(int a) {
	int x, y;
	gcd(a, m, x, y);
	x %= m;
	(x < 0) && (x += m);
	return x;
}

int add(int a, int b) {
	return a + b >= m ? a + b - m : a + b;
}

int sub(int a, int b) {
	return a - b < 0 ? a - b + m : a - b;
}

int mul(int a, int b) {
	return int(a * 1ll * b % m);
}

void inc(int& a, int b) {
	a = add(a, b);
}

void dec(int& a, int b) {
	a = sub(a, b);
}

int getC(int n, int k) {
	if (k < 0 || k >= n) return 0;
	return mul(fact[n], mul(ifact[k], ifact[n - k]));
}

int main() {
	cin >> n;
	pw[0] = 1;
	fore(i, 1, N) pw[i] = mul(pw[i - 1], 4);
	fact[0] = 1;
	fore(i, 1, N) fact[i] = mul(fact[i - 1], i);
	forn(i, N) ifact[i] = inv(fact[i]);
	forn(k, N) {
		int v = getC(k, k / 2);
		z1[k] = (k & 1) ? 0 : mul(v, v);
	}
	int ans = 0;
	forn(k, n + 1) {
		z2[k] = sub(pw[k], z2[k]);
		inc(z2[k + 1], mul(z2[k], z1[1]));
		int len = 1;
		while (k && k % len == 0) {
			forn(i, len) {
				a[i] = z2[k - len + i];
				b[i] = z1[len + 1 + i];
			}
			mul(a, b, len, m);
			forn(i, 2 * len - 1) {
				inc(z2[k + 1 + i], a[i]);
			}
			len *= 2;
		}
		inc(ans, mul(z2[k], pw[n - k]));
	}
	cout << ans;
}