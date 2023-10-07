#define _CRT_SECURE_NO_DEPRECATE
#include<iostream>
#include<vector>
#include<map>
using namespace std;
typedef unsigned long long UI64;
map<int, UI64> num2phi;

bool witness(int a, int n) {
	UI64 d = 1ULL;
	int b = n - 1;
	for (int i = 31; i >= 0; i--) {
		UI64 x = d;
		d = (d * d) % n;
		if (d == 1ULL && x != 1ULL && x != (UI64)(n - 1)) return true;
		if (b & (1 << i)) d = (d * a) % n;
	}
	return d != 1ULL;
}

bool MillerRabin(int n, int tries = 2) {
	while (tries-- > 0) {
		if (witness(rand() % (n - 1) + 1, n)) return false;
	}
	return true;
}

bool prime(int n) {
	if ((n > 7) && !((n % 2) && (n % 3) && (n % 5) && (n % 7))) return false;
	if (n == 1 || !MillerRabin(n)) return false;
	return true;
}

vector<pair<UI64, UI64>> fac(int n) {
	vector<pair<UI64, UI64>> result;
	int d = 5, p = 0;
	bool p2 = true;
	while (n % 2 == 0) {
		n /= 2;
		p++;
	}
	if (p > 0) {
		result.push_back(make_pair(2ULL, (UI64)p));
	}
	p = 0;
	while (n % 3 == 0) {
		n /= 3;
		p++;
	}
	if (p > 0) {
		result.push_back(make_pair(3ULL, (UI64)p));
	}
	p = 0;
	while (!prime(n) && n != 1) {
		while (n % d != 0) {
			d += (p2 ? 2 : 4);
			p2 = !p2;
		}
		while (n % d == 0) {
			p++;
			n = n / d;
		}
		result.push_back(make_pair((UI64)d, (UI64)p));
		p = 0;
	}
	if (n > 1) {
		result.push_back(make_pair((UI64)n, 1ULL));
	}
	return result;
}

UI64 pow(UI64 base, UI64 exponent, UI64 modulus) {
	if (modulus == 1ULL) {
		return 0ULL;
	}
	UI64 result = 1ULL;
	while (exponent > 0ULL) {
		if (exponent % 2ULL == 1ULL) {
			result = (result * base) % modulus;
		}
		exponent = exponent >> 1ULL;
		base = (base * base) % modulus;
	}
	return result;
}

UI64 pow(UI64 base, UI64 exponent) {
	return pow(base, exponent, 1ULL << 60);
}

UI64 phi(int m) {
	if (num2phi.count(m) > 0) {
		return num2phi[m];
	}
	UI64 result = 1ULL;
	vector<pair<UI64, UI64>> f = fac(m);
	for (size_t i = 0; i < f.size(); i++) {
		result = result * (f[i].first - 1ULL);
		if (f[i].second > 1ULL) {
			result = result * pow(f[i].first, f[i].second - 1ULL);
		}
	}
	num2phi[m] = result;
	return result;
}

UI64 modpow(UI64 p, UI64 z, UI64 b, UI64 c, UI64 m) {
	if (m == 2ULL) {
		return p % m;
	}
	UI64 cp = 0ULL;
	while (m % p == 0ULL) {
		cp++;
		m /= p;
	}
	UI64 t = phi((int)m);
	UI64 exponent = ((pow(b, c, t) * z) % t + t - (cp % t)) % t;
	UI64 result = 1ULL;
	for (UI64 i = 1ULL; i <= cp; i++) {
		result *= p;
	}
	return result * pow(p, exponent, m);
}

UI64 solve(UI64 a, UI64 b, UI64 c, UI64 m) {
	if (m == 1ULL) {
		return 0ULL;
	}
	if (a == 1ULL) {
		return 1ULL;
	}
	if (b == 1ULL) {
		return a % m;
	}
	if (c == 1ULL) {
		return pow(a, b, m);
	}
	if (b + c < 20ULL) {
		return pow(a, pow(b, c), m);
	}
	UI64 result = 1ULL;
	vector<pair<UI64, UI64>> f = fac((int)a);
	for (size_t i = 0; i < f.size(); i++) {
		result *= modpow(f[i].first, f[i].second, b, c, m);
		result %= m;
	}
	return result;
}

int main() {
	srand(NULL);
	UI64 a, b, c, m;
	while (scanf("%I64d%I64d%I64d%I64d", &a, &b, &c, &m) == 4)
		printf("%I64d\n", solve(a, b, c, m));
}